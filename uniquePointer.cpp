#include <iostream>
#include <string>
using namespace std;


template <typename T>
class UniquePointer {
private:
    T* ptr;

public:
    // Constructor
    explicit UniquePointer(T* p = nullptr) : ptr(p) {
        cout<<"UniquePointer instance created, Contructor is called!!\n";
    }

    // Destructor
    ~UniquePointer() {
        cout<<"UniquePointer deleted, Destructor is called!!\n";
        delete ptr;
    }

    // Disable copy constructor and copy assignment (no copying allowed)
    UniquePointer(const UniquePointer&) = delete;
    UniquePointer& operator=(const UniquePointer&) = delete;

    // Move constructor: transfers ownership from another UniquePointer
    UniquePointer(UniquePointer&& other) noexcept : ptr(other.ptr) {
        cout<<"Move constructor called\n";
        other.ptr = nullptr;  // Set the other pointer to nullptr after the move
    }

    // Move assignment: transfers ownership from another UniquePointer
    UniquePointer& operator=(UniquePointer&& other) noexcept {
        if (this != &other) {  // Prevent self-assignment
            delete ptr;          // Free the current resource
            ptr = other.ptr;     // Transfer ownership
            other.ptr = nullptr; // Set the other pointer to nullptr
        }
        cout<<"Move assignment operator called\n";
        return *this;
    }

    // Overload dereference operator (*)
    T& operator*() const {
        cout<<"overloading dereference operator\n";
        return *ptr;
    }

    // Overload arrow operator (->)
    T* operator->() const {
        cout<<"overloading arrow oprator\n";
        return ptr;
    }

    // Utility function to release ownership and return the pointer
    T* release() {
        cout<<"utility function to release ownership\n";
        T* oldPtr = ptr;
        ptr = nullptr;
        return oldPtr;
    }

    // Utility function to reset the pointer with a new one
    void reset(T* p = nullptr) {
        cout<<"utility function to reset the pointer with a new one\n";
        delete ptr;  // Free the current resource
        ptr = p;     // Take ownership of the new pointer
    }
};

// A sample class to use with UniquePointer
class MyClass {
public:
    MyClass() {
        cout << "MyClass constructor called!" << '\n';
    }

    ~MyClass() {
        cout << "MyClass destructor called!" << '\n';
    }

    void display() const {
        cout << "Hello from MyClass!" << '\n';
    }
};

int main() {
    // Create a UniquePointer to MyClass
    UniquePointer<MyClass> unique_ptr(new MyClass());
    
    // Use arrow operator to call display function of MyClass
    unique_ptr->display();

    // Transfer ownership to another UniquePointer
    UniquePointer<MyClass> unique_ptr2 = move(unique_ptr);

    // uptr no longer holds ownership, uptr2 now owns the resource
    if (!unique_ptr.release()) {
        cout << "Ownership transferred" << '\n';
    }

    // Use the new owner to access the object
    unique_ptr2->display();

    return 0;
}
