#include "../include/Processing_block.h"
#include "../include/data_type_headers.h"

int main(void)
{
        Processing_block A;
        output_port<default_data::Msg> C;
	output_port<default_data2::Msg> D;
	
        C.attach(&A,"Test");
	D.attach(&A,"Test2");
		
	default_data::Msg data;	
	default_data2::Msg data2;
	while(1)
	{

		C.write(data);
		D.write(data2);
	}
}
