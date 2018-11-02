#ifndef _LATERAL_DISTANCE_ERROR_H_
#define _LATERAL_DISTANCE_ERROR_H_

#include <dds/core/ddscore.hpp>

namespace lateral_distance_error
{
    class Msg OSPL_DDS_FINAL
    {
    public:
        int32_t id_;
        double lateral_distance_error_;

    public:
        Msg() :
                id_(0),
                lateral_distance_error_(0.0) {}

        explicit Msg(
            int32_t id,
            double lateral_distance_error) : 
                id_(id),
                lateral_distance_error_(lateral_distance_error) {}

        Msg(const Msg &_other) : 
                id_(_other.id_),
                lateral_distance_error_(_other.lateral_distance_error_) {}

#ifdef OSPL_DDS_CXX11
        Msg(Msg &&_other) : 
                id_(::std::move(_other.id_)),
                lateral_distance_error_(::std::move(_other.lateral_distance_error_)) {}

        Msg& operator=(Msg &&_other)
        {
            if (this != &_other) {
                id_ = ::std::move(_other.id_);
                lateral_distance_error_ = ::std::move(_other.lateral_distance_error_);
            }
            return *this;
        }
#endif

        Msg& operator=(const Msg &_other)
        {
            if (this != &_other) {
                id_ = _other.id_;
                lateral_distance_error_ = _other.lateral_distance_error_;
            }
            return *this;
        }

        bool operator==(const Msg& _other) const
        {
            return id_ == _other.id_ &&
                lateral_distance_error_ == _other.lateral_distance_error_;
        }

        bool operator!=(const Msg& _other) const
        {
            return !(*this == _other);
        }

        int32_t id() const { return this->id_; }
        int32_t& id() { return this->id_; }
        void id(int32_t _val_) { this->id_ = _val_; }
        double lateral_distance_error() const { return this->lateral_distance_error_; }
        double& lateral_distance_error() { return this->lateral_distance_error_; }
        void lateral_distance_error(double _val_) { this->lateral_distance_error_ = _val_; }
    };

}

#endif /* _LATERAL_DISTANCE_ERROR_H_ */
