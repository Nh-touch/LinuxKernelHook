
#include "FilterBase.h"

#define LOG_TAG "Filter"

namespace pipeline {

void* 
CFilter::Execute(void *package)
{
    return Deliver(Process(Receive(package)));
}

void 
CFilter::Init()
{
    return;
}

_ctx
CFilter::Receive(void *package)
{
    _ctx sp_ctx;
    sp_ctx.reset(new filter_context_t());
    sp_ctx->package = package;

    sp_ctx->b_bypass  = false;
    if (!Check(sp_ctx))
        sp_ctx->b_bypass = true;

    return sp_ctx;
}

void*
CFilter::Deliver(_ctx sp_ctx)
{
    return sp_ctx->package;
}

}
