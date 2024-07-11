/**
 * item 25 : 考虑写出一个不抛异常的 swap 函数
*/

// 标准库提供的 swap 算法涉及到三个对象的复制
// template<typename T>
// void swap(T& a, T& b)
// {
//     T temp(a);
//     a = b;
//     b = temp;
// }

#include <vector>

// 对于某些类型而言, 这些复制动作无一必要.
// 最常见的表现形式就是 ``pimpl手法''(pointer to implementation)
class WidgetImpl
{
public:
    // ...
private:
    int a, b, c;
    std::vector<double> v;
};

// 这个类使用 pimpl 手法
class Widget
{
public:
    Widget(const Widget& rhs);
    Widget& operator=(const Widget& rhs)
    {
        // ...
        *pImpl = *(rhs.pImpl);
        // ...
    }
private:
    WidgetImpl* pImpl;
};

// 一旦置换上述两个 Widget 对象值, 唯一需要做的就是置换其 pImpl 指针
// 默认的 swap 算法不只复制三个 Widgets, 还复制三个 WidgetImpl 对象, 缺乏效率

