/**
 * item 17 : 以独立语句将 newed 对象置入智能指针
*/

#include <iostream>
#include <memory>

class Widget { };

// 揭示处理程序的优先权
int priority();

// 在某动态分配所得的 Widget 上进行某些带有优先权的处理
void processWidget(std::shared_ptr<Widget> pw, int priority);

int main()
{
    // 无法通过编译, shared_ptr构造函数需要一个原始指针, 但该构造函数是 explict 的
    // processWidget(new Widget, priority());

    // 可以写为以下形式
    processWidget(std::shared_ptr<Widget>(new Widget), priority());
    // 虽然在此使用 ``对象管理式资源'' , 但是上述调用却可能出现资源泄露

    /**
     * 调用 processWiget之前, 编译器必须创建代码, 做以下三件事情:
     * 
     * - 调用 priority
     * - 执行 new Widget 表达式
     * - 调用 shared_ptr 构造函数
     * 
     * 但是上述语句执行次序不确定
     * 
     * 1. 执行 new Widget 表达式
     * 2. 调用 priority     (抛出异常)
     * 3. 调用 shared_ptr 构造函数
     * 
     * new Widget 返回的指针遗失, 
    */

    // 解决方案 : 使用分离语句
    // 1. 创建 Widget
    // 2. 将它置入一个智能指针内, 然后再把那个智能指针传给 processWidget
    std::shared_ptr<Widget> pw(new Widget);
    processWidget(pw, priority());
    // 编译器对于 ``跨越语句的各项操作" 没有重新排列的自由(只有在语句内它才拥有那个自由度)

    return 0;
}

/**
 * 以独立语句将 newed 对象存储于(置于)智能指针内, 如果不这样做, 一旦异常被抛出, 有可能导致难以察觉的资源泄漏.
*/