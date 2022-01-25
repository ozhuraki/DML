/*
 * Copyright 2021 Intel Corporation.
 *
 * This software and the related documents are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they
 * were provided to you ("License"). Unless the License provides otherwise,
 * you may not use, modify, copy, publish, distribute, disclose or transmit
 * this software or the related documents without Intel's prior written
 * permission.
 *
 * This software and the related documents are provided as is, with no
 * express or implied warranties, other than those that are expressly
 * stated in the License.
 *
 */

#ifndef DML_CORE_OPERATIONS_HPP
#define DML_CORE_OPERATIONS_HPP

#include <core/types.hpp>
#include <type_traits>

namespace dml::core
{
    enum class operation : operation_t
    {
        nop             = 0x00,
        batch           = 0x01,
        drain           = 0x02,
        mem_move        = 0x03,
        fill            = 0x04,
        compare         = 0x05,
        compare_pattern = 0x06,
        create_delta    = 0x07,
        apply_delta     = 0x08,
        dualcast        = 0x09,
        crc             = 0x10,
        copy_crc        = 0x11,
        dif_check       = 0x12,
        dif_insert      = 0x13,
        dif_strip       = 0x14,
        dif_update      = 0x15,
        cache_flush     = 0x20
    };
}  // namespace dml::core

#endif  //DML_CORE_OPERATIONS_HPP
