#include <iostream>
using namespace std;

// Constants for minimum and maximum numbers and list sizes
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:  // Private members that are only accesible inside the class itself
    struct Node {   // Node structure to represent each element in the list
        int data;   // The value stored in the node
        Node* prev; // Points to the previous node in the list
        Node* next; // Points to the next node in the list

        // Constructor, initialize a node with data and optional prev. & next pointers
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head; // Pointer to the first node in the list
    Node* tail; // Pointer to the last node in the list

public: // Members that can be accessed outside the class after creating an instance

    // Constructor to initialize an empty list
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // Method to insert a new node with a int data after a specified position
    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        // Create a new node with the given value
        Node* newNode = new Node(value);
        if (!head) { // If the list is empty, set head and tail to the new node
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        // Traverse the list to find the node at the specified position
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) { // If position exceeds list size, print message and delete new node
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        // If the position is valid:
        // Stitch the new node into the list
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next) // If temp isn't the last node, set the next node's prev to new node
            temp->next->prev = newNode;
        else // Otherwise, update tail to the new node
            tail = newNode;
        temp->next = newNode;
    }

    // Method to delete the first node that contains the specified value
    void delete_val(int value) {
        if (!head) return; //return if list is empty

        Node* temp = head; 
        
        // Traverse the list to find the node with the specified value
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Return if value isnt found in list

        // stitch the previous and next nodes of temp together
        if (temp->prev) // If temp has a prev. node:
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next) // if temp has a next node:
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp; // Delete the node containing the value
    }

    // Method to delete the node at a specified position
    void delete_pos(int pos) {
        // Check if the list is empty
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        // If the position is 1, call pop_front to remove the first node
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        // Traverse the list to find the node at the specified position
        for (int i = 1; i < pos; i++){
            // If end of list is reached before the position, print message and return
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        // If temp is null, it means the position doesn't exist in the list
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        // If temp is the last node, call pop_back to remove it
        if (!temp->next) {
            pop_back();
            return;
        }
    
        // If temp exists:
        // Stitch the previous and next nodes of temp together, then delete temp
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    // Method to add a new node with the specified data at the end of the list
    void push_back(int v) {
        // Create a new node with the given value
        Node* newNode = new Node(v);
        if (!tail) // If list is empty, set head and tail to the new node
            head = tail = newNode;
        else { // Otherwise, stitch new node at the end of the list and update tail
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    // Method to add a new node with the specified data at the beginning of the list
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}