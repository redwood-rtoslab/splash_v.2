#include "../../include/data_type_headers.h"
#include <vector>
#include <map>
#include <mutex>
#pragma once
template <typename Data_0>
class input_port;



class Sink_tag
{
	private:
		dds::domain::DomainParticipant pb_domain_participant {org::opensplice::domain::default_id()};
		dds::pub::Publisher pb_pub{pb_domain_participant, pb_domain_participant.default_publisher_qos()};
		dds::sub::Subscriber pb_sub{pb_domain_participant, pb_domain_participant.default_subscriber_qos()};
		std::map<char*, void*> input_port_map;
						
	public:
		dds::domain::DomainParticipant* get_domain();
		dds::sub::Subscriber* get_subscriber();
		std::map<char*,void*>* get_input_port_map();
		void* get_input_port(char* topic_name);
		void write(void* output_data, char* output_topic_name);
		void initiate();

		template <typename Data_0>
		void user_function(Data_0);
};

dds::domain::DomainParticipant* Sink_tag::get_domain()
{
	return &pb_domain_participant;
}

dds::sub::Subscriber* Sink_tag::get_subscriber()
{
	return &pb_sub;
}

std::map<char*,void*>* Sink_tag::get_input_port_map()
{
	return &input_port_map;
}

void* Sink_tag::get_input_port(char* topic_name)
{
	return input_port_map[topic_name];
}

void Sink_tag::initiate()
{

	while(1) sleep(10000);
}


//============================================================================================================
template <typename Data_0>
class Sink_tag_listener: public dds::sub::NoOpDataReaderListener<Data_0>
{
	private:
		Sink_tag* Sinktag;
		char* input_topic_name;
		std::mutex listener_mutex;
		input_port<Data_0>* assigned_port;
	public:
		virtual void on_data_available(dds::sub::DataReader<Data_0>& dr);
		void register_sink_tag(Sink_tag*);
		void register_topic_name (char* topic_name);
		void register_input_port (input_port<Data_0>* input_port);
};

template <typename Data_0>
void Sink_tag_listener<Data_0>::register_sink_tag(Sink_tag* Sink_tag)
{
	Sinktag = Sink_tag;
}

template <typename Data_0>
void Sink_tag_listener<Data_0>::register_input_port(input_port<Data_0>* input_port)
{
	assigned_port = input_port;
}

template <typename Data_0>
void Sink_tag_listener<Data_0>::register_topic_name(char* topic_name)
{
	this->input_topic_name = topic_name;
}



template <typename Data_0>//passing data reader as the parameter is crucial
void Sink_tag_listener<Data_0>::on_data_available(dds::sub::DataReader<Data_0>& dr)
{
	listener_mutex.lock();	
	dds::sub::Sample<Data_0> message;	
	assigned_port->read(&message);
	Data_0 input_message = message.data();
	Sinktag->user_function<Data_0>(input_message);	
	listener_mutex.unlock();
}

//============================================================================================================
template <typename Data_0>
class input_port
{
	private:
		dds::topic::Topic<Data_0>* topic;
		dds::sub::DataReader<Data_0>* data_reader;
		Sink_tag_listener<Data_0> input_port_listener;			
		std::vector<dds::sub::Sample<Data_0>> input_data;
		typename std::vector<dds::sub::Sample<Data_0>>::iterator iter;		
	public:
		
		void attach(Sink_tag* pb, char* topic_name);
		void read(dds::sub::Sample<Data_0>* sample);
};

template <typename Data_0>
void input_port<Data_0>::attach(Sink_tag* pb, char* topic_name)
{	
	(*(pb->get_input_port_map()))[topic_name] = this;		
	input_port_listener.register_sink_tag(pb);	
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

