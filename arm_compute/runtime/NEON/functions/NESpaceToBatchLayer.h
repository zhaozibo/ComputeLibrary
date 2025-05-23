/*
 * Copyright (c) 2019-2021, 2024-2025 Arm Limited.
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
#ifndef ACL_ARM_COMPUTE_RUNTIME_NEON_FUNCTIONS_NESPACETOBATCHLAYER_H
#define ACL_ARM_COMPUTE_RUNTIME_NEON_FUNCTIONS_NESPACETOBATCHLAYER_H

/** @file
 * @publicapi
 */

#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/IFunction.h"

#include <memory>

namespace arm_compute
{
class ITensor;
class ITensorInfo;
class NESpaceToBatchLayerKernel;
class NEFill;

/** Basic function to spatial divide a tensor. This function calls the following kernels/functions:
 *
 *  -# @ref NEFill
 *  -# NESpaceToBatchLayerKernel
 */
class NESpaceToBatchLayer : public IFunction
{
public:
    /** Default constructor */
    NESpaceToBatchLayer();
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    NESpaceToBatchLayer(const NESpaceToBatchLayer &) = delete;
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    NESpaceToBatchLayer &operator=(const NESpaceToBatchLayer &) = delete;
    /** Allow instances of this class to be moved */
    NESpaceToBatchLayer(NESpaceToBatchLayer &&) = default;
    /** Allow instances of this class to be moved */
    NESpaceToBatchLayer &operator=(NESpaceToBatchLayer &&) = default;
    /** Default destructor */
    ~NESpaceToBatchLayer();
    /** Set the input and output tensors.
     *
     * Valid data layouts:
     * - NHWC
     * - NCHW
     *
     * Valid data type configurations:
     * |src0      |src1      |src2      |dst       |
     * |:---------|:---------|:---------|:---------|
     * |All       |S32       |S32       |All       |
     *
     * @param[in]  input       Tensor input. Supported tensor rank: 4. Data types supported: All.
     * @param[in]  block_shape 1-D tensor with shape [M]. Supported M: 2. Data types supported: S32
     * @param[in]  paddings    2-D tensor with shape [2, M] (First dimension is the fastest-changing dimension). Supported M: 2. Data types supported: S32
     * @param[out] output      Tensor output. Data types supported: same as @p input
     */
    void configure(const ITensor *input, const ITensor *block_shape, const ITensor *paddings, ITensor *output);
    /** Set the input and output tensors. (Static block shape and paddings)
     *
     * @param[in]  input         Tensor input. Supported tensor rank: 4. Data types supported: All.
     * @param[in]  block_shape_x Block shape x value.
     * @param[in]  block_shape_y Block shape y value.
     * @param[in]  padding_left  The padding at the beginning of every dimension of the output tensor.
     * @param[in]  padding_right The padding at the end of every dimension of the output tensor.
     * @param[out] output        Tensor output. Data types supported: same as @p input
     */
    void configure(const ITensor *input,
                   const int      block_shape_x,
                   const int      block_shape_y,
                   const Size2D  &padding_left,
                   const Size2D  &padding_right,
                   ITensor       *output);
    /** Static function to check if given info will lead to a valid configuration of @ref NESpaceToBatchLayer
     *
     * @param[in] input       Tensor input info. Supported tensor rank: 4. Data types supported: All.
     * @param[in] block_shape 1-D tensor with shape [M]. Supported M: 2. Data types supported: S32
     * @param[in] paddings    2-D tensor with shape [2, M] (First dimension is the fastest-changing dimension). Supported M: 2. Data types supported: S32
     * @param[in] output      Tensor output info. Data types supported: same as @p input
     *
     * @return a status
     */
    static Status validate(const ITensorInfo *input,
                           const ITensorInfo *block_shape,
                           const ITensorInfo *paddings,
                           const ITensorInfo *output);
    /** Static function to check if given info will lead to a valid configuration of @ref NESpaceToBatchLayer (Static block shape and paddings)
     *
     * @param[in] input         Tensor input info. Supported tensor rank: 4. Data types supported: All.
     * @param[in] block_shape_x Block shape x value.
     * @param[in] block_shape_y Block shape y value.
     * @param[in] padding_left  The padding at the beginning of every dimension of the output tensor.
     * @param[in] padding_right The padding at the end of every dimension of the output tensor.
     * @param[in] output        Tensor output info. Data types supported: same as @p input
     *
     * @return a status
     */
    static Status validate(const ITensorInfo *input,
                           const int          block_shape_x,
                           const int          block_shape_y,
                           const Size2D      &padding_left,
                           const Size2D      &padding_right,
                           const ITensorInfo *output);

    // Inherited methods overridden:
    void run() override;

private:
    std::unique_ptr<NESpaceToBatchLayerKernel> _space_to_batch_kernel; /**< SpaceToBatch kernel to run */
    std::unique_ptr<NEFill>                    _fill_f;                /**< Fill function to run */
    bool                                       _has_padding;           /**< Flag to check if the output has padding */
};
} // namespace arm_compute
#endif // ACL_ARM_COMPUTE_RUNTIME_NEON_FUNCTIONS_NESPACETOBATCHLAYER_H
