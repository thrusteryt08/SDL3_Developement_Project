#pragma once

namespace AxionForge {

	// Singly linked list node
    template<typename type>
    class Node {
    public:
		// The value stored in the node
        type value;
		// Pointer to the next node
        Node<type>* next = nullptr;

        Node() {}
        Node(type value) { this->value = value; }
        Node(type value, Node<type>* next) : Node(value) {
            this->next = next;
        }
    };

	// Doubly linked list node
    template<typename type>
    class DoubleLinkNode {
    public:
		// The value stored in the node
        type value;
		// Pointer to the next node
        DoubleLinkNode<type>* next = nullptr;
		// Pointer to the previous node
        DoubleLinkNode<type>* prev = nullptr;

        DoubleLinkNode(type value) { this->value = value; }
        DoubleLinkNode(type value, DoubleLinkNode<type>* next) : DoubleLinkNode(value) {
            this->next = next;
        }
        DoubleLinkNode(type value, DoubleLinkNode<type>* next, DoubleLinkNode<type>* prev) : DoubleLinkNode(value, next) {
            this->prev = prev;
        }
    };

}