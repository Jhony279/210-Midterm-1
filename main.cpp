#include <iostream>
using namespace std;

// Constants for minimum and maximum numbers and list sizes
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

/// @brief A class representing a doubly linked list data structure
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
        // Create a new node with the given value
        Node* newNode = new Node(v);
        if (!head) // If list is empty, set head and tail to the new node
            head = tail = newNode;
        else { // Otherwise, stitch new node at the start of the list and update head
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    // Method to remove the first node from the list
    void pop_front() {

        if (!head) { // If the list is empty, print message and return
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        // If there's more than one node in the list:
        // update head to next node and set its prev to null
        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else // If there's only one node, set head and tail to null
            head = tail = nullptr;
        delete temp; // Delete the old head node
    }

    // Method to remove the last node from the list
    void pop_back() {
        if (!tail) { // If the list is empty, print message and return
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        // If there's more than one node in the list:
        // update tail to previous node and set its next to null
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else // If there's only one node, set head and tail to null
            head = tail = nullptr;
        delete temp; // Delete the old tail node
    }

    // Destructor to clean up memory by deleting all nodes in the list
    ~DoublyLinkedList() {
        while (head) { // While there are still nodes in the list:
            Node* temp = head; // Store the current head node in temp
            head = head->next; // Move head to the next node in the list
            delete temp; // Delete the old head node stored in temp
        }
    }
    // Method to print the elements of the list from head to tail
    void print() {
        Node* current = head;
        if (!current) { // If the list is empty, print message and return
            cout << "List is empty." << endl;
            return;
        }
        while (current) { // Traverse the list and print each node's data
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Method to print the elements of the list from tail to head
    void print_reverse() {
        Node* current = tail;
        if (!current) { // If the list is empty, print message and return
            cout << "List is empty." << endl;
            return;
        }
        while (current) { // Traverse the list in reverse and print each node's data
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    // Method to print every other element in the list, starting with the first element
    void every_other_element(){
        Node* current = head;
        if (!current) { // If the list is empty, print message and return
            cout << "List is empty." << endl;
            return;
        }

        for (int i = 0; current; i++) { // Traverse the list
            if (i % 2 == 0) // If the index is even, print the node's data
                cout << current->data << " ";
            current = current->next;
        }
    }
};

int main() {
    // Create an instance of the DoublyLinkedList class
    DoublyLinkedList list;

    // Populate list with random integers between MIN_NR and MAX_NR
    for (int i = 0; i < 10; i++)
    // Use the push_back method to add random integers to the end of the list
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);

    list.print(); // Print the entire list
    list.every_other_element(); // Print every other element in the list

    return 0;
}