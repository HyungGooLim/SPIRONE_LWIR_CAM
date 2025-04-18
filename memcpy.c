/*
 *  ===== memcpy =====
 *  Run-Time Library routine for compilers which don't support this function...
 */
void* memcpy(void* dst, void* src, int count)
{
    char* dstPtr = dst;
    char* srcPtr = src;
    while (count)
    {
        *dstPtr++ = *srcPtr++;
        --count;
    }
    return dst;
}
