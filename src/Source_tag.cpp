//I have to implement write for source tags
//

#include "data_type_headers.h"
#include <vector>
#include <map>
#include <mutex>
#pragma once

class Source_tag
{
	private:
		dds::domain::DomainParticipant st_domain_participant {org::opensplice::domain::default_id()};
		dds::pub::Publisher st_pub{st_domain_participant, st_domain_participant.default_publisher_qos()};
		std::map<char*, void*> output_port_map;
		void* output_port;
		char* output_topic;				
	public:
		dds::domain::DomainParticipant* get_domain();
		dds::pub::Publisher* get_publisher();
		void* get_output_port();
		void write(void* output_data);
		void initiate();
		void output_st_type_caster(char* output_topic_name);
};

dds::domain::DomainParticipant* Source_tag::get_domain()
{
	return &st_domain_participant;
}

dds::pub::Publisher* Source_tag::get_publisher()
{
	return &st_pub;
}

void* Source_tag::get_output_port()
{
	return output_port;
}

void Source_tag::initiate()
{
	output_st_type_caster(output_topic);
	
}

//============================================================================================
template <typename Data_0>
class output_port
{
	private:
		dds::topic::Topic<Data_0>* topic;
		dds::pub::DataWriter<Data_0>*  data_writer;
	public:
		dds::pub::DataWriter<Data_0>* get_datawriter();
		void attach(Source_tag* st, char* topic_name);
		void write(Data_0);
};


template<typename Data_0>
void output_port<Data_0>::attach(Source_tag* st, char* topic_name)
{
	st->output_port=this;
	st->output_topic = topic_name;
	topic = new dds::topic::Topic<Data_0> (*(st->get_domain()),topic_name,(st->get_domain())->default_topic_qos());

	data_writer = new dds::pub::DataWriter<Data_0>(*(st->get_publisher()),*topic,(*(st->get_publisher())).default_datawriter_qos());

		
}

template<typename Data_0>
void output_port<Data_0>::write(Data_0 X)
{
	data_writer->write(X);
}

