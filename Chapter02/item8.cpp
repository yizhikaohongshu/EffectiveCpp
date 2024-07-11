/**
 * item 8: 别让异常逃离析构函数
*/

// C++ 并不禁止析构函数吐出异常, 但它不鼓励这样做
#include <vector>
#include <iostream>

class Widget
{
public:
    ~Widget() { }
};

void doSomething()
{
    std::vector<Widget> v;
}

/**
 * 当 vector v 被销毁, 它有责任销毁其内含的所有 Widget
 * 
 * 假设 v 内含十个 Widget, 在析构第一个元素期间, 有个异常被抛出
 * , 其他 9 个 Widget 还是应该被销毁(否则它们保存的任何资源都会发生泄漏)
 * 假设第二个 Widget 析构函数又抛出异常, 现在有两个同时作用的异常, 这对C++而言太多了
 * 
 * 在两个异常同时存在的情况下, 程序若不是结束执行就是导致不明确的行为
*/

class DBConnection
{
public:
    static DBConnection create();   // 函数返回 DBConnection对象, 

    void close();   // 关闭连接, 失败则抛出异常
};

// 为确保客户不会忘记在 DBConnection 对象身上调用 close(),
// 一个合理的想法是创建一个用来管理 DBConnection 资源的 class,
// 并在其析构函数中调用 close()
class DBConn
{
public:
    DBConn(DBConnection db) : _db(db) { }
    ~DBConn()   // 确保数据库连接总是会关闭
    {
        _db.close();
    }
private:
    DBConnection _db;
};

// int main()
// {
//     DBConn dbc(DBConnection::create()); // 创建数据库连接


// }   // 在区块结束点, DBConn对象被销毁, 因而自动为 DBConnection 对象调用 close

// 只要调用 close() 成功, 一切都很美好, 但如果该调用异常, DBConn析构函数会传播该异常


// 两个解决办法, DBConn析构函数可以：
// 1. 如果 close 抛出异常就结束程序, abort
// DBConn::~DBConn()
// {
//     try {
//         _db.close();
//     }
//     catch (...) {
//         // 制作运转记录, 记下对 close 的调用失败
//         std::abort();
//     }
// }
// 可以阻止异常从析构函数中传播出去

// 2. 吞下因调用 close 而发生的异常
// DBConn::~DBConn()
// {
//     try {
//         _db.close();
//     }
//     catch (...) {
//         // 制作运转记录, 记下对 close 的调用失败
//     }
// }
// 一般而言, 将异常吞掉是个坏主意, 因为掩盖了``某些动作失败"的重要信息
// 然而有时吞下异常也比负担 ``草率结束程序''或``不明确行为带来的风险''好. 

// 较佳的策略是重新设计 DBConn 接口, 使其客户有机会对可能出现的问题做出反应
class DBConn
{
public:
    void close()    // 供客户使用的新函数
    {
        db.close();
        closed = true;
    }

    ~DBConn()
    {
        if (!closed)
        {
            try {   // 关闭连接(如果客户不那么做的话)
                db.close();
            }
            catch (...) {
                // 制作运转记录, 记下对 close 的调用失败
                // 吞下异常
            }
        }
    }
private:
    DBConnection db;
    bool closed;
};

// 上述接口把调用 close 的责任从 DBConn析构函数 手上移到 DBConn 客户手上
// DBConn 析构函数仍有一个``双保险"调用
// 如果某个操作可能在失败时抛出异常, 而又存在某种需要必须处理该异常, 那个该异常必须来自析构函数以外的某个函数
// 析构函数吐出异常就是危险, 总会带来 过早结束程序 或 发生不明确行为 的风险

// 本例由客户自己调用 close() 并不会对他们带来负担, 而是给他们一个处理错误的机会, 否则他们没机会响应

/**
 * SUMMARY
 * 
 * 析构函数绝对不要吐出异常. 如果一个被析构函数调用的函数可能抛出异常, 析构函数应该捕捉任何异常, 然后吞下它们(不传播), 或结束程序
 * 
 * 如果客户需要对某个操作函数运行期间抛出的异常做出反应, 那么 class 应该提供一个普通函数(而不是在析构函数中)执行该操作
*/