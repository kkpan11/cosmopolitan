/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2022 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/atomic.h"
#include "libc/calls/blocksigs.internal.h"
#include "libc/calls/calls.h"
#include "libc/dce.h"
#include "libc/errno.h"
#include "libc/runtime/runtime.h"
#include "libc/testlib/testlib.h"
#include "libc/thread/thread.h"
#include "libc/thread/thread2.h"

int pfds[2];
pthread_cond_t cv;
pthread_mutex_t mu;
atomic_bool gotcleanup;
char testlib_enable_tmp_setup_teardown;

void SetUp(void) {
  gotcleanup = false;
}

void OnCleanup(void *arg) {
  gotcleanup = true;
}

void *CancelSelfWorkerDeferred(void *arg) {
  char buf[8];
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, 0);
  pthread_cleanup_push(OnCleanup, 0);
  pthread_cancel(pthread_self());
  read(pfds[0], buf, sizeof(buf));
  pthread_cleanup_pop(0);
  return 0;
}

TEST(pthread_cancel, self_deferred_waitsForCancellationPoint) {
  void *rc;
  pthread_t th;
  ASSERT_SYS(0, 0, pipe(pfds));
  ASSERT_EQ(0, pthread_create(&th, 0, CancelSelfWorkerDeferred, 0));
  ASSERT_EQ(0, pthread_join(th, &rc));
  ASSERT_EQ(PTHREAD_CANCELED, rc);
  ASSERT_TRUE(gotcleanup);
  ASSERT_SYS(0, 0, close(pfds[1]));
  ASSERT_SYS(0, 0, close(pfds[0]));
}

void *CancelSelfWorkerAsync(void *arg) {
  char buf[8];
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, 0);
  pthread_cleanup_push(OnCleanup, 0);
  pthread_cancel(pthread_self());
  pthread_cleanup_pop(0);
  return 0;
}

TEST(pthread_cancel, self_asynchronous_takesImmediateEffect) {
  void *rc;
  pthread_t th;
  ASSERT_SYS(0, 0, pipe(pfds));
  ASSERT_EQ(0, pthread_create(&th, 0, CancelSelfWorkerAsync, 0));
  ASSERT_EQ(0, pthread_join(th, &rc));
  ASSERT_EQ(PTHREAD_CANCELED, rc);
  ASSERT_TRUE(gotcleanup);
  ASSERT_SYS(0, 0, close(pfds[1]));
  ASSERT_SYS(0, 0, close(pfds[0]));
}

void *Worker(void *arg) {
  int n;
  char buf[8];
  pthread_cleanup_push(OnCleanup, 0);
  read(pfds[0], buf, sizeof(buf));
  pthread_cleanup_pop(0);
  return 0;
}

TEST(pthread_cancel, synchronous) {
  void *rc;
  pthread_t th;
  ASSERT_SYS(0, 0, pipe(pfds));
  ASSERT_EQ(0, pthread_create(&th, 0, Worker, 0));
  ASSERT_EQ(0, pthread_cancel(th));
  ASSERT_EQ(0, pthread_join(th, &rc));
  ASSERT_EQ(PTHREAD_CANCELED, rc);
  ASSERT_TRUE(gotcleanup);
  ASSERT_SYS(0, 0, close(pfds[1]));
  ASSERT_SYS(0, 0, close(pfds[0]));
}

TEST(pthread_cancel, synchronous_delayed) {
  void *rc;
  pthread_t th;
  ASSERT_SYS(0, 0, pipe(pfds));
  ASSERT_EQ(0, pthread_create(&th, 0, Worker, 0));
  usleep(10);
  ASSERT_EQ(0, pthread_cancel(th));
  ASSERT_EQ(0, pthread_join(th, &rc));
  ASSERT_EQ(PTHREAD_CANCELED, rc);
  ASSERT_TRUE(gotcleanup);
  ASSERT_SYS(0, 0, close(pfds[1]));
  ASSERT_SYS(0, 0, close(pfds[0]));
}

