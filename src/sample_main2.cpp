#include "Processing_block.cpp"
#include "data_type_headers.h"

int main(void)
{
        Processing_block A;
        input_port<default_data::Msg> B;
        output_port<default_data::Msg> C;
	
	dds::sub::Sample<default_data::Msg> received_data;

        B.attach(A,"TEST_2");
		
	

	while(1)
	{

		B.read(&received_data);
		printf("%d\n",received_data.data().id());	
	}
}
