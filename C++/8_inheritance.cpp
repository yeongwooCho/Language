
//inheritance
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum EmployeeLevel { 사원, 대리, 과장, 차장, 부장 };
class Employee {
private:
	string name;
	const EmployeeLevel level;
public:
	Employee(const string _name, const EmployeeLevel _level)
		:name(_name), level(_level)
	{}

	string getName() const { return name; }
	EmployeeLevel getLevel() const { return level; }

	friend ostream& operator<<(ostream&, Employee&);
};

ostream& operator<<(ostream& os, Employee& em) {
	os << em.getLevel() << '\t' << em.getName() << endl;
	return os;
}

class Manager : public Employee {
private:
	vector<Employee*> group;
public:
	Manager(const string _name, const EmployeeLevel _level)
		:Employee(_name, _level)
	{
		group.clear();
	}

	vector<Employee*> getGroup() const { return group; }

	void addEmployee(Employee* ePointer) {
		group.push_back(ePointer);
	}
	friend ostream& operator<<(ostream& os, Manager& em);
};

ostream& operator<<(ostream& os, Manager& em) {
	os << em.getLevel() << '\t' << em.getName() << endl;
	os << "List of employees managed by me" << endl;
	for (auto iter : em.group) { os << *iter; }
	return os;
}


int main() {
	Employee e1("홍", 사원), e2("김", 대리), e3("차", 사원);
	cout << e1 << e2 << e3;

	Manager m1("Tom", 차장);
	m1.addEmployee(&e1);
	m1.addEmployee(&e2);
	m1.addEmployee(&e3);
	cout << endl << "Information for Manager" << endl;
	cout << m1;

	return 0;
}