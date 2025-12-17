#include "../SDL3_Developement_Project/Include/Basic.h"
/*
template<typename type>
class Array {
	type* array;
public:
	Array() {}
	Array(int size) {
		this->size = size;
		array = new type[size];
	}
	Array(int size, type defaultValue) {
		this->size = size;
		array = new type[size];
		for (int i = 0; i < size; i++)
			array[i] = defaultValue;
	}
	Array(type* array, int size) {
		this.size = size;
		this->array = array;
	}
	Array(const Array& other) {
		size = other.size;
		array = new type[size];
		for (int i = 0; i < size; i++)
			array[i] = other.array[i];
	}
	Array& operator=(const Array& other) {
		if (this != &other) {
			delete[] array;
			size = other.size;
			array = new type[size];
			for (int i = 0; i < size; i++)
				array[i] = other.array[i];
		}
		return *this;
	}
	~Array() {
		delete[] array;
	}
	bool IsEmpty() const {
		return size == 0;
	}
	void Clear() {
		delete[] array;
		array = nullptr;
		size = 0;
	}
	int Size() const {
		return sizeof(array) / sizeof(*array);
	}

	void Sort(bool (*order)(type, type)) {
		std::sort(array, array + size - 1, order);
	}
	type operator[](int index) const {
		return *(array + index);
	}
	void Print() const {
		for (int i = 0; i < size; i++)
			std::cout << *(array + i);
	}
	void Print(char separator) const {
		for (int i = 0; i < size; i++)
			std::cout << *(array + i) << separator;
	}
};
*/
class HashTable {
};

template<typename type>
class Node {
public:
	type value;
	Node<type>* next = nullptr;

	Node() {}
	Node(type value) {
		this->value = value;
		//next = nullptr;
	}
	Node(type value, Node<type>* next) : Node(value) {
		this->next = next;
	}
};

template<typename type>
class LinkedList {
protected:
	Node<type>* root = nullptr;
public:
	
	LinkedList() {}

	LinkedList(const LinkedList& other) {
		copyFrom(other);
	}

	void copyFrom(const LinkedList& other) {
		if (!other.root) {
			root = nullptr;
			return;
		}

		// Copy root
		root = new Node<type>(other.root->value);
		Node<type>* currNew = root;
		Node<type>* currOld = other.root->next;

		// Copy Nodes
		while (currOld) {
			currNew->next = new Node<type>(currOld->value);
			currNew = currNew->next;
			currOld = currOld->next;
		}
	}

	void Add(type value) {
		Node<type>* current = root;
		if (!current) {
			root = new Node<type>(value);
			return;
		}
		while (current->next)
			current = current->next;
		current->next = new Node<type>(value);
		return;
	}
	bool isEmpty() const {
		return root == nullptr;
	}
	int Length() const {
		int length = 0;
		Node<type>* current = root;
		while (current) {
			length++;
			current = current->next;
		}
		return length;
	}
	void Remove(int index) {
		if (index < 0 || !root)
			return;

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
	void Clear() {
		Node<type>* current = root;
		while (current) {
			Node<type>* next = current->next;
			delete current;
			current = next;
		}
		root = nullptr;
	}
	void Sort(bool (*order)(type, type) = Ascending) {
		if (!root || !root->next)
			return; // nothing to sort

		bool swapped;
		do {
			swapped = false;
			Node<type>* curr = root;

			while (curr->next) {
				if (order(curr->value, curr->next->value)) {
					std::swap(curr->value, curr->next->value);
					swapped = true;
				}
				curr = curr->next;
			}
		} while (swapped);
	}

	Node<type>* getRoot() { return root; }

	type& operator[](int index) {
		int len = Length();

		if (index < 0)
			index = len + index;

		if (index < 0 || index >= len)
			throw std::out_of_range("Index out of range");

		Node<type>* current = root;
		for (int i = 0; i < index; i++)
			current = current->next;

		return current->value;
	}
	bool operator==(const LinkedList<type>& other) const {
		Node<type>* a = root;
		Node<type>* b = other.root;

		while (a && b) {
			if (a->value != b->value)
				return false;
			a = a->next;
			b = b->next;
		}

		return a == nullptr && b == nullptr; // both ended at same time
	}
	LinkedList& operator=(const LinkedList& other) {
		if (this != &other) {
			Clear();           // delete existing data
			copyFrom(other);   // deep-copy new data
		}
		return *this;
	}
	type Max() {
		if (!root)
			return type();
		type max = root->value;
		Node<type>* curr = root->next;
		while (curr) {
			if (curr->value > max)
				max = curr->value;
			curr = curr->next;
		}
		return max;
	}
	~LinkedList() {
		Clear();
	}
};

template<typename type>
class DoubleLinkNode {
public:
	type value;
	DoubleLinkNode<type>* next = nullptr;
	DoubleLinkNode<type>* prev = nullptr;

