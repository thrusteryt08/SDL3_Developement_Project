#pragma once
#include "../Core/Enums.h"

namespace AxionForge {

	class Event {
		EventType Type;

	public:
		Event() {
			Type = EventType::FIRST;
		}
		Event(EventType type) {
			Type = type;
		}
		Event(SDL_Event event) {
			Type = (EventType)event.type;
		}

		EventType GetType() const {
			return Type;
		}
	};

}