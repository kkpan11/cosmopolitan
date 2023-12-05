/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:4;tab-width:4;coding:utf-8 -*-│
│ vi: set noet ft=c ts=2 sts=2 sw=2 fenc=utf-8                             :vi │
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright The Mbed TLS Contributors                                          │
│                                                                              │
│ Licensed under the Apache License, Version 2.0 (the "License");              │
│ you may not use this file except in compliance with the License.             │
│ You may obtain a copy of the License at                                      │
│                                                                              │
│     http://www.apache.org/licenses/LICENSE-2.0                               │
│                                                                              │
│ Unless required by applicable law or agreed to in writing, software          │
│ distributed under the License is distributed on an "AS IS" BASIS,            │
│ WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.     │
│ See the License for the specific language governing permissions and          │
│ limitations under the License.                                               │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "third_party/mbedtls/iana.h"

/**
 * Returns ciphersuite name.
 *
 * This contains a superset of what's actually supported. It should
 * include all IANA assignments.
 */
const char *GetCipherSuiteName(uint16_t x) {
  switch (x) {
    case 0x0000:
      return "NULL-NULL-NULL";
    case 0x0001:
      return "RSA-NULL-MD5";
    case 0x0002:
      return "RSA-NULL-SHA";
    case 0x0003:
      return "RSA-EXPORT-RC4-40-MD5";
    case 0x0004:
      return "RSA-RC4-128-MD5";
    case 0x0005:
      return "RSA-RC4-128-SHA";
    case 0x0006:
      return "RSA-EXPORT-RC2-CBC-40-MD5";
    case 0x0007:
      return "RSA-IDEA-CBC-SHA";
    case 0x0008:
      return "RSA-EXPORT-DES40-CBC-SHA";
    case 0x0009:
      return "RSA-DES-CBC-SHA";
    case 0x000A:
      return "RSA-3DES-EDE-CBC-SHA";
    case 0x000B:
      return "DH-DSS-EXPORT-DES40-CBC-SHA";
    case 0x000C:
      return "DH-DSS-DES-CBC-SHA";
    case 0x000D:
      return "DH-DSS-3DES-EDE-CBC-SHA";
    case 0x000E:
      return "DH-RSA-EXPORT-DES40-CBC-SHA";
    case 0x000F:
      return "DH-RSA-DES-CBC-SHA";
    case 0x0010:
      return "DH-RSA-3DES-EDE-CBC-SHA";
    case 0x0011:
      return "DHE-DSS-EXPORT-DES40-CBC-SHA";
    case 0x0012:
      return "DHE-DSS-DES-CBC-SHA";
    case 0x0013:
      return "DHE-DSS-3DES-EDE-CBC-SHA";
    case 0x0014:
      return "DHE-RSA-EXPORT-DES40-CBC-SHA";
    case 0x0015:
      return "DHE-RSA-DES-CBC-SHA";
    case 0x0016:
      return "DHE-RSA-3DES-EDE-CBC-SHA";
    case 0x0017:
      return "DH-anon-EXPORT-RC4-40-MD5";
    case 0x0018:
      return "DH-anon-RC4-128-MD5";
    case 0x0019:
      return "DH-anon-EXPORT-DES40-CBC-SHA";
    case 0x001A:
      return "DH-anon-DES-CBC-SHA";
    case 0x001B:
      return "DH-anon-3DES-EDE-CBC-SHA";
    case 0x001E:
      return "KRB5-DES-CBC-SHA";
    case 0x001F:
      return "KRB5-3DES-EDE-CBC-SHA";
    case 0x0020:
      return "KRB5-RC4-128-SHA";
    case 0x0021:
      return "KRB5-IDEA-CBC-SHA";
    case 0x0022:
      return "KRB5-DES-CBC-MD5";
    case 0x0023:
      return "KRB5-3DES-EDE-CBC-MD5";
    case 0x0024:
      return "KRB5-RC4-128-MD5";
    case 0x0025:
      return "KRB5-IDEA-CBC-MD5";
    case 0x0026:
      return "KRB5-EXPORT-DES-CBC-40-SHA";
    case 0x0027:
      return "KRB5-EXPORT-RC2-CBC-40-SHA";
    case 0x0028:
      return "KRB5-EXPORT-RC4-40-SHA";
    case 0x0029:
      return "KRB5-EXPORT-DES-CBC-40-MD5";
    case 0x002A:
      return "KRB5-EXPORT-RC2-CBC-40-MD5";
    case 0x002B:
      return "KRB5-EXPORT-RC4-40-MD5";
    case 0x002C:
      return "PSK-NULL-SHA";
    case 0x002D:
      return "DHE-PSK-NULL-SHA";
    case 0x002E:
      return "RSA-PSK-NULL-SHA";
    case 0x002F:
      return "RSA-AES128-CBC-SHA";
    case 0x0030:
      return "DH-DSS-AES128-CBC-SHA";
    case 0x0031:
      return "DH-RSA-AES128-CBC-SHA";
    case 0x0032:
      return "DHE-DSS-AES128-CBC-SHA";
    case 0x0033:
      return "DHE-RSA-AES128-CBC-SHA";
    case 0x0034:
      return "DH-anon-AES128-CBC-SHA";
    case 0x0035:
      return "RSA-AES256-CBC-SHA";
    case 0x0036:
      return "DH-DSS-AES256-CBC-SHA";
    case 0x0037:
      return "DH-RSA-AES256-CBC-SHA";
    case 0x0038:
      return "DHE-DSS-AES256-CBC-SHA";
    case 0x0039:
      return "DHE-RSA-AES256-CBC-SHA";
    case 0x003A:
      return "DH-anon-AES256-CBC-SHA";
    case 0x003B:
      return "RSA-NULL-SHA256";
    case 0x003C:
      return "RSA-AES128-CBC-SHA256";
    case 0x003D:
      return "RSA-AES256-CBC-SHA256";
    case 0x003E:
      return "DH-DSS-AES128-CBC-SHA256";
    case 0x003F:
      return "DH-RSA-AES128-CBC-SHA256";
    case 0x0040:
      return "DHE-DSS-AES128-CBC-SHA256";
    case 0x0041:
      return "RSA-CAMELLIA128-CBC-SHA";
    case 0x0042:
      return "DH-DSS-CAMELLIA128-CBC-SHA";
    case 0x0043:
      return "DH-RSA-CAMELLIA128-CBC-SHA";
    case 0x0044:
      return "DHE-DSS-CAMELLIA128-CBC-SHA";
    case 0x0045:
      return "DHE-RSA-CAMELLIA128-CBC-SHA";
    case 0x0046:
      return "DH-anon-CAMELLIA128-CBC-SHA";
    case 0x0067:
      return "DHE-RSA-AES128-CBC-SHA256";
    case 0x0068:
      return "DH-DSS-AES256-CBC-SHA256";
    case 0x0069:
      return "DH-RSA-AES256-CBC-SHA256";
    case 0x006A:
      return "DHE-DSS-AES256-CBC-SHA256";
    case 0x006B:
      return "DHE-RSA-AES256-CBC-SHA256";
    case 0x006C:
      return "DH-anon-AES128-CBC-SHA256";
    case 0x006D:
      return "DH-anon-AES256-CBC-SHA256";
    case 0x0084:
      return "RSA-CAMELLIA256-CBC-SHA";
    case 0x0085:
      return "DH-DSS-CAMELLIA256-CBC-SHA";
    case 0x0086:
      return "DH-RSA-CAMELLIA256-CBC-SHA";
    case 0x0087:
      return "DHE-DSS-CAMELLIA256-CBC-SHA";
    case 0x0088:
      return "DHE-RSA-CAMELLIA256-CBC-SHA";
    case 0x0089:
      return "DH-anon-CAMELLIA256-CBC-SHA";
    case 0x008A:
      return "PSK-RC4-128-SHA";
    case 0x008B:
      return "PSK-3DES-EDE-CBC-SHA";
    case 0x008C:
      return "PSK-AES128-CBC-SHA";
    case 0x008D:
      return "PSK-AES256-CBC-SHA";
    case 0x008E:
      return "DHE-PSK-RC4-128-SHA";
    case 0x008F:
      return "DHE-PSK-3DES-EDE-CBC-SHA";
    case 0x0090:
      return "DHE-PSK-AES128-CBC-SHA";
    case 0x0091:
      return "DHE-PSK-AES256-CBC-SHA";
    case 0x0092:
      return "RSA-PSK-RC4-128-SHA";
    case 0x0093:
      return "RSA-PSK-3DES-EDE-CBC-SHA";
    case 0x0094:
      return "RSA-PSK-AES128-CBC-SHA";
    case 0x0095:
      return "RSA-PSK-AES256-CBC-SHA";
    case 0x0096:
      return "RSA-SEED-CBC-SHA";
    case 0x0097:
      return "DH-DSS-SEED-CBC-SHA";
    case 0x0098:
      return "DH-RSA-SEED-CBC-SHA";
    case 0x0099:
      return "DHE-DSS-SEED-CBC-SHA";
    case 0x009A:
      return "DHE-RSA-SEED-CBC-SHA";
    case 0x009B:
      return "DH-anon-SEED-CBC-SHA";
    case 0x009C:
      return "RSA-AES128-GCM-SHA256";
    case 0x009D:
      return "RSA-AES256-GCM-SHA384";
    case 0x009E:
      return "DHE-RSA-AES128-GCM-SHA256";
    case 0x009F:
      return "DHE-RSA-AES256-GCM-SHA384";
    case 0x00A0:
      return "DH-RSA-AES128-GCM-SHA256";
    case 0x00A1:
      return "DH-RSA-AES256-GCM-SHA384";
    case 0x00A2:
      return "DHE-DSS-AES128-GCM-SHA256";
    case 0x00A3:
      return "DHE-DSS-AES256-GCM-SHA384";
    case 0x00A4:
      return "DH-DSS-AES128-GCM-SHA256";
    case 0x00A5:
      return "DH-DSS-AES256-GCM-SHA384";
    case 0x00A6:
      return "DH-anon-AES128-GCM-SHA256";
    case 0x00A7:
      return "DH-anon-AES256-GCM-SHA384";
    case 0x00A8:
      return "PSK-AES128-GCM-SHA256";
    case 0x00A9:
      return "PSK-AES256-GCM-SHA384";
    case 0x00AA:
      return "DHE-PSK-AES128-GCM-SHA256";
    case 0x00AB:
      return "DHE-PSK-AES256-GCM-SHA384";
    case 0x00AC:
      return "RSA-PSK-AES128-GCM-SHA256";
    case 0x00AD:
      return "RSA-PSK-AES256-GCM-SHA384";
    case 0x00AE:
      return "PSK-AES128-CBC-SHA256";
    case 0x00AF:
      return "PSK-AES256-CBC-SHA384";
    case 0x00B0:
      return "PSK-NULL-SHA256";
    case 0x00B1:
      return "PSK-NULL-SHA384";
    case 0x00B2:
      return "DHE-PSK-AES128-CBC-SHA256";
    case 0x00B3:
      return "DHE-PSK-AES256-CBC-SHA384";
    case 0x00B4:
      return "DHE-PSK-NULL-SHA256";
    case 0x00B5:
      return "DHE-PSK-NULL-SHA384";
    case 0x00B6:
      return "RSA-PSK-AES128-CBC-SHA256";
    case 0x00B7:
      return "RSA-PSK-AES256-CBC-SHA384";
    case 0x00B8:
      return "RSA-PSK-NULL-SHA256";
    case 0x00B9:
      return "RSA-PSK-NULL-SHA384";
    case 0x00BA:
      return "RSA-CAMELLIA128-CBC-SHA256";
    case 0x00BB:
      return "DH-DSS-CAMELLIA128-CBC-SHA256";
    case 0x00BC:
      return "DH-RSA-CAMELLIA128-CBC-SHA256";
    case 0x00BD:
      return "DHE-DSS-CAMELLIA128-CBC-SHA256";
    case 0x00BE:
      return "DHE-RSA-CAMELLIA128-CBC-SHA256";
    case 0x00BF:
      return "DH-anon-CAMELLIA128-CBC-SHA256";
    case 0x00C0:
      return "RSA-CAMELLIA256-CBC-SHA256";
    case 0x00C1:
      return "DH-DSS-CAMELLIA256-CBC-SHA256";
    case 0x00C2:
      return "DH-RSA-CAMELLIA256-CBC-SHA256";
    case 0x00C3:
      return "DHE-DSS-CAMELLIA256-CBC-SHA256";
    case 0x00C4:
      return "DHE-RSA-CAMELLIA256-CBC-SHA256";
    case 0x00C5:
      return "DH-anon-CAMELLIA256-CBC-SHA256";
    case 0x00C6:
      return "SM4-GCM-SM3";
    case 0x00C7:
      return "SM4-CCM-SM3";
    case 0x00FF:
      return "EMPTY-RENEGOTIATION-INFO-SCSV";
    case 0x1301:
      return "AES128-GCM-SHA256";
    case 0x1302:
      return "AES256-GCM-SHA384";
    case 0x1303:
      return "CHACHA20-POLY1305-SHA256";
    case 0x1304:
      return "AES128-CCM-SHA256";
    case 0x1305:
      return "AES128-CCM8-SHA256";
    case 0x5600:
      return "FALLBACK-SCSV";
    case 0xC001:
      return "ECDH-ECDSA-NULL-SHA";
    case 0xC002:
      return "ECDH-ECDSA-RC4-128-SHA";
    case 0xC003:
      return "ECDH-ECDSA-3DES-EDE-CBC-SHA";
    case 0xC004:
      return "ECDH-ECDSA-AES128-CBC-SHA";
    case 0xC005:
      return "ECDH-ECDSA-AES256-CBC-SHA";
    case 0xC006:
      return "ECDHE-ECDSA-NULL-SHA";
    case 0xC007:
      return "ECDHE-ECDSA-RC4-128-SHA";
    case 0xC008:
      return "ECDHE-ECDSA-3DES-EDE-CBC-SHA";
    case 0xC009:
      return "ECDHE-ECDSA-AES128-CBC-SHA";
    case 0xC00A:
      return "ECDHE-ECDSA-AES256-CBC-SHA";
    case 0xC00B:
      return "ECDH-RSA-NULL-SHA";
    case 0xC00C:
      return "ECDH-RSA-RC4-128-SHA";
    case 0xC00D:
      return "ECDH-RSA-3DES-EDE-CBC-SHA";
    case 0xC00E:
      return "ECDH-RSA-AES128-CBC-SHA";
    case 0xC00F:
      return "ECDH-RSA-AES256-CBC-SHA";
    case 0xC010:
      return "ECDHE-RSA-NULL-SHA";
    case 0xC011:
      return "ECDHE-RSA-RC4-128-SHA";
    case 0xC012:
      return "ECDHE-RSA-3DES-EDE-CBC-SHA";
    case 0xC013:
      return "ECDHE-RSA-AES128-CBC-SHA";
    case 0xC014:
      return "ECDHE-RSA-AES256-CBC-SHA";
    case 0xC015:
      return "ECDH-anon-NULL-SHA";
    case 0xC016:
      return "ECDH-anon-RC4-128-SHA";
    case 0xC017:
      return "ECDH-anon-3DES-EDE-CBC-SHA";
    case 0xC018:
      return "ECDH-anon-AES128-CBC-SHA";
    case 0xC019:
      return "ECDH-anon-AES256-CBC-SHA";
    case 0xC01A:
      return "SRP-SHA-3DES-EDE-CBC-SHA";
    case 0xC01B:
      return "SRP-SHA-RSA-3DES-EDE-CBC-SHA";
    case 0xC01C:
      return "SRP-SHA-DSS-3DES-EDE-CBC-SHA";
    case 0xC01D:
      return "SRP-SHA-AES128-CBC-SHA";
    case 0xC01E:
      return "SRP-SHA-RSA-AES128-CBC-SHA";
    case 0xC01F:
      return "SRP-SHA-DSS-AES128-CBC-SHA";
    case 0xC020:
      return "SRP-SHA-AES256-CBC-SHA";
    case 0xC021:
      return "SRP-SHA-RSA-AES256-CBC-SHA";
    case 0xC022:
      return "SRP-SHA-DSS-AES256-CBC-SHA";
    case 0xC023:
      return "ECDHE-ECDSA-AES128-CBC-SHA256";
    case 0xC024:
      return "ECDHE-ECDSA-AES256-CBC-SHA384";
    case 0xC025:
      return "ECDH-ECDSA-AES128-CBC-SHA256";
    case 0xC026:
      return "ECDH-ECDSA-AES256-CBC-SHA384";
    case 0xC027:
      return "ECDHE-RSA-AES128-CBC-SHA256";
    case 0xC028:
      return "ECDHE-RSA-AES256-CBC-SHA384";
    case 0xC029:
      return "ECDH-RSA-AES128-CBC-SHA256";
    case 0xC02A:
      return "ECDH-RSA-AES256-CBC-SHA384";
    case 0xC02B:
      return "ECDHE-ECDSA-AES128-GCM-SHA256";
    case 0xC02C:
      return "ECDHE-ECDSA-AES256-GCM-SHA384";
    case 0xC02D:
      return "ECDH-ECDSA-AES128-GCM-SHA256";
    case 0xC02E:
      return "ECDH-ECDSA-AES256-GCM-SHA384";
    case 0xC02F:
      return "ECDHE-RSA-AES128-GCM-SHA256";
    case 0xC030:
      return "ECDHE-RSA-AES256-GCM-SHA384";
    case 0xC031:
      return "ECDH-RSA-AES128-GCM-SHA256";
    case 0xC032:
      return "ECDH-RSA-AES256-GCM-SHA384";
    case 0xC033:
      return "ECDHE-PSK-RC4-128-SHA";
    case 0xC034:
      return "ECDHE-PSK-3DES-EDE-CBC-SHA";
    case 0xC035:
      return "ECDHE-PSK-AES128-CBC-SHA";
    case 0xC036:
      return "ECDHE-PSK-AES256-CBC-SHA";
    case 0xC037:
      return "ECDHE-PSK-AES128-CBC-SHA256";
    case 0xC038:
      return "ECDHE-PSK-AES256-CBC-SHA384";
    case 0xC039:
      return "ECDHE-PSK-NULL-SHA";
    case 0xC03A:
      return "ECDHE-PSK-NULL-SHA256";
    case 0xC03B:
      return "ECDHE-PSK-NULL-SHA384";
    case 0xC03C:
      return "RSA-ARIA128-CBC-SHA256";
    case 0xC03D:
      return "RSA-ARIA256-CBC-SHA384";
    case 0xC03E:
      return "DH-DSS-ARIA128-CBC-SHA256";
    case 0xC03F:
      return "DH-DSS-ARIA256-CBC-SHA384";
    case 0xC040:
      return "DH-RSA-ARIA128-CBC-SHA256";
    case 0xC041:
      return "DH-RSA-ARIA256-CBC-SHA384";
    case 0xC042:
      return "DHE-DSS-ARIA128-CBC-SHA256";
    case 0xC043:
      return "DHE-DSS-ARIA256-CBC-SHA384";
    case 0xC044:
      return "DHE-RSA-ARIA128-CBC-SHA256";
    case 0xC045:
      return "DHE-RSA-ARIA256-CBC-SHA384";
    case 0xC046:
      return "DH-anon-ARIA128-CBC-SHA256";
    case 0xC047:
      return "DH-anon-ARIA256-CBC-SHA384";
    case 0xC048:
      return "ECDHE-ECDSA-ARIA128-CBC-SHA256";
    case 0xC049:
      return "ECDHE-ECDSA-ARIA256-CBC-SHA384";
    case 0xC04A:
      return "ECDH-ECDSA-ARIA128-CBC-SHA256";
    case 0xC04B:
      return "ECDH-ECDSA-ARIA256-CBC-SHA384";
    case 0xC04C:
      return "ECDHE-RSA-ARIA128-CBC-SHA256";
    case 0xC04D:
      return "ECDHE-RSA-ARIA256-CBC-SHA384";
    case 0xC04E:
      return "ECDH-RSA-ARIA128-CBC-SHA256";
    case 0xC04F:
      return "ECDH-RSA-ARIA256-CBC-SHA384";
    case 0xC050:
      return "RSA-ARIA128-GCM-SHA256";
    case 0xC051:
      return "RSA-ARIA256-GCM-SHA384";
    case 0xC052:
      return "DHE-RSA-ARIA128-GCM-SHA256";
    case 0xC053:
      return "DHE-RSA-ARIA256-GCM-SHA384";
    case 0xC054:
      return "DH-RSA-ARIA128-GCM-SHA256";
    case 0xC055:
      return "DH-RSA-ARIA256-GCM-SHA384";
    case 0xC056:
      return "DHE-DSS-ARIA128-GCM-SHA256";
    case 0xC057:
      return "DHE-DSS-ARIA256-GCM-SHA384";
    case 0xC058:
      return "DH-DSS-ARIA128-GCM-SHA256";
    case 0xC059:
      return "DH-DSS-ARIA256-GCM-SHA384";
    case 0xC05A:
      return "DH-anon-ARIA128-GCM-SHA256";
    case 0xC05B:
      return "DH-anon-ARIA256-GCM-SHA384";
    case 0xC05C:
      return "ECDHE-ECDSA-ARIA128-GCM-SHA256";
    case 0xC05D:
      return "ECDHE-ECDSA-ARIA256-GCM-SHA384";
    case 0xC05E:
      return "ECDH-ECDSA-ARIA128-GCM-SHA256";
    case 0xC05F:
      return "ECDH-ECDSA-ARIA256-GCM-SHA384";
    case 0xC060:
      return "ECDHE-RSA-ARIA128-GCM-SHA256";
    case 0xC061:
      return "ECDHE-RSA-ARIA256-GCM-SHA384";
    case 0xC062:
      return "ECDH-RSA-ARIA128-GCM-SHA256";
    case 0xC063:
      return "ECDH-RSA-ARIA256-GCM-SHA384";
    case 0xC064:
      return "PSK-ARIA128-CBC-SHA256";
    case 0xC065:
      return "PSK-ARIA256-CBC-SHA384";
    case 0xC066:
      return "DHE-PSK-ARIA128-CBC-SHA256";
    case 0xC067:
      return "DHE-PSK-ARIA256-CBC-SHA384";
    case 0xC068:
      return "RSA-PSK-ARIA128-CBC-SHA256";
    case 0xC069:
      return "RSA-PSK-ARIA256-CBC-SHA384";
    case 0xC06A:
      return "PSK-ARIA128-GCM-SHA256";
    case 0xC06B:
      return "PSK-ARIA256-GCM-SHA384";
    case 0xC06C:
      return "DHE-PSK-ARIA128-GCM-SHA256";
    case 0xC06D:
      return "DHE-PSK-ARIA256-GCM-SHA384";
    case 0xC06E:
      return "RSA-PSK-ARIA128-GCM-SHA256";
    case 0xC06F:
      return "RSA-PSK-ARIA256-GCM-SHA384";
    case 0xC070:
      return "ECDHE-PSK-ARIA128-CBC-SHA256";
    case 0xC071:
      return "ECDHE-PSK-ARIA256-CBC-SHA384";
    case 0xC072:
      return "ECDHE-ECDSA-CAMELLIA128-CBC-SHA256";
    case 0xC073:
      return "ECDHE-ECDSA-CAMELLIA256-CBC-SHA384";
    case 0xC074:
      return "ECDH-ECDSA-CAMELLIA128-CBC-SHA256";
    case 0xC075:
      return "ECDH-ECDSA-CAMELLIA256-CBC-SHA384";
    case 0xC076:
      return "ECDHE-RSA-CAMELLIA128-CBC-SHA256";
    case 0xC077:
      return "ECDHE-RSA-CAMELLIA256-CBC-SHA384";
    case 0xC078:
      return "ECDH-RSA-CAMELLIA128-CBC-SHA256";
    case 0xC079:
      return "ECDH-RSA-CAMELLIA256-CBC-SHA384";
    case 0xC07A:
      return "RSA-CAMELLIA128-GCM-SHA256";
    case 0xC07B:
      return "RSA-CAMELLIA256-GCM-SHA384";
    case 0xC07C:
      return "DHE-RSA-CAMELLIA128-GCM-SHA256";
    case 0xC07D:
      return "DHE-RSA-CAMELLIA256-GCM-SHA384";
    case 0xC07E:
      return "DH-RSA-CAMELLIA128-GCM-SHA256";
    case 0xC07F:
      return "DH-RSA-CAMELLIA256-GCM-SHA384";
    case 0xC080:
      return "DHE-DSS-CAMELLIA128-GCM-SHA256";
    case 0xC081:
      return "DHE-DSS-CAMELLIA256-GCM-SHA384";
    case 0xC082:
      return "DH-DSS-CAMELLIA128-GCM-SHA256";
    case 0xC083:
      return "DH-DSS-CAMELLIA256-GCM-SHA384";
    case 0xC084:
      return "DH-anon-CAMELLIA128-GCM-SHA256";
    case 0xC085:
      return "DH-anon-CAMELLIA256-GCM-SHA384";
    case 0xC086:
      return "ECDHE-ECDSA-CAMELLIA128-GCM-SHA256";
    case 0xC087:
      return "ECDHE-ECDSA-CAMELLIA256-GCM-SHA384";
    case 0xC088:
      return "ECDH-ECDSA-CAMELLIA128-GCM-SHA256";
    case 0xC089:
      return "ECDH-ECDSA-CAMELLIA256-GCM-SHA384";
    case 0xC08A:
      return "ECDHE-RSA-CAMELLIA128-GCM-SHA256";
    case 0xC08B:
      return "ECDHE-RSA-CAMELLIA256-GCM-SHA384";
    case 0xC08C:
      return "ECDH-RSA-CAMELLIA128-GCM-SHA256";
    case 0xC08D:
      return "ECDH-RSA-CAMELLIA256-GCM-SHA384";
    case 0xC08E:
      return "PSK-CAMELLIA128-GCM-SHA256";
    case 0xC08F:
      return "PSK-CAMELLIA256-GCM-SHA384";
    case 0xC090:
      return "DHE-PSK-CAMELLIA128-GCM-SHA256";
    case 0xC091:
      return "DHE-PSK-CAMELLIA256-GCM-SHA384";
    case 0xC092:
      return "RSA-PSK-CAMELLIA128-GCM-SHA256";
    case 0xC093:
      return "RSA-PSK-CAMELLIA256-GCM-SHA384";
    case 0xC094:
      return "PSK-CAMELLIA128-CBC-SHA256";
    case 0xC095:
      return "PSK-CAMELLIA256-CBC-SHA384";
    case 0xC096:
      return "DHE-PSK-CAMELLIA128-CBC-SHA256";
    case 0xC097:
      return "DHE-PSK-CAMELLIA256-CBC-SHA384";
    case 0xC098:
      return "RSA-PSK-CAMELLIA128-CBC-SHA256";
    case 0xC099:
      return "RSA-PSK-CAMELLIA256-CBC-SHA384";
    case 0xC09A:
      return "ECDHE-PSK-CAMELLIA128-CBC-SHA256";
    case 0xC09B:
      return "ECDHE-PSK-CAMELLIA256-CBC-SHA384";
    case 0xC09C:
      return "RSA-AES128-CCM";
    case 0xC09D:
      return "RSA-AES256-CCM";
    case 0xC09E:
      return "DHE-RSA-AES128-CCM";
    case 0xC09F:
      return "DHE-RSA-AES256-CCM";
    case 0xC0A0:
      return "RSA-AES128-CCM8";
    case 0xC0A1:
      return "RSA-AES256-CCM8";
    case 0xC0A2:
      return "DHE-RSA-AES128-CCM8";
    case 0xC0A3:
      return "DHE-RSA-AES256-CCM8";
    case 0xC0A4:
      return "PSK-AES128-CCM";
    case 0xC0A5:
      return "PSK-AES256-CCM";
    case 0xC0A6:
      return "DHE-PSK-AES128-CCM";
    case 0xC0A7:
      return "DHE-PSK-AES256-CCM";
    case 0xC0A8:
      return "PSK-AES128-CCM8";
    case 0xC0A9:
      return "PSK-AES256-CCM8";
    case 0xC0AA:
      return "PSK-DHE-AES128-CCM8";
    case 0xC0AB:
      return "PSK-DHE-AES256-CCM8";
    case 0xC0AC:
      return "ECDHE-ECDSA-AES128-CCM";
    case 0xC0AD:
      return "ECDHE-ECDSA-AES256-CCM";
    case 0xC0AE:
      return "ECDHE-ECDSA-AES128-CCM8";
    case 0xC0AF:
      return "ECDHE-ECDSA-AES256-CCM8";
    case 0xC0B0:
      return "ECCPWD-AES128-GCM-SHA256";
    case 0xC0B1:
      return "ECCPWD-AES256-GCM-SHA384";
    case 0xC0B2:
      return "ECCPWD-AES128-CCM-SHA256";
    case 0xC0B3:
      return "ECCPWD-AES256-CCM-SHA384";
    case 0xC0B4:
      return "SHA256-SHA256";
    case 0xC0B5:
      return "SHA384-SHA384";
    case 0xC100:
      return "GOSTR341112-256-KUZNYECHIK-CTR-OMAC";
    case 0xC101:
      return "GOSTR341112-256-MAGMA-CTR-OMAC";
    case 0xC102:
      return "GOSTR341112-256-28147-CNT-IMIT";
    case 0xC103:
      return "GOSTR341112-256-KUZNYECHIK-MGM-L";
    case 0xC104:
      return "GOSTR341112-256-MAGMA-MGM-L";
    case 0xC105:
      return "GOSTR341112-256-KUZNYECHIK-MGM-S";
    case 0xC106:
      return "GOSTR341112-256-MAGMA-MGM-S";
    case 0xCCA8:
      return "ECDHE-RSA-CHACHA20-POLY1305-SHA256";
    case 0xCCA9:
      return "ECDHE-ECDSA-CHACHA20-POLY1305-SHA256";
    case 0xCCAA:
      return "DHE-RSA-CHACHA20-POLY1305-SHA256";
    case 0xCCAB:
      return "PSK-CHACHA20-POLY1305-SHA256";
    case 0xCCAC:
      return "ECDHE-PSK-CHACHA20-POLY1305-SHA256";
    case 0xCCAD:
      return "DHE-PSK-CHACHA20-POLY1305-SHA256";
    case 0xCCAE:
      return "RSA-PSK-CHACHA20-POLY1305-SHA256";
    case 0xD001:
      return "ECDHE-PSK-AES128-GCM-SHA256";
    case 0xD002:
      return "ECDHE-PSK-AES256-GCM-SHA384";
    case 0xD003:
      return "ECDHE-PSK-AES128-CCM8-SHA256";
    case 0xD005:
      return "ECDHE-PSK-AES128-CCM-SHA256";
    case 0x0A0A:
    case 0x1A1A:
    case 0x2A2A:
    case 0x3A3A:
    case 0x4A4A:
    case 0x5A5A:
    case 0x6A6A:
    case 0x7A7A:
    case 0x8A8A:
    case 0x9A9A:
    case 0xAAAA:
    case 0xBABA:
    case 0xCACA:
    case 0xDADA:
    case 0xEAEA:
    case 0xFAFA:
      return "GREASE-RFC8701";
    case 0x0047 ... 0x004F:
    case 0x0050 ... 0x0058:
    case 0x0059 ... 0x005C:
    case 0x0060 ... 0x0066:
    case 0xFEFE ... 0xFEFF:
      return "RESERVED-NO-CONFLICT";
    case 0x001C ... 0x001D:
      return "RESERVED-SSLV3-RFC5246";
    case 0xFF00 ... 0xFFFF:
      return "PRIVATE-USE-RFC8446";
    default:
      return "UNASSIGNED";
  }
}
