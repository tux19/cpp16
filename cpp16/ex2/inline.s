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
	jmp	.L4
	.p2align 4,,10
.L16:
	movsbl	67(%r14), %edx
.L8:
	movq	%r15, %rcx
	call	_ZNSo3putEc
	movq	%rax, %rcx
	call	_ZNSo5flushEv
	leal	1(%rbx), %eax
	cmpl	$12, %eax
	je	.L14
	cmpl	$1, %eax
	je	.L10
	cmpl	$1, %esi
	je	.L11
	movl	%ebx, %edx
	imull	%eax, %edx
	cmpl	$1, %edi
	jle	.L5
	imull	%edi, %edx
	cmpl	$1, %ebp
	jle	.L5
	leal	-3(%rbx), %r8d
	imull	%ebp, %edx
	cmpl	$1, %r8d
	jle	.L5
	leal	-4(%rbx), %ecx
	imull	%r8d, %edx
	cmpl	$1, %ecx
	jle	.L5
	leal	-5(%rbx), %r8d
	imull	%ecx, %edx
	cmpl	$1, %r8d
	jle	.L5
	leal	-6(%rbx), %ecx
	imull	%r8d, %edx
	cmpl	$1, %ecx
	jle	.L5
	subl	$7, %ebx
	imull	%ecx, %edx
	cmpl	$1, %ebx
	jle	.L5
	imull	%ebx, %edx
	cmpl	$10, %esi
	leal	(%rdx,%rdx), %ecx
	cmove	%ecx, %edx
.L5:
	addl	$1, %esi
	addl	$1, %edi
	addl	$1, %ebp
	movl	%eax, %ebx
.L4:
	movq	%r12, %rcx
	call	_ZNSolsEi
	movq	%rax, %r15
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r15,%rax), %r14
	testq	%r14, %r14
	je	.L15
	cmpb	$0, 56(%r14)
	jne	.L16
	movq	%r14, %rcx
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%r14), %rax
	movl	$10, %edx
	movq	48(%rax), %rax
	cmpq	%r13, %rax
	je	.L8
	movq	%r14, %rcx
	call	*%rax
	movsbl	%al, %edx
	jmp	.L8
	.p2align 4,,10
.L11:
	movl	%eax, %edx
	jmp	.L5
	.p2align 4,,10
.L14:
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
.L10:
	movl	$1, %edx
	jmp	.L5
.L15:
	call	_ZSt16__throw_bad_castv
	nop
	.seh_endproc
	.p2align 4,,15
	.def	_GLOBAL__sub_I_main;	.scl	3;	.type	32;	.endef
	.seh_proc	_GLOBAL__sub_I_main
_GLOBAL__sub_I_main:
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
	.quad	_GLOBAL__sub_I_main
.lcomm _ZStL8__ioinit,1,1
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
