#pragma once
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <stdio.h>
using namespace std;

class Point2D
{
private:
	float x, y;
public:
	Point2D();
	Point2D(float iX, float iY);
	Point2D(const Point2D& copyFromObject);
	void printValues();
	double CalculateDistance(const Point2D& distantObject);
	Point2D operator+(const Point2D& addObject);
	bool operator==(const Point2D& compareObject);
	Point2D& operator=(const Point2D& compareObject);
	string toString();
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
};