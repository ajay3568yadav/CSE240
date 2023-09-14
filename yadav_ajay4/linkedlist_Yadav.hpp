#include <iostream>

#include <stdexcept>

using namespace std;

// templated node class
template < class T >
        class Node {
                public:
                //data type of type "T"
                T data;
                //node pointer to the next node
                Node < T > * next;
                //node pointer to the previous node
                Node < T > * prev;
                public:
                        // parametrized node constructor, data value as argument and sets it to data attribute of the node,
                        // set next and previous pointers to nullptr
                        Node(T data) {
                                this -> data = data;
                                next = nullptr;
                                prev = nullptr;
                        }
                // parametrized node constructor, take node and data as argument
                Node(T data, Node < T > * node) {

                        // sets data argument to data attribute of the node
                        this -> data = data;
                        //set next argument to the node pointer argument
                        next = node;
                        prev = nullptr;
                }
                //default constructor set next and previous to nullptr
                Node() {
                        next = nullptr;
                        prev = nullptr;
                }
                //return data in the node
                T getData() {
                        return data;
                }
                //set data to a give value
                void setData(T data) {
                        this -> data = data;
                }
                Node < T > * getNext() {
                        return next;
                }
                //set next pointer to the node argument passed in the function
                void setNext(Node < T > * node) {
                        next = node;
                }
                //returns the previous node node pointer
                Node < T > * getPrevious() {
                        return prev;
                }
                //set the previous node pointer to the node value passed as argument
                void setPrevious(Node < T > * node) {
                        prev = node;
                }
        };

