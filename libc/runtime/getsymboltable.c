/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│ vi: set noet ft=c ts=2 sts=2 sw=2 fenc=utf-8                             :vi │
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
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
#include "libc/intrin/promises.internal.h"
#include "libc/intrin/strace.internal.h"
#include "libc/intrin/weaken.h"
#include "libc/macros.internal.h"
#include "libc/runtime/internal.h"
#include "libc/runtime/runtime.h"
#include "libc/runtime/symbols.internal.h"
#include "libc/runtime/zipos.internal.h"
#include "libc/str/str.h"
#include "libc/thread/thread.h"
#include "libc/x/x.h"
#include "libc/zip.internal.h"
#include "third_party/puff/puff.h"

__static_yoink("__get_symbol");

static pthread_spinlock_t g_lock;
struct SymbolTable *__symtab;  // for kprintf

static ssize_t GetZipFile(struct Zipos *zipos, const char *name) {
  size_t i, n, c, z;
  z = strlen(name);
  c = GetZipCdirOffset(zipos->cdir);
  n = GetZipCdirRecords(zipos->cdir);
  for (i = 0; i < n; ++i, c += ZIP_CFILE_HDRSIZE(zipos->map + c)) {
    if (ZIP_CFILE_NAMESIZE(zipos->map + c) == z &&
        !memcmp(ZIP_CFILE_NAME(zipos->map + c), name, z)) {
      return c;
    }
  }
  return -1;
}

/**
 * Reads symbol table from zip directory.
 * @note This code can't depend on dlmalloc()
 */
static struct SymbolTable *GetSymbolTableFromZip(struct Zipos *zipos) {
  ssize_t cf, lf;
  size_t size, size2;
  struct SymbolTable *res = 0;
  if ((cf = GetZipFile(zipos, ".symtab." _ARCH_NAME)) != -1 ||
      (cf = GetZipFile(zipos, ".symtab")) != -1) {
    lf = GetZipCfileOffset(zipos->map + cf);
    size = GetZipLfileUncompressedSize(zipos->map + lf);
    size2 = ROUNDUP(size, FRAMESIZE);
    if ((res = _mapanon(size2))) {
      switch (ZIP_LFILE_COMPRESSIONMETHOD(zipos->map + lf)) {
        case kZipCompressionNone:
          memcpy(res, (void *)ZIP_LFILE_CONTENT(zipos->map + lf), size);
          break;
        case kZipCompressionDeflate:
          if (__inflate((void *)res, size,
                        (void *)ZIP_LFILE_CONTENT(zipos->map + lf),
                        GetZipLfileCompressedSize(zipos->map + lf))) {
            munmap(res, size2);
            res = 0;
          }
          break;
        default:
          munmap(res, size2);
          res = 0;
          break;
      }
    }
  }
  STRACE("GetSymbolTableFromZip() → %p", res);
  return res;
}

/**
 * Reads symbol table from .com.dbg file.
 * @note This code can't depend on dlmalloc()
 */
static struct SymbolTable *GetSymbolTableFromElf(void) {
  const char *s;
  if (PLEDGED(RPATH) && (s = FindDebugBinary())) {
    return OpenSymbolTable(s);
  } else {
    return 0;
  }
}

/**
 * Returns symbol table singleton.
 *
 * This uses multiple strategies to find the symbol table. The first
 * strategy, depends on whether or not the following is linked:
 *
 *     __static_yoink("__zipos_get");
 *
 * In that case, the symbol table may be read from `/zip/.symtab` which
 * is generated by `o//tool/build/symtab.com`. The second strategy is to
 * look for the concomitant `.com.dbg` executable, which may very well
 * be the one currently executing, or it could be placed in the same
 * folder as your `.com` binary, or lastly, it could be explicitly
 * specified via the `COMDBG` environment variable.
 *
 * Function tracing is disabled throughout the duration of this call.
 * Backtraces and other core runtime functionality depend on this.
 *
 * @return symbol table, or NULL if not found
 */
struct SymbolTable *GetSymbolTable(void) {
  struct Zipos *z;
  if (pthread_spin_trylock(&g_lock)) return 0;
  if (!__symtab && !__isworker) {
    if (_weaken(__zipos_get) && (z = _weaken(__zipos_get)())) {
      if ((__symtab = GetSymbolTableFromZip(z))) {
        __symtab->names =
            (uint32_t *)((char *)__symtab + __symtab->names_offset);
        __symtab->name_base =
            (char *)((char *)__symtab + __symtab->name_base_offset);
      }
    }
    if (!__symtab) {
      __symtab = GetSymbolTableFromElf();
    }
  }
  pthread_spin_unlock(&g_lock);
  return __symtab;
}
