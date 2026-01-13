#pragma once
#include "Object.h"
#include <string>
#include "Event.h"

namespace AxionForge {

	class Control : public Object {

	public:

		virtual bool isColliding(Vector2 point) const {
			return false;
		}


		virtual void OnEvent(Event& e) { }

		virtual std::string ToString() {
			return "Control";
		}
	};
}