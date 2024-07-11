/**
 * item 11 : 在 operator= 中处理 ``自我赋值''
*/

#include <iostream>

// 自我赋值发生在对象被赋值给自己时
// class Widget { };

// int main()
// {
//     Widget w;
//     w = w;

//     return 0;
// }

// 实际上两个对象只要来自同一继承体系, 它们甚至不需要声明为相同类型就可能造成``别名"
// class Base { };

// class Derived: public Base
// {

// };

// // rb 和 *pd 有可能指向一个 derived class 对象
// void doSomething(const Base& rb, Derived* pd);

// class Bitmap 
// { };

// class Widget
// {
// public:
//     Widget(Bitmap b) : pb(new Bitmap(b)) { }

//     Widget& operator=(const Widget& rhs);
// private:
//     Bitmap* pb;
// };

// // 一份不安全的 operator= 实现版本
// Widget& Widget::operator=(const Widget& rhs)
// {
//     delete pb;
//     pb = new Bitmap(*rhs.pb);
//     return *this;
// }

// // 自我赋值问题是, operator=函数内的 *this(赋值的目的端)和 rhs 有可能是同一个对象
// // delete 就不只是销毁当前对象的 bitmap, 它也销毁 rhs 的 bitmap

// // 传统做法是在 operator= 最前面的一个证同测试, 达到自我赋值的检验目的
// Widget& Widget::operator=(const Widget& rhs)
// {
//     if (this == &rhs) return *this;

//     delete pb;
//     pb = new Bitmap(*rhs.pb);
//     return *this;
// }

// // 如果 new Bitmap 导致异常(分配时内存不足或Bitmap的copy ctor抛出异常), Widget最终会持有一个指针指向一块被删除的 Bitmap
// // 这样的指针无法安全删除它们, 也无法读取它们的值

// // 让 operator= 具备 ``异常安全性'' 往往自动获得 ``自我赋值安全'' 的回报
// // 越来越多人对 ``自我赋值'' 的处理态度是倾向不去管它, 把焦点放在 ``异常安全性'' 上
// Widget& Widget::operator=(const Widget& rhs)
// {
//     // 在复制 pb 所指东西之前别删除 pb
//     Bitmap* pOrig = pb;
//     pb = new Bitmap(*rhs.pb);  
//     delete pOrig;
//     return *this;
// }

// 如果 new 抛出异常, pb 还会保持异常; 同时上述代码也能处理自我赋值

// 替代方案, 使用 copy and swap 技术, 这个技术和 ``异常安全性''有密切关系
class Widget
{
public:
    void swap(Widget& rhs);
};

Widget& Widget::operator=(const Widget& rhs)
{
    Widget temp(rhs);
    swap(temp);
    return *this;
}

/**
 * SUMMARY
 * 
 * 确保当对象自我赋值时 operator= 有良好行为. 其中技术包括比较 ``来源对象'' 和 ``目标对象''的地址, 精心周到的语句顺序, 以及 copy-and-swap
 * 确定任何函数如果操作一个以上的对象, 而其中多个对象是同一个对象时, 其行为仍然正确.
*/