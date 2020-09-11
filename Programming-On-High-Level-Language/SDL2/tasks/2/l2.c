#include <stdlib.h>

#if defined(_WIN32) || defined(_WINDOWS)
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

void fillScreen(SDL_Window *window) {
	SDL_Surface *screen = SDL_GetWindowSurface(window);

	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, rand() % 255, rand() % 255, rand() % 255));

	SDL_UpdateWindowSurface(window);
}

int asmFunction(void) {
	static int internalValue = 1;

#ifdef __GNUC__
	__asm__("movl %0, %%eax\n\t"
		"add %%eax, %0"
		: "=r" (internalValue)
		: "r" (internalValue));
#elif _MSC_VER
	_asm {
		mov eax, internalValue
			add internalValue, eax
	};
#endif

	return internalValue;
}

int eventFilter(void *userdata, SDL_Event *event) {
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_q && event->key.keysym.mod == KMOD_LCTRL) {
			SDL_Event exitEvent = { SDL_QUIT };
			SDL_PushEvent(&exitEvent);
		}

		SDL_Log("key Down %d", event->key.keysym.sym);
		break;
	case SDL_KEYUP:
		SDL_Log("key Up %d", event->key.keysym.sym);
		break;
	case SDL_TEXTEDITING:
		SDL_Log("Keyboard text editing (composition). Composition is '%s', cursor start from %d and selection lenght is %d", event->edit.text, event->edit.start, event->edit.length);
		break;
	case SDL_TEXTINPUT:
		SDL_Log("Keyboard text input. Text is '%s'", event->text.text);
		break;
	case SDL_FINGERMOTION:
		SDL_Log("Finger: %i, x: %i, y: %i", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
		break;
	case SDL_FINGERDOWN:
		SDL_Log("Finger: %lld down - x: %i, y: %i",
			event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
		return 1;
	case SDL_FINGERUP:
		SDL_Log("Finger: %lld up - x: %i, y: %i", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
		break;
	case SDL_MULTIGESTURE:
		SDL_Log("Multi Gesture: x = %f, y = %f, dAng = %f, dR = %f", event->mgesture.x, event->mgesture.y, event->mgesture.dTheta, event->mgesture.dDist);
		SDL_Log("Multi Gesture: numDownTouch = %i", event->mgesture.numFingers);
		break;
	case SDL_DOLLARGESTURE:
		SDL_Log("Gesture %lld performed, error: %f", event->dgesture.gestureId, event->dgesture.error);
		break;
	case SDL_DOLLARRECORD:
		SDL_Log("Recorded gesture: %lld", event->dgesture.gestureId);
		break;
	case SDL_MOUSEMOTION:
		SDL_Log("Mouse Move. X=%d, Y=%d, RelativeX=%d, RelativeY=%d", event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
			asmFunction();

		SDL_Log("Mouse Button Down %u", event->button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		SDL_Log("Mouse Button Up %u", event->button.button);
		break;
	case SDL_MOUSEWHEEL:
		SDL_Log("Mouse Wheel X=%d, Y=%d", event->wheel.x, event->wheel.y);
		break;
	case SDL_QUIT:
		SDL_Log("User-requested quit");
		return 1;
	case SDL_WINDOWEVENT:
		switch (event->window.event) {
		case SDL_WINDOWEVENT_SHOWN:
			SDL_Log("Window %d shown", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			SDL_Log("Window %d hidden", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			fillScreen(SDL_GetWindowFromID(event->window.windowID));
			SDL_Log("Window %d exposed", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_MOVED:
			SDL_Log("Window %d moved to %d,%d", event->window.windowID, event->window.data1, event->window.data2);
			break;
		case SDL_WINDOWEVENT_RESIZED:
			SDL_Log("Window %d resized to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			SDL_Log("Window %d size changed to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			SDL_Log("Window %d minimized", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			SDL_Log("Window %d maximized", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_RESTORED:
			SDL_Log("Window %d restored", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_ENTER:
			SDL_Log("Mouse entered window %d", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_LEAVE:
			SDL_Log("Mouse left window %d", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			SDL_Log("Window %d gained keyboard focus", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			SDL_Log("Window %d lost keyboard focus", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_CLOSE:
			SDL_Log("Window %d closed", event->window.windowID);
			break;
		default:
			SDL_Log("Window %d got unknown event %d", event->window.windowID, event->window.event);
			break;
		}
		break;
	default:
		SDL_Log("Got unknown event %d", event->type);
		break;
	}

	return 0;
}

Uint32 customEventFunction(Uint32 interval, void *param) {
	SDL_Event event = { SDL_WINDOWEVENT };

	SDL_Log("Timer signaled with interval %d ms", interval);

	event.window.windowID = SDL_GetWindowID(param);
	event.window.event = SDL_WINDOWEVENT_EXPOSED;

	SDL_PushEvent(&event);
	return(interval);
}

Uint32 repeatOnceFunction(Uint32 interval, void *param) {
	SDL_Event exitEvent = { SDL_QUIT };

	SDL_Log("Timer signaled with interval %d ms", interval);

	if (asmFunction() != 0) {
		SDL_HideWindow(param);

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Something going wrong", "Find me! I'm scared", NULL);

		SDL_Delay(15000); /* 15 sec */
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "You didn't find me! You disappointed me... I'm leaving.");

		SDL_PushEvent(&exitEvent);
	}

	return 0;
}

void clearFunction(void) {
	SDL_Quit();
}

int main(int argc, char *argv[]) {
	SDL_Window *windowContext = NULL;
	SDL_TimerID repeatOnceFunctionTimer;
	SDL_TimerID customEventFunctionTimer;

	atexit(clearFunction);
	srand((unsigned int)NULL);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to init SDL2. See the log for more info.", NULL);
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to init SDL2, error: %s", SDL_GetError());
		return 1;
	}

	SDL_SetEventFilter(eventFilter, NULL);

	SDL_Log("Start creating window");
	if (!(windowContext = SDL_CreateWindow("SDL2: Magic Events", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE))) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create window. See the log for more info.", NULL);
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window, error: %s", SDL_GetError());
		return 1;
	}
	else {
		SDL_Log("Creating window - succeeded");
	}

	if (!(customEventFunctionTimer = SDL_AddTimer(2000 /* 2 sec */, customEventFunction, windowContext))) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create custom event timer. See the log for more info.", windowContext);
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create custom event timer, error: %s", SDL_GetError());
	}

	if (!(repeatOnceFunctionTimer = SDL_AddTimer(10000 /* 10 sec */, repeatOnceFunction, windowContext))) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create repeat once timer. See the log for more info.", windowContext);
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create repeat once timer, error: %s", SDL_GetError());
	}

	SDL_WaitEvent(NULL);

	SDL_RemoveTimer(repeatOnceFunctionTimer);
	SDL_RemoveTimer(customEventFunctionTimer);

	SDL_Log("Start destroing window");
	SDL_DestroyWindow(windowContext);
	windowContext = NULL;
	SDL_Log("destroing window - succeeded");

	return 0;
}
