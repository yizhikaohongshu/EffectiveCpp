/**
 * item 24 : 若所有参数皆需类型转换, 请为此采用 non-member函数
*/

class Rational
{
public:
    // 构造函数刻意不为 explicit; 允许 int 向 Rational 隐式转换
    Rational(int numerator = 0, int denominator = 1);
    int numerator() const;
    int denominator() const;

    // 将 operator* 写成 Rational 成员函数的写法
    const Rational operator*(const Rational& rhs) const;
private:
    // ...
};

int main()
{
    Rational oneEight(1, 8);
    Rational oneHalf(1, 2);

    Rational result = oneHalf * oneEight;
    result = result * oneHalf;

    // 希望支持混合运算, 拿 Rationals 和 ints 相乘
    result = oneHalf * 2;
    // result = 2 * oneHalf;   // 错误

    // result = oneHalf.operator*(2);
    // 本例不存在一个接受 int 和 Rational 作为参数的 non-member operator

    return 0;
}

// ** 只有当参数被列于参数列表内, 这个参数才是隐式类型转换的合格参与者 **
// 让 operator* 成为一个non-member 函数, 允许编译器在每个实参身上执行隐式类型转换.
const Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

/**
 * SUMMARY
 * 
 * 不能够只因函数不该成为 member, 就自动让它成为 friend
 * 如果需要为某个函数的所有参数(包括被this指针所指的那个隐喻参数)进行类型转换, 那么这个函数必须是个 non-member
*/
