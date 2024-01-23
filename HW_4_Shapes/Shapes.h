#pragma once
#include <iostream>

using namespace std;

class Shape
{
protected:
	int serialNumber;  //holds the serial number of the Shape
	char shapeType;    //holds the Shape type

public:
	 void setSerialNumber (int);
	 void setShapeType(char);
	 void setShapeParamA(double);
	 void setShapeParamB(double);
	 double getShapeParamA() const;
	 double getShapeParamB() const;
	 int getSerialNumber() const;
	 char getShapeType() const;

	 virtual void display() = 0;
};

class Spray :public Shape
{
protected:
	int radius;
	double density;

public:
	void display();
};

class Circle : public Spray
{
public:
	void display();
};

class Rectangle :public Shape
{
protected:
	int height;
	int width;

public:
	void display();
};

class Square :public Rectangle
{
public:
	void display();
};