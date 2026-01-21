#include "Control.h"
#include "Color.h"
#include "Renderer.h"

namespace AxionForge {

	class CheckBox : public Control {
		using Function = void(*)(Control&, Event&);
	public:
		Vector2 size = Vector2(20, 20);
		Color backColor = ColorName::White;
		Color fontColor = ColorName::Black;

		std::string Text = "";

		Color boxColorChecked = ColorName::Green;
		Color boxColorUnchecked = ColorName::Red;

		CheckBox() = default;
		CheckBox(Vector2 position) {
			this->position = position;
		}
		CheckBox(Vector2 position, std::string text) {
			this->position = position;
			this->Text = text;
		}

		bool isChecked = false;

		Function onCheckChanged;

		bool isColliding(Vector2 point) const override {
			return Rect(position,size).isColliding(point);
		}

		virtual bool OnEvent(Event& e) override {
			EventDispatcher d(e);
			d.Dispatch<MouseButtonDownEvent>([this](MouseButtonDownEvent& ev) {
				if (ev.Button != 1) return false;
				if (isColliding(ev.Position)) {
					isChecked = !isChecked;
					if (onCheckChanged)
						onCheckChanged(*this, ev);
					return true;
				}
				return false;
				});
			if (e.Handled)
				return true;
			return false;
		}

		virtual void Render(Renderer* renderer) override {
			Color boxColor = isChecked ? boxColorChecked : boxColorUnchecked;
			renderer->RenderColorRect(ColorRect(position, size, boxColor));
			renderer->setDrawColor(fontColor);
			SDL_RenderDebugText(renderer->Instance(), position.x + size.x + 5, position.y, &Text[0]);

		}


		virtual std::string ToString() override {
			return "CheckBox";
		}
	};

}