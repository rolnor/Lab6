#include <point2d.h>
#include <shapes.h>
#include <SDL.h>
#include <vector>
#include<algorithm>

//void createObject(Shape* object);
void changeColor(int colors[4], int val1, int val2, int val3, int val4);
void callRendering(vector<Shape*> shapes, SDL_Renderer* renderer);
void initBricks(vector<Shape*> &BrickItems, int row);

const int winX = 600;
const int winY = 400;
int rgb[4] = { 0,0,0,0 };

int main(int argc, char* args[])
{
	bool shotActive = false;
	vector<Shape*> playerItems;
	vector<Shape*> brickItems;
	SDL_Keycode key = NULL;
	SDL_Event event;
	bool quit = false;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("SpaceBreakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winX, winY, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	Point2D *playerPosition = new Point2D(250,winY-20);
	Point2D *shotPosition = nullptr;
	

	Triangle* player = nullptr;
	Circle* shot = nullptr;

//	srand(time(NULL));

	// Create and draw playerobject
	player = new Triangle(*playerPosition,rgb,30,20);
	playerItems.push_back(player);

	// Init and draw the initial bricks
	for (int numberOfBrickRows = 0; numberOfBrickRows < 3; numberOfBrickRows++)
	{
		initBricks(brickItems, numberOfBrickRows);
	}
	while(!quit)
	{
		SDL_Delay(5);
		SDL_PollEvent(&event);

		if (shotActive)
		{
			int i = 0;
			float getY, getX;
			float shotX, shotY;
			// check if shot position matches any brickpositions
			for (auto brick = brickItems.begin(); brick != brickItems.end(); ++brick)
			{
				getY = brick[0]->getY()+15;  
				getX = brick[0]->getX();
				shotX = shotPosition->getX();
				shotY = shotPosition->getY();
				if (getY >= shotY && getX <= shotX && getX+40 >= shotX)//  && getX >= shotX && brick[0]->getX() <= shotPosition->getY()+40)
				{ 
					Rectangle* myitem = (Rectangle*)brickItems.at(i);
					if (myitem->getDrawMe())
					{
						shotActive = false;
						myitem->setDrawMe(false);
					}	
				}	
				i++;
			}
			// if shot still active continue movement path
			if(shotPosition->getY() > 0 && shotActive)
				shotPosition->setY(shotPosition->getY() - 2);
			// if not active remove the shot and allow player another shot
			else
			{
				playerItems.pop_back();
				delete shot;
				shot = nullptr;
				shotActive = false;
			}	
		}
	
		switch (event.type)
		{		
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						quit = true;
						break;
					case SDLK_LEFT:
						if(playerPosition->getX() > 10)
							playerPosition->setX(playerPosition->getX() - 1);
						break;
					case SDLK_RIGHT:
						if(playerPosition->getX() < winX-40)
							playerPosition->setX(playerPosition->getX() + 1);
						break;
					case SDLK_SPACE:
						if (!shotActive)
						{
							shotActive = true;
							shotPosition = new Point2D(playerPosition->getX()+player->getBase()/2, playerPosition->getY()-player->getHeight());
							shot = new Circle(*shotPosition, rgb, 2);
							playerItems.push_back(shot);
						}
						break;
						/*
					case SDLK_x:
						cout << "remove shapes" << endl;
						shapes.clear();
						shapes.shrink_to_fit();
						break;*/
				}
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		callRendering(playerItems, renderer);
		callRendering(brickItems, renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	playerItems.clear();
	brickItems.clear();

	return 0;
}

void callRendering(vector<Shape*> shapes, SDL_Renderer* renderer)
{
	for (auto iterator = shapes.begin(); iterator < shapes.end(); ++iterator)
	{
		iterator[0]->render(renderer);
	}
}

void changeColor(int colors[4], int val1, int val2, int val3, int val4)
{
	colors[0] = val1;
	colors[1] = val2;
	colors[2] = val3;
	colors[3] = val4;
}

void initBricks(vector<Shape*>& BrickItems, int row)
{
	int rowSpacing = row * 15;
	for(int i = 10; i<winX-45; i+=45)
	{

		Point2D* brickPosition = new Point2D(i, rowSpacing);
		Rectangle *newBrick = new Rectangle(*brickPosition, rgb, 40,10, true);
		BrickItems.push_back(newBrick);
	}
}