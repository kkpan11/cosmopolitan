#include "libc/nt/codegen.h"
.imp	kernel32,__imp_GetCurrentThreadId,GetCurrentThreadId,0

	.text.windows
GetCurrentThreadId:
#ifdef __x86_64__
	push	%rbp
	mov	%rsp,%rbp
	.profilable
	sub	$32,%rsp
	call	*__imp_GetCurrentThreadId(%rip)
	leave
#elif defined(__aarch64__)
	mov	x0,#0
#endif
	ret
	.endfn	GetCurrentThreadId,globl
	.previous