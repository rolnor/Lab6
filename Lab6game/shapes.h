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
public:
	Rectangle(Point2D& inPoint, int inRgb[], float width, float height) : Shape(inPoint, inRgb), width(width), height(height) {};
	void render(SDL_Renderer* renderer);
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
public:
	Circle(Point2D& inPoint, int inRgb[], float radius) : Shape(inPoint, inRgb), radius(radius) {};
	void render(SDL_Renderer* renderer);
};




