#ifndef __MSG_QUEUE_H__
#define __MSG_QUEUE_H__

#include "Interface.h"

namespace communication {
#define BUFF_SIZE (5000)
typedef struct _msg_ctx_t
{
    long int msg_type;
    char text[BUFF_SIZE];
} msg_ctx_t;

class CMsgQueueManager
{
public:
    static CMsgQueueManager* GetInstance();

    CMsgQueueManager();
    virtual ~CMsgQueueManager();
    
    int GetMsgQueueId(int key);

    bool SendOneMsgNonBlock(
        int         msg_id,
        void**      data,
        int         size_without_type,
        int         ms_wait
    );

    bool RecvOneMsgNonBlock(
        int         msg_id,
        void**      rcv_data,
        int         size_without_type,
        long        msg_type,
        int         ms_wait
    );

    bool SendOneMsg(
        int         msg_id,
        void**      data,
        int         size_without_type
    );

    bool RecvOneMsg(
        int         msg_id,
        void**      rcv_data,
        int         size_without_type,
        long        msg_type
    );

    bool RemoveMsgQueue(int msg_id);

protected:

private:
};

}
#endif  /* __MSG_QUEUE_H__ */
