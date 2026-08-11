
#include "EGL/eglConfig.h"

#include "EGL/eglConfig_defs.h"

#include "Common/logger.h"

int* EGL::Config::get_start_config_ptr (void)
{//    FUN_ENTRY(DEBUG_DEPTH);
	return egl_config_defs_array;
}

int* EGL::Config::get_end_config_ptr (void)
{//    FUN_ENTRY(DEBUG_DEPTH);
	int* start_p = get_start_config_ptr();
	
	start_p += sizeof(egl_config_defs_array);
	start_p--;
	
	return start_p;
}

bool EGL::Config::check_is_config_type (int* in_config_ptr)
{//    FUN_ENTRY(DEBUG_DEPTH);
    int* start_p = get_start_config_ptr();
    bool result = true;
    
    if ( (in_config_ptr-start_p)%2 == 0)
    	result = false;
    
    return result;
}

bool EGL::Config::check_is_config (int* in_config_ptr)
{//    FUN_ENTRY(DEBUG_DEPTH);
	int* start_p = get_start_config_ptr();
	int* end_p = get_end_config_ptr();
	end_p -= 2;
	
	bool result = false;
	
	if (in_config_ptr>=start_p &&
		in_config_ptr<=end_p)
		result = true;
	
	return result;
}

int EGL::Config::get_max_config_num (void)
{//    FUN_ENTRY(DEBUG_DEPTH);
	int* start_p = get_start_config_ptr();
	start_p++;
	
	int config_num = 0;
	while (*start_p != EGL_NO_CONFIG) {
		if (*start_p == EGL_NONE)
			config_num++;
		
		start_p += 2;
	}
	
	return config_num;
}

int* EGL::Config::get_next_config_ptr (int* in_config_ptr)
{//    FUN_ENTRY(DEBUG_DEPTH);
	int* result_ptr = NULL;
	
	if (false == check_is_config(in_config_ptr) ) {
		result_ptr = NULL;
		return result_ptr;
	}
	
	if (false == check_is_config_type(in_config_ptr) ) {
		in_config_ptr++;
	}
	
	while (*in_config_ptr != EGL_NONE) {
		in_config_ptr += 2;
	}
	in_config_ptr++;
	
	result_ptr = in_config_ptr;
	
	return result_ptr;
}

int EGL::Config::get_config_value_from_attrib (int* in_config_ptr, int in_attrib)
{
    while (*in_config_ptr != EGL_NONE) {
        if (*in_config_ptr == in_attrib) {
            return *(in_config_ptr + 1);  // 返回对应的值
        }
        in_config_ptr += 2;  // 跳到下一对 attribute-value
    }
    return EGL_NONE;  // 未找到
}

bool EGL::Config::compare_config_attribs (int* in_config_ptr, int* in_attribs_ptr)
{//    FUN_ENTRY(DEBUG_DEPTH);
	bool result = true;
	
	if (in_attribs_ptr == nullptr)
		return true;
	if (false == check_is_config(in_config_ptr) )
		return false;
	
	int in_attrib;
	int in_value;
	int config_value;
	
	while (*in_attribs_ptr != EGL_NONE) {
		in_value = *in_attribs_ptr;
		in_attribs_ptr++;
		in_attrib = *in_attribs_ptr;
		
		config_value = get_config_value_from_attrib(in_config_ptr, in_attrib);
		
		if (config_value != EGL_NONE &&
			config_value != in_value		) {
		    result = false;
		    break;
		}
		
		in_attribs_ptr += 2;
	}
	
	return result;
}

void EGL::Config::get_configs_for_attribs (int** out_configs_ptr, int in_config_num, int* out_config_num_ptr, int* in_attribs_ptr)
{//    FUN_ENTRY(DEBUG_DEPTH);
	int max_config_num = get_max_config_num();
	if (out_config_num_ptr) *out_config_num_ptr = max_config_num;
	if (in_config_num > max_config_num) in_config_num = max_config_num;
	if (out_configs_ptr == nullptr) return;
	
	int* start_p = get_start_config_ptr();
	int out_config_index = 0;
	
	while (start_p) {
		if (out_config_index < in_config_num) {
			if (compare_config_attribs(start_p, in_attribs_ptr) ) {
    			out_configs_ptr[out_config_index] = start_p;
    			out_config_index++;
    		}
		} else {
			break;
		}
		
		start_p = get_next_config_ptr(start_p);
	}
	
}



