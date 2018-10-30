#include "data_type_headers.h"
#include <vector>
#include <map>

class Processing_block
{
	private:
		dds::domain::DomainParticipant pb_domain_participant {org::opensplice::domain::default_id()};
		dds::pub::Publisher pb_pub{pb_domain_participant, pb_domain_participant.default_publisher_qos()};
		dds::sub::Subscriber pb_sub{pb_domain_participant, pb_domain_participant.default_subscriber_qos()};
			
		std::map<char*, void*> topic_map;
		std::map<char*, void*> datareader_map;
		std::map<char*, void*> datawriter_map;				
	public:
		dds::domain::DomainParticipant* get_domain();
		std::map<char*, void*>* get_topic_map();
		std::map<char*, void*>* get_datareader_map();
		std::map<char*, void*>* get_datawriter_map();
		dds::pub::Publisher* get_publisher();
		dds::sub::Subscriber* get_subscriber();
};

dds::domain::DomainParticipant* Processing_block::get_domain()
{
	return &pb_domain_participant;
}

std::map<char*, void*>*  Processing_block::get_topic_map()
{
	return &topic_map;
}

std::map<char*, void*>*  Processing_block::get_datareader_map()
{
	return &datareader_map;
}

std::map<char*, void*>*  Processing_block::get_datawriter_map()
{
	return &datawriter_map;
}



dds::pub::Publisher* Processing_block::get_publisher()
{
	return &pb_pub;
}

dds::sub::Subscriber* Processing_block::get_subscriber()
{
	return &pb_sub;
}


//============================================================================================
template <typename Data_0>
class input_port
{
	private:
		void* topic;
		void* data_reader;
		std::vector<dds::sub::Sample<Data_0>> input_data;
		typename std::vector<dds::sub::Sample<Data_0>>::iterator iter;		
	public:
		
		void attach(Processing_block pb, char* topic_name);
		void read(dds::sub::Sample<Data_0>* sample);
};

template <typename Data_0>
void input_port<Data_0>::attach(Processing_block pb, char* topic_name)
{	

		dds::topic::Topic<Data_0>* created_topic = new dds::topic::Topic<Data_0> (*(pb.get_domain()), topic_name,(pb.get_domain())->default_topic_qos());

		topic = created_topic;		

		dds::sub::DataReader<Data_0>* reader = new dds::sub::DataReader<Data_0>(*(pb.get_subscriber()),*created_topic,(*(pb.get_subscriber())).default_datareader_qos()); 

		data_reader = reader;

		
		//allows the processing block to access the topic and datareader
		//for later development	
		(*(pb.get_datareader_map()))[topic_name] = reader;

		(*(pb.get_topic_map()))[topic_name]= created_topic;
	 	
		

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
	((dds::sub::DataReader<Data_0>*)data_reader)->take(iter,1);
	*sample = *iter;

}
//==========================================================================================
template <typename Data_0>
class output_port
{
	private:
		void* topic;
		void* data_writer;
	public:
		void attach(Processing_block pb, char* topic_name);
		void write(Data_0);
};


template<typename Data_0>
void output_port<Data_0>::attach(Processing_block pb, char* topic_name)
{
		dds::topic::Topic<Data_0>* created_topic = new dds::topic::Topic<Data_0> (*(pb.get_domain()),topic_name,(pb.get_domain())->default_topic_qos());

	 
		topic = created_topic;

		dds::pub::DataWriter<Data_0>* writer = new dds::pub::DataWriter<Data_0>(*(pb.get_publisher()),*created_topic,(*(pb.get_publisher())).default_datawriter_qos());

		data_writer = writer;
		
	
		//allows the processing block to access the topic and datawriter
		//for later development 
		(*(pb.get_datawriter_map()))[topic_name] = writer;

		(*(pb.get_topic_map()))[topic_name] = created_topic;
}

template<typename Data_0>
void output_port<Data_0>::write(Data_0 X)
{
	((dds::pub::DataWriter<Data_0>*)data_writer)->write(X);

}

