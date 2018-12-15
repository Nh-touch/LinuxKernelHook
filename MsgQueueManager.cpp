#include "MsgQueueManager.h"
#include <sys/msg.h>
#include <poll.h>

#define LOG_TAG "MsgQueueManager"

namespace communication {

CMsgQueueManager*
CMsgQueueManager::GetInstance()
{
    static CMsgQueueManager s_manager;
    return &s_manager;
}

CMsgQueueManager::CMsgQueueManager()
{
    // ����һ��Msg
}

CMsgQueueManager::~CMsgQueueManager()
{
    // ����
}

int 
CMsgQueueManager::GetMsgQueueId(int key)
{
    return msgget((key_t)key, 0666 | IPC_CREAT);
}

bool 
CMsgQueueManager::SendOneMsgNonBlock(
    int         msg_id,
    void**      data,
    int         size_without_type,
    int         ms_wait
)
{
    while (true) {
        if (-1 == msgsnd(msg_id, (void*)data, size_without_type, IPC_NOWAIT)) {
            if (EAGAIN == errno) {
                poll(NULL, 0, ms_wait);
                continue;
            }

            return false;
        }

        return true;
    }
}

bool
CMsgQueueManager::RecvOneMsgNonBlock(
    int         msg_id,
    void**      rcv_data,
    int         size_without_type,
    long        msg_type,
    int         ms_wait
)
{
    while (true) {
        if (-1 == msgrcv(msg_id, (void*)rcv_data, size_without_type, msg_type, IPC_NOWAIT)) {
            if (ENOMSG == errno) {
                poll(NULL, 0, ms_wait);
                continue;
            }

            return false;
        }

        return true;
    }
}

bool
CMsgQueueManager::SendOneMsg(
    int         msg_id,
    void**      data,
    int         size_without_type
)
{
    if (-1 == msgsnd(msg_id, (void*)data, size_without_type, IPC_NOWAIT)) {
        return false;
    }

    return true;
}

bool
CMsgQueueManager::RecvOneMsg(
    int         msg_id,
    void**      rcv_data,
    int         size_without_type,
    long        msg_type
)
{
    if (-1 == msgrcv(msg_id, (void*)rcv_data, size_without_type, msg_type, IPC_NOWAIT)) {
        return false;
    }

    return true;
}

bool 
CMsgQueueManager::RemoveMsgQueue(int msg_id)
{
    if (-1 == msgctl(msg_id, IPC_RMID, 0)) { 
        return false;
    }

    return true;
}

}

//// manager (����worker), ����Ӧ����2~3��manger
//CMsgQueueManager *p_mq_manager = CMsgQueueManager::GetInstance();
//int msg_id = p_mq_manager->GetMsgQueueId(11002394);
//
//while (true) {
//    if (!p_mq_manager->RecvOneMsgNonBlock(msg_id, data, BUFF_SIZE, 0, 50)) {
//        continue;
//    }
//
//    string info = string(data);
//    if (!IsFileExists(info.c_str())) {
//        // fifo not exist
//        continue;
//    }
//
//    // worker ����workerר������Ϣid/·�������������� ���ڴ���pipeline
//}
//
//// filter���ɷ�����(ֱ�Ӹ���manager)
//// filter�ڽ��շ��ص���Ϣ, �����Ƿ�ȫ�����,����Ƿ����,��ɺ󷵻�
//
//// python��:
//import posix_ipc
//
// create fifo
//
// mq = posix_ipc.MessageQueue('py_to_dserver')
// mq.send('/home/test/xxxx/34392349')
//
//// send fifo(begin to write)
//
//// recv fifo(begin to receive data)
// delete fifo
