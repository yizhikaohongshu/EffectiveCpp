/**
 * Chapter 3  资源管理
 * 
 * item 13 : 以对象管理资源
 * 
 * C++ 常见的资源有动态分配内存, 文件描述器, 互斥锁, 图形界面中的字型和笔刷, 数据库连接, 网络socket
 * 
 * 无论哪种资源, 当我们不在使用时, 必须归还给系统
*/

#include <iostream>
#include <memory>

class Investment { };   // ``投资类型"体系中的 root class

/**
 * 工厂函数, 返回指针, 指向 Investment 继承体系内的动态分配对象
 * 调用者有责任删除它
*/
Investment* createInvestment();

// void f()
// {
//     Investment* pInv = createInvestment();  
//     // ...
//     delete pInv;
// }

// 若干种情况可能无法删除资源, Ex. ...区域内有一个过早的 return 语句
// ...区域抛出异常

// 为确保 createInvestment 返回的资源总是被释放, 需要将资源放到对象内
// 当控制流离开 f, 该对象的析构函数会自动释放那些资源.

void f()
{
    std::unique_ptr<Investment> pInv(createInvestment()); // unique_ptr 的析构函数自动对其所指对象调用 delete
    
    // ...
}

// unique_ptr的替代方案是 ``引用计数型智能指针(reference-counting smart pointer, RCSP)", 持续追踪共有多少对象指向某笔资源
// 在无人指向时自动删除该资源.

void f()
{
    // ...
    std::shared_ptr<Investment> pInv1(createInvestment());
    // ...
    std::shared_ptr<Investment> pInv2(pInv1);   // pInv1 和 pInv2指向同一个对象
    pInv1 = pInv2;
    // ...
}   // pInv1 和 pInv2 被销毁, 它们所指向的对象也被自动销毁

/**
 * 以对象管理资源
 * 
 * 
 * 1. 获得对象后立即放进管理对象内. ``以对象管理资源" 的观念常被称为 ``资源取得时机便是初始化时机(Resource Acquisition Is Initialization; RAII)"
 *    因为我们几乎总是在获得一笔资源后于同一语句内以它初始化某个管理对象. 有时候获得的资源被拿来赋值某个管理对象, 但不论哪一种做法, 每一笔资源都在获得
 *    的同时立刻被放进管理对象中
 * 
 * 2. 管理对象运用析构函数确保资源被释放
 *    不论控制流如何离开区块, 一旦对象被销毁(例如对象离开作用域), 其析构函数自然会被自动调用, 于是资源被释放. 
*/

/**
 * SUMMARY
 * 
 * 为防止资源泄漏, 请使用 RAII 对象, 它们在构造函数中获得资源并在析构函数中释放资源;
 * 
 * 两个常被使用的 RAII 类是 std::shared_ptr 和 std::unique_ptr
*/