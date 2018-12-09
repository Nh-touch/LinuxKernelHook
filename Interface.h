#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <memory>
namespace pipeline {
// main struct
typedef enum _cmd_e
{
    kSendFile   = 0,
    kRcvFile    = 1,

    kButt
} cmd_e;

typedef struct _cmd_sendfile_t
{

} cmd_sendfile_t;

typedef struct _cmd_recvfile_t
{

} cmd_recvfile_t;

typedef struct _package_t
{
    cmd_e   cmd;
    union {
        cmd_sendfile_t  snd;
        cmd_recvfile_t  rcv;
    };
} package_t;

typedef struct _filter_context_t
{
    void *package;
    bool b_bypass;
} filter_context_t;

using _ctx = std::shared_ptr<filter_context_t>;

}
#endif  /* __INTERFACE_H__ */
