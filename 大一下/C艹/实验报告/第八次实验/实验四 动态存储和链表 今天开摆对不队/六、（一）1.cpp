#include <iostream>
using namespace std;

class List {
	public:
		List() {
			create_List();
		}
		~List() {
			clear();
		}
		void create_List();
		void insert(const int& d);
		void print();
		void delete_between(const int& mink,const int& maxk);
	private:
		//节点结构
		struct Node {
			int data;
			Node * next;
			Node(const int& d):data(d),next(NULL) {}
		};
		Node * head;//头节点
		//清理链表函数
		void clear() {
			Node * p = head;
			//从头节点开始循环删除
			while(p) {
				Node * q = p->next;
				delete p;
				p = q;
			}
		}
		//查找数据d的上一个节点位置的函数
		//为了方便后面删除操作
		Node* find(const int& d) {
			Node * p = head;
			for(; p; p=p->next) {
				if(p->next->data==d)
					break;
			}
			return p;
		}
};

//创建头结点
void List::create_List() {
	head = new Node(0);
}
//从头插入一个节点
void List::insert(const int& d) {
	Node *p = new Node(d);
	p->next = head->next;
	head->next = p;
}
//打印函数
void List::print() {
	for(Node * p = head->next; p; p=p->next) {
		cout << p->data << endl;
	}
	cout << endl;
}
//删除有序表中所有其值大于 mink 且小于maxk的数据元素
void List::delete_between(const int& mink,const int& maxk) {
	for(Node * p = head->next; p; p=p->next) {
		if(p->next->data <= mink) {
			continue;
		}
		for(Node * q = p; q; q=q->next) {
			if(q->data < maxk) {
				continue;
			}
			p->next = q;
			break;
		}
		break;
	}
}

int main(int argc, const char * argv[]) {
	// insert code here...
	List list;
	list.insert(30);
	list.insert(25);
	list.insert(20);
	list.insert(15);
	list.insert(10);
	cout << "删除前:" << endl;
	list.print();
	list.delete_between(15,25);
	cout << "删除后:" << endl;
	list.print();
	return 0;
}
