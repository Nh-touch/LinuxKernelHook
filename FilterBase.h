#ifndef __FILTER_BASE_H__
#define __FILTER_BASE_H__

#include "Interface.h"
#include <memory>

namespace pipeline {

class CFilter
{
public:
    CFilter()           = default;
    virtual ~CFilter()  = default;
    void* Execute(void *package);
    virtual void Init();

protected:
    virtual _ctx Receive(void *package);
    virtual void* Deliver(_ctx sp_ctx);

    virtual bool Check(_ctx sp_ctx) = 0;
    virtual _ctx Process(_ctx sp_ctx) = 0;
    //virtual void* Combine(void *package) = 0;
};

template<typename T>
class Single
{
public:
    static CFilter* GetInstance()
    {
        static T filter;
        return (CFilter *)(&filter);
    }
};

}
#endif  /* __FILTER_BASE_H__ */
