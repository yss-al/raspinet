#ifndef NET_CHANNEL_POOL_H_
#define NET_CHANNEL_POOL_H_

#define CHANNEL_CLUSTER_SIZE 25
namespace net {

class ChannelPool {

public:
ChannelPool();

~ChannelPool();

Channel *allocChannel();

bool freeChannel(Channel *channel);
bool appendChannel(Channel *channel);

Channel* offerChannel(uint32_t id);

Channel* getTimeoutList(int64_t now);

bool appendFreeList(Channel *addList);

int getUseListCount() {
return static_cast<int32_t>(_useMap.size());
}

void setExpireTime(Channel *channel, int64_t now);

private:
__gnu_cxx::hash_map<uint32_t, Channel*> _useMap; // ʹ�õ�map
std::list<Channel*> _clusterList;                // cluster list
sys::CThreadMutex _mutex;

Channel *_freeListHead;             // �յ�����
Channel *_freeListTail;
Channel *_useListHead;              // ��ʹ�õ�����
Channel *_useListTail;
int _maxUseCount;                   // ��������ĳ���

static atomic_t _globalChannelId;   // ����ͳһ��id
static atomic_t _globalTotalCount;
};

}

#endif /*CHANNEL_POOL_H_*/