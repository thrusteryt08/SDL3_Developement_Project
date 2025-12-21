#include <SDL3/SDL.h>

#include "DataStructures.h"
#include "Core/Window.h"
#include "Objects.h"

#include "Utils/Console.h"
#include "Utils/Random.h"

#include "EventHandling/Event.h"
#include "EventHandling/EventPump.h"




namespace AxionForge {

	class Application {
		Window* window = nullptr;
		bool isRunning = true;
	public:
		Application();
		void INIT();
		void RUN();
		void QUIT();
	};

}