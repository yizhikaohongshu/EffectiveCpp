/**
 * item 18 : 让接口容易被正确使用, 不易被误用
 * 
 * C++ 的接口有 函数接口, class接口, template接口. 每一种接口都是客户与你代码互动的手段.
 * 理想上, 如果客户企图使用某个接口而却没有获得他所预期的行为, 代码不该通过编译;
 * 如果代码通过了编译, 它的作为就是客户所想要的.
*/

// 为一个用来表现日期的 class 设计构造函数
class Date
{
public:
    Date(int month, int day, int year);
};

// 乍看之下这个接口合理, 但是客户容易犯下至少两个错误
// 第一, 他们也许会以错误次序传递参数
Date d1(30, 3, 2024);

// 第二, 他们也许会传递一个无效的月份或天数
Date d2(2, 30, 2024);

/**
 * 许多客户端错误可以因导入新类型而获得预防.
 * 在防范``不值得拥有的代码''上, 类型系统是你的主要同盟国
 * 
 * 通过导入 外覆类型(wrapper type) 来区别天数、月份和年份, 然后于 Date 构造函数中使用这些类型
*/ 

struct Day
{
    explicit Day(int d) : val(d) { }
    int val;
};

struct Month
{
    explicit Month(int m) : val(m) { }
    int val;
};

struct Year
{
    explicit Year(int y) : val(y) { }
    int val;
};

class NewDate
{
public:
    NewDate(const Month& m, const Day& d, const Year& y);
};

int main()
{
    // NewDate d(30, 3, 1995);                     // 错误, 类型不正确
    // NewDate d(Day(30), Month(3), Year(2024));   // 错误, 类型不正确
    // NewDate d(Month(3), Day(30), Year(2024));   // OK

    /**
     * 令Day, Month, Year 成为成熟且充分锻炼的 classes 并封装其内数据, 比简单使用上述 structs 好.
     * 
     * 明智而审慎地导入新类型对预防 ``接口被误用" 有神奇疗效.
    */

    return 0;
}

// 一旦正确的类型定位, 限制其值有时候是通情达理的
// 一年有 12 个月份
class Month
{
public:
    static Month Jan() { return Month(1); }
    static Month Feb() { return Month(2); }
    static Month Mar() { return Month(3); }
    // ...
    static Month Dec() { return Month(12); }
private:
    explicit Month(int m);
};

NewDate d(Month::Mar(), Day(30), Year(2024));


/**
 * 1. 明智而审慎地导入新类型对预防 ``接口被误用" 有神奇疗效 ;
 * 
 * 2. 预防客户错误的另一个办法是, 限制类型什么事可做, 什么事不能做: 常见的限制是加上 const ;
 * 
 * 3. 除非有好的理由, 否则应该尽量令你的 types 行为与内置 types 一致. Ex: STL size() .
*/

#include <memory>

// 4. 任何接口如果要求客户必须记得做某些事情, 就是有着 ``不正确使用" 的倾向, 因为客户有可能会忘记做那些事情 . item 13
class Investment
{

};

// 为避免资源泄漏, createInvestment 返回的指针最终必须被删除
// , 至少开启两个客户犯错误机会: 没有删除指针, 或删除同一指针超过一次
Investment* createInvestment();

// item 13, 将 createInvestment 的返回值存入智能指针中, 将 delete 的责任推给智能指针
// std::shared_ptr<Investment> pInv(createInvestment());
// , 但客户有可能忘记使用智能指针. 较好的接口设计原则是先发制人, 即令 factory 函数返回一个智能指针

std::shared_ptr<Investment> newCreateInvestment();

/**
 * SUMMARY
 * 
 * 好的接口很容易被正确使用, 不容易被误用. 应该在你的所有接口中努力达成这些性质
 * 
 * ``促进正确使用"的办法包括 接口的一致性 以及与内置类型的行为兼容
 * 
 * ``阻止误用"的办法包括 建立新类型, 限制类型上的操作, 束缚对象值, 以及消除客户的资源管理责任
 * 
 * shared_ptr支持定制型删除器, 可防范 DLL 问题, 可被用来自动解除互斥锁
*/

