#include "../language_construct/Source_tag.cpp"
#include <string.h>
#pragma once
void Source_tag::write(void* output_data, char* output_topic_name)
{
	if(strcmp("Test3",output_topic_name))
	{
		output_port<default_data::Msg>* user_output_port = (output_port<default_data::Msg>*)(this->get_output_port(output_topic_name));
		default_data::Msg* data = (default_data::Msg*)output_data;
		user_output_port->write(*data);
	}

	if(strcmp("Test4",output_topic_name))
	{
		output_port<default_data2::Msg>* user_output_port = (output_port<default_data2::Msg>*)(this->get_output_port(output_topic_name));
		default_data2::Msg* data = (default_data2::Msg*)output_data;
		user_output_port->write(*data);
	}	
	
}
