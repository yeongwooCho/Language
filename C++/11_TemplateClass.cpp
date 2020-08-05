//Template class
#include <iostream>
#include <cstring>
using namespace std;

class Complex {
private:
	float real, imaginary;
public:
	Complex(float r = 0.F, float i = 0.F)
		:real(r), imaginary(i) {}
	Complex(const Complex& copy) 
		: Complex(copy.getR(), copy.getI()) {}
	float getR() const { return real; }
	float getI() const { return imaginary; }

	bool operator==(const Complex& c) const {
		if (this->getI() == c.getI() && this->getR() == c.getR())
			return true;
		else return false;
	}
};
ostream& operator<<(ostream& os, const Complex& c) {
	os << c.getR() << ", " << c.getI();
	return os;
}


class MyString {
private:
	char* str;
public:
	MyString() : str(nullptr) {}
	MyString(const char* s) {
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}
	MyString(const MyString& s) {
		str = new char[strlen(s.getStr()) + 1];
		strcpy(str, s.getStr());
	}
	char* getStr() const { return str; }

	bool operator==(const MyString& s) const {
		if (strcmp(str, s.getStr()) == 0) return true;
		else return false;
	}
};
ostream& operator<<(ostream& os, const MyString& s) {
	os << s.getStr();
	return os;
}



template<class T, int sz>
class List {
private:
	T* pElems;
	int size;
public:
	List() : size(0) { pElems = new T[sz]; }
	//List<MyString, 200> s2List(sList);
	List(const List& copy) {
		*this = copy;
		//size = copy.getSize();
		//pElems = new T[sz];
		//for (auto i = 0; i < size; i++) {
		//	pElems[i] = copy.getPElems()[i];
		//}
	}
	void operator=(const List& copy) { 
		size = copy.getSize();
		pElems = new T[sz];
		for (auto i = 0; i < size; i++) {
			pElems[i] = copy.getPElems()[i];
		}
	}
	int getSize() const { return size; }
	T* getPElems() const { return pElems; }


	//stack push와 유사한 add
	void add(const T& data) {
		pElems[size++] = data;
		cout << data << " is added" << endl;
	}

	//현재 데이터의 크기까지 순차 탐색
	bool find(const T& f) {
		for (auto i = 0; i < size; i++) {
			if (pElems[i] == f) {
				cout << f << " is found" << endl;
				return true;
			}
		}
		cout << f << " is not found" << endl;
		return false;
	}

	//해당 key의 index를 찾아 덮어쓰기 하듯이 remove!!
	void remove(const T& f) {
		int index = 0;
		for (auto i = 0; i < size; i++) {
			if (pElems[i] == f) { index = i; }
		}
		//size는 비어있는 top을 의미, i+1을 i에 넣기
		for (auto i = index; i < size - 1; i++) {
			pElems[i] = pElems[i + 1];
		}
		size--; //size가 하나 줄었다.
		cout << f << " is removed" << endl;
	}
};



int main() {
	List<Complex, 100> cList;
	List<MyString, 200> sList;

	cList.add(Complex(0, 0));
	cList.add(Complex(1, 1));
	cout << endl;

	sList.add("abc");
	sList.add("def");
	cout << endl;

	cList.find(Complex(1, 0));
	sList.find("def");
	cList.remove(Complex(0, 0));
	sList.remove("abc");
	cout << endl;

	List<MyString, 200> s2List(sList);
	List<MyString, 200> s3List;
	s3List.add("123");
	s3List = s2List; //이 과정에서 123이 없어짐
	s3List.remove("def");

	/*
	cout << "---------------" << endl;
	sList.find("abc");
	sList.find("def");
	sList.find("123");
	cout << endl;
	s2List.find("abc");
	s2List.find("def");
	s2List.find("123");
	cout << endl;
	s3List.find("abc");
	s3List.find("def");
	s3List.find("123");
	cout << "---------------" << endl;
	*/
}