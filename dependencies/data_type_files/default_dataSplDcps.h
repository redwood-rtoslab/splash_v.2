#ifndef DEFAULT_DATASPLTYPES_H
#define DEFAULT_DATASPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "default_data_DCPS.hpp"


extern c_metaObject __default_data_default_data__load (c_base base);

extern const char *default_data_Msg_metaDescriptor[];
extern const int default_data_Msg_metaDescriptorArrLength;
extern const int default_data_Msg_metaDescriptorLength;
extern c_metaObject __default_data_Msg__load (c_base base);
struct _default_data_Msg ;
extern  v_copyin_result __default_data_Msg__copyIn(c_base base, const class default_data::Msg *from, struct _default_data_Msg *to);
extern  void __default_data_Msg__copyOut(const void *_from, void *_to);
struct _default_data_Msg {
    c_long id;
    c_string message;
    c_longlong constraint_deadline_duetime;
    c_longlong constraint_freshness_gentime;
};

#undef OS_API
#endif
