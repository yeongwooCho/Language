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
	MyString(const char* input) { //string�� �ƴϱ⿡ null���ڸ� �Ű��� �Ѵ�.
		size = strlen(input); //string length(null ���� ����)
		str = new char[size + 1]; // '\0'�� ������ �������� �Ҵ�
		strncpy(str, input, size + 1);
	}
	MyString(const MyString& myString) { //copy constructor��  ���� ����
		size = myString.getSize();
		str = new char[size + 1];
		strncpy(str, myString.getStr(), size + 1);
	}

	void set(const char* input) {
		//delete->new �� ���� ���ҽ� �Һ� �ֱ⿡ �� �� ���ڿ��� ���ö�����
		//�ѹ� �Ҵ��� ������ �״�� ����ϰڴ�!
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
