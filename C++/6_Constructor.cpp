//class constructor & destructor
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class MyString {
private:
	char* str;
	int size;
public:
	MyString() {
		str = nullptr;
		size = 0;
	}
	MyString(const char* input) { //string이 아니기에 null문자를 신경써야 한다.
		size = strlen(input); //string length(null 문자 제외)
		str = new char[size + 1]; // '\0'를 삽입할 공간까지 할당
		strncpy(str, input, size + 1);
	}
	MyString(const MyString& myString) { //copy constructor의  깊은 복사
		size = myString.getSize();
		str = new char[size + 1];
		strncpy(str, myString.getStr(), size + 1);
	}

	void set(const char* input) {
		//delete->new 는 많은 리소스 소비가 있기에 더 긴 문자열이 들어올때까지
		//한번 할당한 공간은 그대로 사용하겠다!
		if (size < strlen(input)) { delete[] str; }

		size = strlen(input);
		str = new char[size + 1];
		strncpy(str, input, size + 1);
	}

	bool isEqual(const MyString tar) const {
		if (strcmp(str, tar.getStr())) { return false; }
		else { return true; }
	}

	char* getStr() const { return str; }
	int getSize() const { return size; }
	void print() const { cout << str << endl; }
	~MyString() { delete[] str; }
};

int main() {
    MyString strs[] = {
		MyString("C"),
		MyString(),
		MyString("Java")
	};
	strs[1].set("C++");

	const MyString target("Java");
	for (int i = 0; i < 3; i++) {
		const MyString str(strs[i]);
		if (str.isEqual(target)) {
			cout << "[" << i << "]: ";
			str.print();
			break;
		}
	}

	for (int i = 0; i < 3; i++) {
		const MyString& str = strs[i];
		str.print();
	}

	return 0;
}
