#include <Windows.h>
// Mutex
#define __mutex_t  CRITICAL_SECTION
#define __mutex_init InitializeCriticalSection
#define __mutex_lock EnterCriticalSection
#define __mutex_unlock LeaveCriticalSection
#define __mutex_try_lock(x) (TryEnterCriticalSection(x) ? 0 : -1)
#define __mutex_destroy DeleteCriticalSection
class noncopyable {
protected:
    noncopyable() {}
    ~noncopyable() {}
private:
    noncopyable(const noncopyable &);
    noncopyable & operator=(const noncopyable &);
};
class Mutex : noncopyable
{
public:
    Mutex() {
        __mutex_init(&mutex);
    }

    ~Mutex() {
        __mutex_destroy(&mutex);
    }

    void lock(void) {
        __mutex_lock(&mutex);
    }

    int try_lock(void) {
        return __mutex_try_lock(&mutex);
    }

    void unlock(void) {
        __mutex_unlock(&mutex);
    }

private:
    __mutex_t mutex;
};
class ScopedLock : noncopyable
{
public:
    explicit ScopedLock(Mutex & m) : mutex(m) {
        mutex.lock();
    }
    explicit ScopedLock(Mutex * m) : mutex(*m) {
        mutex.lock();
    }

    ~ScopedLock() {
        mutex.unlock();
    }
private:    
    Mutex & mutex;
};