#pragma once
#include "SDL3/SDL_events.h"
#include "Control.h"
#include <functional>
#include "Console.h"
#include "Array.h"
#include "Vector2.h"
#include "Static_Class.h"
#include <queue>

namespace AxionForge {

	enum class EventType : uint16_t {
		_NONE = 0,

		// Application
		_QUIT,

		// Keyboard
		_KEY_DOWN,
		_KEY_UP,
		_TEXT_INPUT,

		// Mouse
		_MOUSE_MOVE,
		_MOUSE_BUTTON_DOWN,
		_MOUSE_BUTTON_UP,
		_MOUSE_WHEEL,

		// Window
		_WINDOW_RESIZE,
		_WINDOW_FOCUS_GAINED,
		_WINDOW_FOCUS_LOST,
	};

	class Event {
	public:
		bool Handled = false;
		virtual EventType GetType() const = 0;
		virtual ~Event() = default;
	};

	class QuitEvent : public Event {
	public:
		static EventType StaticType() { return EventType::_QUIT; }
		EventType GetType() const override { return StaticType(); }
	};

	class MouseMoveEvent : public Event {
	public:
		Vector2 Position;
		Vector2 Relative;

		MouseMoveEvent(int x, int y, int relX, int relY)
			: Position((float)x, (float)y),
			Relative((float)relX, (float)relY) {
		}

		static EventType StaticType() { return EventType::_MOUSE_MOVE; }
		EventType GetType() const override { return StaticType(); }
	};

	class MouseButtonEvent : public Event {
	public:
		Vector2 Position;
		uint8_t Button;

		MouseButtonEvent(int x, int y, uint8_t button)
			: Position((float)x, (float)y), Button(button) {
		}
	};

	class MouseButtonDownEvent : public MouseButtonEvent {
	public:
		using MouseButtonEvent::MouseButtonEvent;

		static EventType StaticType() { return EventType::_MOUSE_BUTTON_DOWN; }
		EventType GetType() const override { return StaticType(); }
	};

	class MouseButtonUpEvent : public MouseButtonEvent {
	public:
		using MouseButtonEvent::MouseButtonEvent;

		static EventType StaticType() { return EventType::_MOUSE_BUTTON_UP; }
		EventType GetType() const override { return StaticType(); }
	};

	class SDLEventTranslator {
	public:
		static Event* Translate(const SDL_Event& e) {
			switch (e.type) {

			case SDL_EVENT_QUIT:
				return new QuitEvent();

			case SDL_EVENT_MOUSE_MOTION:
				return new MouseMoveEvent(
					e.motion.x,
					e.motion.y,
					e.motion.xrel,
					e.motion.yrel
				);

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				return new MouseButtonDownEvent(
					e.button.x,
					e.button.y,
					e.button.button
				);

			case SDL_EVENT_MOUSE_BUTTON_UP:
				return new MouseButtonUpEvent(
					e.button.x,
					e.button.y,
					e.button.button
				);
			}
			return nullptr;
		}
	};

	class EventQueue {
		std::queue<Event*> Queue;
	public:
		void Push(Event* e) {
			if (e) Queue.push(e);
		}

		Event* Pop() {
			if (Queue.empty()) return nullptr;
			Event* e = Queue.front();
			Queue.pop();
			return e;
		}

		bool IsEmpty() const { return Queue.empty(); }
	};

	class EventDispatcher {
		Event& event;

	public:
		EventDispatcher(Event& e) : event(e) {}

		template<typename T, typename F>
		bool Dispatch(const F& func) {
			if (event.GetType() == T::StaticType()) {
				event.Handled = func(static_cast<T&>(event));
				return true;
			}
			return false;
		}
	};

}