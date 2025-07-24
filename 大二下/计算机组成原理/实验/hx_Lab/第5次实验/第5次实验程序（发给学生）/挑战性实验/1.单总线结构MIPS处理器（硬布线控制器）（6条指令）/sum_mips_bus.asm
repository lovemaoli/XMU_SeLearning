#MIPS程序  求累加和                                      	#求累加和：1+2+……+n，n的值为10（可以改变），累加和的结果存放到地址为1024的数据存储器中

main:	
	addi $s0,$zero,10                    # n=10 -> s0                              
	addi $s1,$zero,1               	#        1 -> s1              
	addi $s2,$zero,1               	#        1 -> s2
	addi $s3,$zero,0              	#        0 -> s3           
loop:
	add $s3,$s3,$s1                 	# s3+s1 -> s3                       
	beq $s1,$s0,finish              	# 如果s1=s0，则转finish       
	add $s1,$s1,$s2                  	# s1+s2 -> s1     
	beq $zero,$zero,loop              # goto loop
finish:
	sw $s3,1024($zero)                	# s3 存到地址为0的存储单元中
end:
	beq $zero,$zero,end               # goto end