/**
 * item 7: 为多态基类声明 virtual 析构函数
*/

#include <iostream>

using namespace std;

// class TimeKeeper
// {
// public:
//     TimeKeeper();
//     ~TimeKeeper();
// };

// // 原子钟
// class AtomicClock: public TimeKeeper
// { };

// // 水钟
// class WaterClock: public TimeKeeper
// { };

// // 腕钟
// class WristWatch: public TimeKeeper
// { };

// // 工厂函数, 返回指针指向一个计时对象
// // Factory function 返回基类指针, 指向 TimeKeeper 派生类的动态分配对象
// TimeKeeper* getTimeKeeper()
// {
//     // heap
//     TimeKeeper* ptk = new WaterClock();
//     return ptk;
// }

// int main()
// {
//     // 将factory函数返回的每一个对象适当 delete 掉很重要
//     // item 13: 依赖客户执行 delete 动作, 基本上便带有某种错误倾向
//     TimeKeeper* ptk = getTimeKeeper();

//     delete ptk;

//     /** 
//      * 上述出错的问题在于, getTimeKeeper 返回的指针指向一个派生类对象, 
//      * 而那个对象经由一个 基类指针 删除; 目前基类有一个 non-virtual 析构函数
//      * 
//      * C++ 明确指出, 当derived-class 对象经由一个 base class 指针被删除, 而该
//      * base class 带有一个 non-virtual 析构函数, 其结果未定义--实际执行时通常发生的
//      * 是对象的 derived 成分没有被销毁. 通常 base class 部分会被销毁, 造成一种``局部销毁"对象
//      * 
//      * 解决办法, 给 base class 一个 virtual 析构函数
//      * 
//      * class TimeKeeper
//      * {
//      * public:
//      *      TimeKeeper();
//      *      virtual ~TimeKeeper();
//      * };
//      * 
//      * TimeKeeper& pkt = getTimeKeeper();
//      * ...
//      * delete pkt;
//     */
//     return 0;
// }

// 如果类不含 virtual 函数, 通常表示它并不意图被用作一个 base class
// 当 class 不企图当作 base class, 令其析构函数为 virtual 往往是个馊主意
class Point
{
public:
    Point(int xCoord, int yCoord);
    ~Point();
private:
    int x;
    int y;
};

int main()
{
    /**
     * 欲实现出 virtual 函数, 对象必须携带某些信息, 主要用来决定在运行期决定那个 virtual 函数被调用
     * 这份信息通常由 vptr(virtual table pointer)指出, vptr 指向一个由函数指针组成的数组, 称为 vtbl
     * 
     * 
     * 析构函数为 non-virtual : 8  Bytes
     * 析构函数为 virtual     : 16 Bytes
    */
    cout << sizeof(Point) << endl;

    return 0;
}

// 有时候希望拥有 抽象基类, 而手中没有 pure virtual 函数
// 可将该类的析构函数声明为 pure virtual 析构函数
class AWOV
{
public:
    virtual ~AWOV() = 0;
};

// 必须为这个 pure virtual 析构函数提供一份定义
AWOV::~AWOV() { }

/**
 * 析构函数的运作方式是, 最深层派生的那个 class 其析构函数最先被调用
 * , 然后其每个 base class 的析构函数被调用
*/


/**
 * 任何类只要带有 virtual 函数几乎确定应该也有一个 virtual 析构函数
 * 
 * polymorphic(带多态性质的) base classes 应该声明一个 virtual 析构函数.
 * 如果 class 带有任何 virtual 函数, 它就应该拥有一个 virtual 析构函数.
 * 
 * classes 的设计目的如果不是作为 base classes 使用, 或不是为了具备多态性(polymorphically), 
 * 就不改声明 virtual 析构函数.
*/