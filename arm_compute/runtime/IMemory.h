/*
 * Copyright (c) 2018-2019, 2025 Arm Limited.
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
#ifndef ACL_ARM_COMPUTE_RUNTIME_IMEMORY_H
#define ACL_ARM_COMPUTE_RUNTIME_IMEMORY_H

/** @file
 * @publicapi
 */

#include "arm_compute/runtime/IMemoryRegion.h"

namespace arm_compute
{
/** Memory interface*/
class IMemory
{
public:
    /** Virtual default destructor */
    virtual ~IMemory() = default;
    /** Region accessor
     *
     * @return Memory region
     */
    virtual IMemoryRegion *region() = 0;
    /** Region accessor
     *
     * @return Memory region
     */
    virtual IMemoryRegion *region() const = 0;
    /** Sets a memory region
     *
     * @warning Ownership of the memory region remains to the caller
     *
     * @param region Memory region
     */
    virtual void set_region(IMemoryRegion *region) = 0;
    /** Sets a memory region
     *
     * @warning Ownership of the memory region is transfered along
     *
     * @param region Memory region
     */
    virtual void set_owned_region(std::unique_ptr<IMemoryRegion> region) = 0;
};
} // namespace arm_compute
#endif // ACL_ARM_COMPUTE_RUNTIME_IMEMORY_H
