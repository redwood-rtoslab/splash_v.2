#include "../../include/data_type_headers.h"
#include <vector>
#include <map>
#include <mutex>
#pragma once
template <typename Data_0>
class input_port;

class Fusion_operator
{
	private:
		dds::domain::DomainParticipant pb_domain_participant {org::opensplice::domain::default_id()};
		dds::pub::Publisher pb_pub{pb_domain_participant, pb_domain_participant.default_publisher_qos()};
		dds::sub::Subscriber pb_sub{pb_domain_participant, pb_domain_participant.default_subscriber_qos()};
		std::map<char*, void*> input_port_map;
		int number_of_input_ports=0;
		void* fused_output_port;
		void* bitset_of_input_ports;
	public:
		dds::domain::DomainParticipant* get_domain();
		dds::pub::Publisher* get_publisher();
		dds::sub::Subscriber* get_subscriber();
		std::map<char*,void*>* get_input_port_map();
		void fuse();
		void* get_output_port();
		void* get_input_port(char* topic_name);
		void initiate();
};

dds::domain::DomainParticipant* Fusion_operator::get_domain()
{
	return &pb_domain_participant;
}

dds::pub::Publisher* Fusion_operator::get_publisher()
{
	return &pb_pub;
}

dds::sub::Subscriber* Fusion_operator::get_subscriber()
{
	return &pb_sub;
}

std::map<char*,void*>* Fusion_operator::get_input_port_map()
{
	return &input_port_map;
}

void* Fusion_operator::get_output_port()
{
	return fused_output_port;
}

void* Fusion_operator::get_input_port(char* topic_name)
{
	return input_port_map[topic_name];
}

void Fusion_operator::initiate()
{
	int a = number_of_input_ports;
	bitset_of_input_ports = new std::bitset<100>;
	while(1) sleep(10000);
}


//============================================================================================================
template <typename Data_0>
class Fusion_operator_listener: public dds::sub::NoOpDataReaderListener<Data_0>
{
	private:
		Fusion_operator* Fusionoperator;
		char* input_topic_name;
		std::mutex listener_mutex;
		input_port<Data_0>* assigned_port;
	public:
		virtual void on_data_available(dds::sub::DataReader<Data_0>& dr);
		void register_fusion_operator(Fusion_operator*);
		void register_topic_name (char* topic_name);
		void register_input_port (input_port<Data_0>* input_port);
};

template <typename Data_0>
void Fusion_operator_listener<Data_0>::register_fusion_operator(Fusion_operator* Fusion_operator)
{
	Fusionoperator = Fusion_operator;
}

template <typename Data_0>
void Fusion_operator_listener<Data_0>::register_input_port(input_port<Data_0>* input_port)
{
	assigned_port = input_port;
}

template <typename Data_0>
void Fusion_operator_listener<Data_0>::register_topic_name(char* topic_name)
{
	this->input_topic_name = topic_name;
}



template <typename Data_0>//passing data reader as the parameter is crucial
void Fusion_operator_listener<Data_0>::on_data_available(dds::sub::DataReader<Data_0>& dr)
{
	dds::sub::Sample<Data_0> message;	
	assigned_port->read(&message);
	Data_0 input_message = message.data();
	(assigned_port->received_data).push_back(input_message);
		
}

//============================================================================================================
template <typename Data_0>
class input_port
{
	private:
		int mandatory;
		std::vector<Data_0> received_data;
		dds::topic::Topic<Data_0>* topic;
		dds::sub::DataReader<Data_0>* data_reader;
		Fusion_operator_listener<Data_0> input_port_listener;			
		std::vector<dds::sub::Sample<Data_0>> input_data;
		typename std::vector<dds::sub::Sample<Data_0>>::iterator iter;		
	public:
		
		void attach(Fusion_operator* pb, char* topic_name);
		void read(dds::sub::Sample<Data_0>* sample);
};

template <typename Data_0>
void input_port<Data_0>::attach(Fusion_operator* pb, char* topic_name)
{	
	(*(pb->get_input_port_map()))[topic_name] = this;		
	pb->number_of_input_ports++;

	input_port_listener.register_fusion_operator(pb);	
	input_port_listener.register_topic_name(topic_name);
	input_port_listener.register_input_port(this);

	topic = new dds::topic::Topic<Data_0> (*(pb->get_domain()), topic_name,(pb->get_domain())->default_topic_qos());

	data_reader = new dds::sub::DataReader<Data_0>(*(pb->get_subscriber()),*topic,(*(pb->get_subscriber())).default_datareader_qos()); 

	data_reader->listener(&input_port_listener, dds::core::status::StatusMask::data_available());
}

template <typename Data_0>
void input_port<Data_0>::read(dds::sub::Sample<Data_0>* sample)
{
	input_data.resize(1);
	iter = input_data.begin();
	data_reader->take(iter,1);
	*sample = *iter;
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
		void write(Data_0);
		void attach(Fusion_operator* pb, char* topic_name);
};


template<typename Data_0>
void output_port<Data_0>::attach(Fusion_operator* pb, char* topic_name)
{
	pb->fused_output_port = this;
	topic = new dds::topic::Topic<Data_0> (*(pb->get_domain()),topic_name,(pb->get_domain())->default_topic_qos());

	data_writer = new dds::pub::DataWriter<Data_0>(*(pb->get_publisher()),*topic,(*(pb->get_publisher())).default_datawriter_qos());

	
}

template<typename Data_0>
void output_port<Data_0>::write(Data_0 data)
{
	data_writer->write(data);
}
