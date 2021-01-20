#include <point2d.h>
#include <shapes.h>
#include <SDL.h>
#include <vector>

//void createObject(Shape* object);
void changeColor(int colors[4], int val1, int val2, int val3, int val4);
void testRendering(vector<Shape*> shapes, SDL_Renderer* renderer);


int main(int argc, char* args[])
{
	vector<Shape*> shapes;
	SDL_Keycode key = NULL;
	SDL_Event event;
	bool quit = false;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("SpaceBreakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	Point2D *playerPosition = new Point2D(250,350);
	int rgb[4] = { 0,0,0,0 };

	Triangle* player = NULL;
//	Triangle* triPoint = NULL;
//	Circle* cirPoint = NULL;
	srand(time(NULL));

	player = new Triangle(*playerPosition,rgb,30,20);
	shapes.push_back(player);

	while(!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{		
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_q:
						quit = true;
						break;
					case SDLK_LEFT:
						playerPosition->setX(playerPosition->getX() - 10);
						break;
					case SDLK_RIGHT:
						playerPosition->setX(playerPosition->getX() + 10);
						break;
/*					case SDLK_r:
						changeColor(rgb, 255, 0, 0, 255);
						point2d.setX(randomx);
						point2d.setY(randomy);
						recPoint = new Rectangle(point2d, rgb, randomw, randomh);
						shapes.push_back(recPoint);
						break;
					case SDLK_t:
						changeColor(rgb, 155, 155, 0, 255);
						point2d.setX(randomx);
						point2d.setY(randomy);
						triPoint = new Triangle(point2d, rgb, randomb, randomh);
						shapes.push_back(triPoint);
						break;
					case SDLK_x:
						cout << "remove shapes" << endl;
						shapes.clear();
						shapes.shrink_to_fit();
						break;*/
				}
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		testRendering(shapes, renderer);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	delete player;
//	if(paddlePosition != nullptr)
//		delete paddlePosition;
//	delete triPoint;
//	delete cirPoint;
	return 0;
}

void testRendering(vector<Shape*> shapes, SDL_Renderer* renderer)
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