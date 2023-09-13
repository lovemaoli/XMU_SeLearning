#测试   lw、sw、beq、slt、addi、add、j  等7条指令的程序
#MIPS程序    sort1_mips_bus.asm    排序（降序排列，从大到小）和求累加和程序                       
#先将5个数（4、1、5、2、3）存放到地址为1024开始的数据存储器中（100存储单元），然后对这5个数进行排序。
#然后求1+2+...+10=55=37H    结果保存到1088开始的存储单元中（110存储单元）
main:
 	addi $s0,$zero,4                        #第1个数=4（可以修改）保存到(1024+0)
 	sw $s0,1024($zero)
 	addi $s0,$zero,1                        #第2个数=1（可以修改）保存到(1024+4)
 	sw $s0,1028($zero)
 	addi $s0,$zero,5                        #第3个数=5（可以修改）保存到(1024+8)
 	sw $s0,1032($zero)
 	addi $s0,$zero,2                        #第4个数=2（可以修改）保存到(1024+12)
	sw $s0,1036($zero)
 	addi $s0,$zero,3                        #第5个数=3（可以修改）保存到(1024+16)
	sw $s0,1040($zero)
 	addi $s0,$zero,1024                  #$s0=1024                              排序区间开始地址
 	addi $s1,$zero,1040  	  #$s1=1040=1024+5*4-4       排序区间结束地址         5个数        
sort_loop:
 	lw $s3,0($s0)                     	  #$s3=($s0)
	lw $s4,0($s1)                	  #$s4=($s1)
 	slt $t0,$s3,$s4                	  #如果$s3<$s4，则置$t0=1；否则，置$t0=0        降序排序         从大到小
 	beq $t0,$zero,sort_next   	  #如果$t0=0，则转sort_nent       
 	sw $s3,0($s1)                	  #交换($s0)和($s1)
	sw $s4,0($s0)                   	  #交换($s0)和($s1)
sort_next:
	addi $s1,$s1,-4                          #$s1-4 -> $s1
 	beq $s0,$s1,loop1                     #如果$s0=$s1，则转loop1   
 	beq $zero,$zero,sort_loop        #转sort_loop
loop1:
  	addi $s0,$s0,4                           #$s0+4 -> $s0
	addi $s1,$zero,1040                 #$s1=1040=1024+5*4-4   排序区间结束地址                5个数            
 	beq $s0,$s1,loop2                    #如果$s0=$s1，则转loop2
 	beq $zero,$zero,sort_loop       #转sort_loop
loop2:
	addi $s0,$zero,10                    # n=10 -> s0                              
	addi $s1,$zero,1               	#        1 -> s1              
	addi $s2,$zero,1               	#        1 -> s2
	addi $s3,$zero,0              	#        0 -> s3           
loop3:
	add $s3,$s3,$s1                 	# s3+s1 -> s3                       
	beq $s1,$s0,loop4              	# 如果s1=s0，则转loop4       
	add $s1,$s1,$s2                  	# s1+s2 -> s1     
	j loop3
loop4:
	sw $s3,1088($zero)                	# s3 存到地址为1088的存储单元中
finish:      
	j finish



