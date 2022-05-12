#include <iostream>
#include <math.h>

using namespace std;

class Point {
public:
	float x;
	float y;
	Point() {}
	Point(float x, float y) {
        this->x = x;
        this->y = y;
	}
};

ostream& operator<<(ostream& stream, const Point& p) {
	stream << p.x << " " << p.y << " ";
	return stream;
}

// vector class
class vector {
private:
	float vx;
	float vy;
public:
	vector() {
		vx = 0.0;
		vy = 0.0;
	}
	vector(float, float);
	vector& operator+(const vector&);
	void setVector(float, float);
	bool operator==(const vector&);
};

vector& vector::operator+(const vector& vec) {
	vector *nv = new vector();
	nv->vx = this->vx + vec.vx;
	nv->vy = this->vy + vec.vy;
	return *nv;
}

vector::vector(float vx, float vy) {
	this->setVector(vx, vy);
}

void vector::setVector(float vx, float vy) {
	this->vx = vx;
	this->vy = vy;
}

bool vector::operator==(const vector& vec) {
	return this->vx == vec.vx && this->vy == vec.vy;
}



class Geometry {
public:
	// memeber function
	virtual bool PointInGeometry(Point* p) {}
	virtual float Area() {}
	virtual void Print() {}
	virtual void setKind(char) {}
	virtual void setGeomID(int) {}
};

class Triangle : public Geometry {
private:
	Point p1, p2, p3;
	char Kind = 0;
	int GeomID = 0;
public:
	Triangle() {}
	Triangle(float x1, float y1, float x2, float y2, float x3, float x4);
	bool PointInGeometry(Point* p);
	float Area();
	void Print();
	void setKind(char);
	void setGeomID(int);
};

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	p1.x = x1, p1.y = y1;
	p2.x = x2, p2.y = y2;
	p3.x = x3, p3.y = y3;
}

bool Triangle::PointInGeometry(Point* p) {
	// use three vector to confirm
	if (!p) return 0;
	vector* vectors = new vector[3];
	vectors[0].setVector(p->x - p1.x, p->y - p1.y);
	vectors[1].setVector(p->x - p2.x, p->y - p2.y);
	vectors[2].setVector(p->x - p3.x, p->y - p3.y);
	return vectors[0] + vectors[1] + vectors[2] == vector(0, 0);
}

float Triangle::Area() {
	float A = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
	A = sqrt(A);
	float B = (p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y);
	B = sqrt(B);
	float C = (p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y);
	C = sqrt(C);
	return (A + B + C) / 2;
}

void Triangle::Print() {
	cout << "GeomID" << GeomID << " " << Kind << " " << p1 << p2 << p3 << endl;
}

void Triangle::setKind(char kind) {
	Kind = kind;
}

void Triangle::setGeomID(int ID) {
	GeomID = ID;
}

class Rectangle : public Geometry {
private:
	char Kind;
	int GeomID;
	float wide;
	float high;
	Point p1, p2;

public:
	Rectangle(float, float, float, float);
	bool PointInGeometry(Point* p);
	float Area();
	void Print();
	void setKind(char);
	void setGeomID(int);
};
Rectangle::Rectangle(float x1, float y1, float x2, float y2) {
	this->wide = abs(x2 - x1);
	this->high = abs(y2 - y1);
	p1.x = x1, p1.y = y1;
	p2.x = x2, p2.y = y2;
}

bool Rectangle::PointInGeometry(Point* p) {
	return (p1.x <= p->x && p2.x >= p->x) && (p1.y <= p->y && p2.y >= p->y);
}

float Rectangle::Area() {

	float wide = abs(p1.x - p2.x);
	float high = abs(p1.y - p2.y);

	return wide * high;
}

void Rectangle::Print() {
	cout << "GeomID" << GeomID << " " << Kind << " " << p1.x << " " << p1.y + high << " " << p1 << " "
          << p1.x + wide << p1.y << " " << p2 << endl;
}
void Rectangle::setKind(char kind) {
	Kind = kind;
}
void Rectangle::setGeomID(int ID) {
	GeomID = ID;
}
class Square : public Geometry {
private:
	float Long;
	char Kind;
	int GeomID;
	Point p1;
public:
	Square() {}
	Square(float, float, float);
	bool PointInGeometry(Point* p);
	float Area();
	void Print();
	void setKind(char);
	void setGeomID(int);
	void setLong(float);
};

