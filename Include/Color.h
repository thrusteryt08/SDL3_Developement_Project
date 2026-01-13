#pragma once
#include "SDL3/SDL_stdinc.h"
#include "Opacity.h"

namespace AxionForge {

	enum class ColorName : int {
		AliceBlue, AntiqueWhite, Aqua, Aquamarine, Azure,
		Beige, Bisque, Black, BlanchedAlmond, Blue, BlueViolet, Brown, BurlyWood,
		CadetBlue, Chartreuse, Chocolate, Coral, CornflowerBlue, Cornsilk, Crimson, Cyan,
		DarkBlue, DarkCyan, DarkGoldenRod, DarkGray, DarkGreen, DarkKhaki, DarkMagenta, DarkOliveGreen, DarkOrange, DarkOrchid, DarkRed, DarkSalmon, DarkSeaGreen, DarkSlateBlue, DarkSlateGray, DarkTurquoise, DarkViolet, DeepPink, DeepSkyBlue, DimGray, DodgerBlue,
		FireBrick, FloralWhite, ForestGreen, Fuchsia,
		Gainsboro, GhostWhite, Gold, GoldenRod, Gray, Green, GreenYellow, HoneyDew, HotPink,
		IndianRed, Indigo, Ivory,
		Khaki,
		Lavender, LavenderBlush, LawnGreen, LemonChiffon, LightBlue, LightCoral, LightCyan, LightGoldenRodYellow, LightGray, LightGreen, LightPink, LightSalmon, LightSeaGreen, LightSkyBlue, LightSlateGray, LightSteelBlue, LightYellow, Lime, LimeGreen, Linen, Magenta,
		Maroon, MediumAquaMarine, MediumBlue, MediumOrchid, MediumPurple,
		MediumSeaGreen, MediumSlateBlue, MediumSpringGreen, MediumTurquoise, MediumVioletRed, MidnightBlue, MintCream, MistyRose, Moccasin,
		NavajoWhite, Navy,
		OldLace, Olive, OliveDrab, Orange,
		OrangeRed, Orchid, PaleGoldenRod, PaleGreen, PaleTurquoise,
		PaleVioletRed, PapayaWhip, PeachPuff, Peru, Pink,
		Plum, PowderBlue, Purple, RebeccaPurple, Red,
		RosyBrown, RoyalBlue, SaddleBrown, Salmon, SandyBrown,
		SeaGreen, SeaShell, Sienna, Silver, SkyBlue,
		SlateBlue, SlateGray, Snow, SpringGreen, SteelBlue,
		Tan, Teal, Thistle, Tomato, Turquoise,
		Violet, Wheat, White, WhiteSmoke, Yellow,
		YellowGreen
	};

	class Color {
	private:
		void setColor(Uint8 red, Uint8 green, Uint8 blue) {
			this->red = red;
			this->green = green;
			this->blue = blue;
		}

		void setFromColorName(ColorName color) {
			const Uint8 MAX = 255;
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
		Color() { setColor(0, 0, 0); }
		Color(Uint8 red, Uint8 green, Uint8 blue) { setColor(red, green, blue); }
		Color(Uint8 red, Uint8 green, Uint8 blue, Opacity opacity) : Color(red, green, blue) { this->opacity = opacity; }
		Color(ColorName color) { setFromColorName(color); }
		Color(ColorName color, Opacity o) : Color(color) { opacity = o; }

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