#include "Source_tag.cpp"
#include "Source_tag_user_functions.cpp"
#include <string.h>
#pragma once
void Source_tag::output_st_type_caster(char* output_topic)
{
	if(strcmp("lateral_error",output_topic))
	{
		lateral_error_user_function(this);
	}
	
}
