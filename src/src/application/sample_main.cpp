#include "../language_construct/Processing_block.cpp"
#include "../type_caster/Output_pb_type_caster.cpp"
#include <string.h>
#include "../../include/data_type_headers.h"


template <typename Data_0>
void Processing_block::user_functions(Data_0 message, char* input_topic)
{
	printf("AAAA\n");
	if(!strcmp("Test",input_topic))
	{//function called when port C receives input
		
		default_data::Msg A;
		//this->write(&A, "Test3");		
	}

	else if(!strcmp("Test2",input_topic))
	{//function called when port D receives input

	}	

}

int main(void)
{/*
        Processing_block A;
        input_port<default_data::Msg> C;
	input_port<default_data2::Msg> D;
	output_port<default_data::Msg> E;
	output_port<default_data2::Msg> F;

        C.attach(&A,"Test");
	D.attach(&A,"Test2");
		
	E.attach(&A, "Test3");
	F.attach(&A, "Test4");

	A.initiate();
*/

	dds::domain::DomainParticipant participant(org::opensplice::domain::default_id());
	dds::sub::Subscriber builtinSubscriber = dds::sub::builtin_subscriber(participant);
	std::string name = "DCPSTopic";
	std::vector<dds::sub::DataReader<dds::topic::TopicBuiltinTopicData>> readersvector;
	dds::sub::find<dds::sub::DataReader<dds::topic::TopicBuiltinTopicData>,std::back_insert_iterator<std::vector<dds::sub::DataReader<dds::topic::TopicBuiltinTopicData> > > >(builtinSubscriber, name, std::back_inserter<std::vector<dds::sub::DataReader<dds::topic::TopicBuiltinTopicData>>>(readersvector));
	dds::sub::DataReader<dds::topic::TopicBuiltinTopicData> builtinReader = readersvector[0];
	dds::core::cond::WaitSet ws;
	dds::sub::cond::ReadCondition rc(builtinReader, dds::sub::status::DataState::new_data());
	ws.attach_condition(rc);
	ws.wait();
	
	while(true)
	{
	dds::sub::LoanedSamples<dds::topic::TopicBuiltinTopicData> samples = builtinReader.take();
	for(dds::sub::LoanedSamples<dds::topic::TopicBuiltinTopicData>::const_iterator sample = samples.begin();sample<samples.end();++sample)
	{
		
		std::cout<<sample->data().name()<<std::endl<<sample->data().type_name()<<std::endl<<std::flush;
		std::cout<<std::endl;
	}
	}
	/*
	dds::topic::TopicBuiltinTopicData B;	
	std::vector<dds::sub::Sample<dds::topic::TopicBuiltinTopicData>> topic_data;
	typename std::vector<dds::sub::Sample<dds::topic::TopicBuiltinTopicData>>::iterator iter;
	topic_data.resize(1);
	iter = topic_data.begin();
	builtinReader.take(iter,1);
	dds::sub::Sample<dds::topic::TopicBuiltinTopicData> A = *iter;
	B = A.data();

	while(true)
	{
		std::cout<<B.name()<<std::endl;
	}*/
}
