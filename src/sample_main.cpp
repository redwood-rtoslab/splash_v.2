#include "Processing_block.cpp"
#include "data_type_headers.h"

int main(void)
{
	Processing_block A;
	input_port<default_data::Msg> B;
	output_port<default_data::Msg> C;

	C.attach(A,"TEST_2");
	
	default_data::Msg the_moment;
	int i=0;
	while(1)
	{
		the_moment.id()=i;
		C.write(the_moment);
		i++;
	}
}
