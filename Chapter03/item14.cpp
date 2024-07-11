/**
 * item 14 : 在资源管理类中小心 copying 行为
*/

#include <iostream>
#include <pthread.h>
#include <mutex>

using namespace std;

void lock(mutex* pm);
void unlock(mutex* pm);

class Lock
{
public:
    explicit Lock(mutex* pm) : mutexPtr(pm) { lock(mutexPtr); }
    ~Lock() { unlock(mutexPtr); }
private:
    mutex* mutexPtr;
};

