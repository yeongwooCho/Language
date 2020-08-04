#include <iostream>
#include <string>
#include <vector>
#include <cassert> //void assert(int expression)
using namespace std;

struct Rectangle {
	int width;
	int height;
};
enum CommandKind { ADD, SORT, PRINT, CLEAR, EXIT, INVALID };

CommandKind getCommandKind(string); //string -> enum
Rectangle getRectangle(); //Rectangle �� ������ ���� �Է¹ް� �޾ƿ��°�
void print(const vector<Rectangle>&); //vector�� �ش��ϴ� ��� ������ print
void sort(vector<Rectangle>&); //�־��� ���ǿ� �°� vector�� ������ ���� swap
inline void swap(Rectangle& t1, Rectangle& t2);

int main() {
	vector<Rectangle> rectangles;
	while (true) {
		string commandString;
		cin >> commandString;
		const CommandKind command = getCommandKind(commandString);

		switch (command) {
		case ADD: {
			const Rectangle& newRectangle = getRectangle();
			rectangles.push_back(newRectangle);
			break;
		}
		case PRINT: {
			print(rectangles);
			//use const_iterator in print()
			//define and call print(const Rectangle&)
			break;
		}
		case SORT: {
			sort(rectangles); //define and call swap in sort()
			print(rectangles);
			break;
		}
		case CLEAR: rectangles.clear(); break;
		case EXIT: break;
		default: assert(false); break; //exception�� ���� ���
		}
		if (command == EXIT) break;
	}
	return 0;
}

CommandKind getCommandKind(string str) {
	if (str == "ADD") { return ADD; }
	else if (str == "SORT") { return SORT; }
	else if (str == "PRINT") { return PRINT; }
	else if (str == "CLEAR") { return CLEAR; }
	else if (str == "EXIT") { return EXIT; }
	else { return INVALID; }
}

Rectangle getRectangle() {
	Rectangle newRectangle;
	cin >> newRectangle.width;
	cin >> newRectangle.height;
	return newRectangle;
}

void print(const vector<Rectangle>& rec) {
	//use const_iterator in print()
	//define and call print(const Rectangle&)
	cout << "Rectangle Count: " << rec.size() << endl;
	for (vector<Rectangle>::const_iterator it = rec.begin(); it != rec.end(); it++) {
		cout << '\t' << it->width << ' ' << it->height << ' ';
		cout << (it->width) * (it->height) << endl;
	}
}

inline void swap(Rectangle& t1, Rectangle& t2) {
	// define and call swap in sort()
	Rectangle temp;
	temp = t1;
	t1 = t2;
	t2 = temp;
}

void sort(vector<Rectangle>& rec) {
	// define and call swap in sort()
	// Selection Sort �� Ȱ��
	for (vector<Rectangle>::iterator it1 = rec.begin(); it1 != rec.end() - 1; it1++) {
		for (vector<Rectangle>::iterator it2 = it1 + 1; it2 != rec.end(); it2++) {
			if ((it1->width) * (it1->height) > (it2->width) * (it2->height))
			{
				swap(*it1,*it2);
			}
		}
	}
}
