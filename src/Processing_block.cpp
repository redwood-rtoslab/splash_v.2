#include "data_type_headers.h"
#include <vector>
#include <map>
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
		
};

dds::domain::DomainParticipant* Processing_block::get_domain()
{
	return &pb_domain_participant;
}

dds::pub::Publisher* Processing_block::get_publisher()
{
	return &pb_pub;
}

dds::sub::Subscriber* Processing_block::get_subscriber()
{
	return &pb_sub;
}

std::map<char*,void*>* Processing_block::get_input_port_map()
{
	return &input_port_map;
}

std::map<char*,void*>* Processing_block::get_output_port_map()
{
	return &output_port_map;
}

//============================================================================================
template <typename Data_0>
class SplashListener: public dds::sub::NoOpDataReaderListener<Data_0>
{
	private:
		Processing_block* Processingblock;
		
	public:
		virtual void on_data_available(dds::sub::DataReader<Data_0>& data_reader);
		void register_processing_block(Processing_block);

};

template <typename Data_0>
void SplashListener<Data_0>::register_processing_block(Processing_block processingblock)
{
	Processingblock = processingblock;
}


//============================================================================================
template <typename Data_0>
class input_port
{
	private:
		dds::topic::Topic<Data_0>* topic;
		dds::sub::DataReader<Data_0>* data_reader;
		SplashListener<Data_0> input_port_listener;			
		//required for implementation
		std::vector<dds::sub::Sample<Data_0>> input_data;
		typename std::vector<dds::sub::Sample<Data_0>>::iterator iter;		
	public:
		
		void attach(Processing_block pb, char* topic_name);
		void read(dds::sub::Sample<Data_0>* sample);
		void spin();
};

template <typename Data_0>
void input_port<Data_0>::attach(Processing_block pb, char* topic_name)
{	
	(*(pb.get_input_port_map()))[topic_name] = this;		
	input_port_listener.register_output_ports(pb.get_output_port_map());	
	topic = new dds::topic::Topic<Data_0> (*(pb.get_domain()), topic_name,(pb.get_domain())->default_topic_qos());

	data_reader = new dds::sub::DataReader<Data_0>(*(pb.get_subscriber()),*topic,(*(pb.get_subscriber())).default_datareader_qos()); 

}

template <typename Data_0>
void input_port<Data_0>::read(dds::sub::Sample<Data_0>* sample)
{
	dds::core::cond::WaitSet ws;
	dds::sub::cond::ReadCondition rc(*((dds::sub::DataReader<Data_0>*)data_reader),dds::sub::status::DataState::new_data());
	ws.attach_condition(rc);
	ws.wait();	
	input_data.resize(1);
	iter = input_data.begin();
	data_reader->take(iter,1);
	*sample = *iter;

}

//==========================================================================================
template <typename Data_0>
class output_port
{
	private:
		dds::topic::Topic<Data_0>* topic;
		dds::pub::DataWriter<Data_0>*  data_writer;
	public:
		dds::pub::DataWriter<Data_0>* get_datawriter();
		void attach(Processing_block pb, char* topic_name);
		void write(Data_0);
};


template<typename Data_0>
void output_port<Data_0>::attach(Processing_block pb, char* topic_name)
{
	(*(pb.get_output_port_map()))[topic_name]=this;
	topic = new dds::topic::Topic<Data_0> (*(pb.get_domain()),topic_name,(pb.get_domain())->default_topic_qos());

	data_writer = new dds::pub::DataWriter<Data_0>(*(pb.get_publisher()),*topic,(*(pb.get_publisher())).default_datawriter_qos());

		
}

template<typename Data_0>
void output_port<Data_0>::write(Data_0 X)
{
	data_writer->write(X);

}

template<typename Data_0>
dds::pub::DataWriter<Data_0>* output_port<Data_0>::get_datawriter()
{
	return data_writer;
}