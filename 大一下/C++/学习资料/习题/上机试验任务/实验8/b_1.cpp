#include <iostream>
using namespace std;
const int MAX_SIZE = 100;

class A {
protected:
	int list[MAX_SIZE];
	int size;
public:
	A() {
		size = 0;
		memset(list, '\0', MAX_SIZE);
	}

	~A() {
		size = 0;
		memset(list, '\0', MAX_SIZE);
	}

	A(A& a) {
		size = a.size;
		for (int i = 0; i < a.size; i++)
			list[i] = a.list[i];
	}

	A(int array[]) {
		size = 0;
		if (sizeof(array) / 4 > MAX_SIZE)
		{
			cout << "下标越界！" << endl;
			exit(-1);
		}

		for (int i = 0; i < sizeof(array) / 4; i++)
		{
			list[i] = array[i];
			size++;
		}
	}
	void input()
	{
		cout << "输入个数：" << endl;
		cin >> size;
		if (size > MAX_SIZE)
		{
			cout << "越界！";
			exit(-1);
		}
		cout << "输入元素：" << endl;
		for (int i = 0; i < size; i++)
		{
			cin >> list[i];
		}
		cout << endl;
	}

	void output() {
		cout << "所有元素为：" << endl;
		for (int i = 0; i < size; i++)
			cout << list[i] << " ";
		cout << endl;
	}

	int get_size() { return size; }
};

//class B 用于实现排序
class B :virtual public A {
public:
	void sort() {
		for (int i = 0; i < get_size() - 1; i++)
			for (int j = 0; j < get_size() - 1 - i; j++)
			{
				int temp;
				if (list[j] > list[j + 1])
				{
					temp = list[j + 1];
					list[j + 1] = list[j];
					list[j] = temp;
				}
			}
	}

};

class C :virtual public A {
public:
	double average() {
		double aver = 0;
		double size_d = (double)size;
		for (int i = 0; i < size; i++)
		{
			aver += (1 / size_d) * list[i];
		}
		return aver;
	}
};


class D :public C, public B {
};


int main() {
	D d;
	d.input();
	d.output();
	d.sort();
	cout << "排序后为：" << endl;
	d.output();
	cout<<"平均值为：" << d.average() << endl;
	return 0;
}