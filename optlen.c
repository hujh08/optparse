#include "optparse.h"

int optlen(optSpec *opts)
{
    int len=0;
    while(opts[len].lname) len++;
    return len;
}