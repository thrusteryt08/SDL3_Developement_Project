#pragma once
#include "Node.h"
#include <initializer_list>

namespace AxionForge {

	template<typename type>
	class LinkedList {
	protected:
		Node<type>* root = nullptr;

	public:
		LinkedList() = default;

		LinkedList(const LinkedList& other) {
			copyFrom(other);
		}

		LinkedList(std::initializer_list<type> init) {
			for (const auto& value : init)
				Add(value);
		}
		~LinkedList() {
			Clear();
		}

		Node<type>* getRoot() { return root; }
		const Node<type>* getRoot() const { return root; }

		// Add element to end
		void Add(type value) {
			if (!root) {
				root = new Node<type>(value);
				return;
			}
			Node<type>* current = root;
			while (current->next)
				current = current->next;
			current->next = new Node<type>(value);
		}

		// Remove element at index
		void RemoveAt(int index) {
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
		void Clear() {
			Node<type>* current = root;
			while (current) {
				Node<type>* next = current->next;
				delete current;
				current = next;
			}
			root = nullptr;
		}

		int Length() const {
			int length = 0;
			Node<type>* current = root;
			while (current) {
				++length;
				current = current->next;
			}
			return length;
		}

		bool isEmpty() const {
			return root == nullptr;
		}

		type Max() const {
			if (!root) return type{};
			type max = root->value;
			Node<type>* curr = root->next;
			while (curr) {
				if (curr->value > max)
					max = curr->value;
				curr = curr->next;
			}
			return max;
		}

		void copyFrom(const LinkedList& other) {
			Node<type>* current = other.root;
			while (current) {
				Add(current->value);
				current = current->next;
			}
		}

		type& operator[](int index) {
			int len = Length();
			if (index < 0) index += len;
			if (index < 0 || index >= len)
				throw std::out_of_range("Index out of range");

			Node<type>* current = root;
			for (int i = 0; i < index; i++)
				current = current->next;

			return current->value;
		}

		const type& operator[](int index) const {
			int len = Length();
			if (index < 0) index += len;
			if (index < 0 || index >= len)
				throw std::out_of_range("Index out of range");

			Node<type>* current = root;
			for (int i = 0; i < index; i++)
				current = current->next;

			return current->value;
		}

		LinkedList& operator=(const LinkedList& other) {
			if (this != &other) {
				Clear();
				copyFrom(other);
			}
			return *this;
		}

		bool operator==(const LinkedList& other) const {
			Node<type>* a = root;
			Node<type>* b = other.root;

			while (a && b) {
				if (a->value != b->value)
					return false;
				a = a->next;
				b = b->next;
			}
			return a == nullptr && b == nullptr;
		}

		class iterator {
			Node<type>* current;

		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = type;
			using difference_type = std::ptrdiff_t;
			using pointer = type*;
			using reference = type&;

			iterator(Node<type>* node = nullptr)
				: current(node) {
			}

			reference operator*() const {
				return current->value;
			}

			pointer operator->() const {
				return &current->value;
			}

			iterator& operator++() {
				if (current) current = current->next;
				return *this;
			}

			iterator operator++(int) {
				iterator temp = *this;
				++(*this);
				return temp;
			}

			bool operator==(const iterator& other) const {
				return current == other.current;
			}

			bool operator!=(const iterator& other) const {
				return current != other.current;
			}
		};
		class const_iterator {
			const Node<type>* current;

		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = type;
			using difference_type = std::ptrdiff_t;
			using pointer = const type*;
			using reference = const type&;

			const_iterator(const Node<type>* node = nullptr)
				: current(node) {
			}

			reference operator*() const {
				return current->value;
			}

			pointer operator->() const {
				return &current->value;
			}

			const_iterator& operator++() {
				if (current) current = current->next;
				return *this;
			}

			const_iterator operator++(int) {
				const_iterator temp = *this;
				++(*this);
				return temp;
			}

			bool operator==(const const_iterator& other) const {
				return current == other.current;
			}

			bool operator!=(const const_iterator& other) const {
				return current != other.current;
			}
		};
		iterator begin() {
			return iterator(root);
		}
		iterator end() {
			return iterator(nullptr);
		}

		const_iterator begin() const {
			return const_iterator(root);
		}
		const_iterator end() const {
			return const_iterator(nullptr);
		}
	};

}