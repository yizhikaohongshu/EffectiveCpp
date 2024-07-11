/**
 * item 12 : 复制对象时勿忘其每一个成分
*/

#include <iostream>
#include <string>

using std::cout;
using std::endl;

// 设计良好的 OO 会将对象的内部封装起来, 只留两个函数负责对象拷贝, copying 函数
void logCall(const std::string& funName);

class Date { };

class Customer
{
public:
    Customer() = default;
    Customer(std::string n) : name(n) { }
    Customer(const Customer& rhs);
    Customer& operator=(const Customer& rhs);
private:
    std::string name;
    
    // 新加入的数据成员
    // Date lastTransaction;
};

void logCall(const std::string& funName)
{
    cout << funName << endl;
}

Customer::Customer(const Customer& rhs) : name(rhs.name)
{
    logCall("Customer copy constructor");
}

Customer& Customer::operator=(const Customer& rhs)
{
    logCall("Customer copy assignment operator");
    name = rhs.name;
    return *this;
}

// int main()
// {
//     // 添加新的成员 lastTransaction, 但是 copying 函数没有添加新成员的赋值操作, 
//     // 对此编译器不发出警告
//     Customer c1("zhang"), c2;
//     c2 = c1;
//     Customer c3 = c1;

//     // 如果为 class 添加一个成员变量, 必须同时修改 copying 函数

//     return 0;
// }

// 一旦发生继承, 会造成一个潜藏危机
class PriorityCustomer: public Customer
{
public:
    PriorityCustomer() = default;
    PriorityCustomer(std::string name, int prior): Customer(name), priority(prior) { }
    PriorityCustomer(const PriorityCustomer& rhs);
    PriorityCustomer& operator=(const PriorityCustomer& rhs);
private:
    int priority;
};

// PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
// {
//     // 调用 Customer 的默认构造函数对其成员进行默认初始化
//     logCall("PriorityCustomer copy constructor");
// }

// PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
// {
//     logCall("PriorityCustomer copy assignment operator");
//     priority = rhs.priority;
//     return *this;
// }

// PriorityCustomer 的 copying 函数看起来好像复制了 PriorityCustomer 内的每一样东西,
// 但是 PriorityCustomer 继承 Customer 成员变量复件, 而那些成员未被复制

/**
 * 任何时候要承担起 为 derived class 撰写 copying 函数的重大责任,
 * 必须很小心的复制其 base class 部分, 那些成分往往是 private, 无法直接访问
 * , 应该让 derived class 的 copying 函数调用相应的 base class 函数
*/

PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs) 
    : Customer(rhs), priority(rhs.priority)  // 调用 base class 的 copy 构造函数
{
    logCall("PriorityCustomer copy constructor");
}

PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
    logCall("PriorityCustomer copy assignment operator");
    Customer::operator=(rhs);   // 对 base class 成分进行赋值动作
    priority = rhs.priority;
    return *this;
}

int main()
{
    PriorityCustomer pc1("zhang", 1), pc2;
    PriorityCustomer pc3(pc1);
    pc2 = pc3;


    return 0;
}

/**
 * 当编写一个 copying 函数, 请确保 
 * 
 * (1), 复制所有 local 成员变量; 
 * (2), 调用所有 base classes 内的适当的 copying 函数.
 * 
 * 
 * 如果 copy构造函数 和 copy assignment 运算符有相近的代码,
 * 消除重复代码的做法是, 建立一个新的成员函数给两者调用, 这样的函数往往是 private 且常被命名为 init
 * 
 * 
 * SUMMARY
 * 
 * Copying 函数应该确保复制 ``对象内的所有成员变量'' 及所有 ``所有 base class成分''.
 * 
 * 不要尝试以某个 copying 函数实现另一个 copying 函数, 应该将共同机制放进第三个函数中, 并由两个 copying 函数共同调用.
*/

