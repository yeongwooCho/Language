//Class Á¤ÀÇ
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum MajorType { CE, EE, ME, UD };
class Major {
private:
	MajorType majorType;
public:
	Major(MajorType _majorType = UD) { majorType = _majorType; }
	MajorType getMajorType() { return majorType; }
	void setMajorType(MajorType _majorType) { majorType = _majorType; }

	void printMajor() const {
		if (majorType == CE) { cout << "Computer Eng."; }
		else if (majorType == EE) { cout << "Electrical Eng."; }
		else if (majorType == ME) { cout << "Mechanical Eng."; }
		else if (majorType == UD) { cout << "UnDetermined"; }
	}
};

class Student {
private:
	string name;
	float gpa;
	Major major;
public:
	Student() : name("Nobody"), gpa(0.0F), major(UD)
	{}
	Student(string _name, MajorType _majorType)
		:name(_name), gpa(0.0F), major(_majorType)
	{}
	Student(string _name, float _gpa = 0.0F)
		:name(_name), gpa(_gpa), major(UD)
	{}
	Student(string _name, float _gpa, MajorType _majorType)
		:name(_name), gpa(_gpa), major(_majorType)
	{}

	void setGPA(float gpa) { this->gpa = gpa; }
	void setName(string name) { this->name = name; }
	void setMajor(Major major) { this->major = major; }
	float getGPA() const { return gpa; }
	string getName() const { return name; }
	Major getMajor() const { return major; }

	void print() const {
		cout << '\t' << "Name: " << name;
		cout << " GPA: " << gpa << " Major: ";
		major.printMajor();
		cout << endl;
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

	Student* addStudent(string str, float f);
	Student* addStudent(string str, MajorType _majorType);

	void print() const;
	void swap(Student& i, Student& j);
	void sort();
};


int main() {
	School pnu("PNU");

	Student* kim = pnu.addStudent("Kim", EE);
	kim->setGPA(3.5F);

	Student* hong = pnu.addStudent("Hong", CE);
	hong->setGPA(4.3F);

	Student* lee = pnu.addStudent("Lee", 4.0F);
	lee->setMajor(CE);

	Student* joo = pnu.addStudent("Joo", 1.5F);
	joo->setMajor(ME);

	pnu.print();

	pnu.sort(); //descending
	pnu.print();

	return 0;
}



Student* School::addStudent(string str, float f) {
	Student stu(str, f);
	students.push_back(stu);
	return &(students.back());
}

Student* School::addStudent(string str, MajorType _majorType) {
	Student stu(str, _majorType);
	students.push_back(stu);
	return &(students.back());
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

