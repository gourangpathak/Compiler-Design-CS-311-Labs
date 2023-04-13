	.file	"main.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	$0, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$50, %esi
	movq	%rax, %rdi
	call	insert@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$30, %esi
	movq	%rax, %rdi
	call	insert@PLT
	movq	-8(%rbp), %rax
	movl	$20, %esi
	movq	%rax, %rdi
	call	insert@PLT
	movq	-8(%rbp), %rax
	movl	$40, %esi
	movq	%rax, %rdi
	call	insert@PLT
	movq	-8(%rbp), %rax
	movl	$70, %esi
	movq	%rax, %rdi
	call	insert@PLT
	movq	-8(%rbp), %rax
	movl	$60, %esi
	movq	%rax, %rdi
	call	insert@PLT
	movq	-8(%rbp), %rax
	movl	$80, %esi
	movq	%rax, %rdi
	call	insert@PLT
	movq	-8(%rbp), %rax
	movl	$60, %esi
	movq	%rax, %rdi
	call	deleteNode@PLT
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	inorder@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
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
