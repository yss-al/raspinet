
#ifndef SYSEX_THREAD_H
#define SYSEX_THREAD_H
#include "Shared.h"
#include "Handle.h"
#include "Mutex.h"
#include "Cond.h"
#include "Time.h"

namespace util
{
class Thread : virtual public util::Shared
{
public:

Thread();
virtual ~Thread();

virtual void run() = 0;

int  start(size_t stackSize= 0);

bool isAlive() const;

void _done();

int join();

int detach();

pthread_t id() const;

static void yield();
static void ssleep(const util::Time& timeout);

protected:
bool  _running;   //�߳����б�־
bool _started;    //�߳��Ƿ��ڿ�ʼ״̬
bool _detachable; //�Ƿ�ȫʹ�̴߳��ڷ���״̬
pthread_t _thread;//�߳�ID
util::Mutex _mutex;     //�߳����б�־��
private:
Thread(const Thread&);
Thread& operator=(const Thread&);
};
typedef util::Handle<Thread> ThreadPtr;
}//end namespace util

#endif
