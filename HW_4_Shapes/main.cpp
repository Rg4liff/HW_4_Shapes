#include <iostream>
#include <iomanip>
#include <fstream> 
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;
//global variables
const int SIZE = 99;

class Shape
{
protected:
	int serialNumber;  //holds the serial number of the Shape
	char shapeType;    //holds the Shape type

public:
	void setSerialNumber(int ser)
	{
		serialNumber = ser;
	};
	void setShapeType(char shT)
	{
		shapeType = shT;
	};
	int getSerialNumber() const
	{
		return serialNumber;
	};
	char getShapeType() const 
	{
		return shapeType;
	};

	virtual void display() {};
};

class Spray :public Shape
{
protected:
	double radius;
	double density;

public:
	virtual void display() 
	{
		int r = getRadius();
		double den = getDensity();

		const int Cwidth = r;
		const int Clength = r * 1.5;
		int start = 0;
		int end = 0;
		int point;
		int lineAmtLeft;
		int densityAmt;
		int output;
		bool hasprintedcheck = false;

		for (int y = Cwidth; y >= -Cwidth; y -= 2)
		{
			for (int x = -Clength; x <= Clength; x++)
			{
				point = sqrt(pow(x, 2) + pow(y, 2));
				if (point == r)
				{
					cout << "*";
					if (!hasprintedcheck)
					{
						start = x;
						end = -x;
						lineAmtLeft = end * 2;
						densityAmt = lineAmtLeft * (den / 100);
						hasprintedcheck = true;
					}
				}
				else if (x > start && x < end && densityAmt != 0)
				{
					output = 0 + rand() % 100;
					if (output <= den)
					{
						cout << "*";
						densityAmt--;
						lineAmtLeft--;
					}
					else if (lineAmtLeft <= densityAmt)
					{
						cout << "*";
						densityAmt--;
						lineAmtLeft--;
					}
					else
					{
						cout << " ";
						lineAmtLeft--;
					}
				}
				else
				{
					cout << " ";
				}
			}
			cout << "\n";
			hasprintedcheck = false;
		}
	};
	void setRadius(double r)
	{
		radius = r;
	}
	void setDensity(double d)
	{
		density = d;
	}
	double getRadius()
	{
		return radius;
	}
	double getDensity()
	{
		return density;
	}
};

class Circle : public Spray
{

public:
	void display() 
	{

		int r = getRadius();

		const int Cwidth = r;
		const int Clength = r * 1.5;
		int start = 0;
		int end = 0;
		int point;
		bool hasprintedcheck = false;

		for (int y = Cwidth; y >= -Cwidth; y -= 2)
		{
			for (int x = -Clength; x <= Clength; x++)
			{
				point = sqrt(pow(x, 2) + pow(y, 2));
				if (point == r)
				{
					cout << "*";
					if (!hasprintedcheck)
					{
						start = x;
						end = -x;
						hasprintedcheck = true;
					}
				}
				else if (x > start && x < end)
				{
					cout << "*";
				}
				else cout << " ";
			}
			cout << "\n";
			hasprintedcheck = false;
		}
	};

};

class Rectangle :public Shape
{
	double width;
	double height;

public:
	virtual void display() 
	{
		//data
		double dWidth = getWidth();
		double dHeight = getHeight();
		for (int row = 0; row < dHeight; row++)
		{
			for (int col = 0; col < dWidth; col++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
	void setWidth(double w)
	{
		width = w;
	}
	void setHeight(double h)
	{
		height = h;
	}
	double getWidth()
	{
		return width;
	}
	double getHeight()
	{
		return height;
	}
};

class Square :public Rectangle
{
public:
	void display() 
	{
		//data
		double dWidth = getWidth();
		double dHeight = getHeight();
		for (int row = 0; row < dHeight; row++)
		{
			for (int col = 0; col < dWidth; col++)
			{
				cout << "* ";
			}
			cout << endl;
		}
	}
};
//Shape.cpp

class MgrShape : public Shape
{
	//data
	Shape * shapeArray[SIZE] = { nullptr };

public:
	MgrShape()
	{
		populateShapeData();
	}
	~MgrShape()
	{
		for (int delI = 0; delI < SIZE; delI++)
		{
			if (shapeArray[delI] != nullptr)
			{
				delete shapeArray[delI];
				shapeArray[delI] = nullptr;
			}
		}
	};

	void populateShapeData()
	{
		//data
		ifstream myfile;
		char aShapetype;
		int shapeIndex = 0;
		int aSerialNum;
		double aShapeparam1;
		double aShapeparam2;



		myfile.open("shaperecords.txt");
		if (myfile.is_open())
		{
			while (!myfile.eof())
			{
				myfile >> aShapetype >> aSerialNum >> aShapeparam1 >> aShapeparam2;
				switch (aShapetype)
				{
				case 'C':
				{
					Circle* aCirc = new Circle;

					aCirc->setShapeType(aShapetype);
					aCirc->setSerialNumber(aSerialNum);
					aCirc->setRadius(aShapeparam1);
					aCirc->setDensity(1);
					shapeArray[shapeIndex] = aCirc;
					shapeIndex++;
					break;
				}
				case 'R':
				{
					Rectangle* aRect = new Rectangle;

					aRect->setShapeType(aShapetype);
					aRect->setSerialNumber(aSerialNum);
					aRect->setWidth(aShapeparam1);
					aRect->setHeight(aShapeparam2);
					shapeArray[shapeIndex] = aRect;
					shapeIndex++;
					break;
				}
				case 'S':
				{

					Spray* aSp = new Spray;

					aSp->setShapeType(aShapetype);
					aSp->setSerialNumber(aSerialNum);
					aSp->setRadius(aShapeparam1);
					aSp->setDensity(aShapeparam2);
					shapeArray[shapeIndex] = aSp;
					shapeIndex++;
					break;
				}
				case 'Q':
				{
					Square* aSq = new Square;
					aSq->setShapeType(aShapetype);
					aSq->setSerialNumber(aSerialNum);
					aSq->setWidth(aShapeparam1);
					aSq->setHeight(aShapeparam1);
					shapeArray[shapeIndex] = aSq;
					shapeIndex++;
					break;
				}

				}
			}
			myfile.close();
		}

	}

	void readFile()
	{
	
	}

	void displayAll()
	{

		Shape* dShape = new Shape();
		
		for (int dIndex = 0; dIndex < SIZE; dIndex++)
		{
			if (shapeArray[dIndex] != nullptr)
			{
				dShape = shapeArray[dIndex];
				dShape->display();
				cout << endl << endl;
			}
		}
	}
};

//main cpp
int main()
{
	srand(time(0)); rand();

	MgrShape ms;

	ms.displayAll();

}