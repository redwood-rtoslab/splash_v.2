#include "User_functions.cpp"
#include "data_type_headers.h"
#include <string.h>
void Processing_block::type_caster(char* input_topic_name)
{
	if(strcmp("Test",input_topic_name))
	{	
		input_port<default_data::Msg>* user_input_port = (input_port<default_data::Msg>*)(this->get_input_port(input_topic_name));
		dds::sub::Sample<default_data::Msg> input_data;
		user_input_port->read(&input_data);
		Test_user_function(input_data.data());			
		
			
	}

	else if (strcmp("Test2",input_topic_name))
	{
		input_port<default_data2::Msg>* user_input_port = (input_port<default_data2::Msg>*)(this->get_input_port(input_topic_name));
		dds::sub::Sample<default_data2::Msg> input_data;
		user_input_port ->read(&input_data);
		Test2_user_function(input_data.data());
	}
}

