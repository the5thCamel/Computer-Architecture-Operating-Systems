.file	"calc.c"
	.text
	.globl	calcnew
	.type	calcnew, @function
calcnew:
.LFB23:
	.cfi_startproc
	endbr64
	movl %esi, %ecx
	shll $2, %esi  				
	movl %esi, %eax  				
	shll $0, %ecx      					
	addl %ecx, %eax     				
	addl %edi, %eax     				
	movl %edx, %ebp   
	shll $4, %edx      				
	shll $1, %ebp					
	subl %ebp, %edx                                 
	addl %edx, %eax                                 
	ret
	.cfi_endproc
.LFE23:
	.size	calcnew, .-calcnew
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
