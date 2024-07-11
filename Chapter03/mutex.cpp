#include <iostream>
#include <mutex>

/**
 * C++ 提供了 4 种语义的互斥量(mutex)
 * 
 * std::mutex                   : 独占互斥量, 不能递归使用
 * std::time_mutex              : 带超时的互斥量, 不能递归使用
 * std::recursive_mutex         : 递归互斥量, 不带超时功能
 * std::recursive_timed_mutex   : 带超时的递归互斥量
*/

#define TRY_MUTEX   0
#define MY_MUTEX    1

std::mutex mtx;

