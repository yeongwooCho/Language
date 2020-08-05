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
		//������ ��ǥ�� �˶�, ���̸� ���ϴ� ����
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
		//rectangle�̶� ���簢���� �ǹ��Ѵ�.
		//������ �־��� �������� ����纯���� �־����⿡, 
		//������ �簢���� �־����� �ִٰ� �����ϰ� ���̸� ���Ѵ�.
		//�簢���� �ΰ��� �ɰ��� �ΰ��� �ﰢ���� ���̸� ���Ѵ�. 
		//4���� ���� ������ ���̶��, �� ���� ��ġ�� �ľ��ؾ��Ѵ�.
		//x+y�� ���� ���� 3�������� ���� 3���� ���� �����ϸ�,
		//���� �������� Area()�� ����Ҽ� �ִ�.
		Point arr[4] = { point1, point2, point3, point4 };

		for (int i = 0; i < 4; i++) {
			//x+y�� ���� ���� ���� Point�� �迭 ���� ������ ��ġ
			if (arr[0].getX() + arr[0].getY() > arr[i].getX() + arr[i].getY()) {
				Point tmp = arr[0];
				arr[0] = arr[i];
				arr[i] = tmp;
			}

			//x+y�� ���� ���� ū Point�� �迭 ���� �ڷ� ��ġ
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
		//shape�� �ƴ� ���Ӱ� �����Ҵ� �� clone�� vector�� push�ϹǷ� 
		//main()���� delete ������ �����ϴ�.
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
			delete shape; //��� new�� ���� delete
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