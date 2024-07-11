/**
 * item 5: 了解 C++ 默默编写并调用哪些函数
 * 
 * 如果没有自己声明, 编译器就会为它声明(编译器版本的)一个 默认构造函数、拷贝构造函数、拷贝赋值运算符和析构函数
 * 这些函数都是 inline 且 public 的
*/
#include <iostream>
#include <string>

using namespace std;


class Empty
{ };

// class Empty
// {
// public:
//     Empty() { }
//     Empty(const Empty& rhs) { }
//     ~Empty() { }

//     Empty& operator=(const Empty& rhs) { }
// };

// 只有当这些函数被需要(被调用), 它们才会被编译器创建出来

// int main()
// {
//     Empty e1;       // default 构造函数
//     Empty e2(e1);   // copy 构造函数
//     e2 = e1;        // copy assignment 运算符

//     return 0;
// }

// template<typename T>
// class NamedObject
// {
// public: 
//     void display() const 
//     {
//         cout << nameValue << " " << objectValue << endl;
//     }
//     NamedObject(const char* name, const T& value)
//     {
//         nameValue = name;
//         objectValue = value;
//     }
//     NamedObject(const std::string& name, const T& value);
// private:
//     std::string nameValue;
//     T objectValue;
// };

// // 编译器生成的 copy ctor 以 no1.nameValue 和 no1.objectValue 为初值
// // 来设定 no2.nameValue, no2.objectValue, 标准 string 有 copy ctor 
// int main()
// {
//     NamedObject<int> no1("Smallest Prime Number", 2);
//     no1.display();
//     NamedObject<int> no2(no1);
//     no2.display();

//     return 0;
// }

template<typename T>
class NamedObject
{
public: 
    void display() const 
    {
        cout << nameValue << " " << objectValue << endl;
    }
    
    NamedObject(const std::string& name, const T& value)
    {
        nameValue = name;
        objectValue = value;
    }
private:
    std::string& nameValue;
    T objectValue;
};

int main()
{
    string newDog("Persephone");
    string oldDog("Satch");

    NamedObject<int> p(newDog, 2);
    NamedObject<int> s(oldDog, 32);

    //  p = s; // 错误, 改动引用自身

    // 如果打算在一个``内含 reference 成员"内支持赋值操作, 必须自己定义一个 copy assignment
    return 0;
}


/**
 * SUMMARY
 * 
 * big 3
 * 编译器可以暗自为 class 创建 默认构造函数, 拷贝构造函数, 拷贝赋值运算符, 析构函数
*/