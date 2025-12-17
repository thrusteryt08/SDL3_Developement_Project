#pragma once
#include <SDL.h>
#include "Core/Enums.h"
#include "Opacity.h"

namespace AxionForge {

	class Color {
	private:
		void setColor(Uint8 red, Uint8 green, Uint8 blue) {
			this->red = red;
			this->green = green;
			this->blue = blue;
		}

		void setFromColorName(ColorName color) {
			constexpr Uint8 MAX = 255;
			switch (color) {
			case ColorName::Red:        setColor(MAX, 0, 0); break;
			case ColorName::Lime:       setColor(0, MAX, 0); break;
			case ColorName::Blue:       setColor(0, 0, MAX); break;
			case ColorName::White:      setColor(MAX, MAX, MAX); break;
			case ColorName::Pink:       setColor(255, 192, 203); break;
			case ColorName::DarkRed:    setColor(139, 0, 0); break;
			case ColorName::LightGreen: setColor(144, 238, 144); break;
			case ColorName::Green:      setColor(0, 128, 0); break;
			case ColorName::DarkGreen:  setColor(0, 100, 0); break;
			case ColorName::LightBlue:  setColor(173, 216, 230); break;
			case ColorName::DarkBlue:   setColor(0, 0, 139); break;
			case ColorName::Gray:       setColor(128, 128, 128); break;
			case ColorName::Yellow:     setColor(MAX, MAX, 0); break;
			case ColorName::Cyan:       setColor(0, MAX, MAX); break;
			case ColorName::Magenta:    setColor(MAX, 0, MAX); break;
			case ColorName::Black:
			default:                    setColor(0, 0, 0); break;
			}
		}

	public:
		Uint8 red = 0;
		Uint8 green = 0;
		Uint8 blue = 0;
		Opacity opacity;

		static constexpr Uint8 MAX = 255;

		// Constructors
		explicit Color() { setColor(0, 0, 0); }
		explicit Color(Uint8 red, Uint8 green, Uint8 blue) { setColor(red, green, blue); }
		explicit Color(Uint8 red, Uint8 green, Uint8 blue, Opacity opacity) : Color(red, green, blue) { this->opacity = opacity; }
		explicit Color(ColorName color) { setFromColorName(color); }
		explicit Color(ColorName color, Opacity o) : Color(color) { opacity = o; }

		// Operators
		Color operator+(const Color& c) const {
			return Color(red + c.red, green + c.green, blue + c.blue);
		}

		Color& operator=(const Color& c) {
			red = c.red;
			green = c.green;
			blue = c.blue;
			opacity = c.opacity;
			return *this;
		}

		bool operator==(const Color& c) const {
			return red == c.red && green == c.green && blue == c.blue;
		}

		bool operator!=(const Color& c) const {
			return !(*this == c);
		}
	};

}