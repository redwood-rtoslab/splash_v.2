#include "default_data_DCPS.hpp"

#include <v_copyIn.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__default_data_Msg__copyIn(
    c_base base,
    const class ::default_data::Msg *from,
    struct _default_data_Msg *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    to->id = (c_long)from->id_;
#ifdef OSPL_BOUNDS_CHECK
        to->message = c_stringNew_s(base, from->message_.c_str());
        if(to->message == NULL) {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
#else
            to->message = c_stringNew_s(base, from->message_.c_str());
            if(to->message == NULL) {
                result = V_COPYIN_RESULT_OUT_OF_MEMORY;
            }
#endif
    to->constraint_deadline_duetime = (c_longlong)from->constraint_deadline_duetime_;
    to->constraint_freshness_gentime = (c_longlong)from->constraint_freshness_gentime_;
    return result;
}

void
__default_data_Msg__copyOut(
    const void *_from,
    void *_to)
{
    const struct _default_data_Msg *from = (const struct _default_data_Msg *)_from;
    class ::default_data::Msg *to = (class ::default_data::Msg *)_to;
    to->id((int32_t)from->id);
    to->message(from->message ? from->message : "");
    to->constraint_deadline_duetime((int64_t)from->constraint_deadline_duetime);
    to->constraint_freshness_gentime((int64_t)from->constraint_freshness_gentime);
}

