/*
 * Copyright (c) 2017-2021, 2024-2025 Arm Limited.
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
#ifndef ACL_ARM_COMPUTE_RUNTIME_NEON_FUNCTIONS_NEDEQUANTIZATIONLAYER_H
#define ACL_ARM_COMPUTE_RUNTIME_NEON_FUNCTIONS_NEDEQUANTIZATIONLAYER_H

/** @file
 * @publicapi
 */

#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/IFunction.h"

#include <memory>

namespace arm_compute
{
// Forward declarations
class ITensor;
class ITensorInfo;

/** Basic function to run cpu::CpuDequantize that dequantizes an input tensor */
class NEDequantizationLayer : public IFunction
{
public:
    /** Default Constructor */
    NEDequantizationLayer();
    /** Default Destructor */
    ~NEDequantizationLayer();
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    NEDequantizationLayer(const NEDequantizationLayer &) = delete;
    /** Default move constructor */
    NEDequantizationLayer(NEDequantizationLayer &&) = default;
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    NEDequantizationLayer &operator=(const NEDequantizationLayer &) = delete;
    /** Default move assignment operator */
    NEDequantizationLayer &operator=(NEDequantizationLayer &&) = default;
    /** Configure the kernel.
     *
     * Valid data layouts:
     * - All
     *
     * Valid data type configurations:
     * |src                |dst         |
     * |:------------------|:-----------|
     * |QASYMM8            |F16, F32    |
     * |QASYMM8_SIGNED     |F16, F32    |
     * |QSYMM8_PER_CHANNEL |F16, F32    |
     * |QSYMM8             |F16, F32    |
     * |QSYMM16            |F16, F32    |
     *
     * @param[in]  input  Source tensor. Data types supported: QASYMM8/QASYMM8_SIGNED/QSYMM8_PER_CHANNEL/QSYMM8/QSYMM16.
     * @param[out] output Destination tensor with the same dimensions of input. Data type supported: F16/F32.
     */
    void configure(const ITensor *input, ITensor *output);
    /** Static function to check if given info will lead to a valid configuration of @ref NEDequantizationLayer
     *
     * @param[in] input  Input tensor info. Data types supported: QASYMM8/QASYMM8_SIGNED/QSYMM8_PER_CHANNEL/QSYMM8/QSYMM16.
     * @param[in] output Output tensor info. Data type supported: F16/F32.
     *
     * @return a status
     */
    static Status validate(const ITensorInfo *input, const ITensorInfo *output);

    // Inherited methods overridden:
    void run() override;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};
} // namespace arm_compute
#endif // ACL_ARM_COMPUTE_RUNTIME_NEON_FUNCTIONS_NEDEQUANTIZATIONLAYER_H
