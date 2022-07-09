/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2021 Justine Alexandra Roberts Tunney                              │
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
#include "libc/bits/popcnt.h"
#include "libc/dce.h"
#include "libc/intrin/asan.internal.h"
#include "libc/intrin/describeflags.internal.h"
#include "libc/intrin/kprintf.h"
#include "libc/str/str.h"

#define N 128

const char *(DescribeSigset)(char buf[N], int rc, const sigset_t *ss) {
  bool gotsome;
  int i, sig;
  sigset_t sigset;

  if (rc == -1) return "n/a";
  if (!ss) return "NULL";
  if ((!IsAsan() && kisdangerous(ss)) ||
      (IsAsan() && !__asan_is_valid(ss, sizeof(*ss)))) {
    ksnprintf(buf, N, "%p", ss);
    return buf;
  }

  i = 0;
  sigset = *ss;
  gotsome = false;
  if (popcnt(sigset.__bits[0] & 0xffffffff) > 16) {
    i += ksnprintf(buf + i, N - i, "~");
    sigset.__bits[0] = ~sigset.__bits[0];
    sigset.__bits[1] = ~sigset.__bits[1];
  }
  i += ksnprintf(buf + i, N - i, "{");
  for (sig = 1; sig < 32; ++sig) {
    if (sigismember(&sigset, sig)) {
      if (gotsome) {
        i += ksnprintf(buf + i, N - i, ",");
      } else {
        gotsome = true;
      }
      i += ksnprintf(buf + i, N - i, "%s", strsignal(sig) + 3);
    }
  }
  i += ksnprintf(buf + i, N - i, "}");

  return buf;
}
