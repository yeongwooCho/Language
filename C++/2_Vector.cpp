#include <vector>
#include <iostream>
using namespace std;

const int SUBJECT_NO = 3;
struct StudentInfo {
	string name = "Nobody";
	int scores[SUBJECT_NO] = { 0 };
	int sum = 0;
	float average = 0;
};

void printStudent(StudentInfo stu, int i);
void printVector(vector<StudentInfo>& vec);
void totalSum(vector<StudentInfo>& vec);

int main() {
	int intSize;
	cin >> intSize;
	// 1) Use vector<StudentInfo>
	vector<StudentInfo> vecScore(intSize);

	//Set data
	for (auto& n : vecScore) {
		cin >> n.name >> n.scores[0] >> n.scores[1] >> n.scores[2];
		n.sum = n.scores[0] + n.scores[1] + n.scores[2];
		n.average = (float)(n.scores[0] + n.scores[1] + n.scores[2]) / SUBJECT_NO;
	}
	StudentInfo total{ "Total", {0,0,0}, 0, 0}; //Total struct element
	vecScore.push_back(total); //Push element

	totalSum(vecScore); //total 점수를 완성시켜줌

	printVector(vecScore); //Print

	return 0;
}

//Make total score
void totalSum(vector<StudentInfo>& vec) {
	for (vector<StudentInfo>::iterator it = vec.begin(); it != vec.end()-1; it++) {
		(vec.end() - 1)->scores[0] += it->scores[0];
		(vec.end() - 1)->scores[1] += it->scores[1];
		(vec.end() - 1)->scores[2] += it->scores[2];
		(vec.end() - 1)->sum += it->sum;
	}
}

// 2) Define a function that print a StudentInfo
void printStudent(StudentInfo stu, int i) {
	if (stu.name != "Total") {
		cout << i + 1 << '\t' << stu.name << '\t' << stu.scores[0] << '\t';
		cout << stu.scores[1] << '\t' << stu.scores[2] << '\t' << stu.sum;
		cout << '\t' << stu.average << endl;
	}
	else {
		cout << stu.name << "\t\t" << stu.scores[0] << '\t';
		cout << stu.scores[1] << '\t' << stu.scores[2] << '\t' << stu.sum << endl;
	}
}

// 3) Define a function that print vector<StudentInfo>
void printVector(vector<StudentInfo>& vec) {
	int i = 0;
	cout << endl;
	// 4) Use iterator
	for (vector<StudentInfo>::iterator it = vec.begin(); it != vec.end(); it++) {
		printStudent(*it,i);
		i++;
	}
}
