namespace AxionForge {

    // Destructor
    template<typename type>
    DoubleLinkedList<type>::~DoubleLinkedList() {
        Clear();
    }

    // Capacity / Info
    template<typename type>
    bool DoubleLinkedList<type>::isEmpty() const {
        return root == nullptr;
    }

    template<typename type>
    int DoubleLinkedList<type>::Length() const {
        int length = 0;
        DoubleLinkNode<type>* current = root;
        while (current) {
            length++;
            current = current->next;
        }
        return length;
    }

    // Element access
    template<typename type>
    DoubleLinkNode<type>* DoubleLinkedList<type>::GetRoot() {
        return root;
    }

    // Modifiers
    template<typename type>
    void DoubleLinkedList<type>::Add(type value) {
        if (!root) {
            root = new DoubleLinkNode<type>(value);
            return;
        }
        DoubleLinkNode<type>* current = root;
        while (current->next) current = current->next;
        current->next = new DoubleLinkNode<type>(value, nullptr, current);
    }

    template<typename type>
    void DoubleLinkedList<type>::Clear() {
        DoubleLinkNode<type>* current = root;
        while (current) {
            DoubleLinkNode<type>* next = current->next;
            delete current;
            current = next;
        }
        root = nullptr;
    }

}