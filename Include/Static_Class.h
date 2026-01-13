#pragma once


namespace AxionForge {

	class Static_Class {
	protected:
		Static_Class() {}
		Static_Class(const Static_Class&) = delete;
		Static_Class& operator=(const Static_Class&) = delete;
	};

}