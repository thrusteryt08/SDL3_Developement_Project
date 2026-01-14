#pragma once

namespace AxionForge {

	template<typename type>
	class Node {
	public:
		type value;
		Node<type>* next = nullptr;

		Node() {}
		Node(type value) { this->value = value; }
		Node(type value, Node<type>* next) : Node(value) {
			this->next = next;
		}
	};

}
