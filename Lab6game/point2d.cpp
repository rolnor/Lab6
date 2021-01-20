#include<point2d.h>

Point2D::Point2D()
{
	x = NULL;
	y = NULL;
}

Point2D::Point2D(float iX, float iY)
{
	x = iX;
	y = iY;
}

float Point2D::getX()
{
	return this->x;
}

float Point2D::getY()
{
	return this->y;
}

void Point2D::setX(float x)
{
	this->x = x;
}

void Point2D::setY(float y)
{
	this->y = y;
}

void Point2D::printValues()
{
//	cout << x << endl << y << endl;
	cout << "x: " << x << "\ty: " << y << endl;
}

Point2D::Point2D(const Point2D& copyFromObject) 
{
	x = copyFromObject.x;
	y = copyFromObject.y;
}

double Point2D::CalculateDistance(const Point2D& distantObject)
{
	double distance;
	distance = sqrt(pow((x - distantObject.x),2) + pow((y - distantObject.y), 2));
	return distance;
}

string Point2D::toString()
{
	char buffer[20];
	sprintf_s(buffer,"[%f,%f]",x,y);
	return buffer;
}

Point2D Point2D::operator+(const Point2D& addObject)
{
	Point2D newObject;
	newObject.x = this->x + addObject.x;
	newObject.y = this->y + addObject.y;
	return newObject;
}

bool Point2D::operator==(const Point2D& compareObject)
{
	if (x == compareObject.x && y == compareObject.y)
		return true;
	else return false;
}

Point2D& Point2D::operator=(const Point2D& setObject)
{
	x = setObject.x;
	y = setObject.y;
	return *this;
}