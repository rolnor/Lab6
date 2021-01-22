#include <shapes.h>
Shape::Shape(Point2D& inPoint, int rgbAlpha[4])
{
	for (int i = 0; i < 3; i++)
	{
		if (rgbAlpha[i] >= 0 && rgbAlpha[i] < 256)
			rgb[i] = rgbAlpha[i];
		else rgb[i] = 0;
	}

	point = &inPoint;
}

Shape::~Shape()
{
	delete point;
}

int Shape::getrgb(int index)
{
	return rgb[index];
}

float Shape::getX()
{
	return this->point->getX();
}

float Shape::getY()
{
	return this->point->getY();
}