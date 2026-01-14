#pragma once


namespace AxionForge {

	class Singleton {
	protected:
		Singleton() {}
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
	};

}