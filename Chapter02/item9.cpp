/**
 * item 9 : 绝不在构造和析构过程中调用 virtual 函数
*/

class Transaction
{
public:
    Transaction();
    virtual void logTransaction() const = 0;    // 日志记录
};

Transaction::Transaction()
{
    // ...
    logTransaction();   // 引发问题的起点
}

class BuyTransaction : public Transaction
{
public:
    virtual void logTransaction() const;
};

class SellTransaction : public Transaction
{
public:
    virtual void logTransaction() const;
};

int main()
{
    BuyTransaction b;
    /**
     * 无疑地会有一个 BuyTransaction 构造函数会被调用, 但首先 Transaction 构造函数一定会更早被调用
     * 此时调用的 logTransaction 是 Transaction 内的版本, 不是 BuyTransaction 内的版本
     * 
     * base classes 构造期间 virtual 函数绝不会下降到 derived classes 阶层
     * 
     * base class 构造函数的执行更早于 derived class 构造函数, 当 base class 构造函数执行时 derived class 的成员变量尚未初始化
     * 如果期间 virtual 函数下降至 derived classes 阶层, derived class 的函数几乎必然取用 local 成员变量, 而那些变量尚未初始化
     * 
     * 由内而外构造, 由外而内析构 
    */

    return 0;
}

