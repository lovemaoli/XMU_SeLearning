#MIPS程序    冒泡法排序（降序排列，从大到小）  +   累加和程序        

#测试   lw、sw、beq、bne、add、slt、addi、syscall、j          9条指令                        

#先将10个数（8、1、5、2、7、9、6、4、3、10）存放到地址为1024开始的数据存储器中，然后对这10个数进行排序。

#求累加和：1+2+……+n，n的值为10（可以改变），累加和的结果存放到地址为2048的数据存储器中


 .text
main:
 	addi $s0,$zero,8                        #第1个数=8（可以修改）保存到(1024)
 	sw $s0,1024($zero)
 	addi $s0,$zero,1                        #第2个数=1（可以修改）保存到(1028)
 	sw $s0,1028($zero)
 	addi $s0,$zero,5                        #第3个数=5（可以修改）保存到(1032)
 	sw $s0,1032($zero)
 	addi $s0,$zero,2                        #第4个数=2（可以修改）保存到(1036)
	sw $s0,1036($zero)
 	addi $s0,$zero,7                        #第5个数=7（可以修改）保存到(1040)
	sw $s0,1040($zero)
 	addi $s0,$zero,9                        #第6个数=9（可以修改）保存到(1044)
 	sw $s0,1044($zero)
 	addi $s0,$zero,6                        #第7个数=6（可以修改）保存到(1048)
 	sw $s0,1048($zero)
 	addi $s0,$zero,4                        #第8个数=4（可以修改）保存到(1052)
 	sw $s0,1052($zero)
 	addi $s0,$zero,3                        #第9个数=3（可以修改）保存到(1056)
 	sw $s0,1056($zero)
 	addi $s0,$zero,10                      #第10个数=10（可以修改）保存到(1060)
 	sw $s0,1060($zero)
 	addi $s0,$zero,0          	 #$s0=0                      排序区间开始地址-1024
 	addi $s1,$zero,36  		 #$s1=36=10*4-4      排序区间结束地址-1024         10个数        如果不是20个数，这里要修改，例如20个数，这里修改为76
sort_loop:
 	lw $s3,1024($s0)                     	#$s3=($s0)
	lw $s4,1024($s1)                	#$s4=($s1)
 	slt $t0,$s3,$s4                	#如果$s3<$s4，则置$t0=1；否则，置$t0=0
 	beq $t0,$zero,sort_next   	#如果$t0=0，则转sort_nent       降序排序         从大到小
 	sw $s3,1024($s1)                	#交换($s0)和($s1)
	sw $s4,1024($s0)                   	#交换($s0)和($s1)
sort_next:
	addi $s1,$s1,-4                        # $s1-4 -> $s1
 	bne $s0,$s1,sort_loop             #如果$s0不等于$s1，则转sort_loop
  	addi $s0,$s0,4                         #$s0+4 -> $s0
	addi $s1,$zero,36                   	#$s1=36=10*4-4   排序区间结束地址-1024                10个数             如果不是10个数，这里要修改，例如20个数，这里修改为76

	bne $s0,$s1,sort_loop 	#如果$s0不等于$s1，则转sort_loop


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
	sw $s3,2048($zero)                	# s3 存到地址为0的存储单元中

	addi   $v0,$zero,10         	# 10号系统调用
	syscall                  		# 程序退出
