#pragma once
#include <algorithm>
#include <stdexcept>

namespace AxionForge {

    template<typename type>
    LinkedList<type>::LinkedList(const LinkedList<type>& other) {
        copyFrom(other);
    }

    template<typename type>
    LinkedList<type>::~LinkedList() {
        Clear();
    }

	// Copy from another list
    template<typename type>
    void LinkedList<type>::copyFrom(const LinkedList<type>& other) {
        if (!other.root) {
            root = nullptr;
            return;
        }
        root = new Node<type>(other.root->value);
        Node<type>* currNew = root;
        Node<type>* currOld = other.root->next;

        while (currOld) {
            currNew->next = new Node<type>(currOld->value);
            currNew = currNew->next;
            currOld = currOld->next;
        }
    }

	// Assignment operator
    template<typename type>
    LinkedList<type>& LinkedList<type>::operator=(const LinkedList<type>& other) {
        if (this != &other) {
            Clear();
            copyFrom(other);
        }
        return *this;
    }

	// Check if the list is empty
    template<typename type>
    bool LinkedList<type>::isEmpty() const {
        return root == nullptr;
    }

	// Get length of the list
    template<typename type>
    int LinkedList<type>::Length() const {
        int length = 0;
        Node<type>* current = root;
        while (current) {
            length++;
            current = current->next;
        }
        return length;
    }

	// Max element
    template<typename type>
    type LinkedList<type>::Max() {
        if (!root) return type();
        type max = root->value;
        Node<type>* curr = root->next;
        while (curr) {
            if (curr->value > max) max = curr->value;
            curr = curr->next;
        }
        return max;
    }

    // Element Access
    template<typename type>
    type& LinkedList<type>::operator[](int index) {
        int len = Length();
        if (index < 0) index = len + index;
        if (index < 0 || index >= len) throw std::out_of_range("Index out of range");

        Node<type>* current = root;
        for (int i = 0; i < index; i++) current = current->next;
        return current->value;
    }

	// Get root node
    template<typename type>
    Node<type>* LinkedList<type>::getRoot() {
        return root;
    }

	// Add element to the end
    template<typename type>
    void LinkedList<type>::Add(type value) {
        if (!root) {
            root = new Node<type>(value);
            return;
        }
        Node<type>* current = root;
        while (current->next) current = current->next;
        current->next = new Node<type>(value);
    }

	// Remove element at index
    template<typename type>
    void LinkedList<type>::RemoveAt(int index) {
        if (index < 0 || !root) return;
        if (index == 0) {
            Node<type>* old = root;
            root = root->next;
            delete old;
            return;
        }
        Node<type>* prev = root;
        for (int i = 0; i < index - 1; i++) {
            if (!prev->next) return;
            prev = prev->next;
        }
        Node<type>* toDelete = prev->next;
        if (!toDelete) return;
        prev->next = toDelete->next;
        delete toDelete;
    }

	// Remove all elements
    template<typename type>
    void LinkedList<type>::Clear() {
        Node<type>* current = root;
        while (current) {
            Node<type>* next = current->next;
            delete current;
            current = next;
        }
        root = nullptr;
    }

    template<typename type>
    bool LinkedList<type>::operator==(const LinkedList<type>& other) const {
        Node<type>* a = root;
        Node<type>* b = other.root;
        while (a && b) {
            if (a->value != b->value) return false;
            a = a->next;
            b = b->next;
        }
        return a == nullptr && b == nullptr;
    }

}