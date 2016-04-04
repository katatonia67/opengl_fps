#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <SDL.h>
#include <vector>
#include <utils.h>

#define _tWinMain wWinMain

class ApplicationInterface{
public:

	ApplicationInterface(){
		resW = 640;
		resH = 480;
	}

	virtual int Init() = 0;
	virtual void Display() = 0;
	virtual void Close() = 0;
	virtual void KeyboardEvent(SDL_KeyboardEvent &key) = 0;

	int resW;
	int resH;

};

#endif