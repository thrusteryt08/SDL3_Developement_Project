#pragma once
#include "Node.h"

namespace AxionForge {

	template<typename type>
	class DoubleLinkedList {
		DoubleLinkNode<type>* root = nullptr;
	public:
		DoubleLinkedList() {}
		~DoubleLinkedList();

		// Capacity / Info
		bool isEmpty() const;
		int Length() const;

		// Element access
		DoubleLinkNode<type>* GetRoot();

		// Modifiers
		void Add(type value);
		void Clear();
	};

}
#include "DoubleLinkedList.inl"