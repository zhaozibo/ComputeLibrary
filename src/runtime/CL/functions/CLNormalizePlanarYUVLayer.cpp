/*
 * Copyright (c) 2018-2021, 2024 Arm Limited.
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

#include "arm_compute/runtime/CL/functions/CLNormalizePlanarYUVLayer.h"

#include "src/common/utils/Log.h"
#include "src/core/CL/kernels/CLNormalizePlanarYUVLayerKernel.h"

#include <utility>

namespace arm_compute
{
void CLNormalizePlanarYUVLayer::configure(const ICLTensor *input,
                                          ICLTensor       *output,
                                          const ICLTensor *mean,
                                          const ICLTensor *std)
{
    configure(CLKernelLibrary::get().get_compile_context(), input, output, mean, std);
}

void CLNormalizePlanarYUVLayer::configure(const CLCompileContext &compile_context,
                                          const ICLTensor        *input,
                                          ICLTensor              *output,
                                          const ICLTensor        *mean,
                                          const ICLTensor        *std)
{
    ARM_COMPUTE_LOG_PARAMS(input, output, mean, std);
    auto k = std::make_unique<CLNormalizePlanarYUVLayerKernel>();
    k->configure(compile_context, input, output, mean, std);
    _kernel = std::move(k);
}

Status CLNormalizePlanarYUVLayer::validate(const ITensorInfo *input,
                                           const ITensorInfo *output,
                                           const ITensorInfo *mean,
                                           const ITensorInfo *std)
{
    ARM_COMPUTE_RETURN_ERROR_ON_DYNAMIC_SHAPE(input, output, mean, std);
    return CLNormalizePlanarYUVLayerKernel::validate(input, output, mean, std);
}
} // namespace arm_compute
