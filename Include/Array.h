#pragma once
#include <xutility>
namespace AxionForge {

	template<typename type>
	class Array {
	private:
		type* data = nullptr;
		size_t size = 0;
		size_t capacity = 0;

		void Reserve(size_t newCapacity) {
			if (newCapacity <= capacity)
				return;

			type* newData = new type[newCapacity];
			for (size_t i = 0; i < size; ++i)
				newData[i] = std::move(data[i]);

			delete[] data;
			data = newData;
			capacity = newCapacity;
		}

	public:
		// constructors
		Array() = default;

		Array(size_t initialSize)
			: data(new type[initialSize]), size(initialSize), capacity(initialSize) {
		}

		// copy
		Array(const Array& other)
			: data(new type[other.size]), size(other.size), capacity(other.size) {
			for (size_t i = 0; i < size; ++i)
				data[i] = other.data[i];
		}

		Array& operator=(const Array& other) {
			if (this == &other)
				return *this;

			delete[] data;
			data = new type[other.size];
			size = capacity = other.size;

			for (size_t i = 0; i < size; ++i)
				data[i] = other.data[i];

			return *this;
		}

		// move
		Array(Array&& other) noexcept
			: data(other.data), size(other.size), capacity(other.capacity) {
			other.data = nullptr;
			other.size = other.capacity = 0;
		}

		Array(std::initializer_list<type> init)
			: data(nullptr), size(0), capacity(0)
		{
			Reserve(init.size());
			for (const auto& value : init)
				data[size++] = value;
		}

		Array& operator=(Array&& other) noexcept {
			if (this == &other)
				return *this;

			delete[] data;
			data = other.data;
			size = other.size;
			capacity = other.capacity;

			other.data = nullptr;
			other.size = other.capacity = 0;
			return *this;
		}

		// destructor
		~Array() {
			delete[] data;
		}

		// capacity
		size_t Length() const { return size; }
		bool Empty() const { return size == 0; }

		type* Data() { return data; }
		const type* Data() const { return data; }

		// element access
		type& operator[](size_t index) { return data[index]; }
		const type& operator[](size_t index) const { return data[index]; }

		// modifiers
		void Add(const type& value) {
			if (size >= capacity)
				Reserve(capacity == 0 ? 2 : capacity * 2);

			data[size++] = value;
		}

		void Add(type&& value) {
			if (size >= capacity)
				Reserve(capacity == 0 ? 2 : capacity * 2);

			data[size++] = std::move(value);
		}

		void Insert(size_t index, const type& value) {
			if (index > size)
				return;

			if (size >= capacity)
				Reserve(capacity == 0 ? 2 : capacity * 2);

			for (size_t i = size; i > index; --i)
				data[i] = std::move(data[i - 1]);

			data[index] = value;
			++size;
		}

		void RemoveAt(size_t index) {
			if (index >= size)
				return;

			for (size_t i = index; i + 1 < size; ++i)
				data[i] = std::move(data[i + 1]);

			--size;
		}

		void Clear() {
			size = 0;
		}

		// iterators
		class Iterator {
			type* ptr;
		public:
			explicit Iterator(type* p) : ptr(p) {}
			type& operator*() { return *ptr; }
			Iterator& operator++() { ++ptr; return *this; }
			bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
		};

		class ConstIterator {
			const type* ptr;
		public:
			explicit ConstIterator(const type* p) : ptr(p) {}
			const type& operator*() const { return *ptr; }
			ConstIterator& operator++() { ++ptr; return *this; }
			bool operator!=(const ConstIterator& other) const { return ptr != other.ptr; }
		};

		Iterator begin() { return Iterator(data); }
		Iterator end() { return Iterator(data + size); }

		ConstIterator begin() const { return ConstIterator(data); }
		ConstIterator end() const { return ConstIterator(data + size); }

		ConstIterator cbegin() const { return ConstIterator(data); }
		ConstIterator cend() const { return ConstIterator(data + size); }
	};

}