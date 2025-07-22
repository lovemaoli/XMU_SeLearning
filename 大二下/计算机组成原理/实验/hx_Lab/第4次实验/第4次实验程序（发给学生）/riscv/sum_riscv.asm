# RISC-V计算累加和程序           sum_riscv.asm               result=1+2+...+n               
# 结果result存放在地址为0的数据存储器中

main:
                ori a3,zero,10		# a3=10=n
	ori a5, zero, 1     		# a5=1          
	ori a2, zero, 1     		# a2=1        
                ori a4, zero, 0                          # a4=0          
loop:
	add a4, a4, a5     		# a4+a5  ->   a4       
	beq a5, a3, finish  		# 判断a5=a3？          若a5=a3=n，则跳出循环
    	add a5, a5, a2     		# a5+a2 -> a5           
    	jal zero, loop		# 无条件跳转到loop执行
finish:
	sw a4, 0(zero)    		# a4 -> (0)                  将累加结果result保存到存储器中
end:
	jal zero, end		# 无条件跳转到end执行
