#include <iostream>
#include <string>
using namespace std;

template<typename T>
class smartPointer{
    private:
        T *ptr; // raw pointer

    public:
        // constructor
        explicit smartPointer(T* p=nullptr):ptr(p) {
            cout<<"smartPointer instance created, Contructor is called!!\n";
        }
        // destructor
        ~smartPointer(){
            cout<<"smartPointer deleted, Destructor is called!!\n";
            delete ptr;
        }

        // overloading dereference operator to access, note: the return type is T&
        T& operator*() const {
            cout<<"overloading dereference operator\n";
            return *ptr; 
        }

        // overloading arrow oprator to access the object's members, note: the return type is T*
        T* operator->() const {
            cout<<"overloading arrow oprator\n";
            return ptr;
        }


 };

// Example class to demonstrate SmartPointer usage
class MyClass {
public:
    MyClass() {
        std::cout << "MyClass Constructor is called\n";
    }

    ~MyClass() {
        std::cout << "MyClass is going out of scope!!!! Destructor is called\n" ;
    }

    void show() const {
        std::cout << "MyClass instance function!\n" ;
    }
};

int main()
{
    // create a smart pointer to manage MyClass instance
    smartPointer<MyClass>sp1(new MyClass()); // sp1 is a smart pointer to an object of MyClass

    // accessing the memeber function show via smart pointer
    sp1->show(); // using arrow operator 
    (*sp1).show(); // using dereference operator

    return 0;
}