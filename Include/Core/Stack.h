#pragma once
#include "Node.h"

namespace AxionForge {

    template<typename type>
    class Stack {
        Node<type>* top = nullptr;
    public:
        Stack() {}
        ~Stack();

        // Capacity
        bool isEmpty() const;

        // Element access
        type* Top();

        // Modifiers
        void Push(type value);
        Node<type> Pop();
    };

}
#include "Stack.inl"