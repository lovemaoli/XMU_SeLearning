#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <math.h>

using namespace std;

#define BLOCK_SIZE 2 // 每块大小为2k
#define TOTAL_BLOCKS 500 // 磁盘块总数

// Bitmap：0为空闲，1为占用
vector<int> diskBlocks(TOTAL_BLOCKS, 0);

struct File {
    int size; // 文件大小（kB）
    vector<int> blocks; // 分配的磁盘块号
};
map<string, File> fileTable;

//分配空闲块
vector<int> allocateBlocks(int fileSize) {
    int blocksNeeded = (fileSize + BLOCK_SIZE - 1) / BLOCK_SIZE; // 需要的块数
    vector<int> allocated;

    for (int i = 0; i < TOTAL_BLOCKS && blocksNeeded > 0; ++i) {
        if (diskBlocks[i] == 0) { // 找到空闲块
            diskBlocks[i] = 1;
            allocated.push_back(i);
            --blocksNeeded;
        }
    }

    if (blocksNeeded > 0) { // 如果空闲块不足，回滚
        for (int block : allocated) {
            diskBlocks[block] = 0;
        }
        allocated.clear();
    }

    return allocated;
}

// 释放块
void freeBlocks(const vector<int> &blocks) {
    for (int block : blocks) {
        diskBlocks[block] = 0;
    }
}

// 创建文件
bool createFile(const string &name, double size) {
    int useSize = (int) ceil(size);
    if (fileTable.find(name) != fileTable.end()) {
        cerr << "File " << name << " already exists!\n";
        return false;
    }

    vector<int> allocated = allocateBlocks(useSize);
    if (allocated.empty()) {
        cerr << "Not enough space for file " << name << "!\n";
        return false;
    }

    fileTable[name] = {useSize, allocated};
    return true;
}

// 删除文件
bool deleteFile(const string &name) {
    auto it = fileTable.find(name);
    if (it == fileTable.end()) {
        cerr << "File " << name << " not found!\n";
        return false;
    }

    freeBlocks(it->second.blocks);
    fileTable.erase(it);
    return true;
}

// 显示文件分配表
void displayFileTable() {
    cout << "\nFile Allocation Table:\n";
    cout << setw(10) << "File" << setw(10) << "Size(kB)" << " Blocks\n";
    for (const auto &entry : fileTable) {
        cout << setw(10) << entry.first << setw(10) << entry.second.size << " [";
        for (size_t i = 0; i < entry.second.blocks.size(); ++i) {
            cout << entry.second.blocks[i];
            if (i < entry.second.blocks.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
}

// 显示空闲块状态
void displayFreeBlocks() {
    cout << "\nFree Blocks:\n";
    for (int i = 0; i < TOTAL_BLOCKS; ++i) {
        if (diskBlocks[i] == 0) {
            cout << i << " ";
        }
    }
    cout << "\n";
}

int main() {
    srand(time(0));

    // (1) 随机生成 50 个文件并存储
    for (int i = 1; i <= 50; ++i) {
        int fileSize = 2 + rand() % 9; // 生成 2k-10k 的随机文件大小
        createFile(to_string(i) + ".txt", fileSize);
    }

    displayFileTable();
    displayFreeBlocks();

    // (2) 删除奇数编号文件
    for (int i = 1; i <= 50; i += 2) {
        deleteFile(to_string(i) + ".txt");
    }

    displayFileTable();
    displayFreeBlocks();

    // (3) 创建 5 个新文件
    createFile("A.txt", 7);
    createFile("B.txt", 5);
    createFile("C.txt", 2);
    createFile("D.txt", 9);
    createFile("E.txt", 3.5);

    displayFileTable();
    displayFreeBlocks();

    return 0;
}
