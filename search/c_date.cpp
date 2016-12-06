#pragma hdrstop

#include "c_date.h"
#include <cstdio>
#pragma package(smart_init)

string cexpand::time_str(time_t t)
{
    struct tm  tb;
    char format[50] = { 0 };
    tb = *localtime(&t);
    sprintf(format, "%d-%02d-%02d %02d:%02d:%02d", tb.tm_year + 1900, tb.tm_mon + 1, tb.tm_mday, tb.tm_hour, tb.tm_min, tb.tm_sec);

    return string(format);
}
time_t cexpand::str_time(const char* t_str)
{
    struct tm tm1;
    memset(&tm1, 0, sizeof(struct tm));
    time_t r_time = 0;

    sscanf(t_str, "%d-%d-%d %d:%d:%d",
             &tm1.tm_year,
             &tm1.tm_mon,
             &tm1.tm_mday,
             &tm1.tm_hour,
             &tm1.tm_min,
             &tm1.tm_sec
            );
    tm1.tm_year -= 1900;
    tm1.tm_mon--;

    r_time = mktime(&tm1);
    return r_time;
}

/**
 * 获取日期部分
 * @param  t 
 * @return   
 * 下面的逻辑可以使用   t - t%(24*3600)代替，但是这种方法有缺点
 * 计算出来的数值是UTC+0，而不是本地时间，如果是北京，则为UTC+8;
 * 所以即便其时间部分已经是0，使用localtime进行计算的话，会得到小时数是8
 * 也就是说不具有兼容性。
 * 当然如果程序如果仅仅会在一个地方进行运行，则无问题，可以使用  t-t%(24*3600)-8*3600 弥补这个差值
 * 这样使用localtime得到的就是本地时间的零时
 */
time_t cexpand::pure_date(time_t t)
{
    struct tm tb;
    tb = *localtime(&t);          

    tb.tm_hour = 0;
    tb.tm_min = 0;
    tb.tm_sec = 0;

    return mktime(&tb);
}

/**
 * 获取日期字符串
 * @param  t   
 * @return   
 */
string cexpand::date_str(time_t t)
{
    struct tm  tb;
    char format[50] = { 0 };
    tb = *localtime(&t);
    sprintf(format, "%d-%02d-%02d", tb.tm_year + 1900, tb.tm_mon + 1, tb.tm_mday);

    return string(format);
}

time_t cexpand::pre_day(time_t t)
{
    return t - 24*3600;     /*不会对合法性检测*/
}
