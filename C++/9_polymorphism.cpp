//Polymorphism
#include <iostream>
#include <vector>
using namespace std;

class Point {
private:
	int xpos, ypos;
public:
	Point() : xpos(0), ypos(0) {}
	Point(int x, int y) : xpos(x), ypos(y)
	{}
	Point(const Point& copy) {
		xpos = copy.xpos;
		ypos = copy.ypos;
	}
	int getX() const { return xpos; }
	int getY() const { return ypos; }
	void print() const { cout << '(' << xpos << ", " << ypos << ')'; }
};


enum Color { RED, BLUE, YELLOW };


class Shape {
private:
	Color lineColor;
public:
	Color getLineColor() const { return lineColor; }
	virtual Shape* clone() const = 0;
	virtual void print() const = 0;
	virtual float getLength() const = 0;
};


class ClosedShape : public Shape {
public:
	ClosedShape() : Shape() {}
};


class Polygon : public ClosedShape {
public:
	Polygon() : ClosedShape() {}
	float getArea(Point p1, Point p2, Point p3) const {
		//세점의 좌표를 알때, 넓이를 구하는 공식
		// |(x1*y2+x2*y3+x3*y1)-(x1*y3+x3*y2+x2*y1)| / 2
		float value = (((p1.getX()) * (p2.getY()))
			+ ((p2.getX()) * (p3.getY()))
			+ ((p3.getX()) * (p1.getY())))
			- (((p1.getX()) * (p3.getY()))
				+ ((p3.getX()) * (p2.getY()))
				+ ((p2.getX()) * (p1.getY())));
		if (value < 0) { value = -value; }
		return value / 2;
	}
};


class Triangle : public Polygon {
private:
	Point point1, point2, point3;
public:
	Triangle() : Polygon() {}
	Triangle(Point p1, Point p2, Point p3)
		:Polygon(), point1(p1), point2(p2), point3(p3)
	{}
	
	virtual Shape* clone() const {
		Shape* const cln = new Triangle(point1, point2, point3);
		return cln;
	}

	void print() const {
		cout << "Triangle: ";
		point1.print();
		point2.print();
		point3.print();
	}
	
	virtual float getLength() const {
		return getArea(point1, point2, point3);
	}
};


class Rectangle : public Polygon {
private:
	Point point1, point2, point3, point4;
public:
	Rectangle() : Polygon() {}
	Rectangle(Point p1, Point p2, Point p3, Point p4)
		:Polygon(), point1(p1), point2(p2), point3(p3), point4(p4)
	{}

	virtual Shape* clone() const {
		Shape* const cln = new Rectangle(point1, point2, point3, point4);
		return cln;
	}

	void print() const {
		cout << "Rectangle: ";
		point1.print();
		point2.print();
		point3.print();
		point4.print();
	}

	virtual float getLength() const {
		//rectangle이란 직사각형을 의미한다.
		//하지만 주어진 과제에서 평행사변형이 주어졌기에, 
		//임의의 사각형이 주어질수 있다고 가정하고 넓이를 구한다.
		//사각형을 두개로 쪼개서 두개의 삼각형의 넓이를 구한다. 
		//4개의 점이 임의의 점이라면, 각 점의 위치를 파악해야한다.
		//x+y의 값이 작은 3개의점과 높은 3개의 점을 선택하면,
		//논리의 오류없이 Area()를 사용할수 있다.
		Point arr[4] = { point1, point2, point3, point4 };

		for (int i = 0; i < 4; i++) {
			//x+y의 값이 가장 작은 Point를 배열 제일 앞으로 위치
			if (arr[0].getX() + arr[0].getY() > arr[i].getX() + arr[i].getY()) {
				Point tmp = arr[0];
				arr[0] = arr[i];
				arr[i] = tmp;
			}

			//x+y의 값이 가장 큰 Point를 배열 제일 뒤로 위치
			if (arr[3].getX() + arr[3].getY() < arr[i].getX() + arr[i].getY()) {
				Point tmp = arr[3];
				arr[3] = arr[i];
				arr[i] = tmp;
			}
		}

		return getArea(arr[0], arr[1], arr[2]) + getArea(arr[1], arr[2], arr[3]);
	}
};


class ShapeList {
private:
	vector<Shape*> shapes;
public:
	ShapeList() {
		shapes.clear();
	}

	void addShape(Shape* const shape) {
		//shape이 아닌 새롭게 동적할당 한 clone을 vector에 push하므로 
		//main()에서 delete 연산이 가능하다.
		shapes.push_back(shape->clone()); 
	}

	void print() const {
		for (vector<Shape*>::const_iterator it = shapes.begin(); it != shapes.end(); it++) {
			(*it)->print();
			cout << endl;
		}
	}

	float getTotalArea() const {
		float totalArea = 0.0F;
		for (auto shape : shapes) { totalArea += shape->getLength(); }
		return totalArea;
	}

	~ShapeList() {
		for (auto shape : shapes) {
			delete shape; //모든 new에 대한 delete
		}
	}
};



int main() {
	Point p1(0, 0), p2(0, 10), p3(20, 20), p4(20, 30);

	Shape* const r = new Rectangle(p1, p2, p3, p4);
	Shape* const t = new Triangle(p1, p2, p3);

	ShapeList list{};
	list.addShape(r);
	list.addShape(t);
	delete r;
	delete t;

	list.print();
	cout << list.getTotalArea() << endl;

	return 0;
}