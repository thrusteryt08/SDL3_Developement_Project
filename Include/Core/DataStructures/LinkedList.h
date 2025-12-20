#pragma once
#include "Node.h"

namespace AxionForge {

    template<typename type>
    class LinkedList {
    protected:
        Node<type>* root = nullptr;

    public:
        LinkedList() {}
        LinkedList(const LinkedList<type>& other);

		// Add element to the end
        void Add(type value);

		// Clear all elements
        void Clear();

		// Copy from another list
		void copyFrom(const LinkedList<type>& other);

		// Remove element at index
        void RemoveAt(int index);
		// Access element at index
        type& operator[](int index);
        // Access element at index (const)
        const type& operator[](int index) const;
		// Check if the list is empty
		bool isEmpty() const;
		// Assignment operator
        LinkedList<type>& operator=(const LinkedList<type>& other);

        bool operator==(const LinkedList<type>& other) const;
        int Length() const;
        type Max();
        Node<type>* getRoot();
        ~LinkedList();
    };

}
#include "LinkedList.inl"