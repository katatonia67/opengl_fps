#pragma once

#include <iostream>
#include "framework.h"

class Application: public ApplicationInterface{
	int Init();
	void Close();
	void Display();
	void KeyboardEvent(SDL_KeyboardEvent &key);
}; 