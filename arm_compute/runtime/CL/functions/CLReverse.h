/*
 * Copyright (c) 2018-2021, 2023-2025 Arm Limited.
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
#ifndef ACL_ARM_COMPUTE_RUNTIME_CL_FUNCTIONS_CLREVERSE_H
#define ACL_ARM_COMPUTE_RUNTIME_CL_FUNCTIONS_CLREVERSE_H

/** @file
 * @publicapi
 */

#include "arm_compute/core/Error.h"
#include "arm_compute/runtime/CL/ICLSimpleFunction.h"

namespace arm_compute
{
class CLCompileContext;
class ICLTensor;
class ITensorInfo;

/** Basic function to run CLReverseKernel */
class CLReverse : public ICLSimpleFunction
{
public:
    /** Initialize the function
     *
     * Valid data layouts:
     * - All
     *
     * Valid data type configurations:
     * |src0           |src1           |dst            |
     * |:--------------|:--------------|:--------------|
     * |All            |U32, S32       |All            |
     *
     * @param[in]  input             Input tensor. Data types supported: All.
     * @param[out] output            Output tensor. Data type supported: Same as @p input
     * @param[in]  axis              Axis tensor. Contains the indices of the dimensions to reverse. Data type supported: U32/S32
     * @param[in]  use_inverted_axis Reverse ACL axis indices convention, if true, (inverted)axis = (tensor_rank - 1) - axis
     */
    void configure(const ICLTensor *input, ICLTensor *output, const ICLTensor *axis, bool use_inverted_axis);
    /** Initialize the function
     *
     * @param[in]  compile_context   The compile context to be used.
     * @param[in]  input             Input tensor. Data types supported: All.
     * @param[out] output            Output tensor. Data type supported: Same as @p input
     * @param[in]  axis              Axis tensor. Contains the indices of the dimensions to reverse. Data type supported: U32/S32
     * @param[in]  use_inverted_axis Reverse ACL axis indices convention, if true, (inverted)axis = (tensor_rank - 1) - axis
     */
    void configure(const CLCompileContext &compile_context,
                   const ICLTensor        *input,
                   ICLTensor              *output,
                   const ICLTensor        *axis,
                   bool                    use_inverted_axis);
    /** Static function to check if given info will lead to a valid configuration of CLReverseKernel
     *
     * @param[in] input             Input tensor info. Data types supported: All.
     * @param[in] output            Output tensor info. Data type supported: Same as @p input
     * @param[in] axis              Axis tensor info. Contains the indices of the dimensions to reverse. Data type supported: U32/S32
     * @param[in] use_inverted_axis Reverse ACL axis indices convention, if true, (inverted)axis = (tensor_rank - 1) - axis
     *
     * @return a status
     */
    static Status
    validate(const ITensorInfo *input, const ITensorInfo *output, const ITensorInfo *axis, bool use_inverted_axis);
};
} // namespace arm_compute
#endif // ACL_ARM_COMPUTE_RUNTIME_CL_FUNCTIONS_CLREVERSE_H
