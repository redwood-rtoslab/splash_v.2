#include "Processing_block.cpp"
#include "Output_pb_type_caster.cpp"
#include <string.h>
#include "data_type_headers.h"


template <typename Data_0>
void Processing_block::user_functions(Data_0 message, char* input_topic)
{
	if(!strcmp("Test",input_topic))
	{//function called when port C receives input
		
		default_data::Msg A;
		this->write(&A, "Test3");		
	}

	else if(!strcmp("Test2",input_topic))
	{//function called when port D receives input

	}	

}

int main(void)
{
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
}
