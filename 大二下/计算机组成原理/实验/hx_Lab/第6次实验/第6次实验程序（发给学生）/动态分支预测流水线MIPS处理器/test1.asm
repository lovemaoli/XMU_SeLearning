#气泡流水线分支相关测试程序   test1.asm
#该程序测试j、jal、jr、beq、bne等分支指令的相关性，采用气泡流水线后，该程序无分支相关
#程序功能：s1的初值为32，调用子程序后，s1减1，变为31（1FH），然后在数码管上显示，之后再减1，变为30（1EH），在数码管上显示，直到变为0
#该程序执行后，过一段时间，数码管显示1F，之后减1、显示1E，一直到0

	addi $s1,$zero,32
	addi $v0,$zero,34       		#34=22H      syscall的34号功能（8个数码管显示8个十六进制数，即32位二进制数）
	j jmp_next1                  		#跳转到jmp_next1

	addi $s1,$zero,4         		#接下去3条指令不会执行
	addi $s2,$zero,5
	addi $s3,$zero,6

jmp_next1:
	beq $zero,$zero, jmp_next2             	#相当于j指令     跳转到jmp_next2

	addi $s1,$zero,7         		#接下去3条指令不会执行
	addi $s2,$zero,8
	addi $s3,$zero,9

jmp_next2:
	bne $zero,$s1, jmp_next3          	#因为s1=32  不等于0  因此跳转到jmp_next3

	addi $s1,$zero,10        		#接下去3条指令不会执行
	addi $s2,$zero,11
	addi $s3,$zero,12

jmp_next3:
	jal jmp_func           			#子程序调用指令

	addi $v0,$zero,10           		#syscall的10号功能       子程序返回到这里
	nop
	nop
	nop
	syscall				#系统退出

jmp_func:
	addi $s1,$s1,-1
	nop
	nop
	nop
	add $a0,$0,$s1               		#a0=s1
	nop
	nop
	nop
	syscall				#在数码管上从1F（32-1=31=1F）开始显示，接下去减1，直到显示0
	bne $s1,$zero,jmp_func
	jr $31                              		#子程序返回指令

