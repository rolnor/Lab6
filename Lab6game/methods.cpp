#include <shapes.h>
#include <math.h>

void Rectangle::render(SDL_Renderer* renderer)
{
//	cout << "Rectangle" << endl << "Width: " << this->width << " Height: " << this->height << endl;
//	cout << "Position:  X = " << this-> getX() << " Y = " << this->getY() << endl << endl;
	if (this->getDrawMe())
	{
		SDL_SetRenderDrawColor(renderer, this->getrgb(0), this->getrgb(1), this->getrgb(2), this->getrgb(3));
		SDL_RenderDrawLine(renderer, this->getX(), this->getY(), this->getX() + this->width, this->getY());
		SDL_RenderDrawLine(renderer, this->getX(), this->getY(), this->getX(), this->getY() + this->height);
		SDL_RenderDrawLine(renderer, this->getX() + this->width, this->getY(), this->getX() + this->width, (int)this->getY() + this->height);
		SDL_RenderDrawLine(renderer, this->getX(), this->getY() + this->height, this->getX() + this->width, (int)this->getY() + this->height);
	}
}

void Triangle::render(SDL_Renderer* renderer)
{
//	cout << "Triangle" << endl << "Base: " << this->base << " Height: " << this->height << endl;
//	cout << "Position:  X = " << this->getX() << " Y = " << this->getY() << endl << endl;
	SDL_SetRenderDrawColor(renderer, this->getrgb(0), this->getrgb(1), this->getrgb(2), this->getrgb(3));

	SDL_RenderDrawLine(renderer, this->getX(), this->getY(), this->getX() + this->getBase(), this->getY());
	SDL_RenderDrawLine(renderer, this->getX(), this->getY(), this->getX() + this->getBase()/2, this->getY()-this->getHeight());
	SDL_RenderDrawLine(renderer, this->getX()+this->getBase(), this->getY(), this->getX() + this->getBase() / 2, this->getY() - this->height);
}

void Circle::render(SDL_Renderer* renderer)
{
//	cout << "Circle" << endl << "Radius: " << this->radius << endl;
//	cout << "Position:  X = " << this->getX() << " Y = " << this->getY() << endl << endl;
	SDL_SetRenderDrawColor(renderer, this->getrgb(0), this->getrgb(1), this->getrgb(2), this->getrgb(3));

	for (int deg = 0; deg < 360; deg++)
	{
		float radtodeg = deg * 3.1415 / 180;
		float nx = cos(radtodeg) * this->radius;
		float ny = sin(radtodeg) * this->radius;
		SDL_RenderDrawLine(renderer, this->getX(), this->getY(), this->getX()+nx, this->getY()+ny);
	}
}

void Circle::doBounce(char axis)
{
	if(axis == 'y') 
		this->directionY *= -1;
	else if(axis == 'x')
		this->directionX *= -1;
	else if(axis == 's')
	{
		this->directionY *= -1;
		this->directionX *= 0;
	}
	else if (axis == 'l')
	{
		this->directionY *= -1;
		this->directionX = -1;
	}
	else if (axis == 'r')
	{
		this->directionY *= -1;
		this->directionX = 1;
	}
}

int Circle::getDirectionX()
{
	return this->directionX;
}

int Circle::getDirectionY()
{
	return this->directionY;
}

float Triangle::getBase() 
{
	return this->base;
}
float Triangle::getHeight()
{
	return this->height;
}

bool Rectangle::getDrawMe()
{
	return this->drawMe;
}

void Rectangle::setDrawMe(bool changeValue)
{
	this->drawMe = changeValue;
}

float Rectangle::getWidth()
{
	return this->width;
}


float Rectangle::getHeight()
{
	return this->height;
}