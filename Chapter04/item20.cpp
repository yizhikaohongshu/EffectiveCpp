/**
 * item 20 : 宁以 pass-by-reference-to-const 替换 pass-by-value
 * 
 * 默认情况下 C++ 以 by value 的方式将对象传递给函数, 除非另外指定, 否则函数都是以实际实参的副本为初值
 * , 而调用端所获得的亦是函数返回值的一个副本, 这些副本由函数的 copy ctor 产出, 使得 pass-by-value 可能是费时的操作
*/

#include <iostream>
#include <string>

using std::string;

class Person
{
public:
    Person();
    virtual ~Person();
private:
    string name;
    string address;
};

class Student : public Person
{
public:
    Student();
    ~Student();
private:
    string schoolName;
    string schoolAddress;
};

// bool validateStudent(Student s);

// int main()
// {
//     Student plato;
//     bool platoIsOK = validateStudent(plato);
//     /**
//      * Student 的 copy ctor 会被调用, Student s = plato;
//      * validateStudent返回时, s 会被销毁
//      * (对上述调用而言, 函数的传递成本是 Student 的 copy ctor 和 析构函数)
//      * 
//      * 实际上总体成本是 6次构造函数 和 6次析构函数
//     */

//     return 0;
// }

// pass by reference-to-const
bool validateStudent(const Student& s);
/**
 * 1. 传递方式的效率高得多, 没有任何构造函数或析构函数被调用, 因为没有任何新对象被创建. 
 *    参数声明中的 const 是重要的, 原来的 pass-by-value传递的是对象的一个副本, 调用者知道参数收到保护.
 * 
 * 2. 以 by reference 方式传递参数可以避免 对象切割 问题. 当一个 derived class 对象以 by value 方式
 *    传递并被视为一个 base class 对象, base class 的 copy ctor会被调用.
 * 
*/

class Window
{
public:
    string name() const;
    virtual void display() const;
private:
    string name;
};

class WindowWithScrollBars: public Window
{
    virtual void display() const;
};

// 打印窗口名称
void printNameAndDisplay(Window w)  // 不正确, 参数可能被切割
{
    std::cout << w.name();
    w.display();
}

int main()
{
    WindowWithScrollBars wwsb;
    // printNameAndDisplay(wwsb);

    return 0;
}

// 解决切割问题的办法, 就是以 by-reference-to-const 的方式传递 w 
void printNameAndDisplay(const Window& w)
{
    std::cout << w.name();
    w.display();
}

// 从C++编译器底层看出, references 往往以指针实现出来, 因此 pass by reference 通常意味着传递的是真正的指针(8B)
// 对内置类型而言, 当有机会选择采用 pass by value 或 pass-by-reference-to-const时, 选择 pass-by-value并非没有道理

/**
 * SUMMARY
 * 
 * 尽量以 pass-by-reference-to-const 替换 pass-by-value, 前者通常比较高效, 并可以避免参数切割问题;
 * 
 * 以上规则不适合内置类型, 以及 STL 的迭代器和函数对象. 对他们而言, pass-by-value 往往比较适当.
*/


