#pragma once
#include <SDL.h>
#include <stdlib.h>

void fillScreen(SDL_Window* window);
int asmFunction(void);
int eventFilter(void* userdata, SDL_Event* event);
Uint32 repeatOnceFunction(Uint32 interval, void* param);
Uint32 customEventFunction(Uint32 interval, void* param);