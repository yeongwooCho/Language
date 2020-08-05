//Exception Handling
#include <iostream>
#include <string>
#include <cstring>
using namespace std;


class StackException {
	const string msg;
public:
	StackException(const string& msg);
	void print() const { cout << msg << endl; }
};
StackException::StackException(const string& _msg) : msg(_msg) {}


class CharStack {
private:
	int size;
	int top;
	char* s;
public:
	//size�� ����� �ƴѰ��, (0�� ��쵵 stack���ν� �ǹ̰� ����.)
	CharStack(int sz) { 
		if (sz <= 0) 
			throw StackException("Constructor Error : The Size is not positive!");
		top = 0; 
		s = new char[size = sz]; 
	}
	
	//destructor, copy constructor, and assignment operator
	~CharStack() { delete s; }
	/*
	int getSize() const { return size; }
	int getTop() const { return top; }
	char* getS() const { return s; }
	CharStack(const CharStack& copy) {
		//copy�� �̹� ���������� ���� ��ü�̱⿡ size�� ���� ���ܰ� �߻����� �ʴ´�.
		top = copy.getTop();
		s = new char[size = copy.getSize()];
		strcpy(s, copy.getS()); //
	}
	*/
	


	//top�� size ���� ũ�ų� ���� ���
	//size�� ũ��, top�� �����Ͱ� �� index
	void push(char c) { 
		if (size <= top) 
			throw StackException("PUSH Error : The stack is full!");
		s[top++] = c; 
	}

	//����ִ� stack�� pop�� ��� �Ҵ����� ���� �޸𸮿� ����
	char pop() { 
		if (top == 0) 
			throw StackException("POP Error : The stack is empty!");
		char r = s[--top]; 
		s[top] = '\0'; 
		return r; 
	}
	
	void print() const {
		for (int i = 0; i < top; i++) cout << s[i];
		cout << endl;
	}
};



int main() {
	//���� 1��
	cout << "------------����1��" << endl;
	try { CharStack stack(-1); } //error
	catch (const StackException& e) { e.print(); cout << endl; }


	//���� 2��
	cout << "------------����2��" << endl;
	try { 
		CharStack stack(3);
		stack.push('a'); stack.print();
		stack.push('b'); stack.print();
		stack.push('c'); stack.print();
		stack.push('d'); stack.print(); //error
	}
	catch (const StackException& e) { e.print(); cout << endl; }


	//���� 3��
	cout << "------------����3��" << endl;
	try {
		char c = 0;
		CharStack stack(3);
		stack.push('e');

		c = stack.pop(); // c = 'e';
		cout << c << endl; 
		c = stack.pop(); // error
		cout << c << endl;
	}
	catch (const StackException& e) { e.print(); cout << endl; }

	return 0;
}

