#include <stdio.h>
#include "vrt.h"
#include "vcc_if.h"
#include "cache.h"


typedef struct sess re_ctx;


double
vmod_time(struct sess *sp, const char *time_string, double fallback)
{
    // this is a trivial converter for unix timestamps for now, we
    // need to turn it into a factory for all the different potential
    // formats it could discover (RFC 1123, etc.)
    double timestamp;
    if (sscanf(time_string, "%lf", &timestamp) != 1) {
        return fallback;
    }
    return timestamp;
}


double
vmod_add(struct sess *sp, double time, double offset)
{
    return time + offset;
}


double
vmod_sub(struct sess *sp, double time, double offset)
{
    return time - offset;
}


unsigned
vmod_is_after(struct sess *sp, double time1, double time2)
{
    return time1 > time2;
}


const char *
vmod_strftime(struct sess *sp, const char *format, double time)
{
    if (format == NULL) {
        return "";
    }
    char *result;
    unsigned available = WS_Reserve(sp->wrk->ws, 0);
    result = sp->wrk->ws->f;
    const time_t timestamp = (long int)time;
    struct tm *time_info = gmtime(&timestamp);
    size_t bytes = strftime(result, available, format, time_info);
    if (bytes == 0) {
        result = "";
    }
    bytes += 1; // including the null terminator
    WS_Release(sp->wrk->ws, bytes);
    return result;
}
