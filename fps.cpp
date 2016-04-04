#include <glload\gl_all.hpp>

#include "fps.h"
#include "map.h"

Application fps_application;
ApplicationInterface *mApplicationInterface = &fps_application;
std::string appTitle = "OpenGL fps";

Map map;

int Application::Init(){
	std::cout << "Exp00 init function called" << std::endl;
	map.init();
	return 0;
}

void Application::Display(){
	std::cout << "Exp00 display function called" << std::endl;

	gl::ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gl::Clear(gl::COLOR_BUFFER_BIT);
	map.draw();
}

void Application::Close(){
	std::cout << "Exp00 close function called" << std::endl;
}

void Application::KeyboardEvent(SDL_KeyboardEvent &key){

	static int temp = 0;
	/*
	if (key.keysym.sym == SDLK_DOWN)
		mConsole.ScrollDown();

	if (key.keysym.sym == SDLK_UP)
		mConsole.ScrollUp();
	*/
	/*
	if (key.keysym.sym == SDLK_RETURN){
		mConsole.PutLetter('X');
	}
	*/
	const char *keyName = SDL_GetKeyName(key.keysym.sym);
}