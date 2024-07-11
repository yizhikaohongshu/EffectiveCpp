/**
 * item 10 : 令 operator= 返回一个 reference to *this
*/
#include <iostream>

using namespace std;

class Point
{
friend ostream& operator<<(ostream&, const Point&);
public:
    Point() = default;
    Point(int a, int b) : x(a), y(b) { }
    Point& operator=(const Point&);
private:
    int x, y;
};

Point& Point::operator=(const Point& rhs)
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}

ostream& operator<<(ostream& os, const Point& p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}


int main()
{
    int a, b, c = 0;
    // 连锁赋值
    a = b = c;
    cout << a << " " << b << " " << c << endl;

    // 赋值采用 右结合律
    a = (b = (c = 15));
    cout << a << " " << b << " " << c << endl;

    // 为了实现连锁赋值, 赋值操作符必须返回一个 reference 指向操作符的左侧实参
    Point x(3, 4);
    cout << x << endl;

    Point y, z;
    y = z = x;
    cout << y << " " << z << endl;

    return 0;
}

/**
 * SUMMARY
 * 
 * 令赋值运算符返回一个 reference to *this
*/