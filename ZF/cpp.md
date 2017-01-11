# CPP 2016
TODO:

- [ ]   dynamic (inheritance) vs. static (template) polymorphism  - when and where?
- [ ]   inheritance vs templates - type safety e.g.
- [x]   inline - when and where?
- [x]   auto - when and where?
- [x]   const - when and where?
- [x]   constexpr - when and where?

- [x]   delete - when and where?
- [ ]   for_each - when and where?
- [ ]   transform
- [ ]   function objects
- [ ]   lambda functions
- [ ]   finally - java vs c++
- [ ]   traits - what is it? and for what?
- [ ]   copy/move constructor
- [ ]   iterator java vs c++  (ArrayList vs bidirectional iterator)
- [ ]   binding - static vs dynamic
- [ ]   memory management
- [ ]   exeptions
- [ ]   regex
- [ ]   threads
- [ ]   liskov substitution principle

Algorithmus schreiben, um zu bestimmen, ob ein Iterator zwischen zwei anderen Iteratoren liegt. "Lösung" :
```cpp
    #include <iterator>
    #include <algorithm>
    
    // random access iterator
    template<typename Iter>
    bool between_impl(Iter fst, Iter lst, Iter i, std::random_access_iterator_tag){
        return ( fst < i && i < lst);
    }
    
    // forward iterator
    template<typename Iter>
    bool between_impl(Iter fst, Iter lst, Iter i, std::forward_iterator_tag){
        auto dist1 = std::distance(fst,i);
        auto dist2 = std::distance(i,lst); 
    
        return ( dist1 > 0 && dist2 > 0);
    }
    
    template<typename Iter>
    bool between(Iter fst, Iter lst, Iter i){
        using iter_tag = typename std::iterator_traits<Iter>::iterator_category;
        return between_impl(fst,lst,i, iter_tag());
    }

```
MyVector Klasse mit int *array und int array_sz als Felder, kein default/copy constructor/assignment operator vorhanden. Was kann schief gehen bezügl. memory leaking? Klasse neu implementieren: Lösung - wenn eine Klasse virtual ist dann braucht man auch einen virtual destructor!!! und die Methode in der erbenden Klasse muss auch als virtual deklariert werden (Frage kam auch letztes Jahr!!) dfdfsd

## Templates vs. Classes (inheritance)

## `inline` Keyword

The `inline` keyword asks the conpiler to inline the a function. Inlining means that the compiler replaces a function call to the inlined funtion by it's body (similar to the `#define` macro). Unlike macros, argument types are checked, eventual conversions performed.
```cpp
inline
void f(int i, char c)
{
  // ...
}
```
- Inlined function definition **have** to be in the header. If the function would be in a `.cpp` file, a function call to this inlined function would get an "unresolved external" error from the linker.

- Today the `inline` keyword is just a hint to the compiler, generally he inlines everything reasonable and can deny the usage of inline if it makes no sense (function body to big).

- Generally a call to a dynamically dispached virtual function cannot be inlined e.g.
    ```cpp
    virt1 *v = rand() % 2 ? new virt1() : new virt2();
    v->virtFunc(5);}
    ```
    But even then, if the compiler can predict the dynamic type, the function may be inlined.

- Also in theory not inlinable are recursive function calls. Compilers may optimize and inlint a certain fixed recursion depth. Tail recursive functions can also be inlined by the compiler.

> **Summary**
> - definition in header
> - gives only hints to the compiler
> - virtual function calls and recursive functions are typically not inlinable

see: [here][1] and [here][2]

[1]: http://stackoverflow.com/questions/19942034/not-inlineable-functions/19942418#19942418
[2]: http://stackoverflow.com/questions/145838/benefits-of-inline-functions-in-c

## `auto` Keyword
The keyword was introduced with C++11. It is a type specifier that deduces the type automatically.

 `auto` is used for type inference, i.e. to declare a type based on the expression, instead of explicitly stating it.

