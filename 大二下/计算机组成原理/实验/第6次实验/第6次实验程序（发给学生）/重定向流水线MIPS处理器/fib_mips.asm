#MIPS程序    计算费波那契数列        fib_mips.asm                   
# n=10（可以改变），计算好的n+1个数（0、1、1、2、3、5、8、13、21、34、55……）保存在地址为0、4、8、12、...的数据存储器中
#该程序执行后，数码管依次显示：0、1、1、2、3、5、8、D、15、22、37

main:
                addi $s2,$zero,10               		# $s2=n=10        

	addi $s1,$zero,0			# $s1=0 		
	sw $s1,0($zero)                                       # 0 -> (0)

                addi $s1,$zero,1			# $s1=1 	
	sw $s1,4($zero)			# 1 -> (4)

                addi $s1,$zero,1			# $s1=1 	
	sw $s1,8($zero)			# 1 -> (8)

                addi $s3,$zero,2			# $s3 = 2
                addi $s4,$zero,1			# $s4 = 1
                addi $s5,$zero,1			# $s5 = 1
loop:
                add $s6,$s4,$s5			# $s4+$s5 -> $s6	
                addi $s4,$s5,0			# $s5 -> $s4	
                addi $s5,$s6,0			# $s6 -> $s5	
                addi $s3,$s3,1			# $s3+1 -> $s3	
                add $s7,$s3,$s3			# $s3+$s3 -> $s7
                add $s0,$s7,$s7			# $s7+$s7 -> $s0	
                sw $s6,0($s0)                		# $s6 -> 0($s0)	
	beq $s2,$s3,end			# if $s2 = $s3 goto end	
                j loop				# goto loop
end:


                lw $a0,0($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        0号单元）       0
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  


                lw $a0,4($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        4号单元）       1
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,8($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        8号单元）        1
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,12($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        12号单元）          2
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,16($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        16号单元）      3
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,20($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        20号单元）    5
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,24($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        24号单元）      8
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,28($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        28号单元）          13=D
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,32($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        32号单元）      21=15H
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,36($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        36号单元）         34=22H
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,40($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        40号单元）         55=37H
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

	addi   $v0,$zero,10         	# syscall的10号系统调用
	syscall                  		# 程序退出
