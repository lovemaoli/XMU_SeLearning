# 计算费波那契数列         fib_armv7.s    
# n=10    可以改变，保存在0x100存储单元中
# 计算好的n+1个数（0、1、1、2、3、5、8、13、21、34、55......           0、1、1、2、3、5、8、0dh、15h、22h、37h……      ）   
# 保存在0x200、0x204、0x208、...的存储单元中

.global _start
_start:
.org 0
	ldr r10,=num
	ldr r11,=result
                ldr r2,[r10]
	mov r1,#0
	add r12,r11,#0
	str r1,[r12]
	mov r1,#1
	add r12,r11,#4
	str r1,[r12]
	add r12,r11,#8
	str r1,[r12]
	mov r3,#2
	mov r4,#1
	mov r5,#1
loop:
	add r6,r4,r5
	mov r4,r5 
	mov r5,r6
	add r3,r3,#1
	add r7,r3,r3
	add r0,r7,r7
	add r0,r0,r11
	str r6,[r0]
	cmp r2,r3
	beq stop
	b loop
stop:
	b stop

.org 0x100
num: 
	.word 10
.org 0x200
result: 
	.word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 



	