void *DisabledWorker(void *arg) {
  char buf[8];
  pthread_setcancelstate(PTHREAD_CANCEL_MASKED, 0);
  pthread_cleanup_push(OnCleanup, 0);
  ASSERT_SYS(ECANCELED, -1, read(pfds[0], buf, sizeof(buf)));
  pthread_cleanup_pop(0);
  return 0;
}

TEST(pthread_cancel, masked) {
  void *rc;
  pthread_t th;
  ASSERT_SYS(0, 0, pipe(pfds));
  ASSERT_EQ(0, pthread_create(&th, 0, DisabledWorker, 0));
  ASSERT_EQ(0, pthread_cancel(th));
  ASSERT_EQ(0, pthread_join(th, &rc));
  ASSERT_EQ(0, rc);
  ASSERT_FALSE(gotcleanup);
  ASSERT_SYS(0, 0, close(pfds[1]));
  ASSERT_SYS(0, 0, close(pfds[0]));
}

TEST(pthread_cancel, masked_delayed) {
  void *rc;
  pthread_t th;
  ASSERT_SYS(0, 0, pipe(pfds));
  ASSERT_EQ(0, pthread_create(&th, 0, DisabledWorker, 0));
  usleep(10);
  ASSERT_EQ(0, pthread_cancel(th));
  ASSERT_EQ(0, pthread_join(th, &rc));
  ASSERT_EQ(0, rc);
  ASSERT_FALSE(gotcleanup);
  ASSERT_SYS(0, 0, close(pfds[1]));
  ASSERT_SYS(0, 0, close(pfds[0]));
}

void *CondWaitMaskedWorker(void *arg) {
  pthread_setcancelstate(PTHREAD_CANCEL_MASKED, 0);
  ASSERT_EQ(0, pthread_mutex_lock(&mu));
  ASSERT_EQ(ECANCELED, pthread_cond_timedwait(&cv, &mu, 0));
  ASSERT_EQ(0, pthread_mutex_unlock(&mu));
  return 0;
}

TEST(pthread_cancel, condMaskedWait) {
  void *rc;
  pthread_t th;
  ASSERT_EQ(0, pthread_create(&th, 0, CondWaitMaskedWorker, 0));
  ASSERT_EQ(0, pthread_cancel(th));
  ASSERT_EQ(0, pthread_join(th, &rc));
  ASSERT_EQ(0, rc);
}

TEST(pthread_cancel, condWaitMaskedDelayed) {
  void *rc;
  pthread_t th;
  ASSERT_EQ(0, pthread_create(&th, 0, CondWaitMaskedWorker, 0));
  usleep(10);
  ASSERT_EQ(0, pthread_cancel(th));
  ASSERT_EQ(0, pthread_join(th, &rc));
  ASSERT_EQ(0, rc);
}

void *CondWaitDeferredWorker(void *arg) {
  pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, 0);
  ASSERT_EQ(0, pthread_mutex_lock(&mu));
  ASSERT_EQ(ECANCELED, pthread_cond_timedwait(&cv, &mu, 0));
  ASSERT_EQ(0, pthread_mutex_unlock(&mu));
  return 0;
}

TEST(pthread_cancel, condDeferredWait) {
  void *rc;
  pthread_t th;
  ASSERT_EQ(0, pthread_create(&th, 0, CondWaitDeferredWorker, 0));
  ASSERT_EQ(0, pthread_cancel(th));
  ASSERT_EQ(0, pthread_join(th, &rc));
  ASSERT_EQ(PTHREAD_CANCELED, rc);
  ASSERT_EQ(0, pthread_mutex_trylock(&mu));
  ASSERT_EQ(0, pthread_mutex_unlock(&mu));
}

TEST(pthread_cancel, condDeferredWaitDelayed) {
  void *rc;
  pthread_t th;
  ASSERT_EQ(0, pthread_create(&th, 0, CondWaitDeferredWorker, 0));
  usleep(10);
  ASSERT_EQ(0, pthread_cancel(th));
  ASSERT_EQ(0, pthread_join(th, &rc));
  ASSERT_EQ(PTHREAD_CANCELED, rc);
  ASSERT_EQ(0, pthread_mutex_trylock(&mu));
  ASSERT_EQ(0, pthread_mutex_unlock(&mu));
}