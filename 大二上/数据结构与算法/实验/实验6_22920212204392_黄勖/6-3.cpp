#include <stdio.h>
#include <stdlib.h>

void fixtree(int* tree, int treeSize, int index) {
	// 左子节点的索引
	int left = index * 2 + 1;
	// 右子节点的索引
	int right = index * 2 + 2;
	// 最小值的索引，初始化为当前节点
	int min = index;
	// 如果左子节点存在，并且比当前最小值小，更新最小值的索引
	if (left < treeSize && tree[left] < tree[min]) {
		min = left;
	}
	// 如果右子节点存在，并且比当前最小值小，更新最小值的索引
	if (right < treeSize && tree[right] < tree[min]) {
		min = right;
	}
	// 如果最小值的索引发生变化，说明子节点中有比堆顶元素更小的
	if (min != index) {
		// 交换顶元素和最小值
		int temp = tree[index];
		tree[index] = tree[min];
		tree[min] = temp;
		fixtree(tree, treeSize, min);
	}
}

// 建立树 
void buildtree(int* tree, int treeSize) {
	// 从最后一个非叶子节点开始，向前依次处理 
	for (int i = treeSize / 2 - 1; i >= 0; i--) {
		fixtree(tree, treeSize, i);
	}
}

// 树形选择排序
void treeSelectSort(int* array, int size) {
	// 建立树 
	buildtree(array, size);
	// 循环取出顶元素，并将树大小减 1
	for (int i = size - 1; i >= 0; i--) {
		// 将顶元素与数组最后一个元素交换
		int temp = array[i];
		array[i] = array[0];
		array[0] = temp;
		// 将树的大小减 1
		size--;
		// 继续处理树 
		fixtree(array, size, 0);
	}
}

int main(void) {
	int array[] = {5, 2, 9, 4, 7, 6, 1, 3, 8};
	int size = sizeof(array) / sizeof(int);
	// 调用树形选择排序算法
	treeSelectSort(array, size);
	// 输出排序后的结果
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	return 0;
}
