/**
 * @brief item4: 确定对象被使用前已先被初始化
 * 
 * 规定总是在初始列中列出所有成员变量
 * 总是使用成员初始列
*/
#include <iostream>
#include <string>
#include <list>
#include "item4.hpp"

using std::cout;
using std::endl;
using std::cin;

// class Point
// {
// public:
//     int x;
//     int y;
// };

// int main()
// {
//     // 读取未初始化的值会导致 不明确的行为
//     int x;
//     Point p;

//     cout << x << endl;
//     cout << p.x << " " << p.y << endl;

//     // 永远在使用对象之前先将它初始化
//     // int x = 0;
//     const char* text = "A C-style string";
//     double pi;
//     cin >> pi;

//     return 0;
// }

class PhoneNumber
{

};

class ABEntry
{
public:
    ABEntry(const std::string&, const std::string&, const std::list<PhoneNumber>&);
    ABEntry(const std::string&, const std::string&, const std::list<PhoneNumber>&, int);
private:
    std::string theName;
    std::string theAddress;
    std::list<PhoneNumber> thePhone;
    int numTimeConsulted;
};

// 确保每一个构造函数将对象的每一个成员初始化
// 需要区分 赋值(assignment) 和 初始化(initialization)
// 对象成员变量的初始化动作发生在 **进入构造函数本体之前** . 初始化发生于成员的默认构造函数被自动调用之时.

// member initialization list
ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phone) 
            : theName(name), theAddress(address), thePhone(phone), numTimeConsulted(0) { }

// 首先调用 默认构造函数 为 theName, theAddress, thePhone 设初值, 然后调用 copy assignment 运算符为其赋新值
ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phone, int num)
{
    theName = name;
    theAddress = address;
    thePhone = phone;
    numTimeConsulted = num;
} 

class Directory
{
public:
    Directory();
};

Directory::Directory()
{
    std::size_t disks = tfs.numDisks();
    cout << disks << endl;
};

int main()
{
    std::list<PhoneNumber> p;
    ABEntry zhang("Zhang", "Da Tong", p);

    Directory d;

    return 0;
}