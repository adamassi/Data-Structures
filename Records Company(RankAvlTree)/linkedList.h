#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<class T>
class Node {
public:
    T data;
    Node<T> *next;
    Node<T> *prev;
    Node() = default;
    Node(const T &data) : data(data), next(nullptr), prev(nullptr) {};
    ~Node() = default;
};

template<class T>
class LinkedList {
    Node<T> *first;
    Node<T> *last;
    int len;
public:

    LinkedList() : first(nullptr), last(nullptr), len(0) {};

    ~LinkedList() {
        Node<T> *curr = first;
        while (curr != nullptr) {
            Node<T> *temp = curr;
            curr = curr->next;
            delete temp;
        }
        first = nullptr;
        last = nullptr;
        len = 0;
    }

    Node<T> *getFirst() const {
        return first;


    }

    Node<T> *getLast() const {
        return last;
    }

    Node<T> *insert(const T &data) {
        Node<T> *new_node = new Node<T>(data);
        if (last == nullptr && first == nullptr) {
            first = new_node;
            last = new_node;
        } else {
            new_node->next = first;
            first->prev = new_node;
            first = new_node;
        }
        len++;
        return new_node;
    }

    void removeNode(Node<T> *nodeToRemove) {
        if (nodeToRemove->next) {
            nodeToRemove->next->prev = nodeToRemove->prev;
        }
        if (nodeToRemove->prev) {
            nodeToRemove->prev->next = nodeToRemove->next;
        }

        if (nodeToRemove == first) {
            first = first->next;
        }
        if (nodeToRemove == last) {
            last = last->prev;
        }
        delete nodeToRemove;
        len--;
    }

    void remove(T data) {
        Node<T> *currNode = first;
        while (currNode != nullptr) {
            if (*(currNode->data) == *data) {
                removeNode(currNode);
                return;
            }
            currNode = currNode->next;
        }
        delete currNode;
    }

    int Len() const {
        return this->len;
    }
};


#endif
