#include "data_type_headers.h"
#include <mutex>
#pragma once

template <typename Data_0>
class input_port;


class Processing_block
{
	private:
		dds::domain::DomainParticipant pb_domain_participant {org::opensplice::domain::default_id()};
		dds::pub::Publisher pb_pub{pb_domain_participant, pb_domain_participant.default_publisher_qos()};
		dds::sub::Subscriber pb_sub{pb_domain_participant, pb_domain_participant.default_subscriber_qos()};
		std::map<char*, void*> input_port_map;
		std::map<char*, void*> output_port_map;
						
	public:
		dds::domain::DomainParticipant* get_domain();
		dds::pub::Publisher* get_publisher();
		dds::sub::Subscriber* get_subscriber();
		std::map<char*,void*>* get_input_port_map();
		std::map<char*,void*>* get_output_port_map();
		void* get_output_port(char* topic_name);
		void* get_input_port(char* topic_name);
		void write(void* output_data, char* output_topic_name);
		void initiate();

		template <typename Data_0>
		void user_functions(Data_0, char* input_topic);
};

template <typename Data_0>
class processingblock_listener: public dds::sub::NoOpDataReaderListener<Data_0>
{
	private:
		Processing_block* Processingblock;
		char* input_topic_name;
		std::mutex listener_mutex;
		input_port<Data_0>* assigned_port;
	public:
		virtual void on_data_available(dds::sub::DataReader<Data_0>& dr);
		void register_processing_block(Processing_block*);
		void register_topic_name (char* topic_name);
		void register_input_port (input_port<Data_0>* input_port);
};

template <typename Data_0>
class input_port
{
	private:
		dds::topic::Topic<Data_0>* topic;
		dds::sub::DataReader<Data_0>* data_reader;
		processingblock_listener<Data_0> input_port_listener;			
		std::vector<dds::sub::Sample<Data_0>> input_data;
		typename std::vector<dds::sub::Sample<Data_0>>::iterator iter;		
	public:
		
		void attach(Processing_block* pb, char* topic_name);
		void read(dds::sub::Sample<Data_0>* sample);
};


template <typename Data_0>
class output_port
{
	private:
		dds::topic::Topic<Data_0>* topic;
		dds::pub::DataWriter<Data_0>*  data_writer;
	public:
		dds::pub::DataWriter<Data_0>* get_datawriter();
		void write(Data_0);
		void attach(Processing_block* pb, char* topic_name);
};

template class input_port<default_data::Msg>;
template class output_port<default_data::Msg>;
template class processingblock_listener<default_data::Msg>;
template class input_port<default_data2::Msg>;
template class output_port<default_data2::Msg>;
template class processingblock_listener<default_data2::Msg>;

