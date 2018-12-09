#ifndef __FILTER_POOL_H__
#define __FILTER_POOL_H__

#include "FilterBase.h"

namespace pipeline {

class CFileSum
: public CFilter
, public Single<CFileSum>
{
public:
    CFileSum()           = default;
    virtual ~CFileSum()  = default;

protected:
    virtual bool Check(_ctx sp_ctx);
    virtual _ctx Process(_ctx sp_ctx);
};

}

#endif  /* __FILTER_POOL_H__ */