//templated doubly linkedlist class
template < class T >
        class LinkedList {
                //data members: head node pointer and tail node pointer
                private: Node < T > * head;
                Node < T > * tail;
                public: LinkedList() {
                                //default constructor sets head and tail to null
                                head = nullptr;
                                tail = nullptr;
                        }

                        //destructor
                        ~LinkedList() {
                                Node < T > * current = head;
                                while (current != nullptr) {
                                        //iterating throught the list deleting every node
                                        Node < T > * next = current -> getNext();
                                        delete current;
                                        current = next;
                                }
                                //setting head to null
                                head = nullptr;
                        }
                //adds a node with the given data to the front of the list
                void AddToFront(T data) {
                        //create a node to insert at the front
                        Node < T > * node = new Node < T > (data);
                        //if head is null set the node to the head and tail
                        if (head == nullptr) {
                                head = node;
                                tail = node;

                        } else {
                                //if head is not null then set the next pointer of the node to head
                                node -> next = head;
                                //set previous node pointer of the head to the node
                                head -> prev = node;
                                //set head equals to the node
                                head = node;
                        }

                }
                //add a node of a given data to the end of the list
                void AddToEnd(T data) {
                        //create a new node to insert at the end
                        Node < T > * node = new Node < T > (data);
                        //if tail is null then set the tail and head pointer to the new node
                        if (tail == nullptr) {
                                head = node;
                                tail = node;
                        } else {
                                //if tail is not null then set the node's prev to tail
                                node -> prev = tail;
                                //set tail's next pointer to the node
                                tail -> next = node;
                                //put tail equal to node
                                tail = node;
                        }

                }
                //add a node of a given data at a given index
                void AddAtIndex(T data, int index) {
                        //chekcing for acceptable index; throws index out of range error if index is not valid
                        if (index < 0 || index > Length()) {
                                throw std::out_of_range("Index out of range4");
                        } else if (index == 0) {
                                //add the node to the front if index is 0
                                AddToFront(data);
                        } else if (index == Length()) {
                                //add the node to the end if index is equal to the length of the list
                                AddToEnd(data);
                        } else {
                                //create a node to insert at a given index of the list
                                Node < T > * node = new Node < T > (data);
                                //created a current node pointer to iterate it through the list
                                Node < T > * currentNode = head;
                                for (int i = 0; i < index; i++) {
                                        //iterating through the list by reassigning the currentNode pointer to it next pointer until it reaches 
                                        //(index-1)th element
                                        currentNode = currentNode -> next;
                                }
                                //set node's previous to currentNode's previous
                                node -> prev = currentNode -> prev;
                                //set node's next to currentNode
                                node -> next = currentNode;
                                //set currentNode's previous node's next pointer to node
                                currentNode -> prev -> next = node;
                                //set currentNode's previous to node
                                currentNode -> prev = node;
                        }
                }
                // add a node with give data before a given node; takes a node pointer and data as arguments
                void AddBefore(Node < T > * node, T data) {
                        //if node argument is null then throw invalid argument exception
                        if (node == nullptr) {
                                throw std::invalid_argument("Node cannot be null");
                        }
                        //if node argument is equal to head then add the node to the front of the list
                        if (node == head) {
                                AddToFront(data);
                        } else {
                                //in other cases create a new node with the given data
                                Node < T > * newnode = new Node < T > (data);
                                //set the previous of the new node to the node's previous
                                newnode -> prev = node -> prev;
                                //set newnode's next pointer to the node
                                newnode -> next = node;
                                //set the node's previous's next pointer to the new node
                                node -> prev -> next = newnode;
                                //set node's previous pointer to the newnode
                                node -> prev = newnode;
                        }

                }
                // add a node with give data before a given node; takes a node pointer and data as arguments
                void AddAfter(Node < T > * node, T data) {
                        //if node is null then throw invalid argument exception 
                        if (node == nullptr) {
                                throw std::invalid_argument("Node cannot be null");
                        }
                        //if node is tail then add the new node to the end
                        if (node == tail) {
                                AddToEnd(data);
                        } else {
                                //create a newnode to insert after the given node
                                Node < T > * newnode = new Node < T > (data);
                                //set the newnode's next pointer to the given node's next
                                newnode -> next = node -> next;
                                //set the newnode' previous to the given node
                                newnode -> prev = node;
                                //set the given node's next pointer's previous to the newnode
                                node -> next -> prev = newnode;
                                //set the node's next pointer to the newnode
                                node -> next = newnode;
                        }
                }
                //function removes the data from the from of the linked list
                T RemoveFromFront() {
                        //chekcing if list is empty
                        if (head == nullptr) {
                                throw std::out_of_range("List is empty");
                        }
                        //storing the data of the head in data variable
                        T data = head -> data;
                        //creating a new node pointer and setting it to head
                        Node < T > * node = head;
                        //checking if there is only one node in the list
                        if (head == tail) {
                                //deleting the node by reassiging the head and tail to null
                                head = nullptr;
                                tail = nullptr;
                        } else {
                                // setting head to it's next node pointer
                                head = head -> next;
                                //setting head's previous pointer to null to disconnet the node from the list
                                head -> prev = nullptr;
                        }
                        //delete the node that was at the front
                        delete node;
                        //return the data stored in the deleted node
                        return data;
                }
                // function removes the element form the end of the list
                T RemoveFromEnd() {
                        //chekcing if list id empty
                        if (tail == nullptr) {
                                //throwing exception for empty list
                                throw std::out_of_range("List is empty");
                        }
                        //storing the head data in a variable data
                        T data = head -> data;
                        //set node pointer to the tail
                        Node < T > * node = tail;
                        //chekcing if there is only one node in the list
                        if (head == tail) {
                                //remove the node by setting head and tail pointer to null
                                head = nullptr;
                                tail = nullptr;
                        } else {
                                //if there is more than one node then set the tail node to its previous pointer 
                                tail = tail -> prev;
                                //set tails's next pointer to null to disconnect the end node from the list
                                tail -> next = nullptr;
                        }
                        //deleting the end node
                        delete node;
                        //return the data of the deleted node
                        return data;
                }
                //function removes the First node with the given data
                void RemoveTheFirst(T data) {
                        //checking if the list is empty 
                        if (head == nullptr) {
                                //throwing exception if it is
                                throw std::out_of_range("List is empty");
                        }
                        //checking if head's data matches the data given in the argument 
                        if (head -> data == data) {
                                //if it matches then remove the node from the front
                                RemoveFromFront();
                        } else {
                                //create a node currentnode to iterate through the list
                                Node < T > * currentNode = head;
                                //looping thorugh the list untill the currentnode's next pointer is not null 
                                //and its data is not equal to the data given in the argument
                                while (currentNode -> getNext() && currentNode -> data != data) {
                                        //setting currentnode to its next  to move forward in the list
                                        currentNode = currentNode -> next;
                                }
                                //checking if the currentnode's data matches after the loop terminates
                                if (currentNode -> getData() == data) {
                                        //checking if the currentnode' data matches with the head's data
                                        if (currentNode -> getData() == head -> getData()) {
                                                //setting head to currentnode's next node pointer
                                                head = currentNode -> getNext();
                                                //setting head's previosu to null
                                                head -> setPrevious(nullptr);
                                        }
                                        //checking if currentnode's next is not null 
                                        else if (!currentNode -> getNext()) {
                                                //setting currentnode's previous's next to null
                                                currentNode -> prev = nullptr;
                                        } else {
                                                //setting currentnode's previous's next to current node's next
                                                currentNode -> prev -> next = currentNode -> next;
                                                //setting currentnode's next's previous node pointer to currentnode's previous node pointer
                                                currentNode -> next -> prev = currentNode -> prev;
                                        }
                                        //delete currentnode
                                        delete currentNode;
                                }

                        }

                }
                //function that takes a single argument, the data value to be removed from the linked list.
                void RemoveAllOf(T data) {

                        if (head == nullptr) { //Checks if the linked list is empty.
                                throw std::out_of_range("List is empty"); //Throws an exception if the linked list is empty.
                        }
                        if (head -> data == data) {
                                //Checks if the head node contains the given data.
                                RemoveFromFront();
                        }
                        if (tail -> data == data) {
                                //Checks if the tail node contains the given data
                                RemoveFromEnd();
                        }
                        // Initializes a counter variable to count the number of occurrences of the given data
                        int count = 0;
                        //initializes a pointer to the head node for iterating through the linked list
                        Node < T > * current = head;
                        for (int i = 0; i < Length(); i++) {
                                //Iterates through the linked list by the length of the list
                                //Checks if the current node contains the given data
                                if (current -> data == data) {
                                        count++;
                                }
                                current = current -> next;
                        }
                        //Loops through the linked list for each occurrence of the given data
                        for (int i = 0; i < count; i++) {
                                // Removes the first occurrence of the given data by calling the RemoveTheFirst() function
                                RemoveTheFirst(data);
                        }

                }
                //function that takes a single argument, a pointer to the node before the node to be removed
                T RemoveBefore(Node < T > * node) {
                        //Checks if the linked list is empty, or if the given node is the first node or a nullptr
                        if (head == nullptr || node == head || node == nullptr) {
                                //Throws an exception if the linked list is empty, or if the given node is the first node or a nullptr
                                throw std::invalid_argument("Invalid node or node is the first node in the list");
                        } else {
                                // Initializes a pointer to the head node for iterating through the linked list
                                Node < T > * current = head;
                                // Initializes a pointer to the previous node
                                Node < T > * previous = nullptr;
                                //Loops through the linked list until either the end is reached or the given node is found
                                while (current != nullptr && current != node) {
                                        //Sets the previous pointer to the current node
                                        previous = current;
                                        current = current -> next;
                                }
                                //Checks if the given node was not found in the linked list
                                if (current == nullptr) {
                                        //Throws an exception if the given node was not found in the linked list
                                        throw std::out_of_range("Node not found in list");
                                }
                                //Saves the data of the previous node that will be removed
                                T data = previous -> data;
                                // Checks if the previous node has a previous node
                                if (previous -> prev != nullptr) {
                                        //Reconnects the previous node's previous node to the current node
                                        previous -> prev -> next = current;
                                } else {
                                        //If the previous node does not have a previous node
                                        head = current; // Sets the head node to the current node.
                                }
                                // Sets current node's previous to previousNode's previous
                                current -> prev = previous -> prev;
                                // delete the previous node
                                delete previous;
                                //return data of the removed node
                                return data;
                        }
                }
                //remove the node after a given node, take a node pointer as argument
                T RemoveAfter(Node < T > * node) {
                        if (head == nullptr || node == head || node == nullptr) {
                                //throws invalid argument exception if head or node is null
                                throw std::invalid_argument("Invalid node or node is the first node in the list");
                        } else {
                                //create a node pointer to point at the current node and also to iterate throught the list
                                Node < T > * current = head;
                                //create a next pointer to point at the node next to the current node/ other than current's own next pointer
                                Node < T > * next = head -> next;

                                //loop throught the list untill the next pointer is not null and current is not equal to node
                                while (next != nullptr && current != node) {
                                        //set the next node to its next node
                                        next = next -> next;
                                        //set the current node to its next pointer
                                        current = current -> next;
                                }
                                //checking if next is null
                                if (next == nullptr) {
                                        //thorow exception if next is null
                                        throw std::out_of_range("Node not found in list");
                                }
                                //store the data of the head in data variable
                                T data = next -> data;
                                //set the current's next node pointer to next node's next node pointer
                                current -> next = next -> next;
                                //checking if next node's next is not null
                                if (next -> next != nullptr) {
                                        //set next node's previous pointer to current node
                                        next -> next -> prev = current;
                                } else {
                                        //else set tail to current node 
                                        tail = current;
                                }
                                //delete the next node
                                delete next;
                                //return data from the delted node
                                return data;
                        }
                }
                //return bool(true or false) if the element exists in the list
                bool ElementExists(T data) {
                        //create a node to iterate through the list
                        Node < T > * current = head;
                        while (current != NULL) {
                                //checking if the current node's data matches the given data
                                if (current -> data == data) {
                                        //return true if value matches
                                        return true;
                                }
                                //set current to it's next pointer in every loop until a matching value is found
                                current = current -> next;
                        }
                        //return false if the element is not found
                        return false;
                }
                //return the node of the given data value,(if exists)
                Node < T > * Find(T data) {
                        //chekcing if the element exists or not
                        if (ElementExists(data)) {
                                //if the element exists then loop through the list using a node pointer starting from head
                                Node < T > * node = head;
                                while (node -> data != data) {
                                        //reassigning node pointer to move forward in the list
                                        node = node -> next;
                                }
                                //returns the node containing the given data
                                return node;
                        } else {
                                //throw invalid argument exception if the element doesnt exist
                                throw std::invalid_argument("element not found");
                        }

                }
                //returns the index of the node that contains the given data
                int IndexOf(T data) {
                        //chekcing of the element exists
                        if (ElementExists(data)) {
                                int index = 0;
                                //if the element exists then create a node pointer to loop through the list
                                Node < T > * node = head;
                                while (node -> data != data) {
                                        //reassigning node pointer to move forward in the list
                                        node = node -> next;
                                        index++;
                                }
                                //returns the index of the node containing the given data
                                return index;
                        } else { //returns -1 if element doesnt exist
                                return -1;
                        }

                }
                //returns the data stored in the head node of the list
                T RetrieveFront() {
                        // if head pointer is null then thorw out of range exception
                        if (head == nullptr) {
                                throw std::out_of_range("List is empty");
                        }
                        //else return the data stored in the head node of the list
                        return head -> data;
                }
                //returns the data stored in the tail node of the list
                T RetrieveEnd() {
                        // if tail pointer is null then thorw out of range exception
                        if (tail == nullptr) {
                                throw std::out_of_range("List is empty");
                        }
                        //else return the data stored in the tail node
                        return tail -> data;
                }

                //returns the data stored in a node at the given index
                T Retrieve(int index) {
                        //chekcing for acceptability of the index else throw out of range exception
                        if (index < 0 || index >= Length()) {
                                throw std::out_of_range("Index out of range");
                        } else if (index == 0) {
                                //retirve from front if index is 0
                                RetrieveFront();
                        } else if (index == Length() - 1) {
                                //retirve from end if index is (size_of_the_list - 1)
                                RetrieveEnd();
                        }
                        //iterator for iterating through the list to reach the given index
                        int i = 0;
                        Node < T > * node = head;
                        while (i != index) {
                                i++; //incrementing the iterator value
                                node = node -> next; //moving forward by reassigning node to its next pointer
                        }
                        //return the data stored in the node pointer, at the given index
                        return node -> data;
                }
                //prints the list
                void PrintList() {
                        if (head == nullptr && tail == nullptr) {
                                cout << "List is empty" << endl;
                                return;
                        }
                        //creates a node to iterate through each element
                        Node < T > * node = head;
                        for (int i = 0; i < Length(); i++) {
                                cout << node -> data;
                                if (i != Length() - 1) {
                                        cout << "=";
                                }
                                node = node -> next;
                        }
                        cout << endl;
                }
                //deletes the elements from the list
                void Empty() {
                        if (head == nullptr) {
                                //throw out of range error is the list is emptied
                                throw std::out_of_range("Index out of range1");
                        } else {
                                while (head != nullptr) {
                                        //removeing the node form the front till there is no node left
                                        RemoveFromFront();
                                }
                        }
                }
                //return the length of the list
                int Length() {
                        Node < T > * current = head;
                        int count = 0;
                        while (current) {
                                //while there is a next to current, increase the count
                                current = current -> getNext();

                                count++;
                        }
                        return count;
                }
                //return true if there is no element in the list
                bool isEmpty() {
                        if (head == nullptr && tail == nullptr) {
                                return true;
                        }
                        return false;
                }

        };