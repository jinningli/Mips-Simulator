	.data
	.word 1
_static_48:
	.asciiz "\n"
	.align 2
	.word 1
_static_55:
	.asciiz " "
	.align 2
_static_49:
	.word 0
_static_50:
	.word 0
_static_51:
	.word 0
_static_52:
	.word 0
_static_53:
	.word 0
_static_54:
	.word 0
	.data
_buffer:
	.word 0
	.text
_buffer_init:
	li $a0, 256
	li $v0, 9
	syscall
	sw $v0, _buffer
	jr $ra
	.text
main:
	jal _buffer_init
	add $fp, $zero, $sp
	jal _func_main
	move $a0, $v0
	li $v0, 17
	syscall
_func_____built_in_string_less:
	sw $fp, -212($sp)
	add $fp, $sp, -4
	add $sp, $fp, -216
	sw $ra, 0($sp)
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	lw $11, -4($fp)
	sub $12, $11, 4
	lw $13, 0($12)
	sw $10, -8($fp)
	ble $10, $13, _end_if_68
	lw $8, -4($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	sw $10, -8($fp)
_end_if_68:
	li $8, 0
	sw $8, -12($fp)
_begin_loop_56:
	lw $8, -12($fp)
	lw $9, -8($fp)
	bge $8, $9, _end_loop_56
	lw $8, 0($fp)
	lw $9, -12($fp)
	add $10, $8, $9
	lb $11, 0($10)
	lw $12, -4($fp)
	add $13, $12, $9
	lb $14, 0($13)
	sw $11, -16($fp)
	sw $14, -20($fp)
	beq $11, $14, _end_if_69
	lw $8, -16($fp)
	lw $9, -20($fp)
	slt $10, $8, $9
	move $v0, $10
	sw $10, -76($fp)
	b _end_func_____built_in_string_less
_end_if_69:
_continue_loop56:
	lw $8, -12($fp)
	add $8, $8, 1
	sw $8, -12($fp)
	b _begin_loop_56
_end_loop_56:
	lw $8, -4($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	lw $11, -8($fp)
	slt $12, $11, $10
	move $v0, $12
	sw $12, -88($fp)
	b _end_func_____built_in_string_less
_end_func_____built_in_string_less:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -208($fp)
	jr $ra

_func_____built_in_string_equal:
	sw $fp, -188($sp)
	add $fp, $sp, -4
	add $sp, $fp, -192
	sw $ra, 0($sp)
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	lw $11, -4($fp)
	sub $12, $11, 4
	lw $13, 0($12)
	beq $10, $13, _end_if_70
	move $v0, $zero
	b _end_func_____built_in_string_equal
_end_if_70:
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	li $11, 0
	sw $10, -12($fp)
	sw $11, -8($fp)
_begin_loop_57:
	lw $8, -8($fp)
	lw $9, -12($fp)
	bge $8, $9, _end_loop_57
	lw $8, 0($fp)
	lw $9, -8($fp)
	add $10, $8, $9
	lb $11, 0($10)
	lw $12, -4($fp)
	add $13, $12, $9
	lb $14, 0($13)
	beq $11, $14, _end_if_71
	move $v0, $zero
	b _end_func_____built_in_string_equal
_end_if_71:
_continue_loop57:
	lw $8, -8($fp)
	add $8, $8, 1
	sw $8, -8($fp)
	b _begin_loop_57
_end_loop_57:
	li $8, 1
	move $v0, $8
	b _end_func_____built_in_string_equal
_end_func_____built_in_string_equal:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -184($fp)
	jr $ra

_func_____built_in_string_inequal:
	sw $fp, -188($sp)
	add $fp, $sp, -4
	add $sp, $fp, -192
	sw $ra, 0($sp)
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	lw $11, -4($fp)
	sub $12, $11, 4
	lw $13, 0($12)
	beq $10, $13, _end_if_72
	li $8, 1
	move $v0, $8
	b _end_func_____built_in_string_inequal
_end_if_72:
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	li $11, 0
	sw $10, -12($fp)
	sw $11, -8($fp)
_begin_loop_58:
	lw $8, -8($fp)
	lw $9, -12($fp)
	bge $8, $9, _end_loop_58
	lw $8, 0($fp)
	lw $9, -8($fp)
	add $10, $8, $9
	lb $11, 0($10)
	lw $12, -4($fp)
	add $13, $12, $9
	lb $14, 0($13)
	beq $11, $14, _end_if_73
	li $8, 1
	move $v0, $8
	b _end_func_____built_in_string_inequal
_end_if_73:
_continue_loop58:
	lw $8, -8($fp)
	add $8, $8, 1
	sw $8, -8($fp)
	b _begin_loop_58
_end_loop_58:
	move $v0, $zero
	b _end_func_____built_in_string_inequal
_end_func_____built_in_string_inequal:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -184($fp)
	jr $ra

_func_____built_in_string_greater:
	sw $fp, -132($sp)
	add $fp, $sp, -4
	add $sp, $fp, -136
	sw $ra, 0($sp)

	lw $8, -4($fp)
	sw $8, -4($sp)

	lw $9, 0($fp)
	sw $9, -8($sp)

jal _func_____built_in_string_less
	sw $v0, -8($fp)
	lw $8, -8($fp)
	move $v0, $8
	b _end_func_____built_in_string_greater
_end_func_____built_in_string_greater:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -128($fp)
	jr $ra

_func_____built_in_string_less_equal:
	sw $fp, -220($sp)
	add $fp, $sp, -4
	add $sp, $fp, -224
	sw $ra, 0($sp)
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	lw $11, -4($fp)
	sub $12, $11, 4
	lw $13, 0($12)
	sw $10, -8($fp)
	ble $10, $13, _end_if_74
	lw $8, -4($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	sw $10, -8($fp)
_end_if_74:
	li $8, 0
	sw $8, -12($fp)
_begin_loop_59:
	lw $8, -12($fp)
	lw $9, -8($fp)
	bge $8, $9, _end_loop_59
	lw $8, 0($fp)
	lw $9, -12($fp)
	add $10, $8, $9
	lb $11, 0($10)
	lw $12, -4($fp)
	add $13, $12, $9
	lb $14, 0($13)
	sw $11, -16($fp)
	sw $14, -20($fp)
	beq $11, $14, _end_if_75
	lw $8, -16($fp)
	lw $9, -20($fp)
	slt $10, $8, $9
	move $v0, $10
	sw $10, -76($fp)
	b _end_func_____built_in_string_less_equal
_end_if_75:
_continue_loop59:
	lw $8, -12($fp)
	add $8, $8, 1
	sw $8, -12($fp)
	b _begin_loop_59
_end_loop_59:
	lw $8, 0($fp)
	sub $9, $8, 4
	lw $10, 0($9)
	lw $11, -4($fp)
	sub $12, $11, 4
	lw $13, 0($12)
	sle $14, $10, $13
	move $v0, $14
	sw $14, -96($fp)
	b _end_func_____built_in_string_less_equal
_end_func_____built_in_string_less_equal:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -216($fp)
	jr $ra

_func_____built_in_string_greater_equal:
	sw $fp, -132($sp)
	add $fp, $sp, -4
	add $sp, $fp, -136
	sw $ra, 0($sp)

	lw $8, -4($fp)
	sw $8, -4($sp)

	lw $9, 0($fp)
	sw $9, -8($sp)

jal _func_____built_in_string_less_equal
	sw $v0, -8($fp)
	lw $8, -8($fp)
	move $v0, $8
	b _end_func_____built_in_string_greater_equal
_end_func_____built_in_string_greater_equal:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -128($fp)
	jr $ra

_func_____built_in_println:
	sw $fp, -128($sp)
	add $fp, $sp, -4
	add $sp, $fp, -132
	sw $ra, 0($sp)

	lw $8, 0($fp)
	li $v0, 4
	move $a0, $8

	syscall
	la $8, _static_48
	move $9, $8
	li $v0, 4
	move $a0, $9

	syscall
_end_func_____built_in_println:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -124($fp)
	jr $ra

_func_merge:
	sw $fp, -236($sp)
	add $fp, $sp, -4
	add $sp, $fp, -240
	sw $ra, 0($sp)
	lw $8, 0($fp)
	bne $zero, $8, _end_if_76
	lw $8, -4($fp)
	move $v0, $8
	b _end_func_merge
_end_if_76:
	lw $8, -4($fp)
	bne $zero, $8, _end_if_77
	lw $8, 0($fp)
	move $v0, $8
	b _end_func_merge
_end_if_77:
	lw $8, 0($fp)
	mul $9, $8, 4
	lw $10, _static_54
	add $11, $10, $9
	lw $12, 0($11)
	lw $13, -4($fp)
	mul $14, $13, 4
	add $15, $10, $14
	lw $16, 0($15)
	bge $12, $16, _end_if_78
	lw $8, 0($fp)
	lw $9, -4($fp)
	move $10, $8
	sw $8, -8($fp)
	sw $9, 0($fp)
	sw $10, -4($fp)
_end_if_78:
	lw $8, 0($fp)
	mul $9, $8, 4
	lw $10, _static_53
	add $11, $10, $9
	lw $12, 0($11)
	sw $12, -4($sp)

	lw $13, -4($fp)
	sw $13, -8($sp)

jal _func_merge
	sw $v0, -60($fp)
	lw $8, 0($fp)
	mul $9, $8, 4
	lw $10, _static_53
	add $11, $10, $9
	lw $12, -60($fp)
	sw $12, 0($11)
	mul $13, $8, 4
	lw $14, _static_52
	add $15, $14, $13
	lw $16, 0($15)
	mul $17, $8, 4
	add $18, $10, $17
	lw $19, 0($18)
	mul $20, $8, 4
	add $21, $14, $20
	sw $19, 0($21)
	mul $22, $8, 4
	add $23, $10, $22
	sw $16, 0($23)
	move $v0, $8
	sw $16, -12($fp)
	b _end_func_merge
_end_func_merge:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -232($fp)
	jr $ra

_func_main:
	sw $fp, -444($sp)
	add $fp, $sp, -4
	add $sp, $fp, -448
	sw $ra, 0($sp)
	li $v0, 5
	syscall
	sw $v0, -12($fp)
	lw $8, -12($fp)
	sw $8, _static_49
	li $v0, 5
	syscall
	sw $v0, -16($fp)
	lw $8, -16($fp)
	sw $8, _static_50
jal _func_____built_in_getString
	sw $v0, -20($fp)
	lw $8, -20($fp)
	lw $9, _static_49
	lw $10, _static_50
	add $11, $9, $10
	add $12, $11, 5
	add $13, $12, 1
	mul $14, $13, 4
	li $v0, 9
	move $a0, $14
	sw $8, _static_51
	sw $12, -32($fp)
	syscall
	sw $v0, -44($fp)
	lw $8, -32($fp)
	lw $9, -44($fp)
	sw $8, 0($9)
	add $10, $9, 4
	lw $11, _static_49
	lw $12, _static_50
	add $13, $11, $12
	add $14, $13, 5
	add $15, $14, 1
	mul $16, $15, 4
	li $v0, 9
	move $a0, $16
	sw $10, _static_52
	sw $14, -60($fp)
	syscall
	sw $v0, -72($fp)
	lw $8, -60($fp)
	lw $9, -72($fp)
	sw $8, 0($9)
	add $10, $9, 4
	lw $11, _static_49
	lw $12, _static_50
	add $13, $11, $12
	add $14, $13, 5
	add $15, $14, 1
	mul $16, $15, 4
	li $v0, 9
	move $a0, $16
	sw $10, _static_53
	sw $14, -88($fp)
	syscall
	sw $v0, -100($fp)
	lw $8, -88($fp)
	lw $9, -100($fp)
	sw $8, 0($9)
	add $10, $9, 4
	li $11, 1
	sw $10, _static_54
	sw $11, 0($fp)
_begin_loop_60:
	lw $8, 0($fp)
	lw $9, _static_49
	bgt $8, $9, _end_loop_60
	li $v0, 5
	syscall
	sw $v0, -124($fp)
	lw $8, 0($fp)
	mul $9, $8, 4
	lw $10, _static_54
	add $11, $10, $9
	lw $12, -124($fp)
	sw $12, 0($11)
	mul $13, $8, 4
	lw $14, _static_52
	add $15, $14, $13
	sw $zero, 0($15)
	mul $16, $8, 4
	lw $17, _static_53
	add $18, $17, $16
	sw $zero, 0($18)
_continue_loop60:
	lw $8, 0($fp)
	add $8, $8, 1
	move $8, $8
	sw $8, 0($fp)
	b _begin_loop_60
_end_loop_60:
	li $8, 1
	sw $8, 0($fp)
_begin_loop_61:
	lw $8, 0($fp)
	lw $9, _static_50
	bgt $8, $9, _end_loop_61
	lw $8, 0($fp)
	sub $9, $8, 1
	lw $10, _static_51
	add $11, $10, $9
	lb $12, 0($11)
	lw $13, _static_49
	add $14, $8, $13
	mul $15, $14, 4
	lw $16, _static_54
	add $17, $16, $15
	sw $12, 0($17)
	add $18, $8, $13
	mul $19, $18, 4
	lw $20, _static_52
	add $21, $20, $19
	sw $zero, 0($21)
	add $22, $8, $13
	mul $23, $22, 4
	lw $24, _static_53
	add $25, $24, $23
	sw $zero, 0($25)
_continue_loop61:
	lw $8, 0($fp)
	add $8, $8, 1
	move $8, $8
	sw $8, 0($fp)
	b _begin_loop_61
_end_loop_61:
	li $8, 1
	lw $9, _static_49
	add $10, $9, 1
	li $11, 2
	sw $8, -4($fp)
	sw $10, -8($fp)
	sw $11, 0($fp)
_begin_loop_62:
	lw $8, 0($fp)
	lw $9, _static_49
	bgt $8, $9, _end_loop_62

	lw $8, -4($fp)
	sw $8, -4($sp)

	lw $9, 0($fp)
	sw $9, -8($sp)

jal _func_merge
	sw $v0, -232($fp)
	lw $8, -232($fp)
	sw $8, -4($fp)
_continue_loop62:
	lw $8, 0($fp)
	add $8, $8, 1
	move $8, $8
	sw $8, 0($fp)
	b _begin_loop_62
_end_loop_62:
	lw $8, _static_49
	add $9, $8, 2
	sw $9, 0($fp)
_begin_loop_63:
	lw $8, _static_49
	lw $9, _static_50
	add $10, $8, $9
	lw $11, 0($fp)
	bgt $11, $10, _end_loop_63

	lw $8, -8($fp)
	sw $8, -4($sp)

	lw $9, 0($fp)
	sw $9, -8($sp)

jal _func_merge
	sw $v0, -256($fp)
	lw $8, -256($fp)
	sw $8, -8($fp)
_continue_loop63:
	lw $8, 0($fp)
	add $8, $8, 1
	move $8, $8
	sw $8, 0($fp)
	b _begin_loop_63
_end_loop_63:
	lw $8, -4($fp)
	mul $9, $8, 4
	lw $10, _static_54
	add $11, $10, $9
	lw $12, 0($11)
	sw $12, -4($sp)

jal _func_____built_in_toString
	sw $v0, -276($fp)

	lw $8, -276($fp)
	li $v0, 4
	move $a0, $8

	syscall
	la $8, _static_55
	move $9, $8
	li $v0, 4
	move $a0, $9

	syscall
	lw $8, -8($fp)
	lw $9, _static_49
	sub $10, $8, $9
	sub $11, $10, 1
	sub $12, $8, $9
	sub $13, $12, 1

	lw $14, _static_51
	sw $14, -4($sp)
	sw $11, -8($sp)
	sw $13, -12($sp)

jal _func_____built_in_substring
	sw $v0, -308($fp)

	lw $8, -308($fp)
	li $v0, 4
	move $a0, $8

	syscall
	la $8, _static_48
	move $9, $8
	li $v0, 4
	move $a0, $9

	syscall

	lw $8, -4($fp)
	sw $8, -4($sp)

	lw $9, -8($fp)
	sw $9, -8($sp)

jal _func_merge
	sw $v0, -316($fp)

	lw $8, -316($fp)
	sw $8, -4($sp)

jal _func_____built_in_toString
	sw $v0, -320($fp)

	lw $8, -320($fp)
	li $v0, 4
	move $a0, $8

	syscall

	la $8, _static_48
	li $v0, 4
	move $a0, $8

	syscall
	move $v0, $zero
	b _end_func_main
_end_func_main:
	lw $ra, 0($sp)
	add $sp, $fp, 4
	lw $fp, -440($fp)
	jr $ra

	.text
_string_copy:
	_begin_string_copy:
	lb $v0, 0($a0)
	beqz $v0, _exit_string_copy
	sb $v0, 0($a1)
	add $a0, $a0, 1
	add $a1, $a1, 1
	j _begin_string_copy
	_exit_string_copy:
	sb $zero, 0($a1)
	jr $ra

_func_____built_in_substring:
	lw $a0, -4($sp)
	lw $a1, -8($sp)
	lw $a2, -12($sp)
	subu $sp, $sp, 4
	sw $ra, 0($sp)

	move $t0, $a0

	sub $t1, $a2, $a1
	add $t1, $t1, 1
	add $a0, $t1, 5
	li $v0, 9
	syscall
	sw $t1, 0($v0)
	add $v0, $v0, 4

	add $a0, $t0, $a1
	add $t2, $t0, $a2
	lb $t3, 1($t2)
	sb $zero, 1($t2)
	move $a1, $v0
	move $t4, $v0
	jal _string_copy
	move $v0, $t4
	sb $t3, 1($t2)

	lw $ra, 0($sp)
	addu $sp, $sp, 4
	jr $ra

_count_string_length:
	move $v0, $a0

	_begin_count_string_length:
	lb $v1, 0($a0)
	beqz $v1, _exit_count_string_length
	add $a0, $a0, 1
	j _begin_count_string_length

	_exit_count_string_length:
	sub $v0, $a0, $v0
	jr $ra

_func_____built_in_getString:
	subu $sp, $sp, 4
	sw $ra, 0($sp)

	lw $a0, _buffer
	li $a1, 255
	li $v0, 8
	syscall

	jal _count_string_length

	move $a1, $v0
	add $a0, $v0, 5
	li $v0, 9
	syscall
	sw $a1, 0($v0)
	add $v0, $v0, 4
	lw $a0, _buffer
	move $a1, $v0
	move $t0, $v0
	jal _string_copy
	move $v0, $t0

	lw $ra, 0($sp)
	addu $sp, $sp, 4
	jr $ra

_func_____built_in_parseInt:
	lw $a0, -4($sp)
	li $v0, 0
	move $t0, $a0
	li $t2, 1

	_count_number_pos:
	lb $t1, 0($t0)
	bgt $t1, 57, _begin_parse_int
	blt $t1, 48, _begin_parse_int
	add $t0, $t0, 1
	j _count_number_pos

	_begin_parse_int:
	sub $t0, $t0, 1

	_parsing_int:
	blt $t0, $a0, _finish_parse_int
	lb $t1, 0($t0)
	sub $t1, $t1, 48
	mul $t1, $t1, $t2
	add $v0, $v0, $t1
	mul $t2, $t2, 10
	sub $t0, $t0, 1
	j _parsing_int

	_finish_parse_int:
	jr $ra

_func_____built_in_string_concatenate:
	lw $a0, -4($sp)
	lw $a1, -8($sp)
	subu $sp, $sp, 4
	sw $ra, 0($sp)

	move $t2, $a0
	move $t3, $a1

	lw $t0, -4($a0)
	lw $t1, -4($a1)
	add $t5, $t0, $t1
	add $a0, $t5, 5
	li $v0, 9
	syscall
	sw $t5, 0($v0)
	add $v0, $v0, 4
	move $t4, $v0

	move $a0, $t2
	move $a1, $t4
	jal _string_copy

	move $a0, $t3
	add $a1, $t4, $t0
	
	jal _string_copy

	move $v0, $t4
	lw $ra, 0($sp)
	addu $sp, $sp, 4
	jr $ra

_func_____built_in_toString:
	lw $a0, -4($sp)
	li $t0, 0
	bgez $a0, _skip_set_less_than_zero
	li $t0, 1
	neg $a0, $a0
	_skip_set_less_than_zero:
	beqz $a0, _set_zero

	li $t1, 0
	move $t2, $a0
	move $t3, $a0
	li $t5, 10

	_begin_count_digit:
	div $t2, $t5
	mflo $v0
	mfhi $v1
	bgtz $v0, _not_yet
	bgtz $v1, _not_yet
	j _yet
	_not_yet:
	add $t1, $t1, 1
	move $t2, $v0
	j _begin_count_digit

	_yet:
	beqz $t0, _skip_reserve_neg
	add $t1, $t1, 1
	_skip_reserve_neg:
	add $a0, $t1, 5
	li $v0, 9
	syscall
	sw $t1, 0($v0)
	add $v0, $v0, 4
	add $t1, $t1, $v0
	sb $zero, 0($t1)
	sub $t1, $t1, 1

	_continue_toString:
	div $t3, $t5
	mfhi $v1
	add $v1, $v1, 48
	sb $v1, 0($t1)
	sub $t1, $t1, 1
	mflo $t3
	
	bnez $t3, _continue_toString

	beqz $t0, _skip_place_neg
	li $v1, 45
	sb $v1, 0($t1)
	_skip_place_neg:
	
	jr $ra

	_set_zero:
	li $a0, 6
	li $v0, 9
	syscall
	li $a0, 1
	sw $a0, 0($v0)
	add $v0, $v0, 4
	li $a0, 48
	sb $a0, 0($v0)
	jr $ra
