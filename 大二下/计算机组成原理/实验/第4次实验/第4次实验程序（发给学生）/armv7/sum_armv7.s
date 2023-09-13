#ARMv7 汇编语言程序          求累加和     sum=1+2+3+......+n         sum_armv7.s
# 累加和个数n放在[0x100]单元中     可以改变
# 累加和结果sum放在[0x104]单元中

.global _start
_start:
.org 0
	ldr r4,=num                 // r4=0x100
	ldr r5,=result               // r5=0x104

	ldr r3,[r4]                     // 从[0x100]单元中读取数据，送r3
	mov r0,#1
    	mov r1,#0
sum:
    	add r1,r0
    	add r0,#1
    	cmp r0,r3
    	bgt end                        // 如果r0 > r3  则转 end
    	b sum		     // 转 sum
end:	
    	str r1,[r5]                      // 将r1 保存到 [0x104]单元中
stop:
	b stop                          // 转 stop

.org 0x100
num: 
	.word 10

result: 
	.word 0

	