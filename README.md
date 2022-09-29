# SimplePlagChecker
## Assignment in CS 154 (Spring 2021-22)

This is an elementary implementation of plagiarism checker in `C++` for `C++`.
There are two implementaions : `impl1.cpp` and `impl2.cpp`

`impl1.cpp` counts the number of `C++` keywords (frequently used ones) like `int`, `if`, 
`class` etc for each of the files and the score is given based on matching the number under each
category and the number of total keywords. This implementation can easily detect the cases where one tries to just ***change the variable names***
and ***reorganise the code***. This code helps to detect certain kinds of copying (lazy ones **:)**)

However this implementation is not fool-proof as:
* there might be cases where two completely different codes may have matching
* it can be fooled by using different/lesser keywords. Eg. `int x; int y;` can be changed to `int x,y;`.


`impl2.cpp` works well for programs with MANY CLASSES or FUNCTIONS. In this program, 
the classes and functions in both the codes are recognised. Classes by the class name and functions
By their input signature (# of `(int, double, float, char, string, bool, other)` (that is for a function
`f(int a, int b)` signature will be `{2, 0, 0, 0, 0, 0, 0}`).

***Note:*** Both these implememtations are very limited. Also, the criterion for score might not be universal as there might be some 
code where boilerplate is huge, if that is the case, the scores will be high.
