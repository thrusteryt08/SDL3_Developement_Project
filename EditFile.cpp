#include "AxionForge/Include/AxionForge.h"

namespace AxionForge {

	void Button_Click(Control& sender, Event& event) {
		Console::Log("Button clicked!");
	}
	void Button_Enter(Control& sender, Event& event) {
		Console::Log("Mouse entered button area.");
	}
	void Button_Leave(Control& sender, Event& event) {
		Console::Log("Mouse left button area.");
	}
	void Button_Press(Control& sender, Event& event) {
		Console::Log("Button pressed.");
	}
	void Button_Release(Control& sender, Event& event) {
		Console::Log("Button released.");
	}
	void Button_Cancel(Control& sender, Event& event) {
		Console::Log("Button click canceled");
	}

	void Application::AppLoad() {
		Button* button = new Button("Button");

		button->onClick = Button_Click;
		button->onEnter = Button_Enter;
		button->onLeave = Button_Leave;
		button->onPress = Button_Press;
		button->onRelease = Button_Release;
		button->onCancel = Button_Cancel;

		TextBox* textBox = new TextBox();
		textBox->position = Vector2(200, 200);
		window->Objects.Add(textBox);


		window->Objects.Add(button);
	}

	void Application::Iterate(bool& _appState) {
		
	}

	void Application::AppEvent(Event& event) {
		
	}

	void Application::Exit() {
		
	}

}