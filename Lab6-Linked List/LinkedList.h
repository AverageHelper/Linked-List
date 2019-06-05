#include <iostream>
#include <sstream>
#include "LinkedListInterface.h"

template <typename T>
class LinkedList: public LinkedListInterface<T> {
private:
    /// A wrapper around list data.
    struct Node {
        T data;
        Node* next;
        Node(T newData) {
            this->data = newData;
            next = nullptr;
        }
    };
    
    /// The first node in the list.
    Node* headNode;
    int count;
    
public:
    // Constructor
    LinkedList(void) {
        headNode = nullptr;
        count = 0;
    }
    
    // Destructor
    virtual ~LinkedList(void) {
        clear();
    }
    
    /**
     member
     
     Returns a node containing the given value if it exists in the list. Returns `nullptr` otherwise.
     
     */
    Node* member(T value) {
        Node* currentNode = headNode;
        
        while (currentNode != nullptr) {
            if (currentNode->data == value) {
                return currentNode;
            }
            currentNode = currentNode->next;
        }
        return nullptr;
    }
    
    /**
     nodePrior
     
     Returns the node just prior to the target node, if it exists in the list.
     
     */
    Node* nodePrior(T value) {
        Node* currentNode = headNode;
        
        if (currentNode == nullptr) { return nullptr; }
        
        while (currentNode->next != nullptr && currentNode->next->data != value) {
            currentNode = currentNode->next;
        }
        
        if (currentNode->next != nullptr && currentNode->next->data == value) {
            return currentNode;
        }
        return nullptr;
    }
    
    /**
     contains
     
     Returns `true` if the list contains the given value.
     
     */
    bool contains(T value) {
        if (member(value) == nullptr) {
            return false;
        }
        return true;
    }
    
    /**
     insertHead
     
     A node with the given value should be inserted at the beginning of the list.
     
     Do not allow duplicate values in the list.
     */
    virtual void insertHead(T value) {
        // No duplicates!
        if (this->contains(value)) { return; }
        
        Node* newNode = new Node(value);
        
        if (headNode != nullptr) {
            newNode->next = headNode;
        }
        
        headNode = newNode;
        count += 1;
    }
    
    /**
     insertTail
     
     A node with the given value should be inserted at the end of the list.
     
     Do not allow duplicate values in the list.
     */
    virtual void insertTail(T value) {
        // No duplicates!
        if (this->contains(value)) { return; }
        
        Node* currentNode = headNode;
        
        if (currentNode == nullptr) {
            return insertHead(value);
        }
        
        Node* newNode = new Node(value);
        
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        
        currentNode->next = newNode;
        count += 1;
    }
    
    /**
     insertAfter
     
     A node with the given value should be inserted immediately after the
     node whose value is equal to insertionNode.
     
     A node should only be added if the node whose value is equal to
     insertionNode is in the list. Do not allow duplicate values in the list.
     */
    virtual void insertAfter(T value, T insertionNode) {
        Node* insertion = member(insertionNode);
        if (insertion == nullptr) { return; }
        if (member(value) != nullptr) { return; }
        
        Node* newNode = new Node(value);
        
        if (insertion->next != nullptr) {
            Node* nextNode = insertion->next;
            insertion->next = newNode;
            newNode->next = nextNode;
            
        } else {
            insertion->next = newNode;
        }
        
        count += 1;
    }
    
    /**
     remove
     
     The node with the given value should be removed from the list.
     
     The list may or may not include a node with the given value.
     */
    virtual void remove(T value) {
        
        if (headNode != nullptr && headNode->data == value) {
            Node* nextNode = headNode->next;
            delete headNode;
            headNode = nextNode;
            count -= 1;
            return;
        }
        
        Node* priorNode = nodePrior(value);
        if (priorNode == nullptr) { return; }
        if (priorNode->next == nullptr || priorNode->next->data != value) { return; }
        
        Node* nextNode = priorNode->next->next;
        delete priorNode->next;
        priorNode->next = nextNode;
        
        count -= 1;
    }
    
    /**
     clear
     
     Remove all nodes from the list.
     */
    virtual void clear() {
        Node* currentNode = headNode;
        
        while (currentNode != nullptr) {
            Node* nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
        
        headNode = nullptr;
        count = 0;
    }
    
    /**
     at
     
     Returns the value of the node at the given index. The list begins at
     index 0.
     
     If the given index is out of range of the list, throw an out of range exception.
     */
    virtual T at(int index) {
        int currentIndex = 0;
        Node* currentNode = headNode;
        
        while (currentNode != nullptr && currentIndex < index) {
            currentNode = currentNode->next;
            currentIndex += 1;
        }
        
        if (currentNode != nullptr && currentIndex == index) {
            return currentNode->data;
        }
        
        // Throw exception
        throw std::out_of_range("Index " + to_string(index) + " is out of range ending before " + to_string(size()));
    }
    
    /**
     size
     
     Returns the number of nodes in the list.
     */
    virtual int size() {
        return this->count;
    }
    
    /**
     toString
     
     Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
     There should be no trailing space at the end of the string
     
     For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
     "1 2 3 4 5"
     */
    virtual string toString() {
        Node* currentNode = headNode;
        stringstream result;
        
        while (currentNode != nullptr) {
            result << currentNode->data;
            if (currentNode->next != nullptr) {
                result << " ";
            }
            currentNode = currentNode->next;
        }
        
        return result.str();
    }
};
