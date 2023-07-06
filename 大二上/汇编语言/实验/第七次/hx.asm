.386
.model flat, stdcall 
option casemap :none 
include C:\masm32\include\windows.inc 
include C:\masm32\include\masm32.inc
include C:\masm32\include\kernel32.inc 
includelib C:\masm32\lib\kernel32.lib 
includelib C:\masm32\lib\masm32.lib
.stack 4096
.data
	str1 byte "水仙花数共有",0
	str2 byte "四叶玫瑰数共有",0
	str3 byte "个: ",0
	endl byte 0Dh, 0Ah, 0
	sxhs dword 10 dup(0)
	symgs dword 10 dup(0)
	div10 dword 10
	temp byte 6 dup(0)
	count1 byte 2 dup(0)
	count2 byte 2 dup(0)
.code 
;  ml -c -coff hx.asm
;  link -subsystem:console hx.obj
main proc

	call sxh
	call symg
	ret

main endp

sxh proc
	invoke StdOut, addr str1
	mov eax,98h
	xor ecx,ecx
	mov esi,eax
	mov dword ptr[sxhs],0
L1:
	mov eax,esi
	inc eax
	mov esi,eax
	cmp eax,3E7h
	ja L2
	call issxh
    test al,al
	je L1
	mov eax,esi
	mov dword ptr[sxhs+4*ecx],eax
	inc ecx
	jmp L1
L2:
	mov byte ptr[count1],cl
	add byte ptr[count1],30h
	push ecx
	invoke StdOut, addr count1
	invoke StdOut, addr str3
	pop ecx
	lea ebx,dword ptr[sxhs]
L4:
	push ecx
	mov eax,dword ptr[ebx]
	mov dword ptr[temp],eax
	call dw2str
	invoke StdOut, addr temp
	add ebx,4h
	pop ecx
	loop L4
	invoke StdOut, addr endl
	ret
sxh endp

symg proc
	invoke StdOut, addr str2
	mov eax,3E7h
	xor ecx,ecx
	mov esi,eax
	mov dword ptr[symgs],0
L1:
	mov eax,esi
	inc eax
	mov esi,eax
	cmp eax,270Fh
	ja L2
	call issymg
    test al,al
	je L1
	mov eax,esi
	mov dword ptr[symgs+4*ecx],eax
	inc ecx
	jmp L1
L2:
	mov byte ptr[count2],cl
	add byte ptr[count2],30h
	push ecx
	invoke StdOut, addr count2
	invoke StdOut, addr str3
	pop ecx
	lea ebx,dword ptr[symgs]
L4:
	push ecx
	mov eax,dword ptr[ebx]
	mov dword ptr[temp],eax
	call dw2str
	invoke StdOut, addr temp
	add ebx,4h
	pop ecx
	loop L4
	ret
symg endp

dw2str proc
	pushad
	lea ebx,[temp]
	mov eax,dword ptr[ebx]
	xor ecx,ecx
L1:
	xor edx,edx
	div div10
	add edx,30h
	push edx
	inc ecx
	cmp eax,0
	jne L1

L2:
	pop eax
	mov byte ptr[ebx],al
	inc ebx
	loop L2

	mov byte ptr[ebx],20h
	popad
	ret
dw2str endp

issxh proc
	pushad
	push eax
	xor esi,esi
	xor edx,edx
L1:
	xor edx,edx
	div div10
	push eax
	mov eax,edx
	mov ecx,edx
	mul ecx
	mul ecx
	xchg eax,edx
	add esi,edx
	pop eax
	cmp eax,0
	jne L1
    pop eax
	cmp esi,eax
	popad
	mov eax,1
	je L2
	mov eax,0
L2:
	ret
issxh endp

issymg proc
	pushad
	push eax
	xor esi,esi
	xor edx,edx
L1:
	xor edx,edx
	div div10
	push eax
	mov eax,edx
	mov ecx,edx
	mul ecx
	mul ecx
	mul ecx
	xchg eax,edx
	add esi,edx
	pop eax
	cmp eax,0
	jne L1
    pop eax
	cmp esi,eax
	popad
	mov eax,1
	je L2
	mov eax,0
L2:
	ret
issymg endp

end main
