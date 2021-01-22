#pragma once
#include <point2d.h>
#include <SDL.h>

class Shape
{
private:
	int rgb[3] = { 0,0,0 };
	Point2D* point;
public:
	virtual void render(SDL_Renderer* renderer) = 0;
	Shape(Point2D& inPoint, int rgbAlpha[4]);
	~Shape();
	int getrgb(int index);
	float getX();
	float getY();
};

class Rectangle : public Shape
{
private:
	float width, height;
	bool drawMe;
public:
	Rectangle(Point2D& inPoint, int inRgb[], float width, float height, bool drawMe) : Shape(inPoint, inRgb), width(width), height(height), drawMe(drawMe){};
	void render(SDL_Renderer* renderer);
	float getWidth();
	float getHeight();
	bool getDrawMe();
	void setDrawMe(bool changeValue);
};

class Triangle : public Shape
{
private:
	float base, height;
public:
	Triangle(Point2D& inPoint, int inRgb[], float base, float height) : Shape(inPoint, inRgb), base(base), height(height) {};
	void render(SDL_Renderer* renderer);
	float getBase();
	float getHeight();
};

class Circle : public Shape
{
private:
	float radius;
	int directionX, directionY;
public:
	Circle(Point2D& inPoint, int inRgb[], float radius, int directionX, int directionY) : Shape(inPoint, inRgb), radius(radius), directionX(directionX), directionY(directionY) {};
	void render(SDL_Renderer* renderer);
	void doBounce(char axis);
	int getDirectionX();
	int getDirectionY();
};




