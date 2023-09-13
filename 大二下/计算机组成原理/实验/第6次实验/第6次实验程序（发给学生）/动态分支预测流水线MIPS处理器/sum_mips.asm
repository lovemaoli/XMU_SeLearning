#MIPS程序  求累加和                   sum_mips.asm                   	
#求累加和：1+2+……+n，n的值为10（可以改变），累加和的结果存放到地址为0的数据存储器中
#该程序执行结束后，数码管显示37H（55）

main:	
	addi $s0,$zero,10                    # n=10 -> s0                              
	addi $s1,$zero,1               	#        1 -> s1              
	addi $s2,$zero,1               	#        1 -> s2
	addi $s3,$zero,0              	#        0 -> s3           
loop:
	add $s3,$s3,$s1                 	# s3+s1 -> s3                       
	beq $s1,$s0,finish              	# 如果s1=s0，则转finish       
	add $s1,$s1,$s2                  	# s1+s2 -> s1     
	j loop
finish:
	sw $s3,0($zero)                	# s3 存到地址为0的存储单元中

                add $a0,$0,$s3		#要显示的值放在a0中
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值）
                syscall               

	addi   $v0,$zero,10         	# syscall的10号系统调用
	syscall                  		# 程序退出

