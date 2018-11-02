#ifndef ISOCPP2_LATERAL_DISTANCE_ERROR_H
#define ISOCPP2_LATERAL_DISTANCE_ERROR_H

#include "dds/dds.hpp"

#include "lateral_distance_error.h"
#include "lateral_distance_errorSplDcps.h"

#include "org/opensplice/topic/TopicTraits.hpp"
#include "org/opensplice/topic/DataRepresentation.hpp"

namespace org { namespace opensplice { namespace topic {
template <>
class TopicTraits<lateral_distance_error::Msg>
{
public:
    static ::org::opensplice::topic::DataRepresentationId_t getDataRepresentationId()
    {
        return ::org::opensplice::topic::OSPL_REPRESENTATION;
    }

    static ::std::vector<os_uchar> getMetaData()
    {
        return ::std::vector<os_uchar>();
    }

    static ::std::vector<os_uchar> getTypeHash()
    {
        return ::std::vector<os_uchar>();
    }

    static ::std::vector<os_uchar> getExtentions()
    {
        return ::std::vector<os_uchar>();
    }

    static const char *getKeyList()
    {
        return "id";
    }

    static const char *getTypeName()
    {
        return "lateral_distance_error::Msg";
    }

    static std::string getDescriptor()
    {
        const char *elements[] = {
            "<MetaData version=\"1.0.0\"><Module name=\"lateral_distance_error\"><Struct name=\"Msg\"><Member name=\"id\">",
"<Long/></Member><Member name=\"lateral_distance_error\"><Double/></Member></Struct></Module></MetaData>"
        };
        std::string descriptor;
        descriptor.reserve(212);
        for (int i = 0; i < 2; i++) {
            descriptor.append(elements[i]);
        }

        return descriptor;
    }

    static copyInFunction getCopyIn()
    {
        return (copyInFunction) __lateral_distance_error_Msg__copyIn;
    }

    static copyOutFunction getCopyOut()
    {
        return (copyOutFunction) __lateral_distance_error_Msg__copyOut;
    }
};
}}}

namespace dds { namespace topic {
template <>
struct topic_type_name<lateral_distance_error::Msg>
{
    static std::string value()
    {
        return org::opensplice::topic::TopicTraits<lateral_distance_error::Msg>::getTypeName();
    }
};
}}

REGISTER_TOPIC_TYPE(lateral_distance_error::Msg)

#endif /* ISOCPP2_LATERAL_DISTANCE_ERROR_H */
