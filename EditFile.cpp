#include "AxionForge/Include/AxionForge.h"

namespace AxionForge {

	void CheckBoxChanged(Control& control, Event& event) {
		CheckBox& checkbox = static_cast<CheckBox&>(control);
		Console::Log("CheckBox state changed. New state: " + std::string(checkbox.isChecked ? "Checked" : "Unchecked"));
	}

	void Application::AppLoad() {
		TextBox *textbox = new TextBox(Vector2(50, 50), "text");
		const int _Count = 1000000;
		
	}

	void Application::Iterate(bool& _appState) {
		
	}

	void Application::AppEvent(Event& event) {
		
	}

	void Application::Exit() {
		
	}

}