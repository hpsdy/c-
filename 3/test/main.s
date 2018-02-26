	.file	"main.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
.globl one
	.bss
	.align 8
	.type	one, @object
	.size	one, 8
one:
	.zero	8
.globl init
	.data
	.align 4
	.type	init, @object
	.size	init, 4
init:
	.long	100
	.section	.rodata
.LC0:
	.string	" "
	.text
.globl main
	.type	main, @function
main:
.LFB958:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	init(%rip), %eax
	movl	%eax, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movl	$.LC0, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$one, %esi
	movq	%rax, %rdi
	call	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKSbIS4_S5_T1_E
	movl	$.LC0, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$100000, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE958:
	.size	main, .-main
	.section	.rodata
.LC1:
	.string	"hello world"
.globl _Unwind_Resume
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB999:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA999
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	movl	%edi, -36(%rbp)
	movl	%esi, -40(%rbp)
	cmpl	$1, -36(%rbp)
	jne	.L7
	.cfi_offset 3, -32
	.cfi_offset 12, -24
	cmpl	$65535, -40(%rbp)
	jne	.L7
	movl	$_ZStL8__ioinit, %edi
.LEHB0:
	call	_ZNSt8ios_base4InitC1Ev
.LEHE0:
	movl	$_ZNSt8ios_base4InitD1Ev, %eax
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movq	%rax, %rdi
	call	__cxa_atexit
	leaq	-17(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev
	leaq	-17(%rbp), %rax
	movq	%rax, %rdx
	movl	$.LC1, %esi
	movl	$one, %edi
.LEHB1:
	call	_ZNSsC1EPKcRKSaIcE
.LEHE1:
	jmp	.L9
.L8:
.L6:
	movl	%edx, %ebx
	movq	%rax, %r12
	leaq	-17(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	movq	%r12, %rax
	movslq	%ebx, %rdx
	movq	%rax, %rdi
.LEHB2:
	call	_Unwind_Resume
.LEHE2:
.L9:
	leaq	-17(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev
	movl	$_ZNSsD1Ev, %eax
	movl	$__dso_handle, %edx
	movl	$one, %esi
	movq	%rax, %rdi
	call	__cxa_atexit
.L7:
	addq	$32, %rsp
	popq	%rbx
	popq	%r12
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE999:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
.globl __gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA999:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE999-.LLSDACSB999
.LLSDACSB999:
	.uleb128 .LEHB0-.LFB999
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 .LEHB1-.LFB999
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L8-.LFB999
	.uleb128 0x0
	.uleb128 .LEHB2-.LFB999
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE999:
	.text
	.type	_GLOBAL__I_one, @function
_GLOBAL__I_one:
.LFB1000:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1000:
	.size	_GLOBAL__I_one, .-_GLOBAL__I_one
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I_one
	.section	.rodata
	.align 8
	.type	_ZZL18__gthread_active_pvE20__gthread_active_ptr, @object
	.size	_ZZL18__gthread_active_pvE20__gthread_active_ptr, 8
_ZZL18__gthread_active_pvE20__gthread_active_ptr:
	.quad	_ZL22__gthrw_pthread_cancelm
	.weakref	_ZL20__gthrw_pthread_oncePiPFvvE,pthread_once
	.weakref	_ZL27__gthrw_pthread_getspecificj,pthread_getspecific
	.weakref	_ZL27__gthrw_pthread_setspecificjPKv,pthread_setspecific
	.weakref	_ZL22__gthrw_pthread_createPmPK14pthread_attr_tPFPvS3_ES3_,pthread_create
	.weakref	_ZL20__gthrw_pthread_joinmPPv,pthread_join
	.weakref	_ZL21__gthrw_pthread_equalmm,pthread_equal
	.weakref	_ZL20__gthrw_pthread_selfv,pthread_self
	.weakref	_ZL22__gthrw_pthread_detachm,pthread_detach
	.weakref	_ZL22__gthrw_pthread_cancelm,pthread_cancel
	.weakref	_ZL19__gthrw_sched_yieldv,sched_yield
	.weakref	_ZL26__gthrw_pthread_mutex_lockP15pthread_mutex_t,pthread_mutex_lock
	.weakref	_ZL29__gthrw_pthread_mutex_trylockP15pthread_mutex_t,pthread_mutex_trylock
	.weakref	_ZL31__gthrw_pthread_mutex_timedlockP15pthread_mutex_tPK8timespec,pthread_mutex_timedlock
	.weakref	_ZL28__gthrw_pthread_mutex_unlockP15pthread_mutex_t,pthread_mutex_unlock
	.weakref	_ZL26__gthrw_pthread_mutex_initP15pthread_mutex_tPK19pthread_mutexattr_t,pthread_mutex_init
	.weakref	_ZL29__gthrw_pthread_mutex_destroyP15pthread_mutex_t,pthread_mutex_destroy
	.weakref	_ZL30__gthrw_pthread_cond_broadcastP14pthread_cond_t,pthread_cond_broadcast
	.weakref	_ZL27__gthrw_pthread_cond_signalP14pthread_cond_t,pthread_cond_signal
	.weakref	_ZL25__gthrw_pthread_cond_waitP14pthread_cond_tP15pthread_mutex_t,pthread_cond_wait
	.weakref	_ZL30__gthrw_pthread_cond_timedwaitP14pthread_cond_tP15pthread_mutex_tPK8timespec,pthread_cond_timedwait
	.weakref	_ZL28__gthrw_pthread_cond_destroyP14pthread_cond_t,pthread_cond_destroy
	.weakref	_ZL26__gthrw_pthread_key_createPjPFvPvE,pthread_key_create
	.weakref	_ZL26__gthrw_pthread_key_deletej,pthread_key_delete
	.weakref	_ZL30__gthrw_pthread_mutexattr_initP19pthread_mutexattr_t,pthread_mutexattr_init
	.weakref	_ZL33__gthrw_pthread_mutexattr_settypeP19pthread_mutexattr_ti,pthread_mutexattr_settype
	.weakref	_ZL33__gthrw_pthread_mutexattr_destroyP19pthread_mutexattr_t,pthread_mutexattr_destroy
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-18)"
	.section	.note.GNU-stack,"",@progbits
