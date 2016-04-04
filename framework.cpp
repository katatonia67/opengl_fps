#include <Windows.h>
#include <glload/gl_load.hpp>
#include <iostream>
#include "framework.h"

extern ApplicationInterface *mApplicationInterface;
extern std::string appTitle;

bool quit = false;
SDL_Event event;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	SDL_Window *window;
	SDL_Init(SDL_INIT_VIDEO);
	
	//Текущая версия
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	
	window = SDL_CreateWindow(
		"An SDL2 window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		mApplicationInterface->resW,       // width, in pixels
		mApplicationInterface->resH,       // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);
	
	if (window == NULL) {
        std::cout <<"Could not create window:" << SDL_GetError() << std::endl;
        return 1;
    }
	
	SDL_SetWindowTitle(window, appTitle.c_str());
	
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);
	glload::LoadTest tst = glload::LoadFunctions();
	
	//Инициализация пользователя
	mApplicationInterface->Init();
	
	while (!quit){
		
		//Обработка событий
		while (SDL_PollEvent(&event)){

			if (event.type == SDL_QUIT){
				quit = true;
			}

			if (event.type == SDL_KEYDOWN){
				mApplicationInterface->KeyboardEvent(event.key);
			}
			
		//Отрисовка
		mApplicationInterface->Display();
		//Смена экранов
		SDL_GL_SwapWindow(window);	
		
		}
	}
	
	mApplicationInterface->Close();	
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}