#include "Processing_block.cpp"
#include "data_type_headers.h"

int main(void)
{
        Processing_block A;
        output_port<default_data::Msg> C;
	output_port<default_data::Msg> D;
	
        C.attach(&A,"Test");
	D.attach(&A,"Test2");
		
	default_data::Msg data;	

	while(1)
	{

		C.write(data);
		D.write(data);
	}
}
