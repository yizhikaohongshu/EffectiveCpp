/**
 * item 15 : 在资源管理类中提供对原始资源的访问
 * 
 * 可以依赖资源管理类来处理和资源之间的所有互动, 而不用直接处理原始资源.
*/

#include <iostream>
#include <memory>

class Investment
{ 
public:
    bool isTaxFree() const;
};

Investment* createInvestment();

int daysHeld(const Investment* pi);     // 返回投资天数983


int main()
{
    std::unique_ptr<Investment> pInv(createInvestment());
    // 不存在从 "std::unique_ptr<Investment, std::default_delete<Investment>>" 到 "const Investment *" 的适当转换函
    // int days = daysHeld(pInv);

    // 此时需要一个函数可将 RAII class 对象转换为其所内含之原始资源
    
    // 显式转换, 智能指针提供了一个 get() 成员, 它会返回智能指针内部的原始指针
    int days = daysHeld(pInv.get());

    // 隐式转换, 智能指针也重载了指针取值(pointer dereferencing)运算符 (operator-> && operator*), 允许隐式转换至底部的原始指针
    std::shared_ptr<Investment> pInv1(std::make_shared<Investment>(createInvestment()));
    bool taxable1 = !(pInv1->isTaxFree());
    
    bool taxable2 = !((*pInv).isTaxFree());


    return 0;
}

/**
 * RAII classes 并不是为了封装某物而存在, 它们的存在是为了确保一个特殊行为--资源释放会发生
 * 
 * 就像多数设计良好的 classes 一样, 它隐藏了客户不需要看的部分, 但备妥客户需要的所有东西
 * 
 * APIs 往往要求访问原始资源(raw resources), 所以每一个 RAII class 应该提供一个``取得其所管理之资源''的办法
 * 
 * 对原始资源的访问可能经由 显式转换 或 隐式转换 . 一般而言显式转换比较安全, 但隐式转换对客户比较方便. 
*/
