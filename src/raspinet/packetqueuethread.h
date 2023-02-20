#ifndef NET_PACKET_QUEUE_THREAD_H
#define NET_PACKET_QUEUE_THREAD_H

namespace net {

// packet queue�Ĵ����߳�
class IPacketQueueHandler {
public:
virtual ~IPacketQueueHandler() {}
virtual bool handlePacketQueue(Packet *packet, void *args) = 0;
};

class PacketQueueThread : public sys::CDefaultRunnable {
public:
// ����
PacketQueueThread();

// ����
PacketQueueThread(int threadCount, IPacketQueueHandler *handler, void *args);

// ����
~PacketQueueThread();

// ��������
void setThreadParameter(int threadCount, IPacketQueueHandler *handler, void *args);

// stop
void stop(bool waitFinish = false);

// push
bool push(Packet *packet, int maxQueueLen = 0, bool block = true);

// pushQueue
void pushQueue(PacketQueue &packetQueue, int maxQueueLen = 0);

// Runnable �ӿ�
void run(sys::CThread *thread, void *arg);

// �Ƿ���㴦���ٶ�
void setStatSpeed();

// ��������
void setWaitTime(int t);

Packet *head()
{
return _queue.head();
}
Packet *tail()
{
return _queue.tail();
}
size_t size()
{
return _queue.size();
}
private:
//void PacketQueueThread::checkSendSpeed()
void checkSendSpeed();

private:
PacketQueue _queue;
IPacketQueueHandler *_handler;
sys::CThreadCond _cond;
sys::CThreadCond _pushcond;
void *_args;
bool _waitFinish;       // �ȴ����

// ���Ʒ����ٶ�
int _waitTime;
int64_t _speed_t1;
int64_t _speed_t2;
int64_t _overage;

// �Ƿ����ڵȴ�
bool _waiting;
};
}

#endif
