#pragma once
#include "Static_Class.h"
#include <iostream>

namespace AxionForge {

	class Console : public Static_Class {
	public:
		// Use for logging general messages
		template<typename type>
		static void Log(type text) {
			std::cout << "Message:\t" << text << '\n';
		}

		// Use for logging warnings
		template<typename type>
		static void Warning(type text) {
			std::cout << "Warning:\t" << text << '\n';
		}
		// Use for logging errors
		template<typename type>
		static void Error(type text) {
			std::cout << "Error:\t" << text << SDL_GetError() << '\n';
		}

		static void Pause(const std::string& s) {
			std::cout << s << '\n';
			system("pause");
		}

		static void Clear() {
			system("cls");
		}
		template<typename type>
		static void Write(const type s) {
			std::cout << s;
		}
		template<typename type>
		static void WriteLine(type s) {
			std::cout << s << '\n';
		}
	};

}