```cpp
auto val = 3; // here, val is declared as an integer 
```
Obviously this isn't such a big advantage over int val = 3 so let's make a better example:
```cpp
std::vector<int> container; // ...
for (auto it = container.begin(); it != it.end(); it++) {
    // type of it is std::vector<int>::iterator, but you don't need to state that
}
```
here you don't have to care about the real container type, i.e. ```std::vector<int>::iterator it = c.begin()```. Additionally, you can change container from vector to list, and the loop would still work without any changes as type of it would be correctly deduced.

> `auto` should **NOT** be (based on Herb Sutter, Scott Meyers and Andrej Alexandrexcu [[1] - minute 25]) if:
>    - it hurts readability
>    - there is concern about automatic type conversion (e.g. from constructors, assignment, template intermediate types, implicit conversion between integer widths)
>
> everywhere else it should be used, it may prevent implicit (unwanted) type conversions!

 [1]: http://stackoverflow.com/questions/6434971/how-much-is-too-much-with-c11-auto-keyword
## `const` Keyword
The keyword `const`can be used to create named constants, a functionality already available in C. Such a constant has a fixed value after compilation and can't be changed! Difference to the `#define` macro is, that the compiler understands and uses the constant instead of simply replacing the value in the code through the preprocessor.
```cpp
const int CONSTANT1=96;
```
The keyword can also be used with pointers, here the positioning is important
```cpp
const int* const2;
//or
int const* const2;
```
declares a `const2` which is a **variable pointer to a fixed integer**, whereas
```cpp
int* const const3;
```
creates a **constant pointer to a variable integer**, and
```cpp
int const * const const4;
//or
const int* const const4;
```
creates a **constant pointer with a fixed integer**!

The Keyword can be used for parameter passing to specify that the passed parameters (mostly used for references) are not modified inside the function.

A method of a class can also be declared `const` to specify that the method does **not** modify member variables of the object!

```cpp
class Class2
{ void Method1() const;
  int MemberVariable1;}
```

It is sometimes inconvenient that `const` methods cannot make changes to internal parts of an object e.g., a long calculation using multiple `const` methods cannot temporary store the results, they have to be returned, and passed back to the next method. Therefore C++11 introduced the `mutable` keyword for non-static class members of a non-reference non-const type and specifies that the member does not affect the externally visible state of the class. This means that `mutable` declared members of a `const` class can be modified by `const` methods.

`const`'ness is infectious, if an object is declared 'const', **only** `const` methods are allowed in such an object.

## `constexpr` Keyword
`constexpr` was introduced with C++11 and tells the compiler that this expression results in **a compile time constant value**, so it can be used in places like array lengths, assigning to const variables, etc... for everything that requires a constant expression.

`constexpr` as defined by C++11 allows to use functions in such expressions that:

- marked  as constexpr
- must be possible to evaluate them at compile time

> - `constexpr` objects are const and are initialized with values known during compilation; 
> - `constexpr` functions produce compile-time results when called with arguments whose values are known during compilation;
> - `constexpr` objects and functions may be used in a wider range of contexts than non-constexpr objects and functions;
> - `constexpr` is part of an object’s or function’s interface.

 It can have a member initialization list but its body must be empty, apart from typedefs and static asserts. Its arguments must have literal types.

The following link describes the differences between `const` and `constexpr`: 
<http://stackoverflow.com/questions/14116003/difference-between-constexpr-and-const/14117121#14117121>

- allows constant expressions involving user-defined types
- provides a way to guarantee that an initialization is done at compile time

- Please note that constexpr is not a general purpose replacement for const (or vise versa):
    - const's primary function is to express the idea that an object is not modified through an interface (even though the object may very well be modified through other interfaces). It just so happens that declaring an object const provides excellent optimization opportunities for the compiler. In particular, if an object is declared const and its address isn't taken, a compiler is often able to evaluate its initializer at compile time (though that's not guaranteed) and keep that object in its tables rather than emitting it into the generated code.
    - constexpr's primary function is to extend the range of what can be computed at compile time, making such computation type safe. Objects declared constexpr have their initializer evaluated at compile time; they are basically values kept in the compiler's tables and only emitted into the generated code if needed.


## `delete` Keyword
The `delete` keyword (**not** `delete[]` for memory) is used to delete/deacitivate implicitely generated constructors, operators, etc ...
Previousely to C++11 constructers and implicit methods could be 'hidden' in the privat scope of an object.
