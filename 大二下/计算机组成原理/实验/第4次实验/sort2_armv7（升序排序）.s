    @Author : 22920212204392 黄勖
    .syntax unified
    .arch armv7-a

    .global main
    .text

main:
    @ 将数组长度存储在r0中（值长度+1）
    ldr r0, =11

    @ 初始化循环计数器
    mov r1, #0

outer_loop:
    @ 循环计数器加1，并判断是否达到数组长度，如果达到则跳出外层循环
    add r1, r1, #1
    cmp r1, r0
    beq end_sort

    @ 内层循环计数器初始化，r3用于记录最后一次交换的位置
    mov r2, #0
    mov r3, #0

inner_loop:
    @ 计算数组索引，r4保存当前元素，r5保存下一个元素
    add r4, r2, #0
    add r5, r2, #1

    @ 计算数组索引对应的地址
    ldr r6, =arr
    add r6, r6, r4, lsl #2
    ldr r4, [r6]
    add r6, r6, #4
    ldr r5, [r6]

    @ 如果前一个元素比后一个元素大，则交换位置
    cmp r4, r5
    ble no_swap
    str r5, [r6, #-4]
    str r4, [r6]

    @ 记录最后一次交换的位置
    mov r3, r2

no_swap:
    @ 内层循环计数器加1，并判断是否达到数组长度-外层循环计数器-1
    add r2, r2, #1
    sub r6, r0, r1
    sub r6, r6, #1
    cmp r2, r6
    blo inner_loop

    @ 如果内层循环中没有交换位置，则说明已经排好序，跳出外层循环
    cmp r3, #0
    bne outer_loop

end_sort:
    @ 退出程序
    mov r7, #0
    mov r0, #1
    svc 0
    .data
    .align
arr:
    .word 8, 1, 5, 2, 7, 9, 6, 4, 3, 10
