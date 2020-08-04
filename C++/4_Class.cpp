#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
private:
	string name;
	float gpa;

public:
	Student(string _name = "Nobody", float _gpa = 0)
		:name(_name), gpa(_gpa)
	{}
	void setGPA(float gpa) { this->gpa = gpa; }
	void setName(string name) { this->name = name; }
	float getGPA() const { return gpa; }
	string getName() const { return name; }
	void print() const {
		cout << '\t' << "Name: " << name;
		cout << " GPA: " << gpa << endl;
	}
};

class School {
private:
	string schoolName;
	vector<Student> students;

public:
	School(string str) : schoolName(str)
	{}
	string getSchoolName() { return schoolName; }
	void addStudent(string str, float f = 0);
	void print() const;
	void swap(Student& i, Student& j);
	void sort();
	Student& findStudentWithName(string str);
};

int main() {
	School pnu("PNU");

	pnu.addStudent("Kim", 2.7F);
	pnu.addStudent("Hong", 3.5F);
	pnu.addStudent("Lee");
	pnu.addStudent("Joo", 1.5F);

	pnu.print();

	pnu.sort(); //descending
	pnu.print();

	School knu("KNU");
	knu.addStudent("Seo", 2.5F);
	knu.addStudent("Lee", 3.8F);
	knu.print();



	Student& lee = pnu.findStudentWithName("Lee");
	lee.setGPA(3.3F);
	lee.setName("Yoon");

	pnu.print();

	knu.addStudent("Hong", 4.3F);
	Student& hong = knu.findStudentWithName("Hong");
	hong.setGPA(3.3F);
	hong.setName("Joon");
	knu.print();

	return 0;
}




void School::addStudent(string str, float f) {
	Student stu(str, f);
	students.push_back(stu);
}

void School::print() const {
	cout << "School Name: " << schoolName << ", ";
	cout << "Count: " << students.size() << endl;
	for (vector<Student>::const_iterator it = students.begin(); it != students.end(); it++) {
		it->print();
	}
	cout << endl;
}

void School::swap(Student& i, Student& j) {
	Student temp;
	temp = i;
	i = j;
	j = temp;
}

void School::sort() {
	for (int i = 0; i < students.size() - 1; i++) {
		for (int j = i + 1; j < students.size(); j++) {
			if (students[i].getGPA() < students[j].getGPA()) {
				swap(students[i], students[j]);
			}
		}
	}
}

Student& School::findStudentWithName(string str) {
	for (int i = 0; i < students.size(); i++) {
		if (students[i].getName() == str) { return students[i]; }
	}
}
