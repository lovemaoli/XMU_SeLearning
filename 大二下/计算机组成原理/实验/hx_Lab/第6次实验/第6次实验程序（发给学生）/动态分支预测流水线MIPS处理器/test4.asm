#测试程序    test4.asm


	addi $s1,$zero,5               	#设置循环次数=5

	j jmp_next1		#载入BPB（分支预测表），BPB有1个表项
	addi $s1,$zero,1
	addi $s2,$zero,2

jmp_next1:
	j jmp_next2		#载入BPB（分支预测表），BPB有2个表项
	addi $s1,$zero,1
	addi $s2,$zero,2

jmp_next2:
	j jmp_next3		#载入BPB（分支预测表），BPB有3个表项
	addi $s1,$zero,1
	addi $s2,$zero,2

jmp_next3:
	j jmp_next4		#载入BPB（分支预测表），BPB有4个表项
	addi $s1,$zero,1
	addi $s2,$zero,2

jmp_next4:
	j jmp_next5		#载入BPB（分支预测表），BPB有5个表项
	addi $s1,$zero,1
	addi $s2,$zero,2

jmp_next5:
	j jmp_next6		#载入BPB（分支预测表），BPB有6个表项
	addi $s1,$zero,1
	addi $s2,$zero,2

jmp_next6:
	j jmp_next7		#载入BPB（分支预测表），BPB有7个表项
	addi $s1,$zero,1
	addi $s2,$zero,2

jmp_next7:
	j jmp_next8		#载入BPB（分支预测表），BPB有8个表项
	addi $s1,$zero,1
	addi $s2,$zero,2

jmp_next8:
	addi $s1,$s1,-1
	bne $s1,$zero,jmp_next2

	addi $s0,$zero,1
	addi $s2,$zero,255
	addi $s1,$zero,1
	addi $s3,$zero,3

	beq $s0,$s2,jmp_next9
	beq $s0,$s0,jmp_next9

	addi $s1,$zero,1
	addi $s2,$zero,2

jmp_next9:
	bne $s1,$s1,jmp_next10
	bne $s1,$s2,jmp_next10

	addi $s1,$zero,1
	addi $s2,$zero,2

jmp_next10:
	jal func
	addi $v0,$zero,10
	syscall

func:	
	addi $s0,$zero,0
	addi $s0,$s0,1
	add $a0,$zero,$s0
	addi $v0,$zero,34
	syscall
	jr $ra















