#pragma once
#include <iostream>
#include <string>
#include "Core/StaticClass.h"

namespace AxionForge {

	// Console text colors
    enum class COLOR { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };

	// Static class for console logging with colored output
    class Console : public Static_Class {
    public:
		// Use for logging general messages
        static void Log(const std::string& s) {
            std::cout << "\033[32m" << s << "\033[0m\n";
        }
		// Use for logging warnings
        static void Warning(const std::string& s) {
            std::cout << "\033[33m" << s << "\033[0m\n";
        }
		// Use for logging errors
        static void Error(const std::string& s) {
            std::cout << "\033[31m" << s << "\033[0m\n";
        }
		// Use for logging messages with a specific color
        static void Log(const std::string& s, COLOR color) {
            std::string code;
            switch (color) {
            case COLOR::BLACK:   code = "30"; break;
            case COLOR::RED:     code = "31"; break;
            case COLOR::GREEN:   code = "32"; break;
            case COLOR::YELLOW:  code = "33"; break;
            case COLOR::BLUE:    code = "34"; break;
            case COLOR::MAGENTA: code = "35"; break;
            case COLOR::CYAN:    code = "36"; break;
            case COLOR::WHITE:   code = "37"; break;
            default:             code = "0";  break;
            }
            std::cout << "\033[" << code << "m" << s << "\033[0m\n";
        }

        static void Pause(const std::string& s) {
            std::cout << s << '\n';
			system("pause");
        }

    };

}