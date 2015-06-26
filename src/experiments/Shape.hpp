#ifndef Shape_hpp
#define Shape_hpp

class Shape {
 public:
	virtual double getArea();
	virtual double getPerimeter();
	virtual bool contains(Shape shape);
};

#endif				// Shape_hpp
