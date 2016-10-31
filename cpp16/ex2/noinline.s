	.file	"inline_ex.cpp"
	.section	.text$_ZNKSt5ctypeIcE8do_widenEc,"x"
	.linkonce discard
	.align 2
	.p2align 4,,15
	.globl	_ZNKSt5ctypeIcE8do_widenEc
	.def	_ZNKSt5ctypeIcE8do_widenEc;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZNKSt5ctypeIcE8do_widenEc
_ZNKSt5ctypeIcE8do_widenEc:
.LFB1164:
	.seh_endprologue
	movl	%edx, %eax
	ret
	.seh_endproc
	.text
	.p2align 4,,15
	.def	__tcf_0;	.scl	3;	.type	32;	.endef
	.seh_proc	__tcf_0
__tcf_0:
.LFB1596:
	.seh_endprologue
	leaq	_ZStL8__ioinit(%rip), %rcx
	jmp	_ZNSt8ios_base4InitD1Ev
	.seh_endproc
	.p2align 4,,15
	.globl	_Z9factoriali
	.def	_Z9factoriali;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z9factoriali
_Z9factoriali:
.LFB1407:
	.seh_endprologue
	cmpl	$1, %ecx
	jle	.L9
	leal	-5(%rcx), %eax
	leal	-2(%rcx), %edx
	shrl	$2, %eax
	leal	-1(%rcx), %r8d
	addl	$1, %eax
	leal	0(,%rax,4), %r9d
	cmpl	$8, %edx
	jbe	.L10
	movdqa	.LC0(%rip), %xmm0
	movd	%ecx, %xmm5
	xorl	%edx, %edx
	movdqa	.LC2(%rip), %xmm4
	pshufd	$0, %xmm5, %xmm2
	paddd	.LC1(%rip), %xmm2
.L6:
	movdqa	%xmm2, %xmm3
	movdqa	%xmm2, %xmm1
	addl	$1, %edx
	pmuludq	%xmm0, %xmm3
	paddd	%xmm4, %xmm2
	psrlq	$32, %xmm0
	psrlq	$32, %xmm1
	pmuludq	%xmm0, %xmm1
	pshufd	$8, %xmm3, %xmm0
	pshufd	$8, %xmm1, %xmm1
	punpckldq	%xmm1, %xmm0
	cmpl	%edx, %eax
	ja	.L6
	movdqa	%xmm0, %xmm1
	movdqa	%xmm0, %xmm2
	subl	%r9d, %ecx
	psrldq	$8, %xmm1
	pmuludq	%xmm1, %xmm2
	psrlq	$32, %xmm0
	psrlq	$32, %xmm1
	pmuludq	%xmm1, %xmm0
	pshufd	$8, %xmm2, %xmm2
	pshufd	$8, %xmm0, %xmm1
	punpckldq	%xmm1, %xmm2
	movdqa	%xmm2, %xmm1
	movdqa	%xmm2, %xmm0
	psrldq	$4, %xmm1
	pmuludq	%xmm1, %xmm0
	movd	%xmm0, %eax
	cmpl	%r9d, %r8d
	je	.L4
	leal	-1(%rcx), %r8d
.L5:
	imull	%ecx, %eax
	cmpl	$1, %r8d
	je	.L4
	leal	-2(%rcx), %r9d
	imull	%r8d, %eax
	cmpl	$1, %r9d
	je	.L4
	leal	-3(%rcx), %edx
	imull	%r9d, %eax
	cmpl	$1, %edx
	je	.L4
	leal	-4(%rcx), %r8d
	imull	%edx, %eax
	cmpl	$1, %r8d
	je	.L4
	leal	-5(%rcx), %edx
	imull	%r8d, %eax
	cmpl	$1, %edx
	je	.L4
	leal	-6(%rcx), %r8d
	imull	%edx, %eax
	cmpl	$1, %r8d
	je	.L4
	leal	-7(%rcx), %edx
	imull	%r8d, %eax
	cmpl	$1, %edx
	je	.L4
	imull	%edx, %eax
	subl	$8, %ecx
	imull	%ecx, %eax
	ret
	.p2align 4,,10
.L9:
	movl	$1, %eax
.L4:
	ret
	.p2align 4,,10
.L10:
	movl	$1, %eax
	jmp	.L5
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section	.text.startup,"x"
	.p2align 4,,15
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB1408:
	pushq	%r15
	.seh_pushreg	%r15
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movl	$-2, %ebp
	movl	$-1, %edi
	xorl	%esi, %esi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %r13
	xorl	%ebx, %ebx
	call	__main
	movl	$1, %edx
	movq	.refptr._ZSt4cout(%rip), %r12
	jmp	.L35
	.p2align 4,,10
