#include "PB_type_caster.cpp"
#include "data_type_headers.h"

int main(void)
{
        Processing_block A;
        input_port<default_data::Msg> C;
	input_port<default_data::Msg> D;
	
        C.attach(&A,"Test");
	D.attach(&A,"Test2");

	A.initiate();
}
