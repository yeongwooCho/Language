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
	//size가 양수가 아닌경우, (0인 경우도 stack으로써 의미가 없다.)
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
		//copy는 이미 예외적이지 않은 객체이기에 size에 대한 예외가 발생하지 않는다.
		top = copy.getTop();
		s = new char[size = copy.getSize()];
		strcpy(s, copy.getS()); //
	}
	*/
	


	//top가 size 보다 크거나 같은 경우
	//size는 크기, top은 데이터가 들어갈 index
	void push(char c) { 
		if (size <= top) 
			throw StackException("PUSH Error : The stack is full!");
		s[top++] = c; 
	}

	//비어있는 stack을 pop할 경우 할당하지 않은 메모리에 접근
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
	//예외 1번
	cout << "------------예외1번" << endl;
	try { CharStack stack(-1); } //error
	catch (const StackException& e) { e.print(); cout << endl; }


	//예외 2번
	cout << "------------예외2번" << endl;
	try { 
		CharStack stack(3);
		stack.push('a'); stack.print();
		stack.push('b'); stack.print();
		stack.push('c'); stack.print();
		stack.push('d'); stack.print(); //error
	}
	catch (const StackException& e) { e.print(); cout << endl; }


	//예외 3번
	cout << "------------예외3번" << endl;
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