.L46:
	movsbl	67(%r14), %edx
.L39:
	movq	%r15, %rcx
	call	_ZNSo3putEc
	movq	%rax, %rcx
	call	_ZNSo5flushEv
	leal	1(%rbx), %eax
	cmpl	$12, %eax
	je	.L44
	cmpl	$1, %eax
	je	.L41
	cmpl	$1, %esi
	je	.L42
	movl	%ebx, %edx
	imull	%eax, %edx
	cmpl	$1, %edi
	jle	.L36
	imull	%edi, %edx
	cmpl	$1, %ebp
	jle	.L36
	leal	-3(%rbx), %r8d
	imull	%ebp, %edx
	cmpl	$1, %r8d
	jle	.L36
	leal	-4(%rbx), %ecx
	imull	%r8d, %edx
	cmpl	$1, %ecx
	jle	.L36
	leal	-5(%rbx), %r8d
	imull	%ecx, %edx
	cmpl	$1, %r8d
	jle	.L36
	leal	-6(%rbx), %ecx
	imull	%r8d, %edx
	cmpl	$1, %ecx
	jle	.L36
	subl	$7, %ebx
	imull	%ecx, %edx
	cmpl	$1, %ebx
	jle	.L36
	imull	%ebx, %edx
	cmpl	$10, %esi
	leal	(%rdx,%rdx), %ecx
	cmove	%ecx, %edx
.L36:
	addl	$1, %esi
	addl	$1, %edi
	addl	$1, %ebp
	movl	%eax, %ebx
.L35:
	movq	%r12, %rcx
	call	_ZNSolsEi
	movq	%rax, %r15
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r15,%rax), %r14
	testq	%r14, %r14
	je	.L45
	cmpb	$0, 56(%r14)
	jne	.L46
	movq	%r14, %rcx
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%r14), %rax
	movl	$10, %edx
	movq	48(%rax), %rax
	cmpq	%r13, %rax
	je	.L39
	movq	%r14, %rcx
	call	*%rax
	movsbl	%al, %edx
	jmp	.L39
	.p2align 4,,10
.L42:
	movl	%eax, %edx
	jmp	.L36
	.p2align 4,,10
.L44:
	xorl	%eax, %eax
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	ret
.L41:
	movl	$1, %edx
	jmp	.L36
.L45:
	call	_ZSt16__throw_bad_castv
	nop
	.seh_endproc
	.p2align 4,,15
	.def	_GLOBAL__sub_I__Z9factoriali;	.scl	3;	.type	32;	.endef
	.seh_proc	_GLOBAL__sub_I__Z9factoriali
_GLOBAL__sub_I__Z9factoriali:
.LFB1597:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	leaq	_ZStL8__ioinit(%rip), %rcx
	call	_ZNSt8ios_base4InitC1Ev
	leaq	__tcf_0(%rip), %rcx
	addq	$40, %rsp
	jmp	atexit
	.seh_endproc
	.section	.ctors,"w"
	.align 8
	.quad	_GLOBAL__sub_I__Z9factoriali
.lcomm _ZStL8__ioinit,1,1
	.section .rdata,"dr"
	.align 16
.LC0:
	.long	1
	.long	1
	.long	1
	.long	1
	.align 16
.LC1:
	.long	0
	.long	-1
	.long	-2
	.long	-3
	.align 16
.LC2:
	.long	-4
	.long	-4
	.long	-4
	.long	-4
	.ident	"GCC: (GNU) 5.3.0"
	.def	_ZNSt8ios_base4InitD1Ev;	.scl	2;	.type	32;	.endef
	.def	_ZNSo3putEc;	.scl	2;	.type	32;	.endef
	.def	_ZNSo5flushEv;	.scl	2;	.type	32;	.endef
	.def	_ZNSolsEi;	.scl	2;	.type	32;	.endef
	.def	_ZNKSt5ctypeIcE13_M_widen_initEv;	.scl	2;	.type	32;	.endef
	.def	_ZSt16__throw_bad_castv;	.scl	2;	.type	32;	.endef
	.def	_ZNSt8ios_base4InitC1Ev;	.scl	2;	.type	32;	.endef
	.def	atexit;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr._ZSt4cout, "dr"
	.globl	.refptr._ZSt4cout
	.linkonce	discard
.refptr._ZSt4cout:
	.quad	_ZSt4cout
