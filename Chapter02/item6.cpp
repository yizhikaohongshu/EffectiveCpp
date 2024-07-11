/**
 * item 6: 若不想使用编译器自动生成的函数, 就该明确拒绝
*/

#include <iostream>

// class HomeForSale { };

class HomeForSale
{
public:
    HomeForSale();
private:
    HomeForSale(const HomeForSale&);
    HomeForSale& operator=(const HomeForSale&);
};

int main()
{
    // 任何一笔资产都是独一无二的, 为HomeForSale对象做一份副本是没有道理的
    // 希望 HomeForSale对象的拷贝动作失败
    HomeForSale h1;
    HomeForSale h2;
    // HomeForSale h3(h1);
    // h1 = h2;

    return 0;
}

//所有编译器产出的函数都是 public, 为阻止编译器生成这些函数, 需要我们自行声明
// 声明为 private, 阻止编译器暗自创建其专属版本


// 将链接期错误移至编译期是可能的(越早发现错误越好)
// 只要将 copy ctor 和 copy assignment 操作符声明为 private 就可以办到
class Uncopyable
{
protected:
    Uncopyable();        // 允许 derived 对象构造和析构
    ~Uncopyable();
private:
    Uncopyable(const Uncopyable&);      // 但阻止 copying
    Uncopyable& operator=(const Uncopyable&);
};

// 为阻止 HomeForSale 对象被拷贝, 唯一要做的就是继承 Uncopyable
class HomeForSale : private Uncopyable
{

};

/**
 * 任何人, 甚至是 member 函数或 friend 函数尝试拷贝 HomeForSale对象, 编译器便试着
 * 生成一个 copy ctor 和一个 copy assignment 运算符, 这些``编译器生成版"会尝试调用
 * 其基类的对应兄弟, 那些调用会被编译器拒绝, 因为其基类的拷贝函数是 private
*/


/**
 * 为驳回编译器自动提供的机能, 可将相应的成员函数声明为 private 并且不予实现
 * 像 Uncopyable 这样的基类也是一种做法
*/