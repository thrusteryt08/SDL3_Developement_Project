#pragma once
#include "Node.h"

namespace AxionForge {

    template<typename type>
    class DoubleLinkNode {
    public:
        type value;
        DoubleLinkNode<type>* next = nullptr;
        DoubleLinkNode<type>* prev = nullptr;

        DoubleLinkNode(type value) { this->value = value; }
        DoubleLinkNode(type value, DoubleLinkNode<type>* next) : DoubleLinkNode(value) { this->next = next; }
        DoubleLinkNode(type value, DoubleLinkNode<type>* next, DoubleLinkNode<type>* prev) : DoubleLinkNode(value, next) { this->prev = prev; }
    };

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