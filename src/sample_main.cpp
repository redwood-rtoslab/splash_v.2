#include "Processing_block.cpp"
#include "data_type_headers.h"

void Processing_block::user_function(char* input_topic_name)
{
	input_port<default_data::Msg>* user_input_port = (input_port<default_data::Msg>*)(this->get_input_port(input_topic_name));
	dds::sub::Sample<default_data::Msg> input_1;

	user_input_port->read(&input_1);


	printf("%d\n",input_1.data().id());


	
	output_port<default_data::Msg>* user_output_port = (output_port<default_data::Msg>*)(this->get_output_port("Test3"));

	default_data::Msg A;

	user_output_port->write(A);
	
}



int main(void)
{
	Processing_block A;
	input_port<default_data::Msg> B;
	input_port<default_data::Msg> D;
	output_port<default_data::Msg> C;

	B.attach(&A,"Test");
	D.attach(&A,"Test2");

	C.attach(&A, "Test3");

	while(1)
	{
		sleep(10);
	}
}