	DoubleLinkNode(type value) {
		this->value = value;
		next = nullptr;
		prev = nullptr;
	}
	DoubleLinkNode(type value, DoubleLinkNode<type>* next) {
		this->value = value;
		this->next = next;
		prev = nullptr;
	}
	DoubleLinkNode(type value, DoubleLinkNode<type>* next, DoubleLinkNode<type>* prev) {
		this->value = value;
		this->next = next;
		this->prev = prev;
	}
};

template<typename type>
class DoubleLinkedList {
	DoubleLinkNode<type>* root = nullptr;
public:
	DoubleLinkedList() {}
	void Add(type value) {
		if (root == nullptr) {
			root = new DoubleLinkNode<type>(value);;
			return;
		}
		DoubleLinkNode<type>* current = root;
		while (current->next) {
			current = current->next;
		}
		current->next = new DoubleLinkNode<type>(value, nullptr, current);
	}
	bool isEmpty() const {
		return root == nullptr;
	}
	int Length() const {
		if (!root)
			return 0;
		int length = 1;
		DoubleLinkNode<int>* current = root;
		while (current->next) {
			length++;
			current = current->next;
		}
		return length;
	}
	void Clear() {
		DoubleLinkNode<int>* current = root;
		DoubleLinkNode<int>* next;
		while (current) {
			next = current->next;
			delete current;
			current = next;
		}
		root = nullptr;
	}
	DoubleLinkNode<type>* GetRoot() {
		return root;
	}
	~DoubleLinkedList() {
		Clear();
	}
};

class TreeNode {
public:
	int value;
	LinkedList<TreeNode*> children;
	TreeNode(int value) {
		this->value = value;
	}

};

template<typename type>
class Stack {
	Node<type>* top = nullptr;
public:
	Stack() {}
	type* Top() {
		return top->value;
	}
	void Push(type value) {
		top = new Node<type>(value, top);
	}
	bool isEmpty() {
		if (top)
			return true;
		return false;
	}
	Node<type> Pop() {
		if (!top)
			return NULL;
		Node<type> temp = *top;
		Node<type>* next = top->next;
		delete top;
		top = next;
		return temp;
	}
};

template<typename type>
class Set : public LinkedList<type> {
public:
	
	Set() {	}

	Set(const LinkedList<type>& other) : LinkedList<type>(other) { }

	Set(const Set& other) : LinkedList<type>(other) { }

	void Add(type value) {
		Node<type>* curr = this->root;
		Node<type>* prev = nullptr;

		while (curr && curr->value < value) {
			prev = curr;
			curr = curr->next;
		}

		// value already exists → do nothing
		if (curr && curr->value == value)
			return;

		// insert new node
		Node<type>* node = new Node<type>(value);
		if (!prev) {
			// insert at beginning
			node->next = this->root;
			this->root = node;
		}
		else {
			node->next = curr;
			prev->next = node;
		}
	}

	Set operator|(const Set& other) const {
		Set result;

		Node<type>* currA = this->root;
		Node<type>* currB = other.root;

		while (currA && currB) {
			if (currA->value < currB->value) {
				result.Add(currA->value);
				currA = currA->next;
			}
			else if (currB->value < currA->value) {
				result.Add(currB->value);
				currB = currB->next;
			}
			else { // equal → add only once
				result.Add(currA->value);
				currA = currA->next;
				currB = currB->next;
			}
		}

		while (currA) {
			result.Add(currA->value);
			currA = currA->next;
		}

		while (currB) {
			result.Add(currB->value);
			currB = currB->next;
		}

		return result;
	}
	Set operator&(const Set& other) const {
		Set result;

		Node<type>* currA = this->root;
		Node<type>* currB = other.root;

		while (currA && currB) {
			if (currA->value < currB->value) {
				currA = currA->next;
			}
			else if (currB->value < currA->value) {
				currB = currB->next;
			}
			else {
				// values are equal → element is in both sets
				result.Add(currA->value);
				currA = currA->next;
				currB = currB->next;
			}
		}

		return result;
	}
	Set operator-(const Set& other) const {
		Set result;  // result will also be sorted automatically

		Node<type>* currA = this->root;
		Node<type>* currB = other.root;

		while (currA) {
			// Skip all elements in B smaller than currA
			while (currB && currB->value < currA->value)
				currB = currB->next;

			// If currA is not in B, add it to result
			if (!currB || currA->value != currB->value)
				result.Add(currA->value);

			currA = currA->next;
		}

		return result;
	}
	Set<std::pair<type, type>> operator*(const Set<type>& other) const {
		Set<std::pair<type, type>> result;

		Node<type>* currA = this->root;
		while (currA) {
			Node<type>* currB = other.root;
			while (currB) {
				result.Add(std::make_pair(currA->value, currB->value));
				currB = currB->next;
			}
			currA = currA->next;
		}

		return result;
	}
};

template<typename T>
class Vector : public std::vector<T> {
public:
	using std::vector<T>::vector; // inherit constructors
	using CompareFunc = bool(*)(T, T);

	~Vector() {
		ClearPointers();
	}

	void Print() const {
		for (const auto& item : *this)
			std::cout << item << " ";
		std::cout << std::endl;
	}

	int Length() const {
		return static_cast<int>(this->size());
	}

	void Sort(CompareFunc order = Ascending<T>) {
		std::sort(this->begin(), this->end(), order);
	}

	void Clear() {
		std::vector<T>::clear();
	}

	void Add(const T& value) {
		this->push_back(value);
	}

	void Insert(int index, const T& value) {
		assert(index >= 0 && index <= Length());
		this->insert(this->begin() + index, value);
	}

	void Remove(const T& value) {
		auto it = std::find(this->begin(), this->end(), value);
		if (it != this->end()) {
			DeleteIfPointer(*it);
			this->erase(it);
		}
	}

	void RemoveAt(int index) {
		assert(index >= 0 && index < Length());
		DeleteIfPointer((*this)[index]);
		this->erase(this->begin() + index);
	}

	// ONLY use if T is a pointer type
	void ClearPointers() {
		for (auto& item : *this)
			DeleteIfPointer(item);
		std::vector<T>::clear();
	}

private:
	template<typename U = T>
	typename std::enable_if<std::is_pointer<U>::value>::type
		DeleteIfPointer(U ptr) {
		delete ptr;
	}

	template<typename U = T>
	typename std::enable_if<!std::is_pointer<U>::value>::type
		DeleteIfPointer(U ptr) {
		// Do nothing if not a pointer
	}
};