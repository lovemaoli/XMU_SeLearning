#include<iostream>
#include<string>
using namespace std;
template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;
	Node(){}
	~Node(){}
};
template<typename T>
class LinkList
{
public:
	LinkList();                //构造函数
	~LinkList();               //析构函数
	void printList()const;     //打印列表
	void append(const T data); //后插一个数据
	void prepend(const T data);//前插一个数据 
	void removeFront();        //删除第一个元素
	void insert(const T data); //按顺序插入
	bool remove(const T data); //删除特定数据
	bool find(const T data);   //找到特定数据
	bool isEmpty()const;       //判断是否为空
	T getFirst()const;         //获取第一个数据
	T getLast()const;          //获取最后一个数据

	Node<T>* head;
	Node<T>* tail;
};
template<typename T>    //构造函数
LinkList<T>::LinkList()
{
	head = tail = NULL;
}

template<typename T>    //析构函数 
LinkList<T>::~LinkList()
{
	Node<T>* currentNode = head;
	while (currentNode != NULL)
	{
		Node<T>* temp = currentNode->next;
		delete currentNode;
		currentNode = temp;
	}
} 

template<typename T>  //打印链表 
void LinkList<T>::printList()const
{
	Node<T>* temp = head;   
	while(temp!=nullptr)
	{
		cout << temp->data << endl;
		temp = temp->next;
	}
} 

template<typename T>  //后插一个数据
void LinkList<T>::append(const T data)
{
	Node<T>* temp = new Node<T>;
	temp->data = data;
	temp->next = NULL;
	if (head == NULL)
	{
		head = tail = temp;  
	}
	else
	{
		this->tail->next = temp;
		this->tail = temp;
	}
}

template<typename T>  ///前插一个数据  
void LinkList<T>::prepend(const T data)  
{	
    Node<T>* temp = new Node<T>;
	temp->data = data;
	if (head == NULL)
	{
		temp->next = NULL;
		head = tail = temp;
	}
	else
	{
		temp->next = this->head; 
		this->head = temp;
	}
}

template<typename T>  //删除第一个元素  
void LinkList<T>::removeFront()
{
	if (head == NULL)
	{
		cout << "List is empty";
		return;
	}
	Node<T>* temp = this->head;
	this->head = temp->next;
	free(temp);
}

template<typename T> //按顺序插入  
void LinkList<T>::insert(const T data)
{
	Node<T>* temp = new Node<T>;
	Node<T>* p = this->head;
	temp->data = data;
	if (head == NULL)   //若链表为空，插入节点作为头结点
	{
		temp->next = NULL;
		head = tail = temp;
		return;
	}
	else if (data < p->data)  //插入节点小于头结点，则该节点作为头结点
	{
		temp->next = head;
		head = temp;
	}
	else
	{
		while (p->next != NULL)
		{
			if (data < p->next->data)  //不断后移，直到下一个节点比插入节点大
				break;
			p = p->next;    
		}
		temp->next = p->next;
		p->next = temp;   //插入节点
	}
}

template<typename T>  //删除特定数据 
bool LinkList<T>::remove(const T data)
{
	if (head == NULL)
	{
		cout << "List is empty\n";
		return false;
	}

	Node<T>* p = head;
	Node<T>* front;
	while (p->next != nullptr)//下一个节点不为空，表示还可以删除
	{
		front = p;
		p = p->next;
		if (p->data == data)
		{
			front->next = p->next;
			p->next = NULL;
			cout << data << " was successfully removed from the list\n";
			delete p;
			return true;
		}
	}
	cout << data << " was not found in the list when attempting to remove\n";
	return false;
}

template<typename T>  //找到特定数据
bool LinkList<T>::find(const T data)  
{
	Node<T>* p = head;
	if (head == NULL)
	{
		cout << "List is empty\n";
		return false;
	}
	while (p->next != nullptr)
	{
		if (p->data == data)
		{
			cout << data << " was found in the list\n";
			return true;
		}
		p = p->next;  //要先判断当前节点的数据是否为所需查找的节点，再将p往后移
		              //不然容易发生头节点查找不到的情况
	}
	cout << data << " was not found in the list\n";
	return false;
}

template<typename T>   //判断是否为空
bool LinkList<T>::isEmpty()const
{
	if (head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>  //获取第一个数据
T LinkList<T>::getFirst()const
{
	T first_data;
	first_data = head->data;
	return first_data;
}

template<typename T>   //获取最后一个数据
T LinkList<T>::getLast()const
{
	T last_data;
	last_data = tail->data;
	return last_data;
}
int main(){
	//整数链表
	cout << "整数链表" << endl; 
	LinkList<int> intlist;
	intlist.insert(7); //按大小顺序插入数据 
	intlist.insert(3);
	intlist.insert(5);
	intlist.insert(1);
	intlist.printList();
	intlist.remove(3); //删除数据
	intlist.find(5);   //寻找数据 
	//字符链表
	cout << "字符链表" << endl; 
	LinkList<char> charlist;
	charlist.append('h'); //从尾巴插入数据 
	charlist.append('x');
	charlist.append('n');
	charlist.append('b');
	charlist.printList();
	charlist.remove('H'); //删除数据
	charlist.find('0');   //寻找数据 
	//浮点数链表
	cout << "浮点数链表" << endl; 
	LinkList<float> floatlist;
	floatlist.prepend(2002); //从头插入数据 
	floatlist.prepend(520); //插入数据 
	floatlist.prepend(13.14);
	floatlist.printList();
	floatlist.remove(2002); //删除数据
	cout << "删除后：" << endl;
	floatlist.printList();
	floatlist.find(13.14);   //寻找数据 
	return 0;
} 
