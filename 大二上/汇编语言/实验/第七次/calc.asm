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
; 定义常量
ten      db   10
max      dd   10000

.code
; 定义函数: 计算数的每位数的N次幂之和
calculate_self_powers:
    push ebp        ; 保存帧指针
    mov ebp, esp    ; 将堆栈指针设置为帧指针

    ; 参数:
    ;  - [ebp+8] : 数的地址
    ;  - [ebp+12] : 数的位数
    ;
    ; 返回值:
    ;  - eax : 每位数的N次幂之和
    ;
    ; 寄存器使用:
    ;  - ebx : 循环计数器
    ;  - ecx : 当前数字
    ;  - edx : 当前数字的N次幂
    ;  - eax : 每位数的N次幂之和

    xor eax, eax    ; 将 eax 设置为 0
    mov ebx, [ebp+12]   ; 将 ebx 设置为数的位数
    mov edx, 1      ; 将 edx 设置为 1 (当前数字的0次幂)

calculate_self_powers_loop:
    cmp ebx, 0      ; 如果 ebx = 0，则退出循环
    je calculate_self_powers_done

    mov ecx, [ebp+8] ; 将 ecx 设置为数的地址
    add ecx, ebx    ; 将 ecx 设置为当前数字的地址
    dec ebx         ; ebx = ebx - 1
    mov cl, [ecx]   ; 将当前数字存储在 cl 中
    xor edx, edx    ; 将 edx 设置为 0
    mov dl, cl      ; 将 dl 设置为当前数字
    mov eax, 1      ; 将 eax 设置为 1 (当前数字的1次幂)

calculate_self_powers_exponent_loop:
    dec ecx ; ecx = ecx - 1
    cmp ecx, ebp ; 如果 ecx = ebp，则退出循环
    je calculate_self_powers_add
    mul dl          ; edx = edx * dl
    jmp calculate_self_powers_exponent_loop

calculate_self_powers_add:
    add eax, edx ; eax = eax + edx
    jmp calculate_self_powers_loop

calculate_self_powers_done:
    pop ebp ; 恢复帧指针
    ret ; 返回

; 定义函数: 输出数
print_number:
    push ebp ; 保存帧指针
    mov ebp, esp ; 将堆栈指针设置为帧指针
    ; 参数:
    ;  - [ebp+8] : 数的地址
    ;  - [ebp+12] : 数的位数
    ;
    ; 寄存器使用:
    ;  - ebx : 循环计数器
    ;  - ecx : 当前数字
    ;  - edx : 临时变量
    ;  - eax : 临时变量

    mov ebx, [ebp+12]   ; 将 ebx 设置为数的位数

print_number_loop:
    cmp ebx, 0 ; 如果 ebx = 0，则退出循环
    je print_number_done
    mov ecx, [ebp+8] ; 将 ecx 设置为数的地址
    add ecx, ebx    ; 将 ecx 设置为当前数字的地址
    dec ebx         ; ebx = ebx - 1
    mov cl, [ecx]   ; 将当前数字存储在 cl 中
    add cl, '0'     ; 将 cl 转换为 ASCII 码
    mov ah, 0Eh    ; 设置 ah 为 0x0E，以便使用 BIOS 函数
    mov al, cl      ; 将要输出的字符存储在 al 中
    int 10h        ; 调用 BIOS 函数输出字符
    jmp print_number_loop

print_number_done:
    pop ebp ; 恢复帧指针
    ret ; 返回


main proc ;main过程
    ; 设置循环计数器
    mov ebx, 10
    ; 循环枚举数
loop1:
    cmp ebx, max ; 如果 ebx > max，则退出循环
    jg loop_done
    ; 计算数的每位数的N次幂之和
    push ebx        ; 将数压入堆栈
    call calculate_self_powers
    ; 如果数的每位数的N次幂之和 = 数本身，则输出数
    cmp eax, ebx    ; 如果 eax = ebx，则输出数
    je print_number
    add esp, 4      ; 恢复堆栈
    inc ebx         ; ebx = ebx + 1
    jmp loop1
loop_done:
    ; 退出程序
    mov eax, 1h
    xor ebx, ebx
    int 80h
main endp
end main