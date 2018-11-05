#include "Source_tag.cpp"
#include "Sink_tag.cpp"
#include "Output_st_type_caster.cpp"
#include "data_type_headers.h"

void Source_tag::user_function()
{
 
 //create interface with exterior source here

  for(int i=0;i<5;i++)
  {	
    default_data::Msg output_1;
    this->write(&output_1,"Test3");
  }
}

template <typename Data_0>
void Sink_tag::user_function(Data_0 data)
{
 
  printf("%d\n",data.id());
  printf("Data received\n");

}

int main(void)
{
        Source_tag source_tag_1;
	output_port<default_data::Msg> output_port_1;
	output_port<default_data2::Msg> output_port_2;
		
	output_port_1.attach(&source_tag_1, "Test3");
	output_port_2.attach(&source_tag_1, "Test4");


	Sink_tag sink_tag_1;
	input_port<default_data::Msg> input_port_1;
	input_port<default_data2::Msg> input_port_2;
	input_port_1.attach(&sink_tag_1, "Test3");
	input_port_2.attach(&sink_tag_1, "Test4");


	source_tag_1.initiate();
	
	sink_tag_1.initiate();
}