Square::Square(float x1, float y1, float side) {
	this->p1.x = x1;
	this->p1.y = y1;
	Long = side;
}


bool Square::PointInGeometry(Point* p) {
	return (p1.x <= p->x && p1.x + Long >= p->x) && (p1.y <= p->y && p1.y + Long >= p->y);
}
float Square::Area() {
	return Long * Long;
}

void Square::Print() {
	cout << "GeomID" << GeomID << " " << Kind << " " << p1 << Long << endl;
}
void Square::setKind(char kind) {
	Kind = kind;
}
void Square::setGeomID(int ID) {
	GeomID = ID;
}
void Square::setLong(float side) {
	Long = side;
}
class Circle : public Geometry {
private:
	Point center;
	float radius;
	int GeomID;
	char Kind;
public:
	Circle() {}
	Circle(float, float, float);
	Circle(float, Point&);
	bool PointInGeometry(Point* p);
	float Area();
	void Print();
	float getRadius();
	void setRadius(float r);
	void setGeomID(int);
	void setKind(char);
};

Circle::Circle(float x1, float y1, float radius) {
	this->center.x = x1;
	this->center.y = y1;
	this->radius = radius;
}

bool Circle::PointInGeometry(Point* p) {
	float distance = sqrt((center.x - p->x) * (center.x - p->x) + (center.y - p->y) * (center.y - p->y));
	return distance <= radius;
}

float Circle::Area() {
	float pi = 3.14159;
	return pi * radius * radius;
}

void Circle::Print() {
	cout << "GeomID" << GeomID << " " << Kind << " " << center << endl;
}

float Circle::getRadius() {
	return radius;
}

void Circle::setRadius(float r) {
	radius = r;
}

void Circle::setGeomID(int ID) {
    GeomID = ID;
}

void Circle::setKind(char kind) {
    Kind = kind;
}
class GeomSet {
private:
	Geometry** set;
	int n = 0;
public:
	Geometry* operator[](Point* p);
	void Insert();
};

Geometry* GeomSet::operator[](Point* p) {
	float minArea = set[0]->Area();
	int index;
	for (int i = 0; i < n; i++) {
		if (set[i]->PointInGeometry(p)) {
			minArea = min(minArea, set[i]->Area());
			index = i;
		}
	}
	if (!minArea) {
		return NULL;
	}
	else {
		return set[index];
	}
}

void GeomSet::Insert() {
	cin >> n; // length of GeomSet
	set = new Geometry*[n];
	if (!set) exit(1);
	for (int i = 0; i < n; i++) {
		int ID;
		char kind;
		cin >> ID;
		cin >> kind;
		if (kind == 'T') {
            float x1, y1, x2, y2, x3, y3;
			cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            set[i] = new Triangle(x1, y1, x2, y2, x3, y3);
			set[i]->setGeomID(ID);
			set[i]->setKind(kind);
		}
		else if (kind == 'R') {
            float x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			set[i] = new Rectangle(x1, y1, x2, y2);
			set[i]->setGeomID(ID);
			set[i]->setKind(kind);
		}
		else if (kind == 'S') {
			float x1, y1,side;
			cin >> x1 >> y1 >> side;
			set[i] = new Square(x1, y1,side);
            set[i]->setGeomID(ID);
			set[i]->setKind(kind);

		}
		else if (kind == 'C') {
			float x1, y1,radius;
			cin >> x1 >> y1 >> radius;
			set[i] = new Circle(x1, y1,radius);
			set[i]->setGeomID(ID);
			set[i]->setKind(kind);

		}
	}
}

int main() {
	GeomSet A;
	A.Insert();
	Point* p = new Point(10.5, 10.5);
	Geometry* geom = A[p];
	geom->Print();
	return 0;
}
