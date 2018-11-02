#ifndef LATERAL_DISTANCE_ERRORSPLTYPES_H
#define LATERAL_DISTANCE_ERRORSPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "lateral_distance_error_DCPS.hpp"


extern c_metaObject __lateral_distance_error_lateral_distance_error__load (c_base base);

extern const char *lateral_distance_error_Msg_metaDescriptor[];
extern const int lateral_distance_error_Msg_metaDescriptorArrLength;
extern const int lateral_distance_error_Msg_metaDescriptorLength;
extern c_metaObject __lateral_distance_error_Msg__load (c_base base);
struct _lateral_distance_error_Msg ;
extern  v_copyin_result __lateral_distance_error_Msg__copyIn(c_base base, const class lateral_distance_error::Msg *from, struct _lateral_distance_error_Msg *to);
extern  void __lateral_distance_error_Msg__copyOut(const void *_from, void *_to);
struct _lateral_distance_error_Msg {
    c_long id;
    c_double lateral_distance_error;
};

#undef OS_API
#endif
