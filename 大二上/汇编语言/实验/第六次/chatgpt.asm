; 定义要排序的数组
array:     db 7, 5, 3, 2, 6, 9, 1, 8, 4, 0

; 定义函数，实现从小到大排序
bubble_sort_asc:
    ; 定义局部变量
    ; i 和 j 分别用于遍历数组中的元素
    ; temp 用于临时存储元素
    push ebp
    mov ebp, esp
    sub esp, 12
    mov [ebp-4], 0
    mov [ebp-8], 0
    mov [ebp-12], 0

.loop:
    ; 获取数组的长度
    mov eax, 10
    cmp [ebp-4], eax
    jge .done

    ; 对每个元素进行比较
    mov [ebp-8], 0
    mov [ebp-12], 0

.inner_loop:
    ; 获取数组的长度
    mov eax, 10
    cmp [ebp-8], eax
    jge .next

    ; 获取两个元素并比较
    mov edx, [ebp-8]
    mov edx, [array+edx]
    mov eax, [ebp-12]
    mov eax, [array+eax]
    cmp edx, eax
    jg .swap

    ; 如果没有发生交换，则继续比较下一个元素
    inc [ebp-12]
    inc [ebp-8]
    jmp .inner_loop

.swap:
    ; 交换两个元素
    mov edx, [ebp-8]
    mov eax, [ebp-12]
    mov ecx, [array+edx]
    mov [array+edx], [array+eax]
    mov [array+eax], ecx

    ; 继续比较下一个元素
    inc [ebp-12]
    inc [ebp-8]
    jmp .inner_loop

.next:
    ; 比较下一轮
    inc [ebp-4]
    jmp .loop

.done:
    ; 输出排序后的数组
    mov edx, OFFSET array
    mov ecx, 10
    mov ebx, 1
    mov eax, 4
    int 0x80
    ; 返回排序后的数组
    mov eax, array
    leave
    ret
    jmp .loop

.done:
    ; 输出排序后的数组
    mov edx, OFFSET array
    mov ecx, 10
    mov ebx, 1
    mov eax, 4
    int 0x80
    ; 返回排序后的数组
    mov eax, array
    leave
    ret

; 定义函数，实现从大到小排序
bubble_sort_desc:
    ; 定义局部变量
    ; i 和 j 分别用于遍历数组中的元素
    ; temp 用于临时存储元素
    push ebp
    mov ebp, esp
    sub esp, 12
    mov [ebp-4], 0
    mov [ebp-8], 0
    mov [ebp-12], 0

.loop:
    ; 获取数组的长度
    mov eax, 10
    cmp [ebp-4], eax
    jge .done
    ; 对每个元素进行比较
    mov [ebp-8], 0
    mov [ebp-12], 0
.inner_loop:
    ; 获取数组的长度
    mov eax, 10
    cmp [ebp-8], eax
    jge .next
    ; 获取两个元素并比较
    mov edx, [ebp-8]
    mov edx, [array+edx]
    mov eax, [ebp-12]
    mov eax, [array+eax]
    cmp edx, eax
    jl .swap
    ; 如果没有发生交换，则继续比较下一个元素
    inc [ebp-12]
    inc [ebp-8]
    jmp .inner_loop
.swap:
    ; 交换两个元素
    mov edx, [ebp-8]
    mov eax, [ebp-12]
    mov ecx, [array+edx]
    mov [array+edx], [array+eax]
    mov [array+eax], ecx
    ; 继续比较下一个元素
    inc [ebp-12]
    inc [ebp-8]
    jmp .inner_loop
.next:
    ; 比较下一轮
    inc [ebp-4]
    jmp .loop

.done:
    ; 输出排序后的数组
    mov edx, OFFSET array
    mov ecx, 10
    mov ebx, 1
    mov eax, 4
    int 0x80
    ; 返回排序后的数组
    mov eax, array
    leave
    ret
