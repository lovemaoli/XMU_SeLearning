.386 ;允许汇编80386处理器的非特权指令，禁用其后处理器引入的汇编指令
.model flat, stdcall ;.model用于初始化程序的内存模式
option casemap :none ;大小写敏感
include C:\masm32\include\windows.inc 
include C:\masm32\include\masm32.inc
include C:\masm32\include\kernel32.inc 
includelib C:\masm32\lib\kernel32.lib 
includelib C:\masm32\lib\masm32.lib ;函数的常量和链接库声明
.stack 4096 ;栈空间声明
.data
	str1 byte "Please input unsigned int number: ",0 ;提示输入数组(以空格分割)
	str2 byte "The result of bubble sort is: ",0 ;提示输出数组(以空格分割)
	inputstr byte 80 dup(0) ;存储输入的字符串
	pArray dword 15 dup(0) ;存储字符串转化成的各个数字
	outputstr byte 80 dup(0) ;存储输出的字符串
	const10 dword 10 ;常数10
	count dword 1 ;数组长度
	count2 dword 0 ;用于保存ecx
.code 

main proc ;main过程
	invoke StdOut,addr str1 ;输出提示
	invoke StdIn,addr inputstr,60 ;输入数组
	call strtonum ;输入字符串转化为数组
	call BubbleSort ;数组冒泡排序
	call numtostr ;排序后的数组重新转化为可输出的字符串
	invoke StdOut,addr str2 ;输出提示
	invoke StdOut,addr outputstr ;输出排序后数组
	invoke ExitProcess,0
main endp

strtonum proc uses esi eax ebx ecx ;输入字符串转化为数组
	mov esi,0
	mov ebx,0
	mov ecx,0 
L1:
	mov bl,[inputstr+esi] ;以esi为变址寄存器读取输入字符串
	cmp bl,32 ;判断是否读取到空格(ASCII码值为32)
	jne L2
	inc count 
	add ecx,4 ;是空格则count+1,同时ecx+4
	inc esi
	mov bl,[inputstr+esi] ;略过空格
L2:
	sub bl,48 ;字符转化为数字
	mov eax,[pArray+ecx] ;读取数字
	mul const10 ;eax值乘10
	add eax,ebx ;加上刚读取的数字
	mov [pArray+ecx],eax ;存回
	inc esi
	cmp [inputstr+esi],0 ;读取到串尾0停止
	jne L1
	ret
strtonum endp

BubbleSort proc uses eax ecx esi ;数组冒泡排序
	mov ecx,count
	dec ecx ;令ecx等于数组长度-1
L3: 
	push ecx ;入栈,保存外层ecx
	mov esi,0
L4:
	mov eax,[pArray+esi]
	cmp eax,[pArray+esi+4] ;比较数
	jae L5 
	xchg eax,[pArray+esi+4] 
	mov [pArray+esi],eax ;若前一个数比后一个小则交换
L5:
	add esi,4
	loop L4 ;内层循环
	pop ecx ;出栈,恢复外层ecx
	loop L3 ;外层循环
	ret
BubbleSort endp

numtostr proc ;排序后的数组重新转化为可输出的字符串
	mov ecx,count
	dec ecx
	mov esi,0
L10:
    add esi,4
	loop L10 ;使esi=4*(count-1),即偏移为最后一个数字
	mov edi,0
	mov edx,0
	mov ecx,count
L6:
	mov count2,ecx ;保存ecx
	mov eax,[pArray+esi] ;获取数字
	sub esi,4 ;移动到前一个数字
L7:
	div const10 ;除法指令,被除数为edx:eax,eax存商,edx存余数
	mov ecx,edx
	mov edx,0
	add ecx,48 ;数字转化为字符
	push ecx ;字符入栈
	inc edi 
	cmp eax,0
	jne L7
	push 32 ;商为0则入栈一个空格
	inc edi
	mov ecx,count2 ;恢复ecx
	loop L6

	mov ecx,edi ;循环次数为输出字符长度
	mov esi,0 
L8:
	pop eax ;循环出栈
	mov [outputstr+esi],al ;出栈字符保存到输出字符串中
	inc esi
	loop L8
	mov [outputstr+esi],0 ;补充串尾0
	ret
numtostr endp

end main

;  ml -c -coff bubble_sort.asm
;  link -subsystem:console bubble_sort.obj
;  bubble_sort
