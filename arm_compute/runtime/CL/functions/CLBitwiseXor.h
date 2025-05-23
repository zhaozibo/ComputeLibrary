/*
 * Copyright (c) 2016-2021, 2024-2025 Arm Limited.
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
#ifndef ACL_ARM_COMPUTE_RUNTIME_CL_FUNCTIONS_CLBITWISEXOR_H
#define ACL_ARM_COMPUTE_RUNTIME_CL_FUNCTIONS_CLBITWISEXOR_H

/** @file
 * @publicapi
 */

#include "arm_compute/runtime/CL/ICLSimpleFunction.h"

namespace arm_compute
{
class CLCompileContext;
class ICLTensor;

/** Basic function to perform bitwise XOR by running CLBitwiseKernel.
 *
 * @note The tensor data type for the inputs must be U8.
 * @note The function performs a bitwise XOR operation using the two input tensors.
 */
class CLBitwiseXor : public ICLSimpleFunction
{
public:
    /** Initialize the function
     *
     * Valid data layouts:
     * - All
     *
     * Valid data type configurations:
     * |src            |dst            |
     * |:--------------|:--------------|
     * |U8             |U8             |
     *
     * @param[in]  input1 Input tensor. Data types supported: U8.
     * @param[in]  input2 Input tensor. Data types supported: U8.
     * @param[out] output Output tensor. Data types supported: U8.
     */
    void configure(const ICLTensor *input1, const ICLTensor *input2, ICLTensor *output);
    /** Initialize the function
     *
     * @param[in]  compile_context The compile context to be used.
     * @param[in]  input1          Input tensor. Data types supported: U8.
     * @param[in]  input2          Input tensor. Data types supported: U8.
     * @param[out] output          Output tensor. Data types supported: U8.
     */
    void configure(const CLCompileContext &compile_context,
                   const ICLTensor        *input1,
                   const ICLTensor        *input2,
                   ICLTensor              *output);
};
} // namespace arm_compute
#endif // ACL_ARM_COMPUTE_RUNTIME_CL_FUNCTIONS_CLBITWISEXOR_H
