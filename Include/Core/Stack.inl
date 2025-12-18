namespace AxionForge {

    // Destructor
    template<typename type>
    Stack<type>::~Stack() {
        while (!isEmpty()) Pop();
    }

    // Capacity
    template<typename type>
    bool Stack<type>::isEmpty() const {
        return top == nullptr;
    }
    
    // Element access
    template<typename type>
    type* Stack<type>::Top() {
        return top ? &top->value : nullptr;
    }

    // Modifiers
    template<typename type>
    void Stack<type>::Push(type value) {
        top = new Node<type>(value, top);
    }

    template<typename type>
    Node<type> Stack<type>::Pop() {
        if (!top) return Node<type>();

        Node<type> temp = *top;
        Node<type>* nextNode = top->next;
        delete top;
        top = nextNode;
        return temp;
    }

}