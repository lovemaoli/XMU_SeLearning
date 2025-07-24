# RISCV程序 冒泡排序 (从小到大) (10个数据随机，如：8、1、5、2、7、9、6、4、3、10) 
# @Author : 22920212204392 黄勖

main:
        # step 1 存数
        ori s0,zero,10                             # n = 10
        sw s0,0(zero)         	                   # n 存到地址为0的存储单元中
        add t0,s0,zero                             # t0 是外循环次数,此处应等于 n-1
        ori s0,zero,-1
        add t0,t0,s0                               # 实现 t0=n-1

        ori s0,zero,8                              # 8 -> s0 
        sw s0,4(zero)                	# 8 存到地址为4的存储单元中
        ori s0,zero,1                              # 1 -> s0 
        sw s0,8(zero)                	# 1 存到地址为8的存储单元中
        ori s0,zero,5                              # 5 -> s0 
        sw s0,12(zero)                  # 5 存到地址为12的存储单元中
        ori s0,zero,2                              # 2 -> s0 
        sw s0,16(zero)                	# 2 存到地址为16的存储单元中
        ori s0,zero,7                              # 7 -> s0 
        sw s0,20(zero)                	# 7 存到地址为20的存储单元中
        ori s0,zero,9                              # 9 -> s0 
        sw s0,24(zero)                	# 9 存到地址为24的存储单元中
        ori s0,zero,6                              # 6 -> s0 
        sw s0,28(zero)                	# 6 存到地址为28的存储单元中
        ori s0,zero,4                              # 4 -> s0 
        sw s0,32(zero)                	# 4 存到地址为32的存储单元中
        ori s0,zero,3                              # 3 -> s0 
        sw s0,36(zero)                	# 3 存到地址为36的存储单元中
        ori s0,zero,10                             # 10 -> s0 
        sw s0,40(zero)                	# 10 存到地址为40的存储单元中

        # step 2 比较
        ori s1,zero,0                          #s1是loop1的循环变量
        ori s2,zero,0                          #s2是loop2的循环变量
       
        ori s9,zero,1                          #用于后面的循环变量自增1
        ori s10,zero,4                         #用于后面的地址s8加4
loop1:
        ori s8,zero,4                          #s8指向存储单元地址,每次从第一个数的地址4开始
        ori s2,zero,0                          #每次执行外层循环(loop1)都将内层循环(loop2)的循环变量置为0
loop2:
        add s5,s8,zero                         #获取第s8/4个数的地址,存入s5
        lw s3,0(s5)                            #获取第s8/4个数,存入s3

        add s8,s8,s10                          #获取下一个地址(s8每次+4)

        add s6,s8,zero                         #获取第s8/4+1个数的地址,存入s6
        lw s4,0(s6)                            #获取第s8/4+1个数,存入s4
        
        slt s7,s4,s3                                                       
        beq s7,zero, skip                      # s3>s4,交换,跳到skip
        sw s4,0(s5)
        sw s3,0(s6)
skip:
        add s2,s2,s9                           # 内层循环变量自增，且判断是否还满足循环条件
        add  s0,s1,s2                          # s0=s1+s2
        slt s7,t0,s0                           # t0>=s0,s7=0,否则s7=1
        beq s7,zero,loop2                      # 继续内循环
                    
        add s1,s1,s9                           # 外层循环变量自增，且判断是否还满足循环条件
        slt s7,t0,s1                           # t0>=s1,s7=0,否则s7=1
        beq s7,zero,loop1                      # 继续外循环

end:
        jal zero, end		# 无条件跳转到end执行
