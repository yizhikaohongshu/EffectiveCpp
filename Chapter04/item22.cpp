/**
 * item 22 : 将成员变量声明为 private
 * 
 * 1. 从语法一致性角度看, 如果成员变量不是 public, 客户唯一能访问对象的办法就是通过成员函数.
 * 
 * 2. 使用函数可以让你对成员变量的控制有更精确的控制, 如果成员变量为 public, 每个人都可以读写它,
 *    但如果你以函数取得或设定其值, 可以实现出 ``不准访问", ``只读访问" ...
 * 
 * 3. 封装
*/

class AccessLevels
{
public:
    int getReadOnly() const { return readOnly; }
    void setReadWrite(int value) { readWrite = value; }
    int getReadWrite() const { return readWrite; }
    void setWriteOnly(int value) { writeOnly = value; }
private:
    int noAccess;
    int readOnly;
    int readWrite;
    int writeOnly;
};

// 自动测速程序, 汽车通过, 速度便被计算并填入一个速度收集器中
class SpeedDataCollection
{
public:
    void addValue(int speed);           // 添加一笔新数据
    double averageSoFar() const;        // 返回平均速度
};

// 考虑 averageSoFar()
// 1. 在 class 内设计一个成员变量, 记录至今以来所有速度的平均值. 当 averageSoFar() 被调用, 返回成员变量即可.
// 2. 令 averageSoFar() 每次调用时重新计算平均值, 此函数有权力调取收集器内的每一笔速度值.

// 由于通过成员函数来访问平均值, 得以替换不同的实现方式
// 将成员变量隐藏在函数接口的背后, 可以为 ``所有可能的实现'' 提供弹性

// 从封装的角度看, 只有两种访问权限: private(提供封装) 和 其他(不提供封装)

/**
 * SUMMARY
 * 
 * 切记将成员变量声明为 private. 这可赋予客户访问数据的一致性, 可细微划分访问控制, 允许约束条件获得保证, 并提供 class 作者以充分实现弹性
 * 
 * protected 并不比 public 更具封装性.
*/