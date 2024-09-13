# Smart Pointers Implementation Using Raw Pointers and Usage

We have implemented smart pointers using raw pointers. Below is a starter code that mimics a smart pointer. I will explain everything written in the following code blocks. This would help you to have a basic understanding of how a smart pointer works

### The template class for smart pointer

```c++
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

        // overloading dereference operator to access, note: the return type is 'T&'
        T& operator*() const {
            cout<<"overloading dereference operator\n";
            return *ptr;
        }

        // overloading arrow oprator to access the object's members, note: the return type is 'T*'
        T* operator->() const {
            cout<<"overloading arrow oprator\n";
            return ptr;
        }
 };
```

### A sample class whose object we would be pointing to using our smart pointer

```c++
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
```

### Main

```c++
int main()
{
    // create a smart pointer to manage MyClass instance
    smartPointer<MyClass>sp1(new MyClass()); // sp1 is a smart pointer to an object of MyClass

    // accessing the memeber function show via smart pointer
    sp1->show(); // using arrow operator
    (*sp1).show(); // using dereference operator

    return 0;
}
```

## Explanation

Let us start from the main.
An object of `smartPointer` class is created with name `sp1` that points to an object of class `MyClass` created using `new`.
Before we go to the next lines, lets first have a look at the `smartPointer` class structure.

## 1. Why Use `explicit` Before Constructor?

The `explicit` keyword in C++ is used to **prevent implicit conversions** and **copy-initialization** that could occur with single-argument constructors. When a constructor is marked as `explicit`, it can only be invoked through direct initialization, and not through copy initialization.

### Example:

Without `explicit`, the following implicit conversion is allowed:

```cpp
class SmartPointer {
public:
    SmartPointer(int* p) {}  // No explicit
};

SmartPointer sp = 10;  // Implicit conversion from int to SmartPointer
```

Here, `SmartPointer sp = 10;` would be valid, even though it doesn’t make sense.

If you mark the constructor as `explicit`:

```cpp
class SmartPointer {
public:
    explicit SmartPointer(int* p) {}
};

SmartPointer sp = 10;  // Error! No implicit conversion
```

Now the compiler throws an error, preventing implicit conversion. You would need to explicitly call the constructor like this:

```cpp
SmartPointer sp(new int(10));
```

Thus, **`explicit` helps avoid unintentional and incorrect conversions**.

## 2. Constructor with Default Argument

```cpp
explicit SmartPointer(T* p = nullptr) : ptr(p) {}
```

This constructor allows the user to **pass a pointer** during initialization, or if they don’t provide a pointer, **`nullptr` is assigned** by default. This is useful in smart pointers because you may want to initialize them to `nullptr` to indicate they are not yet managing any resource.

Alternatively, you could write the constructor as:

```cpp
explicit SmartPointer() : ptr(nullptr) {}
```

However, this constructor **doesn't allow** the user to pass in a pointer, which removes flexibility. The **first version is preferred** because it gives you the option to pass a pointer or let it default to `nullptr`.

### Key Difference:

- The version with the default argument gives more flexibility, allowing both cases where a pointer is passed or not.
- The version without the argument forces the user to explicitly set the pointer later.

## 3. Dereference Operator (`operator*`)

```cpp
T& operator*() const {
    return *ptr;
}
```

### Breaking it down:

- **Return Type (`T&`)**: This function returns a **reference** (`&`) to an object of type `T`.

  - `T&` means the return value is a reference to the object the smart pointer is managing, allowing you to directly access and modify the original object.

- **Function Name (`operator*()`)**: This is the **dereference operator**. It allows you to dereference the smart pointer, just like you would with a raw pointer (`*ptr`).

- **Body (`return *ptr;`)**:
  - `ptr` is the raw pointer inside the smart pointer.
  - `*ptr` dereferences the pointer to give access to the object it points to.
  - Returning `*ptr` as `T&` means you're giving a reference to the original object.

### Why Return by Reference?

Returning by reference avoids making a copy of the object. In smart pointers, you typically want to work with the **original object**, not a copy, to avoid unnecessary overhead and ensure any changes are made to the actual object being managed.

## 4. Arrow Operator (`operator->`)

```cpp
T* operator->() const {
    return ptr;
}
```

### Breaking it down:

- **Return Type (`T*`)**: This function returns a **pointer** (`T*`) to the object being managed by the smart pointer.

  - The return type is the raw pointer itself (`ptr`), allowing you to access the object’s members directly.

- **Function Name (`operator->()`)**: This is the **arrow operator**. It allows you to use the smart pointer as if it were a raw pointer to access members of the object it points to.

- **Body (`return ptr;`)**:
  - `ptr` is the raw pointer.
  - Returning `ptr` gives access to the object's members.

### Why Return a Pointer in `operator->()`?

The arrow operator needs to return a **pointer** because C++ expects the `->` operator to be followed by member access (`sp->member`). By returning the raw pointer, the smart pointer can provide direct access to the object's members in a natural and efficient way.

## 5. Difference Between `operator*()` and `operator->()`

### `operator*()`:

- Returns a **reference** (`T&`) to the object.
- Used when you want direct access to the object itself.

