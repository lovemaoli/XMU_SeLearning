# MIPS设计实验1 冒泡排序 (从大到小) (10个数据随机，如：8、1、5、2、7、9、6、4、3、10) 
# @Author : 22920212204392 黄勖

main:
        # step 1 存数
        addi $s0,$zero,8                              # 8 -> s0 
        sw $s0,0($zero)                	        # 8 存到地址为0的存储单元中
        addi $s0,$zero,1                              # 1 -> s0 
        sw $s0,4($zero)                	        # 1 存到地址为4的存储单元中
        addi $s0,$zero,5                              # 5 -> s0 
        sw $s0,8($zero)                         # 5 存到地址为8的存储单元中
        addi $s0,$zero,2                              # 2 -> s0 
        sw $s0,12($zero)                	# 2 存到地址为12的存储单元中
        addi $s0,$zero,7                              # 7 -> s0 
        sw $s0,16($zero)                	# 7 存到地址为16的存储单元中
        addi $s0,$zero,9                              # 9-> s0 
        sw $s0,20($zero)                	# 9 存到地址为20的存储单元中
        addi $s0,$zero,6                              # 6 -> s0 
        sw $s0,24($zero)                	# 6 存到地址为24的存储单元中
        addi $s0,$zero,4                              # 4 -> s0 
        sw $s0,28($zero)                	# 4 存到地址为28的存储单元中
        addi $s0,$zero,3                              # 3 -> s0 
        sw $s0,32($zero)                	# 3 存到地址为32的存储单元中
        addi $s0,$zero,10                             # 10 -> s0 
        sw $s0,36($zero)                	# 10 存到地址为36的存储单元中

        # step 2 比较
        addi $s1,$zero,0                        #s1是loop1的循环变量
        addi $s2,$zero,0                        #s2是loop2的循环变量
        addi $t0,$zero,9                        #t0是外循环次数
loop1:
        addi $s2,$zero,0                        # 每次执行外层循环(loop1)都将内层循环(loop2)的循环变量置为0
loop2:
        addi $s0,$s2,0                                #获取第$s2个数(从第0个数开始)
        sll $s5,$s0,2                                   #左移两位,相当于乘4
        lw $s3,0($s5)
         
        addi $s0,$s2,1                               #获取第$s2+1个数
        sll $s6,$s0,2                                   #左移两位,相当于乘4
        lw $s4,0($s6) 
        
        slt $s7,$s3,$s4                                 # $s3>s4, 1->s7,否则0->s7
        beq $s7,$zero, skip                         # s3>s4,不交换,跳到skip
        sw $s4,0($s5)
        sw $s3,0($s6)
skip:
        addi $s2,$s2,1                                 # 内层循环变量自增，且判断是否还满足循环条件
        sub $s0,$t0,$s1
        bne $s2,$s0,loop2                          #继续内循环
        addi $s1,$s1,1                                 #外层循环变量自增，且判断是否还满足循环条件
        sub $s0,$t0,$s1
        bne $s0,$zero,loop1

finish:
       	addi   $v0,$zero,10         	# 10号系统调用
	syscall                  		# 程序退出
