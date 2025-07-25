#include <iostream>
#include <cstdlib>
using namespace std;
const int MAX_OF_STACK;

struct node
{
	int data;
	node* next;
};
class LinearList
{
	node* head;
public:
	LinearList()
	{
		head = NULL;
	}

	LinearList(const LinearList& s)
	{
		node* p;
		p = s.head;
		head = NULL;	//重置head
		for (int i = 0; i < s.length(); i++)
		{
			insert(head,p->data, length());
			p = p->next;
		}
	}

	~LinearList()
	{
		node* p;
		p = head;
		head = NULL;
		if (p != NULL)
			delete[]p;
	}

	bool insert(node* head,int x, int pos);
	bool remove(node* head,int& x, int pos);
	int element(int pos)const;
	int search(int x)const;
	int length()const;
};

class stack :public LinearList
{
	node* bottom;
	int top;
public:
	stack(){
		bottom = new node;
		top = 0;
	}

	~stack(){
		node* p;
		for (p = bottom->next; p->next != NULL; p = p->next)
		{
			delete bottom;
			bottom = p;
		}
		bottom = p;
		delete bottom;
		bottom = nullptr;
		p = nullptr;
	}
	void push(int i);
	void pop();
};

void stack::push(int i){
	if (top < MAX_OF_STACK)
	{
		insert(bottom, i, top);
		top++;
	}

	else
	{
		cout << "overflow!" << endl;
		exit(-1);
	}
}

void stack::pop(){
	int x;
	if (top==0)
	{
		cout << "no index!";
		exit(-1);
	}
	else
	{
		remove(bottom, x, top);
		top--;
	}
}








bool LinearList::insert(node* head, int x, int pos)
{
	node* p1, * p2;
	p1 = head;

	if (head == NULL)return false;
	if (pos > length())return false;

	if (pos == 0)
	{
		p2 = new node;
		p2->data = x;
		p2->next = p1;
		head = p2;
	}
	else if (pos == length())
	{
		p2 = new node;
		p2->data = x;
		p2->next = NULL;
		for (int i = 0; i < pos - 1; i++, p1 = p1->next);
		p1->next = p2;
	}
	else
	{
		p2 = new node;
		for (int i = 0; i < pos; i++, p1 = p1->next);//将p1移动到要插入的节点的后一个节点
		p2->next = p1;//将p2指向该节点,重置p1
		p1 = head;
		for (int i = 0; i < pos - 1; i++, p1 = p1->next);
		p1->next = p2;
	}
	return true;
}

bool LinearList::remove(node * head,int& x, int pos)
{
	node* p1, * p2;
	if (head == NULL || pos > length())return false;

	if (pos == length())
	{
		p1 = head;
		for (int i = 0; i < pos - 1; i++, p1 = p1->next);
		for (int i = 0; i < pos - 2; i++, p2 = p2->next);
		p2->next = NULL;
		x = p1->data;
		delete p1;
	}
	else if (pos == 1)
	{
		p1 = head;
		p2 = p1->next;
		x = p1->data;
		delete p1;
		head = p2;
	}
	else
	{
		p1 = head;
		for (int i = 0; i < pos - 1; i++, p1 = p1->next);
		for (int i = 0; i < pos - 2; i++, p2 = p2->next);
		p2->next = p1->next;
		x = p1->data;
		delete p1;
	}
	return true;
}

int LinearList::element(int pos)const
{
	node* p1;
	p1 = head;
	for (int i = 0; i < pos - 1; i++, p1 = p1->next);
	return p1->data;
}

int LinearList::search(int x)const
{
	node* p;
	int pos = 0;
	for (p = head; p->next != NULL; p = p->next)
	{
		pos++;
		if (p->data == x)return pos;
	}
	return 0;
}

int LinearList::length()const
{
	int size = 1;
	for (node* p = head; p->next != NULL; p = p->next, size++);
	return size;
}