### `operator->()`:

- Returns a **pointer** (`T*`) to the object.
- Used to access the **members** of the object.

In most cases, the `operator->()` is simply a wrapper that returns the internal raw pointer, while `operator*()` provides direct access to the underlying object.

### Example:

```cpp
SmartPointer<MyClass> sp(new MyClass());

// Using the dereference operator (*)
(*sp).someMethod();  // Dereferences the smart pointer, then accesses the object

// Using the arrow operator (->)
sp->someMethod();    // Directly accesses the object’s members via the pointer
```

- **`(*sp).someMethod()`**: First dereferences the smart pointer, then calls `someMethod()` on the object.
- **`sp->someMethod()`**: Uses the arrow operator to directly call `someMethod()` on the object via the pointer.

Now lets come back to the next two lines of `main`

```c++

// Using the arrow operator (->)
sp1->smartPointer();    // Directly accesses the object’s members via the pointer
// Using the dereference operator (*)
(*sp1).samrtPointer();  // Dereferences the smart pointer, then accesses the object

```

Following the explanation above we can see how the smartPointer object sp1 is handled:

- to access the data members of `MyClass` object directly using **`->`** operator as we would do in case of any raw pointer
- to access the `MyClass` object directly using dereference operator _`_`* and then *`.`\* to access its members

The final output is :

```
MyClass Constructor is called
smartPointer instance created, Contructor is called!!
overloading arrow oprator
MyClass instance function!
overloading dereference operator
MyClass instance function!
smartPointer deleted, Destructor is called!!
MyClass is going out of scope!!!! Destructor is called
```

# Unique Pointer Implementation in C++

This project demonstrates how to implement a basic `UniquePointer` in C++, which mimics the behavior of `std::unique_ptr`. It includes move semantics, preventing copying, and managing ownership of a dynamically allocated object.

## Overview

A `UniquePointer` is a smart pointer that:

- Ensures **unique ownership** of a resource (like a dynamically allocated object).
- Implements **move semantics** to transfer ownership between pointers efficiently.
- Prevents copying to maintain unique ownership.

### Key Features

- **Move Constructor**: Transfers ownership of the managed object.
- **Move Assignment Operator**: Transfers ownership while preventing resource leaks.
- **No Copying**: Copy constructor and assignment operator are deleted.
- **Custom Destructor**: Automatically deletes the managed resource when the `UniquePointer` goes out of scope.

The code file is **`uniquePointer.cpp`** at root.

## Code Implementation

```cpp
template<typename T>
class UniquePointer {
private:
    T* ptr;

public:
    // Constructor
    explicit UniquePointer(T* p = nullptr) : ptr(p) {}

    // Destructor
    ~UniquePointer() {
        delete ptr;
    }

    // Delete copy constructor and assignment to prevent copying
    UniquePointer(const UniquePointer&) = delete;
    UniquePointer& operator=(const UniquePointer&) = delete;

    // Move constructor: transfers ownership from another UniquePointer
    UniquePointer(UniquePointer&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;  // Set the other pointer to nullptr after the move
    }

    // Move assignment: transfers ownership from another UniquePointer
    UniquePointer& operator=(UniquePointer&& other) noexcept {
        if (this != &other) {
            delete ptr;          // Free the current resource
            ptr = other.ptr;     // Transfer ownership
            other.ptr = nullptr; // Set the other pointer to nullptr
        }
        return *this;
    }

    // Overloading dereference operator to access the object
    T& operator*() const {
        return *ptr;
    }

    // Overloading arrow operator to access the object's members
    T* operator->() const {
        return ptr;
    }

    // Release function: releases ownership of the pointer
    T* release() {
        T* oldPtr = ptr;
        ptr = nullptr;
        return oldPtr;
    }

    // Utility function to reset the pointer with a new one
    void reset(T* p = nullptr) {
        delete ptr;  // Free the current resource
        ptr = p;     // Take ownership of the new pointer
    }
};
```

## Explanation

### Deleting Copy Constructor

```c++
UniquePointer(const UniquePointer&) = delete; // copy constructor deleted
```

The copy constructor allows an object to be copied, i.e., creating a new object as a copy of an existing object. For a smart pointer, if you allowed copying, you could end up with two pointers managing the same resource, which could lead to problems like **double deletion**.

By writing `= delete`, you are telling the compiler to forbid copying of UniquePointer objects. If any code tries to copy a `UniquePointer` object, the compiler will throw an `error`.

```c++
UniquePointer<int> uptr1(new int(10));
UniquePointer<int> uptr2 = uptr1;  // ERROR: Copy constructor is deleted

```

This ensures that there is always a **single owner** of the resource at any point in time.

### Deleting Copy Assignment Operator

```c++
UniquePointer& operator=(const UniquePointer&) = delete; // copy assignment operator deleted
```

The copy assignment operator is used when you assign one object to another after both have been created. For instance, you might want to assign the contents of one `UniquePointer` to another :

```c++
UniquePointer<int> uptr1(new int(10));
UniquePointer<int> uptr2;
uptr2 = uptr1;  // ERROR: Copy assignment operator is deleted
```

