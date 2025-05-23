/*
 * Copyright (c) 2018-2022, 2024-2025 Arm Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "arm_compute/core/CPP/CPPTypes.h"

#include "arm_compute/core/Error.h"

#include "src/common/cpuinfo/CpuInfo.h"
#include "src/common/cpuinfo/CpuIsaInfo.h"
#include "src/core/NEON/kernels/arm_gemm/utils.hpp"

namespace arm_compute
{
struct CPUInfo::Impl
{
    cpuinfo::CpuInfo info{};
    unsigned int     L1_cache_size = 32768;
    unsigned int     L2_cache_size = 262144;
};

CPUInfo &CPUInfo::get()
{
    static CPUInfo _cpuinfo;
    return _cpuinfo;
}

CPUInfo::CPUInfo() : _impl(std::make_unique<Impl>())
{
    _impl->info = cpuinfo::CpuInfo::build();
}

CPUInfo::~CPUInfo() = default;

unsigned int CPUInfo::get_cpu_num() const
{
    return _impl->info.num_cpus();
}

bool CPUInfo::has_fp16() const
{
    return _impl->info.has_fp16();
}

bool CPUInfo::has_bf16() const
{
    return _impl->info.has_bf16();
}

bool CPUInfo::has_svebf16() const
{
    return _impl->info.has_svebf16();
}

bool CPUInfo::has_dotprod() const
{
    return _impl->info.has_dotprod();
}

bool CPUInfo::has_svef32mm() const
{
    return _impl->info.has_svef32mm();
}

bool CPUInfo::has_i8mm() const
{
    return _impl->info.has_i8mm();
}

bool CPUInfo::has_svei8mm() const
{
    return _impl->info.has_svei8mm();
}

bool CPUInfo::has_fhm() const
{
    return _impl->info.has_fhm();
}

bool CPUInfo::has_sve() const
{
    return _impl->info.has_sve();
}

bool CPUInfo::has_sve2() const
{
    return _impl->info.has_sve2();
}

bool CPUInfo::has_sme() const
{
    return _impl->info.has_sme();
}

bool CPUInfo::has_sme2() const
{
    return _impl->info.has_sme2();
}

CPUModel CPUInfo::get_cpu_model() const
{
    return _impl->info.cpu_model();
}

CPUModel CPUInfo::get_cpu_model(unsigned int cpuid) const
{
    return _impl->info.cpu_model(cpuid);
}

cpuinfo::CpuIsaInfo CPUInfo::get_isa() const
{
    return _impl->info.isa();
}

unsigned int CPUInfo::get_L1_cache_size() const
{
    return _impl->L1_cache_size;
}

unsigned int CPUInfo::get_L2_cache_size() const
{
    return _impl->L2_cache_size;
}

uint64_t CPUInfo::get_sme2_vector_length_in_bytes() const
{
#ifdef ARM_COMPUTE_ENABLE_SME2
    if (this->has_sme2())
        return arm_gemm::utils::sme::get_vector_length<int8_t>();
    else
        return 0;
#else  // ARM_COMPUTE_ENABLE_SME2
    return 0;
#endif // ARM_COMPUTE_ENABLE_SME2
}

uint64_t CPUInfo::get_sme2_vector_length_in_bits() const
{
    return get_sme2_vector_length_in_bytes() * 8;
}

unsigned int CPUInfo::get_cpu_num_excluding_little() const
{
#if defined(__ANDROID__)
    return _impl->info.not_little_num_cpus();
#else  /* defined(__ANDROID__) */
    return get_cpu_num();
#endif /* defined(__ANDROID__) */
}
} // namespace arm_compute
