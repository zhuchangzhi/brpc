// Copyright (c) 2014 Baidu, Inc.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Authors: Ge,Jun (gejun@baidu.com)

#ifndef BRPC_PROFILER_LINKER_H
#define BRPC_PROFILER_LINKER_H

#if defined(BRPC_ENABLE_CPU_PROFILER) || defined(BAIDU_RPC_ENABLE_CPU_PROFILER)
#ifdef __cplusplus
extern "C" {
#endif
// Suppress warning of `google/profiler.h' which has been deprecated since
// gperftools-2.2
void ProfilerStart(const char*);
void ProfilerStop(const char*);
#ifdef __cplusplus
}
#endif
#endif

namespace brpc {

// defined in src/brpc/builtin/index_service.cpp
extern bool cpu_profiler_enabled;

// defined in src/brpc/controller.cpp
extern int PROFILER_LINKER_DUMMY;

struct ProfilerLinker {
    // [ Must be inlined ]
    // This function is included by user's compilation unit to force
    // linking of ProfilerStart()/ProfilerStop()
    // etc when corresponding macros are defined.
    inline ProfilerLinker() {
        
#if defined(BRPC_ENABLE_CPU_PROFILER) || defined(BAIDU_RPC_ENABLE_CPU_PROFILER)
        cpu_profiler_enabled = true;
        // compiler has no way to tell if PROFILER_LINKER_DUMMY is 0 or not,
        // so it has to link the function inside the branch.
        if (PROFILER_LINKER_DUMMY != 0/*must be false*/) {
            ProfilerStart("this_function_should_never_run");
        }
#endif
    }
};

} // namespace brpc


#endif  // BRPC_PROFILER_LINKER_H
