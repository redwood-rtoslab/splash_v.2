#include "data_type_headers.h"
#include "Processing_block.cpp"
#include <string.h>
#pragma once
void Processing_block::write(void* data, char* Output_topic_name)
{
	printf("entered write\n");

	if(strcmp("Test",Output_topic_name))
	{	
		output_port<default_data::Msg>* user_output_port = (output_port<default_data::Msg>*)(this->get_output_port(Output_topic_name));
		default_data::Msg* output_data = (default_data::Msg*)data;
		user_output_port->write(*output_data);
			
	}

	else if (strcmp("Test2",Output_topic_name))
	{
		output_port<default_data2::Msg>* user_output_port = (output_port<default_data2::Msg>*)(this->get_output_port(Output_topic_name));
		default_data2::Msg* output_data = (default_data2::Msg*)data;
		user_output_port->write(*output_data);
	}


	else if (strcmp("Test3",Output_topic_name))
	{
		printf("enter?\n");
		output_port<default_data::Msg>* user_output_port = (output_port<default_data::Msg>*)(this->get_output_port(Output_topic_name));
		default_data::Msg* output_data = (default_data::Msg*)data;
		user_output_port->write(*output_data);
	}

	else if (strcmp("Test4",Output_topic_name))
	{
		printf("Enter?\n");
		output_port<default_data2::Msg>* user_output_port = (output_port<default_data2::Msg>*)(this->get_output_port(Output_topic_name));
		default_data2::Msg* output_data = (default_data2::Msg*)data;
		user_output_port->write(*output_data);
	}

}

