#pragma once
#include "Object.h"
#include <string>
#include "Event.h"

namespace AxionForge {

	class Control : public Object {

	public:
		bool wantsFocus = false;
		bool isFocused = false;

		virtual void Focus() {
			isFocused = true;
		}

		virtual void UnFocus() {
			isFocused = false;
		}

		virtual void Requests() {}

		virtual bool isColliding(Vector2 point) const {
			return false;
		}


		virtual void OnEvent(Event& e) { }

		virtual std::string ToString() {
			return "Control";
		}
	};
}