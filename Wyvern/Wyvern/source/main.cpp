//main.cpp

#include <SDL2/SDL_main.h>
#include "Wyvern_Engine.h"
#include "Wyvern_Game.h"

// COLLISION DETECTION DONE! NOW IMPLEMENT IT! STUPID FAT UGLY CUNT :( 

//https://stackoverflow.com/questions/16596422/template-class-with-template-container

//void Write_Text(SDL_Renderer* renderer, std::string i)
//{
//	TTF_Font* font = TTF_OpenFont("assets/font.otf", 28);
//	SDL_Colour black = { 0, 0, 0, 255 };
//	int w, h;
//	SDL_Surface* surface = TTF_RenderText_Solid(font, i.c_str(), black);
//	w = surface->w;
//	h = surface->h;
//	SDL_Rect rect2 = { 0, 0, w, h };
//	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//	SDL_FreeSurface(surface);
//	SDL_RenderCopy(renderer, texture, NULL, &rect2);
//	SDL_DestroyTexture(texture);
//}

// Global variables = GLOBAL_VARIABLE
// Function variable = function_Variable
// Parameter variable = parameter_variable
// Class variable = class_Variable_

int main(int argc, char* argv[])
{
	Wyvern_Engine engine;

	engine.Initialise();
	engine.Run();
	engine.Exit();

	return 0;
}
