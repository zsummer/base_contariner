
/*
* zmem_color License
* Copyright (C) 2019 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#pragma once
#ifndef _ZMEM_COLOR_H_
#define _ZMEM_COLOR_H_
#include "zallocator.h"
#include "zlist_ext.h"
#include <map>
#include <set>
#include <vector>
#include <list>
#include <string>
namespace zsummer
{
    enum zmem_color_enum
    {
        MEM_COLOR_NULL = 0,
        MEM_COLOR_STRING = 1,
        MEM_COLOR_VECTOR = 2,
        MEM_COLOR_MAP = 3,
        MEM_COLOR_SET = 4,
        MEM_COLOR_LIST = 5,
        MEM_COLOR_SEG_LIST = 6,
        MEM_COLOR_MAX,
    };

    static_assert(MEM_COLOR_MAX < zmalloc::CHUNK_COLOR_MASK / 2, "color max");
    using shm_string = std::basic_string<char, std::char_traits<char>, zallocator<char, MEM_COLOR_STRING> >;

    template<class _Ty>
    using shm_vector = std::vector<_Ty, zallocator<_Ty, MEM_COLOR_VECTOR>>;

    template<class K, class T, class P = std::less<K> >
    using shm_map = std::map<K, T, P, zallocator<std::pair<const K, T>, MEM_COLOR_MAP> >;

    template<class K, class P = std::less<K>>
    using shm_set = std::set<K, P, zallocator<K, MEM_COLOR_SET> >;

    template<class _Ty>
    using shm_list = std::list<_Ty, zallocator<_Ty, MEM_COLOR_LIST>>;

    template<class _Ty, size_t _Size, size_t _FixedSize>
    using shm_zlist_ext = zlist_ext<_Ty, _Size, _FixedSize, zallocator<typename std::aligned_storage<sizeof(_Ty), alignof(_Ty)>::type, MEM_COLOR_SEG_LIST>>;

    //unresumable area.  

};

#endif