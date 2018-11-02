#include "Source_tag.cpp"
#include "data_type_headers.h"
#pragma once
void lateral_error_user_function(Source_tag* source)
{
	

	lateral_distance_error::Msg A;
	source->write(&A,"lateral_error");	
}
