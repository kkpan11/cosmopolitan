#ifndef COSMOPOLITAN_LIBC_INTRIN_NOMULTICS_INTERNAL_H_
#define COSMOPOLITAN_LIBC_INTRIN_NOMULTICS_INTERNAL_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)
COSMOPOLITAN_C_START_

extern char __replmode;
extern char __replstderr;
extern char __ttymagic;
extern char __vintr;
extern char __vquit;

COSMOPOLITAN_C_END_
#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_INTRIN_NOMULTICS_INTERNAL_H_ */
