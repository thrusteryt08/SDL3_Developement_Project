namespace AxionForge {

    template<typename type>
    Vector<type>::~Vector() {
        ClearPointers();
    }

    template<typename type>
    void Vector<type>::Print() const {
        for (const auto& item : *this)
            std::cout << item << " ";
        std::cout << std::endl;
    }

    template<typename type>
    int Vector<type>::Length() const {
        return static_cast<int>(this->size());
    }

    template<typename type>
    void Vector<type>::Sort(CompareFunc order) {
        if (order)
            std::sort(this->begin(), this->end(), order);
        else
            std::sort(this->begin(), this->end());
    }

    template<typename type>
    void Vector<type>::Clear() {
        std::vector<type>::clear();
    }

    template<typename type>
    void Vector<type>::Add(const type& value) {
        this->push_back(value);
    }

    template<typename type>
    void Vector<type>::Insert(int index, const type& value) {
        assert(index >= 0 && index <= Length());
        this->insert(this->begin() + index, value);
    }

    template<typename type>
    void Vector<type>::Remove(const type& value) {
        auto it = std::find(this->begin(), this->end(), value);
        if (it != this->end()) {
            DeleteIfPointer(*it);
            this->erase(it);
        }
    }

    template<typename type>
    void Vector<type>::RemoveAt(int index) {
        assert(index >= 0 && index < Length());
        DeleteIfPointer((*this)[index]);
        this->erase(this->begin() + index);
    }

    template<typename type>
    void Vector<type>::ClearPointers() {
        for (auto& item : *this)
            DeleteIfPointer(item);
        std::vector<type>::clear();
    }

    template<typename type>
    template<typename U>
    typename std::enable_if<std::is_pointer<U>::value>::type
        Vector<type>::DeleteIfPointer(U ptr) {
        delete ptr;
    }

    template<typename type>
    template<typename U>
    typename std::enable_if<!std::is_pointer<U>::value>::type
        Vector<type>::DeleteIfPointer(U ptr) {
        // Do nothing if not a pointer
    }

}