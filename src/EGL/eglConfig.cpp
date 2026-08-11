#include "EGL/eglConfig.h"
#include "EGL/eglConfig_defs.h"
#include "Common/logger.h"

// 如果未定义 EGL_NO_CONFIG，定义为 -1（假设配置属性值不会为 -1）
#ifndef EGL_NO_CONFIG
#define EGL_NO_CONFIG -1
#endif

namespace EGL {
namespace Config {

// 获取数组起始指针
int* get_start_config_ptr(void) {
    return egl_config_defs_array;
}

// 获取数组末尾指针（指向最后一个元素的下一位置，便于范围检查）
int* get_end_config_ptr(void) {
    return egl_config_defs_array + (sizeof(egl_config_defs_array) / sizeof(int));
}

// 检查指针是否指向数组内有效配置（即指向某个配置的起始属性，且地址在数组范围内）
bool check_is_config(int* in_config_ptr) {
    int* start = get_start_config_ptr();
    int* end   = get_end_config_ptr();
    return (in_config_ptr >= start && in_config_ptr < end);
}

// 检查指针是否指向配置的属性（偶数偏移）或值（奇数偏移）
// 我们约定：配置起始指针必须指向属性（偶数索引），所以此处返回 true 表示是属性
bool check_is_config_type(int* in_config_ptr) {
    int* start = get_start_config_ptr();
    ptrdiff_t diff = in_config_ptr - start;
    if (diff < 0) return false;
    return (diff % 2 == 0);  // 属性位于偶数索引
}

// 计算配置总数（遍历整个数组直到遇到 EGL_NO_CONFIG 或数组结束）
int get_max_config_num(void) {
    int* ptr = get_start_config_ptr();
    int count = 0;
    while (ptr < get_end_config_ptr() && *ptr != EGL_NO_CONFIG) {
        // 跳过当前配置的所有属性对，直到 EGL_NONE
        while (ptr < get_end_config_ptr() && *ptr != EGL_NONE) {
            ptr += 2;  // 每对占用两个 int
        }
        if (ptr >= get_end_config_ptr()) break;
        ptr++;  // 跳过 EGL_NONE，指向下一个配置的起始或 EGL_NO_CONFIG
        count++;
    }
    return count;
}

// 获取下一个配置的起始指针（输入为当前配置的起始属性指针）
int* get_next_config_ptr(int* in_config_ptr) {
    if (!check_is_config(in_config_ptr) || !check_is_config_type(in_config_ptr)) {
        return nullptr;  // 无效指针
    }
    int* ptr = in_config_ptr;
    // 跳过当前配置的所有属性对，直到 EGL_NONE
    while (ptr < get_end_config_ptr() && *ptr != EGL_NONE) {
        ptr += 2;
    }
    if (ptr >= get_end_config_ptr()) return nullptr;
    ptr++;  // 跳过 EGL_NONE
    // 检查是否到达数组末尾（EGL_NO_CONFIG）
    if (ptr >= get_end_config_ptr() || *ptr == EGL_NO_CONFIG) {
        return nullptr;
    }
    return ptr;
}

// 修正后的属性值查找（遍历属性对直到匹配或 EGL_NONE）
int get_config_value_from_attrib(int* in_config_ptr, int in_attrib) {
    if (!check_is_config(in_config_ptr) || !check_is_config_type(in_config_ptr)) {
        return EGL_NONE;
    }
    int* ptr = in_config_ptr;
    while (ptr < get_end_config_ptr() && *ptr != EGL_NONE) {
        if (*ptr == in_attrib) {
            return *(ptr + 1);  // 返回对应值
        }
        ptr += 2;
    }
    return EGL_NONE;
}

// 比较配置是否满足给定属性列表（in_attribs_ptr 以 EGL_NONE 结尾）
bool compare_config_attribs(int* in_config_ptr, int* in_attribs_ptr) {
    if (in_attribs_ptr == nullptr) return true;
    if (!check_is_config(in_config_ptr) || !check_is_config_type(in_config_ptr)) {
        return false;
    }
    int* attr_ptr = in_attribs_ptr;
    while (*attr_ptr != EGL_NONE) {
        int attrib = *attr_ptr;
        int required_value = *(attr_ptr + 1);
        int actual_value = get_config_value_from_attrib(in_config_ptr, attrib);
        if (actual_value == EGL_NONE || actual_value != required_value) {
            return false;
        }
        attr_ptr += 2;
    }
    return true;
}

// 主函数：根据属性列表获取匹配的配置列表
void get_configs_for_attribs(int** out_configs_ptr, int in_config_num,
                             int* out_config_num_ptr, int* in_attribs_ptr) {
    int max_config_num = get_max_config_num();
    if (out_config_num_ptr) *out_config_num_ptr = max_config_num;

    if (out_configs_ptr == nullptr || in_config_num <= 0) {
        return;  // 第一次调用，仅返回数量
    }

    int* start = get_start_config_ptr();
    int matched = 0;
    int* current = start;

    while (current < get_end_config_ptr() && *current != EGL_NO_CONFIG && matched < in_config_num) {
        if (compare_config_attribs(current, in_attribs_ptr)) {
            out_configs_ptr[matched] = current;
            matched++;
        }
        current = get_next_config_ptr(current);
        if (current == nullptr) break;
    }
    // 如果 out_config_num_ptr 非空，可以更新为实际匹配数量（可选）
    // 但按 EGL 规范，应返回总数，所以上面已经返回总数，这里不再修改
}
} // namespace Config
} // namespace EGL
