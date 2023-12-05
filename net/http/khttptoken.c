/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│ vi: set noet ft=c ts=2 sts=2 sw=2 fenc=utf-8                             :vi │
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2023 Justine Alexandra Roberts Tunney                              │
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
#include "net/http/escape.h"

//	generated by:
//	o//tool/build/xlat.com -TiC ' ()<>@,;:\"/[]?={}' -iskHttpToken
//
//	    present            absent
//	    ────────────────   ────────────────
//	                       ∅☺☻♥♦♣♠•◘○◙♂♀♪♫☼   0x00
//	                       ►◄↕‼¶§▬↨↑↓→←∟↔▲▼   0x10
//	     ! #$%&‘  *+ -.    ␠ “     ()  ,  /   0x20
//	    0123456789                   :;<=>⁇   0x30
//	     ABCDEFGHIJKLMNO   @                  0x40
//	    PQRSTUVWXYZ   ^_              [⭝]     0x50
//	    `abcdefghijklmno                      0x60
//	    pqrstuvwxyz | ~               { } ⌂   0x70
//	                       ÇüéâäàåçêëèïîìÄÅ   0x80
//	                       ÉæÆôöòûùÿÖÜ¢£¥€ƒ   0x90
//	                       áíóúñÑªº¿⌐¬½¼¡«»   0xa0
//	                       ░▒▓│┤╡╢╖╕╣║╗╝╜╛┐   0xb0
//	                       └┴┬├─┼╞╟╚╔╩╦╠═╬╧   0xc0
//	                       ╨╤╥╙╘╒╓╫╪┘┌█▄▌▐▀   0xd0
//	                       αßΓπΣσμτΦΘΩδ∞φε∩   0xe0
//	                       ≡±≥≤⌠⌡÷≈°∙×√ⁿ²■λ   0xf0

const char kHttpToken[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0x00
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0x10
    0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0,  // 0x20
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,  // 0x30
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  // 0x40
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1,  // 0x50
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  // 0x60
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0,  // 0x70
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0x80
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0x90
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0xa0
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0xb0
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0xc0
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0xd0
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0xe0
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0xf0
};

//	@see RFC2616
//	CHAR           = <any US-ASCII character (octets 0 - 127)>
//	SP             = <US-ASCII SP, space (32)>
//	HT             = <US-ASCII HT, horizontal-tab (9)>
//	CTL            = <any US-ASCII control character
//	                 (octets 0 - 31) and DEL (127)>
//	token          = 1*<any CHAR except CTLs or separators>
//	separators     = "(" | ")" | "<" | ">" | "@"
//	               | "," | ";" | ":" | "\" | <">
//	               | "/" | "[" | "]" | "?" | "="
//	               | "{" | "}" | SP | HT
