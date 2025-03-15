#pragma once

void __glcallClearAllErrors__();
void __glcallRetreiveError__(const char *file, long long line);

#define glCall(x)\
    __glcallClearAllErrors__();\
    x;\
    __glcallRetreiveError__(__FILE__, __LINE__);
