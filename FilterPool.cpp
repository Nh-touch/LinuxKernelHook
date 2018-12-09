
#include "FilterPool.h"

#define LOG_TAG "FilterPool"

namespace pipeline {

bool 
CFileSum::Check(_ctx sp_ctx)
{
    return true;
}

_ctx 
CFileSum::Process(_ctx sp_ctx)
{
    printf("Process!\n");
    return sp_ctx;
}

}

using namespace pipeline;
int main()
{
    CFileSum::GetInstance()->Execute(NULL);
    printf("%p\n", CFileSum::GetInstance());
    CFileSum2::GetInstance()->Execute(NULL);
    printf("%p\n", CFileSum::GetInstance());
    return 0;
}
