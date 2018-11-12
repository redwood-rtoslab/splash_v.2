#include "../../include/data_type_headers.h"
#include <vector>
#include <map>
#include <mutex>
#pragma once
class Source_tag
{
	private:
		dds::domain::DomainParticipant pb_domain_participant {org::opensplice::domain::default_id()};
		dds::pub::Publisher pb_pub{pb_domain_participant, pb_domain_participant.default_publisher_qos()};
		std::map<char*, void*> output_port_map;
						
	public:
		dds::domain::DomainParticipant* get_domain();
		dds::pub::Publisher* get_publisher();
		std::map<char*,void*>* get_output_port_map();
		void* get_output_port(char* topic_name);
		void write(void* output_data, char* output_topic_name);
		void initiate();
		void user_function();
};

dds::domain::DomainParticipant* Source_tag::get_domain()
{
	return &pb_domain_participant;
}

dds::pub::Publisher* Source_tag::get_publisher()
{
	return &pb_pub;
}

std::map<char*,void*>* Source_tag::get_output_port_map()
{
	return &output_port_map;
}

void* Source_tag::get_output_port(char* topic_name)
{
	return output_port_map[topic_name];
}

void Source_tag::initiate()
{
	
		user_function();
		//sleep(10000);
}

//============================================================================================================
template <typename Data_0>
class output_port
{
	private:
		dds::topic::Topic<Data_0>* topic;
		dds::pub::DataWriter<Data_0>*  data_writer;
	public:
		dds::pub::DataWriter<Data_0>* get_datawriter();
		void attach(Source_tag* pb, char* topic_name);
		void write(Data_0);
};


template<typename Data_0>
void output_port<Data_0>::attach(Source_tag* pb, char* topic_name)
{
	(*(pb->get_output_port_map()))[topic_name]=this;
	topic = new dds::topic::Topic<Data_0> (*(pb->get_domain()),topic_name,(pb->get_domain())->default_topic_qos());

	data_writer = new dds::pub::DataWriter<Data_0>(*(pb->get_publisher()),*topic,(*(pb->get_publisher())).default_datawriter_qos());

		
}

template<typename Data_0>
void output_port<Data_0>::write(Data_0 X)
{
	data_writer->write(X);
}

