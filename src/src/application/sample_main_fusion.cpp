#include "../language_construct/Fusion_operator.cpp"
#include <string.h>
#include "../../include/data_type_headers.h"

void Fusion_operator::fuse()
{
		
	
}

int main(void)
{
	Fusion_operator fusion;
	input_port<default_data::Msg> A;
	input_port<default_data::Msg> B;
	
	output_port<default_data2::Msg> C;

	A.attach(&fusion, "topic1", 1);
	B.attach(&fusion, "topic2", 1);
	C.attach(&fusion, "topic3");

}
