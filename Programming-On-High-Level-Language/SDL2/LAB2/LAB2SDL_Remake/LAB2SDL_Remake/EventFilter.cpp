#include "EventFilter.h"


void fillScreen(SDL_Window* window) {
	SDL_Surface* screen = SDL_GetWindowSurface(window);

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

int eventFilter(void* userdata, SDL_Event* event) {
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_q && event->key.keysym.mod == KMOD_LCTRL) {
			SDL_Event exitEvent = { SDL_QUIT };
			SDL_PushEvent(&exitEvent);
		}

		SDL_Log("Кнопочка вниз/key Down %d", event->key.keysym.sym);
		break;
	case SDL_KEYUP:
		SDL_Log("Кнопочка вверх/key Up %d", event->key.keysym.sym);
		break;
	case SDL_TEXTEDITING:
		SDL_Log("Клавиатурка редактирует текст/Keyboard text editing (composition). Composition is '%s', cursor start from %d and selection lenght is %d", event->edit.text, event->edit.start, event->edit.length);
		break;
	case SDL_TEXTINPUT:
		SDL_Log("Ввод текста с клавиатуры/Keyboard text input. Text is '%s'", event->text.text);
		break;
	case SDL_FINGERMOTION:
		SDL_Log("Пальчик/Finger: %lld, x: %f, y: %f", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
		break;
	case SDL_FINGERDOWN:
		SDL_Log("Пальчик вниз/Finger: %lld down - x: %f, y: %f",
			event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
		return 1;
	case SDL_FINGERUP:
		SDL_Log("Пальчик вверх/Finger: %lld up - x: %f, y: %f", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
		break;
	case SDL_MULTIGESTURE:
		SDL_Log("Множественный жест/Multi Gesture: x = %f, y = %f, dAng = %f, dR = %f", event->mgesture.x, event->mgesture.y, event->mgesture.dTheta, event->mgesture.dDist);
		SDL_Log("Множественнный жест: циферкаснизукоснуться/ Multi Gesture: numDownTouch = %i", event->mgesture.numFingers);
		break;
	case SDL_DOLLARGESTURE:
		SDL_Log("Жест номер исполнен, ошибка/Gesture %lld performed, error: %f", event->dgesture.gestureId, event->dgesture.error);
		break;
	case SDL_DOLLARRECORD:
		SDL_Log("Записанный жест/Recorded gesture: %lld", event->dgesture.gestureId);
		break;
	case SDL_MOUSEMOTION:
		SDL_Log("Мышку подвигали/Mouse Move. X=%d, Y=%d, Относительно/RelativeX=%d, Относительно/RelativeY=%d", event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
			asmFunction();

		SDL_Log("Мышечка кнопка вниз/Mouse Button Down %u", event->button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		SDL_Log("Мышечка кнопка вверх/Mouse Button Up %u", event->button.button);
		break;
	case SDL_MOUSEWHEEL:
		SDL_Log("Мышечка колёсико/Mouse Wheel X=%d, Y=%d", event->wheel.x, event->wheel.y);
		break;
	case SDL_QUIT:
		SDL_Log("Пользовательский-запрос выйти/User-requested quit");
		return 1;
	case SDL_WINDOWEVENT:
		switch (event->window.event) {
		case SDL_WINDOWEVENT_SHOWN:
			SDL_Log("Окошко номер показано/Window %d shown", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			SDL_Log("Окошко номер спрятано/Window %d hidden", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			fillScreen(SDL_GetWindowFromID(event->window.windowID));
			SDL_Log("Окошко номер обнаружено/Window %d exposed", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_MOVED:
			SDL_Log("Окошко номер передвинуто ->/Window %d moved to %d,%d", event->window.windowID, event->window.data1, event->window.data2);
			break;
		case SDL_WINDOWEVENT_RESIZED:
			SDL_Log("Окошко номер изменено ->/Window %d resized to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			SDL_Log("Окошко номер размер изменён ->/Window %d size changed to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			SDL_Log("Окошко номер минимизировано/Window %d minimized", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			SDL_Log("Окошко номер максимизировано/Window %d maximized", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_RESTORED:
			SDL_Log("Окошко номер Window %d restored", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_ENTER:
			SDL_Log("Мышка вошла в окно/Mouse entered window %d", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_LEAVE:
			SDL_Log("Мышка покинуло окно/Mouse left window %d", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			SDL_Log("Окно номер было под фокусом клавиатуры/Window %d gained keyboard focus", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			SDL_Log("Окно номер потеряла фокус клавиатуры/Window %d lost keyboard focus", event->window.windowID);
			break;
		case SDL_WINDOWEVENT_CLOSE:
			SDL_Log("Окно номер закрыто/Window %d closed", event->window.windowID);
			break;
		default:
			SDL_Log("Окно номер получило неизвестный эвент/Window %d got unknown event %d", event->window.windowID, event->window.event);
			break;
		}
		break;
	default:
		SDL_Log("Получили неизвестный эвент/Got unknown event %d", event->type);
		break;
	}

	return 0;
}

Uint32 customEventFunction(Uint32 interval, void* param) {
	SDL_Event event = { SDL_WINDOWEVENT };

	SDL_Log("Timer signaled with interval %d ms", interval);

	event.window.windowID = SDL_GetWindowID((SDL_Window*)param);
	event.window.event = SDL_WINDOWEVENT_EXPOSED;

	SDL_PushEvent(&event);
	return(interval);
}

Uint32 repeatOnceFunction(Uint32 interval, void* param) {
	SDL_Event exitEvent = { SDL_QUIT };

	SDL_Log("Timer signaled with interval %d ms", interval);

	if (asmFunction() != 0) {
		SDL_HideWindow((SDL_Window*)param);

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Something going wrong", "Find me! I'm scared", NULL);

		SDL_Delay(15000); /* 15 sec */
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "You didn't find me! You disappointed me... I'm leaving.");

		SDL_PushEvent(&exitEvent);
	}

	return 0;
}

