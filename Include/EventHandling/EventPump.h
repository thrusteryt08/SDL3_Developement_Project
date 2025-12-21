#pragma once
#include<SDL3/SDL.h>
#include "../Include/EventHandling/Event.h"

namespace AxionForge {

	class EventPump {
	public:
		static bool Pull(Event& event) {
			SDL_Event e;
			if (SDL_PollEvent(&e)) {
				event = Event(e);
				return true;
			}
			return false;
		}
	};

}

