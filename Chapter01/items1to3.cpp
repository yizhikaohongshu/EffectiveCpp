#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

/**
 * item1: 视 C++ 为一个语言联邦
 * 
 * 1. C
 * 2. Object-Oriended C++
 * 3. template C++
 * 4. STL
*/


/**
 * item2: 尽量用 const, inline, enum 代替 #define
*/

// class 专属常量
// class GamePlayer
// {
// private:
//     // 为了将常量的作用域限制于class内, 必须让其成为一个成员, 为确保常量只有一份实体, 将其声明为 static
//     static const int NumTurns = 5;  // 声明
//     int scores[NumTurns];
// };

// int main()
// {
//     GamePlayer g;

//     return 0;
// }


/**
 * item3: 尽可能使用 const
*/
// int main()
// {
//     // const允许程序员指定一种语义约束, 而编译器会强制实施这项约束
//     char greeting[] = "Hello";
//     char* p = greeting;                 // non-const pointer, non-const data
//     const char* q = greeting;           // non-const pointer, const data
//     char* const s = greeting;           // const pointer, non-const data
//     const char* const t = greeting;     // const pointer, const data
//     cout << &p << " " << &q << " " << &s << " " << &t << endl;

//     vector<int> vec = {1, 2};
//     const vector<int>::iterator iter = vec.begin();     // T* const, const pointer
//     vector<int>::const_iterator citer = vec.cbegin();    // const T*, const data

//     *iter = 100;
//     cout << *iter << endl;
    
//     ++citer;
//     cout << *citer << endl;

//     return 0;
// }


// 1. 令函数返回一个 const, 可以降低因客户错误造成的意外, 不会放弃安全性与高效性.
class Rational { };
const Rational operator*(const Rational& lhs, const Rational& rhs);

// Rational a, b, c;
// (a * b) = c;
// "良好的用户自定义类型"的特征是它们避免无端的与内置类型不兼容.


// 2. const 参数
// 除非需要改动参数或 local 对象, 否则将他们声明为 const


// 3. 将 const 实施于成员函数
// 优点: 是class接口容易理解, 得知那个函数可以改动对象内容而那个函数不可以; 使操作 const 对象变为可能
// class TextBlock
// {
// public:
//     TextBlock(const std::string& s) : text(s) { }
//     // 两个成员函数如果只是常量性 (constness) 不同, 可以被重载
//     const char& operator[](std::size_t position) const { return text[position]; }
//     char& operator[](std::size_t position) { return text[position]; }
// private:
//     std::string text;
// };

// void print(const TextBlock& ctb)
// {
//     cout << ctb[0] << endl;     // 调用 const opeator[]
// }

// int main()
// {   
//     TextBlock tb("hello");
//     cout << tb[0] << endl;
//     const TextBlock ctb("world");
//     cout << ctb[0] << endl;

//     return 0;
// }


// 成员函数是 const 意味着什么
// bitwise constness & logical constness

// bitwise const 阵营的人相信, 成员函数只有在不更改对象的任何成员变量(static 除外)时才可以说是 const
// 也就是说它不更改对象内任一bit
#include <cstring>

// class CTextBlock
// {
// public:
//     CTextBlock(const char* str)
//     {
//         pText = new char[strlen(str) + 1];
//         strcpy(pText, str);
//         pText[strlen(str) + 1] = '\0';
//     }
//     ~CTextBlock()
//     {
//         delete pText;
//         pText = nullptr;
//     }
//     char& operator[](std::size_t position) const // bitwise const 声明, 但其实不适当
//     {
//         return pText[position];
//     }
//     void print() const
//     {
//         cout << pText << endl;
//     }   
// private: 
//     char* pText;
// };

// int main()
// {
//     const CTextBlock cctb("Hello");
//     cctb.print();
//     char* ps = &cctb[0];
//     *ps = 'J';
//     cctb.print();

//     return 0;
// }

// 导出 logical constness, 一个 const 成员函数可以修改它所处理的对象内的某些 bits
// 只有在客户端侦测不出的情况下才能如此
// class CTextBlock
// {
// public:
//     std::size_t length() const;
// private:
//     char* pText;
//     std::size_t textLength;
//     bool lengthIsValid;
// };

// std::size_t CTextBlock::length() const
// {
//     if (!lengthIsValid)
//     {
//         textLength = strlen(pText);  // 错误, 在 const 成员函数内不能赋值给 textLength 和 lengthIsValid
//         lengthIsValid = true;
//     }
//     return textLength;
// }

// 解决办法, 利用 C++ 的一个与 const 相关的摆动场: mutable
// mutable 释放掉 non-static 成员变量的 bitwise constness 约束
class CTextBlock
{
public:
    std::size_t length() const;
private:
    char* pText;
    mutable std::size_t textLength;  // 这些成员变量可能总是会被更改, 即使在 const 成员函数内
    mutable bool lengthIsValid;
};

std::size_t CTextBlock::length() const
{
    if (!lengthIsValid)
    {
        textLength = strlen(pText);
        lengthIsValid = true;
    }
    return textLength;
}

/* 在const 和 non-const 成员函数中避免重复 */
class TextBlock
{
public:
    const char& operator[](std::size_t position) const
    {
        // ... 边界检验
        // ... 日志访问信息
        // ... 检验数据完整性
        return text[position];
    }

    char& operator[](std::size_t position)
    {
        // ... 边界检验
        // ... 日志访问信息
        // ... 检验数据完整性
        return text[position];
    }

private:
    std::string text;
};

// 为了避免代码重复以及伴随的编译时间、维护、代码膨胀等问题
// 实现 operator[] 的机能一次并使用它两次, 使用一个去调用另一个
// casting away constness 常量性转除
class TextBlock
{
public:
    const char& operator[](std::size_t position) const
    {
        // ... 边界检验
        // ... 日志访问信息
        // ... 检验数据完整性
        return text[position];
    }

    char& operator[](std::size_t position)
    {
        // 第一次转型来为 *this 添加 const
        // 第二次从 const operator[] 的返回值中移除 const
        return const_cast<char&>(static_cast<const TextBlock&>(*this)[position]);
    }

private:
    std::string text;
};


/**
 * SUMMARY
 * 
 * 1. 将某些东西声明为 const 可帮助编译器侦测出错误用法. const 可被施加于任何作用域内的对象、函数参数、函数返回类型、成员函数本体
 * 2. 编译器强制实施 bitwise constness, 但编写的程序应该使用 "概念上的常量性"
 * 3. 当 const 和 non-const 成员函数有着实质等价的实现时, 令 non-const 版本调用 const 版本可避免代码重复 
 * 
*/