But this is also forbidden in `UniquePointer` because it would mean both smart pointers now point to the **same** resource, leading to similar problems like **double deletion**.

If you don’t delete the copy constructor and the copy assignment operator

1. Copying will be allowed, and you might end up with multiple UniquePointer objects pointing to the same resource.
2. Both copies would attempt to delete the same resource when they go out of scope, leading to undefined behavior like double free errors.

### Move Constructor
```c++
UniquePointer(UniquePointer&& other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;  // Set the other pointer to nullptr after the move
}
```
**Purpose :** This constructor is called when an object is moved (i.e., ownership is transferred) rather than copied. For example, if you do 
```c++
UniquePointer uptr2 = std::move(uptr1);
```
the move constructor will be invoked.

**What happens :**
- `ptr` (the raw pointer of the current object) is assigned the value of `other.ptr` (the raw pointer from the `other` `UniquePointer`).
- `other.ptr` is then set to `nullptr`, meaning the original object (`other`) *no longer holds ownership of the resource.*

**Result :** *Ownership is transferred* from `other` to the current object, and the *original object (`other`) is left empty (pointing to `nullptr`)*.

**`noexcept` :** Ensures that this move operation won’t throw exceptions. This is important for performance optimization in certain situations like in *standard containers* (e.g., `std::vector`).
### Move Assignment operator
```c++
UniquePointer& operator=(UniquePointer&& other) noexcept {
    if (this != &other) {  // Prevent self-assignment
        delete ptr;          // Free the current resource
        ptr = other.ptr;     // Transfer ownership
        other.ptr = nullptr; // Set the other pointer to nullptr
    }
    return *this;
}
```
**Purpose :** This operator is called when an already existing UniquePointer needs to take ownership of the resource from another UniquePointer. For example, 
```c++
uptr2 = std::move(uptr1);
```

**What happens :**

- ***Self-assignment check :*** `if (this != &other)` ensures that if you're assigning the object to itself (e.g., `uptr1 = std::move(uptr1);`), nothing happens to avoid errors.
- ***Free current resource :*** If the current object (`this`) already holds a resource, it is deleted with `delete ptr` to avoid memory leaks.
- ***Transfer ownership :*** The raw pointer from `other` is assigned to `this->ptr`, transferring ownership of the resource.
- ***Reset `other.ptr` :*** `other.ptr` is set to `nullptr` so the `other` object no longer holds the resource.

**Result :** *Ownership is transferred* from `other` to the current object, and the *original object (`other`) is left empty (pointing to `nullptr`)*.


Finally, move semantics :
1. **Avoid unnecessary copying :** Instead of creating a deep copy of the resource, the resource's ownership is simply transferred, which is more efficient.
2. **Prevent double deletion :** After the move, the original `UniquePointer` no longer owns the resource (since its pointer is set to `nullptr`), so it won't attempt to `delete` the resource when it goes out of scope.

### Understanding `&` and `&&` Operators

**Lvalue (`&`, locator value):** Refers to an object that occupies some identifiable location in memory. Essentially, it's anything you can take the address of. For example, variables like int `x = 10;` where `x` is an lvalue because it has a memory location.

**Rvalue (`&&`, right-hand value):** Refers to a temporary object or a literal value that does not persist beyond the expression that uses it. For example, the number `10` in int `x = 10;` is an rvalue because it's a temporary value.

1. **Lvalue Reference (`&`) :** Typically used when you want to refer to an existing object that will persist in memory.
    - Can only bind to lvalues.
    - Example: `int& x = var;` (where `var` is a variable).
2. **Rvalue Reference (`&&`) :** Used to implement move semantics, allowing efficient resource management by transferring 
    ownership of temporary objects instead of copying them.
    - Can only bind to rvalues (temporary values).
    - Example: `int&& y = 10;` (binds to the temporary `10`).

### Release() vs Move()
```c++
T* release() {
        T* oldPtr = ptr;
        ptr = nullptr;
        return oldPtr;
    }
```
When you use the `release()` function, you manually release the ownership of the raw pointer from the `UniquePointer`, which returns the raw pointer but does not `delete` the pointer or free the resource. You then have to explicitly assign this raw pointer to another `UniquePointer` (or manage it yourself). After calling `release()`, the original `UniquePointer` is left with `nullptr`.

```c++
UniquePointer<int> uptr1(new int(10));
int* rawPtr = uptr1.release();  // release gives the raw pointer, uptr1 becomes nullptr
UniquePointer<int> uptr2(rawPtr); // now uptr2 takes ownership of the raw pointer
```

**Move() Semantics :**
- *Automatic:* Transfer of ownership is handled automatically by the move constructor/assignment operator.
- After the move, the original `UniquePointer` is safely set to `nullptr`.
- No need to manually manage the raw pointer.

<br>


**Release() Function :** 
- *Manual:* You manually release the raw pointer and then reassign it to another `UniquePointer` (or manage it yourself).
- You need to ensure that the raw pointer is handled correctly to avoid memory leaks.
- After calling `release()`, you are responsible for assigning the raw pointer to a new owner (e.g., another `UniquePointer`).