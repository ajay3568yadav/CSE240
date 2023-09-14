#include <iostream>

#include <stdexcept>

using namespace std;

template < class T >
        class Node {
                public: T data;
                Node < T > * next;
                Node < T > * prev;
                public: Node(T data) {
                        this -> data = data;
                        next = nullptr;
                        prev = nullptr;
                }
                Node(T data, Node < T > * node) {
                        this -> data = data;
                        next = node;
                        prev = nullptr;
                }
                Node() {
                        next = nullptr;
                        prev = nullptr;
                }
                T getData() {
                        return data;
                }
                void setData(T data) {
                        this -> data = data;
                }
                Node < T > * getNext() {
                        return next;
                }
                void setNext(Node < T > * node) {
                        next = node;
                }
                Node < T > * getPrevious() {
                        return prev;
                }
                void setPrevious(Node < T > * node) {
                        prev = node;
                }

        };

template < class T >
        class LinkedList {
                private: int size;
                Node < T > * head;
                Node < T > * tail;
                public: LinkedList() {
                                head = nullptr;
                                tail = nullptr;
                                size = 0;
                        }

                        ~LinkedList() {
                                Node < T > * current = head;
                                while (current != nullptr) {
                                        Node < T > * next = current -> next;
                                        delete current;
                                        current = next;
                                }
                                head = nullptr;
                        }

                void AddToFront(T data) {
                        Node < T > * node = new Node < T > (data);
                        if (head == nullptr) {
                                head = node;
                                tail = node;

                        } else {
                                node -> next = head;
                                head -> prev = node;
                                head = node;
                        }

                        size++;
                }

                void AddToEnd(T data) {
                        Node < T > * node = new Node < T > (data);
                        //cout<<tail->data<<endl;
                        if (tail == nullptr) {
                                head = node;
                                tail = node;
                        } else {
                                node -> prev = tail;
                                tail -> next = node;
                                tail = node;
                        }

                        size++;
                }
                void AddAtIndex(T data, int index) {

                        if (index < 0 || index > Length()) {
                                throw std::out_of_range("Index out of range4");
                        } else if (index == 0) {
                                AddToFront(data);
                        } else if (index == Length()) {
                                AddToEnd(data);
                        } else {
                                Node < T > * node = new Node < T > (data);
                                Node < T > * currentNode = head;
                                for (int i = 0; i < index; i++) {
                                        currentNode = currentNode -> next;
                                }
                                node -> prev = currentNode -> prev;
                                node -> next = currentNode;
                                currentNode -> prev -> next = node;
                                currentNode -> prev = node;
                                size++;

                        }
                }

                void AddBefore(Node < T > * node, T data) {

                        if (node == nullptr) {
                                throw std::invalid_argument("Node cannot be null");
                        }
                        if (node == head) {
                                AddToFront(data);

                        } else {
                                Node < T > * newnode = new Node < T > (data);
                                newnode -> prev = node -> prev;
                                newnode -> next = node;
                                node -> prev -> next = newnode;
                                node -> prev = newnode;
                                size++;
                        }

                }

                void AddAfter(Node < T > * node, T data) {

                        if (node == nullptr) {
                                throw std::invalid_argument("Node cannot be null");
                        }
                        if (node == tail) {
                                AddToEnd(data);
                        } else {
                                Node < T > * newnode = new Node < T > (data);
                                newnode -> next = node -> next;
                                newnode -> prev = node;
                                node -> next -> prev = newnode;
                                node -> next = newnode;
                                size++;
                        }

                }

                T RemoveFromFront() {
                        if (head == nullptr) {
                                throw std::out_of_range("List is empty");
                        }
                        T data = head -> data;
                        Node < T > * node = head;
                        if (head == tail) {
                                head = nullptr;
                                tail = nullptr;
                        } else {
                                head = head -> next;
                                head -> prev = nullptr;
                        }

                        delete node;
                        size--;

                        return data;
                }

                T RemoveFromEnd() {
                        if (tail == nullptr) {
                                throw std::out_of_range("List is empty");
                        }
                        T data = head -> data;
                        Node < T > * node = tail;
                        if (head == tail) {
                                head = nullptr;
                                tail = nullptr;
                        } else {
                                tail = tail -> prev;
                                tail -> next = nullptr;
                        }
                        delete node;
                        size--;
                        return data;
                }

                void RemoveTheFirst(T data) {
                        if (head == nullptr) {
                                throw std::out_of_range("List is empty");
                        }
                        if (head -> data == data) {
                                RemoveFromFront();
                        } else {
                                Node < T > * currentNode = head;
                                while (currentNode -> getNext() && currentNode -> data != data) {
                                        currentNode = currentNode -> next;
                                }
                                if (currentNode -> getData() == data) {
                                        if (currentNode -> getData() == head -> getData()) {
                                                head = currentNode -> getNext();
                                                head -> setPrevious(nullptr);
                                        } else if (!currentNode -> getNext()) {
                                                currentNode -> getPrevious() -> setNext(nullptr);
                                        } else {
                                                currentNode -> prev -> next = currentNode -> next;
                                                currentNode -> next -> prev = currentNode -> prev;

                                        }
                                        delete currentNode;
                                        size--;
                                }

                        }

                }

                void RemoveAllOf(T data) {

                        if (head == nullptr) {
                                throw std::out_of_range("List is empty");
                        }
                        if (head -> data == data) {
                                RemoveFromFront();
                        }
                        if (tail -> data == data) {
                                RemoveFromEnd();
                        }

                        int count = 0;
                        Node < T > * current = head;
                        for (int i = 0; i < Length(); i++) {
                                if (current -> data == data) {
                                        count++;
                                }
                                current = current -> next;
                        }
                        for (int i = 0; i < count; i++) {
                                RemoveTheFirst(data);
                        }

                }

                T RemoveBefore(Node < T > * node) {
                        if (head == nullptr || node == head || node == nullptr) {
                                throw std::invalid_argument("Invalid node or node is the first node in the list");
                        } else {

                                Node < T > * current = head;
                                Node < T > * previous = nullptr;

                                while (current != nullptr && current != node) {
                                        previous = current;
                                        current = current -> next;
                                }
                                if (current == nullptr) {
                                        throw std::out_of_range("Node not found in list");
                                }

                                T data = previous -> data;
                                current -> prev = previous -> prev;
                                previous -> prev -> next = current;
                                delete previous;
                                size--;
                                return data;

                        }

                }

                T RemoveAfter(Node < T > * node) {
                        if (head == nullptr || node == head || node == nullptr) {
                                throw std::invalid_argument("Invalid node or node is the first node in the list");
                        } else {

                                Node < T > * current = head;
                                Node < T > * next = head -> next;

                                while (next != nullptr && current != node) {
                                        next = next -> next;
                                        current = current -> next;
                                }
                                if (next == nullptr) {
                                        throw std::out_of_range("Node not found in list");
                                }

                                T data = next -> data;
                                current -> next = next -> next;
                                next -> next -> prev = current;
                                delete next;
                                size--;
                                return data;

                        }

                }

                bool ElementExists(T data) {
                        Node < T > * current = head;
                        while (current != NULL) {
                                if (current -> data == data) {
                                        return true;
                                }
                                current = current -> next;
                        }
                        return false;
                }

                Node < T > * Find(T data) {
                        if (ElementExists(data)) {
                                Node < T > * node = head;
                                while (node -> data != data) {
                                        node = node -> next;
                                }
                                return node;
                        } else {
                                throw std::invalid_argument("element not found");
                        }

                }

                int IndexOf(T data) {
                        if (ElementExists(data)) {
                                int index = 0;
                                Node < T > * node = head;
                                while (node -> data != data) {
                                        node = node -> next;
                                        index++;
                                }

                                return index;
                        } else {
                                return -1;
                        }

                }

                T RetrieveFront() {

                        return head -> data ? head != nullptr : throw std::out_of_range("Node not found in list");
                }

                T RetrieveEnd() {

                        return tail -> data ? tail != nullptr : throw std::out_of_range("Node not found in list");
                }
                T Retrieve(int index) {
                        if (index < 0 || index > Length() - 1) {
                                throw std::out_of_range("Index out of range3");
                        } else if (index == 0) {
                                RetrieveFront();
                        } else if (index == Length() - 1) {
                                RetrieveEnd();
                        } else {
                                int i = 0;
                                Node < T > * node = head;
                                while (i != index) {
                                        i++;
                                        node = node -> next;
                                }

                                return node -> data;
                        }
                }
                void PrintList() {
                        if (head == nullptr) {
                                throw std::out_of_range("Index out of range20");
                        } else {
                                Node < T > * node = head;
                                for (int i = 0; i < Length(); i++) {
                                        cout << "[" << node -> data << "]";
                                        if (i != Length() - 1) {
                                                cout << "=";
                                        }
                                        node = node -> next;
                                }
                        }

                }

                void Empty() {
                        if (head == nullptr) {
                                throw std::out_of_range("Index out of range1");
                        } else {
                                while (head != nullptr) {
                                        RemoveFromFront();
                                }
                        }
                }

                int Length() {
                        Node < T > * current = head;
                        int count = 0;
                        while (current) {
                                current = current -> getNext();

                                count++;
                        }
                        return count;
                }

                bool isEmpty() {
                        if (head == nullptr && tail == nullptr) {
                                return true;
                        }
                        return false;
                }

        };