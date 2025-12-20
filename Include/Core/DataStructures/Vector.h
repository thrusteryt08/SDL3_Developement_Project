#pragma once
#include <vector>
#include <type_traits>
#include <iostream>
#include <algorithm>

namespace AxionForge {

    template<typename type>
    class Vector : public std::vector<type> {
    public:
        using std::vector<type>::vector; // inherit constructors
        using CompareFunc = bool(*)(type, type);

        ~Vector();

        void Print() const;
        int Length() const;
        void Sort(CompareFunc order = nullptr);
        void Clear();
        void Add(const type& value);
        void Insert(int index, const type& value);
        void Remove(const type& value);
        void RemoveAt(int index);
        void ClearPointers();

    private:
        template<typename U = type>
        typename std::enable_if<std::is_pointer<U>::value>::type DeleteIfPointer(U ptr);

        template<typename U = type>
        typename std::enable_if<!std::is_pointer<U>::value>::type DeleteIfPointer(U ptr);
    };

}
#include "Vector.inl"