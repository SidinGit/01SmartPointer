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
- to access the `MyClass` object directly using dereference operator *`*`* and then *`.`* to access its members