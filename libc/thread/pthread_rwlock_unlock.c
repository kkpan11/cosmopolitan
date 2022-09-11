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
#include "libc/assert.h"
#include "libc/dce.h"
#include "libc/errno.h"
#include "libc/intrin/atomic.h"
#include "libc/intrin/futex.internal.h"
#include "libc/thread/thread.h"

/**
 * Unlocks read-write lock.
 *
 * @return 0 on success, or errno on error
 * @raise EINVAL if lock is in a bad state
 */
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock) {
  int old, waits;
  for (;;) {
    old = atomic_load_explicit(&rwlock->lock, memory_order_relaxed);
    if (!old || old < -1) {
      assert(!"badlock");
      return EINVAL;
    } else if (old == -1 || old == 1) {
      waits = atomic_load_explicit(&rwlock->waits, memory_order_relaxed);
      if (atomic_compare_exchange_weak_explicit(&rwlock->lock, &old, 0,
                                                memory_order_acquire,
                                                memory_order_relaxed)) {
        if (waits && (IsLinux() || IsOpenbsd())) {
          _futex_wake(&rwlock->lock, 1, rwlock->pshared);
        }
        return 0;
      }
    } else if (atomic_compare_exchange_weak_explicit(
                   &rwlock->lock, &old, old - 1, memory_order_acquire,
                   memory_order_relaxed)) {
      return 0;
    }
  }
}