
#ifndef SYS_QUEUE_THREAD_H
#define SYS_QUEUE_THREAD_H

#include <queue>

//using namespace std;

namespace sys {

class CQueueThread : public CDefaultRunnable {
public:
CQueueThread(int threadCount, IQueueHandler *handler, void *args);
~CQueueThread(void);
int writeData(void *data, int len);
void stop();
void run(CThread *thread, void *args);

private:
typedef struct data_pair {
char *data;
int len;
} data_pair;
// queue
std::queue<data_pair*> _queue;

protected:
// �߳���
CThreadCond _mutex;
// ������
IQueueHandler *_handler;
// ��������
void *_args;
};
}

#endif

//////////////////END