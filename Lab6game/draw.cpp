#include <point2d.h>
#include <shapes.h>
#include <SDL.h>
#include <vector>

void callRendering(vector<Shape*> shapes, SDL_Renderer* renderer);
void initBricks(vector<Shape*> &BrickItems, int row);

const int winX = 600;
const int winY = 400;


int main(int argc, char* args[])
{
	int rgb[4] = { 0,0,0,0 };
	bool shotActive = false;
	// Numbers of brick rows
	int gameRows = 3;
	int gameOver = 13 * gameRows;
	int paddleHit = 0;
	// Flag for game over message.
	bool isTheGameOver = false;

	vector<Shape*> playerItems;
	vector<Shape*> brickItems;
	SDL_Event event;
	// Flag for player quit keypress.
	bool quit = false;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Breakout-ish", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winX, winY, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	Point2D *playerPosition = new Point2D(250,winY-20);
	Point2D *shotPosition = nullptr;
	
	Rectangle* player = nullptr;
	Circle* shot = nullptr;

	// Create and draw playerobject
	player = new Rectangle(*playerPosition,rgb,80,5,true);
	playerItems.push_back(player);

	// Init and draw the initial bricks
	for (int numberOfBrickRows = 0; numberOfBrickRows < gameRows; numberOfBrickRows++)
	{
		initBricks(brickItems, numberOfBrickRows);
	}
	while(!quit)
	{
		SDL_Delay(5);
		SDL_PollEvent(&event);

		if (shotActive && gameOver != 0)
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
				// check if brick matches ball position
				if (getY >= shotY && getX <= shotX && getX+40 >= shotX)//  && getX >= shotX && brick[0]->getX() <= shotPosition->getY()+40)
				{ 
					// hide brick if match is found and bounce ball
					Rectangle* myitem = (Rectangle*)brickItems.at(i);
					if (myitem->getDrawMe())
					{
						//shotActive = false;
						myitem->setDrawMe(false);
						gameOver -= 1;
						shot->doBounce('y');
					}	
				}	
				i++;
			}
			// check if ball is on the paddle
			if (shotPosition->getY() == player->getY() && shotPosition->getX() >= player->getX() && shotPosition->getX() <= (player->getX() + player->getWidth()))
			{
				paddleHit = shotPosition->getX() - player->getX();
				// if left edge of the paddle is hit bounce left
				if (paddleHit < 20)
				{
					shot->doBounce('l');
				}
				// if right edge of the paddle is hit bounce right
				else if(paddleHit > player->getWidth() - 20)
				{
					shot->doBounce('r');
				}
				else
				{
					// bounce straight up if middle of paddle is hit.
					if(paddleHit > (player->getWidth()/2)-5 && paddleHit < (player->getWidth() / 2) + 5)
						shot->doBounce('s');
					//else normal bounce
					else
						shot->doBounce('y');
				}
					
			}
			// handle bounce when ball hits the windowframe 
			if (shotPosition->getY() > 0)
			{
				// bounce of left or right window frame
				if (shotPosition->getX() > winX - 1 || shotPosition->getX() <= 1)
					shot->doBounce('x');
				// bounce of top window frame
				else if (shotPosition->getY() <= 1)
				{
					shot->doBounce('y');
				}

				// create movement according to path vector
				shotPosition->setY(shotPosition->getY()+shot->getDirectionY());
				shotPosition->setX(shotPosition->getX() + shot->getDirectionX());
			}			
			
			// restart if ball is missed with paddle		
			if(shotPosition->getY() > winY-1)
			{
				playerItems.pop_back();
				delete shot;
				shot = nullptr;
				shotActive = false;
			}	
		}
		// check if game is complete and inform player
		if (gameOver == 0)
		{
			if (!isTheGameOver)
			{
				cout << "The game is over. Press esc to quit.";
				isTheGameOver = true;
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
						if(playerPosition->getX() >= 0)
							playerPosition->setX(playerPosition->getX() - 2);
						break;
					case SDLK_RIGHT:
						if(playerPosition->getX() < winX-player->getWidth())
							playerPosition->setX(playerPosition->getX() + 2);
						break;
					case SDLK_SPACE:
						if (!shotActive)
						{
							shotActive = true;
							shotPosition = new Point2D(playerPosition->getX()+player->getWidth()/2, playerPosition->getY()-player->getHeight());
							shot = new Circle(*shotPosition, rgb, 2,1,-1);
							playerItems.push_back(shot);
						}
						break;
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

// Draw the brick array
void callRendering(vector<Shape*> shapes, SDL_Renderer* renderer)
{
	for (auto iterator = shapes.begin(); iterator < shapes.end(); ++iterator)
	{
		iterator[0]->render(renderer);
	}
}

// Fill vectorarray with brick objects with spacing between
void initBricks(vector<Shape*>& BrickItems, int row)
{
	int rgb[4] = { 0,0,0,0 };
	int rowSpacing = row * 15;
	
	for(int i = 10; i<winX-45; i+=45)
	{
		Point2D* brickPosition = new Point2D(i, rowSpacing);
		Rectangle *newBrick = new Rectangle(*brickPosition, rgb, 40,10, true);
		BrickItems.push_back(newBrick);
	}
}