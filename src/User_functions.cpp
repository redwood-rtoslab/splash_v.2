#include "Processing_block.cpp"
#pragma once
void Test_user_function(default_data::Msg data, Processing_block* pb)
{
	printf("test was received\n");

	
	default_data::Msg A1;
	pb->write(&A1,"Test3");

}

void Test2_user_function(default_data2::Msg data, Processing_block* pb)
{
	printf("test2 was received\n");

	default_data2::Msg A2;
	pb->write(&A2, "Test4");
}


