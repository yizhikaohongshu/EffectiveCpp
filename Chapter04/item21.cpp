/**
 * item 21 : 必须返回对象时, 别妄想返回其 reference
 * 
 * 传递一些 references 指向其实不存在的对象, 不是件好事.
*/

class Rational
{
friend const Rational operator*(const Rational& lhs, const Rational& rhs);
// friend const Rational& operator*(const Rational& lhs, const Rational& rhs);
public:
    Rational(int numerator = 0, int denominator = 1);
private:
    int n, d;
};

// reference 只是个名称, 代表某个既有对象, 任何时候看到一个 reference 声明式, 应该立即问自己, 它的另一个名称是什么


////// 函数创建新对象的途径有二: stack 空间 和 heap 空间

// 1. 如果创建一个 local 变量, 就是在 stack 空间创建对象
// const Rational& operator*(const Rational& lhs, const Rational& rhs)
// {
//     Rational result(lhs.n * rhs.n, lhs.d * rhs.d);  // 糟糕的代码
//     return result;
//     // 函数返回一个 reference 指向 result, 但 result 是个 local 对象, local 对象在函数推出前已被销毁
// }
// 任何函数如果返回一个 reference 指向某个 local 对象, 都将一败涂地.(如果函数返回指针指向 local 对象, 也是一样)


// 2. 考虑在 heap 内构造一个对象, 并返回 reference 指向它 
// const Rational& operator*(const Rational& lhs, const Rational& rhs)
// {
//     Rational* result = new Rational(lhs.n * rhs.n, lhs.d * rhs.d);  // 更糟的代码
//     return *result;
// }

// // 面对的问题, 谁该对着被 new 出来的对象实施 delete
// int main()
// {
//     Rational w, x, y, z;
//     w = x * y * z;  // operator*(operator*(x, y), z)
//     // 同一语句调用了两次 operator*, 因而使用了两次 new, 也就需要两次 delete.

//     return 0;
// }

// 一个 ``必须返回新对象"的函数的正确的写法是: 就让那个函数返回一个新对象
inline const Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
}

/**
 * SUMMARY
 * 
 * 绝不要返回 pointer 或 reference 指向一个 local stack 对象;
 * 或返回 reference 指向一个 heap-allocated 对象;
 * 或返回 pointer 或 reference 指向一个 local static 对象.
*/
