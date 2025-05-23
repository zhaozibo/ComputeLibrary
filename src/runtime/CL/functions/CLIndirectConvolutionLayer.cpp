/*
 * Copyright (c) 2022, 2024 Arm Limited.
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
#include "arm_compute/runtime/CL/functions/CLIndirectConvolutionLayer.h"

#include "arm_compute/core/CL/ICLTensor.h"
#include "arm_compute/core/Utils.h"
#include "arm_compute/core/Validate.h"

#include "src/common/utils/Log.h"
#include "src/gpu/cl/operators/ClIndirectConv2d.h"

namespace arm_compute
{
struct CLIndirectConvolutionLayer::Impl
{
    const ICLTensor                          *src{nullptr};
    const ICLTensor                          *weights{nullptr};
    const ICLTensor                          *biases{nullptr};
    ICLTensor                                *dst{nullptr};
    std::unique_ptr<opencl::ClIndirectConv2d> op{nullptr};
};

CLIndirectConvolutionLayer::CLIndirectConvolutionLayer() : _impl(std::make_unique<Impl>())
{
}
CLIndirectConvolutionLayer::CLIndirectConvolutionLayer(CLIndirectConvolutionLayer &&)            = default;
CLIndirectConvolutionLayer &CLIndirectConvolutionLayer::operator=(CLIndirectConvolutionLayer &&) = default;
CLIndirectConvolutionLayer::~CLIndirectConvolutionLayer()                                        = default;

void CLIndirectConvolutionLayer::configure(ICLTensor                 *input,
                                           const ICLTensor           *weights,
                                           const ICLTensor           *biases,
                                           ICLTensor                 *output,
                                           const PadStrideInfo       &conv_info,
                                           const ActivationLayerInfo &act_info)
{
    configure(CLKernelLibrary::get().get_compile_context(), input, weights, biases, output, conv_info, act_info);
}

void CLIndirectConvolutionLayer::configure(const CLCompileContext    &compile_context,
                                           ICLTensor                 *input,
                                           const ICLTensor           *weights,
                                           const ICLTensor           *biases,
                                           ICLTensor                 *output,
                                           const PadStrideInfo       &conv_info,
                                           const ActivationLayerInfo &act_info)
{
    ARM_COMPUTE_ERROR_ON_NULLPTR(input, weights, output);
    ARM_COMPUTE_LOG_PARAMS(input, weights, biases, output, conv_info, act_info);

    _impl->src     = input;
    _impl->weights = weights;
    _impl->biases  = biases;
    _impl->dst     = output;
    _impl->op      = std::make_unique<opencl::ClIndirectConv2d>();
    _impl->op->configure(compile_context, input->info(), weights->info(),
                         (biases != nullptr) ? biases->info() : nullptr, output->info(), conv_info, act_info);
}

Status CLIndirectConvolutionLayer::validate(const ITensorInfo         *input,
                                            const ITensorInfo         *weights,
                                            const ITensorInfo         *biases,
                                            const ITensorInfo         *output,
                                            const PadStrideInfo       &conv_info,
                                            const ActivationLayerInfo &act_info)
{
    ARM_COMPUTE_RETURN_ERROR_ON_DYNAMIC_SHAPE(input, weights, biases, output);
    return opencl::ClIndirectConv2d::validate(input, weights, biases, output, conv_info, act_info);
}

void CLIndirectConvolutionLayer::run()
{
    ITensorPack pack;
    pack.add_tensor(TensorType::ACL_SRC, _impl->src);
    pack.add_tensor(TensorType::ACL_SRC_1, _impl->weights);
    pack.add_tensor(TensorType::ACL_SRC_2, _impl->biases);
    pack.add_tensor(TensorType::ACL_DST, _impl->dst);
    _impl->op->run(pack);
}
} // namespace arm_compute
