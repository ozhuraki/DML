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

#ifndef DML_CORE_OWN_KERNELS_HPP
#define DML_CORE_OWN_KERNELS_HPP

#include <core/view.hpp>

namespace dml::core::kernels
{
    void nop(const_view<descriptor, operation::nop> dsc) noexcept;

    void batch(const_view<descriptor, operation::batch> dsc) noexcept;

    void drain(const_view<descriptor, operation::drain> dsc) noexcept;

    void mem_move(const_view<descriptor, operation::mem_move> dsc) noexcept;

    void fill(const_view<descriptor, operation::fill> dsc) noexcept;

    void compare(const_view<descriptor, operation::compare> dsc) noexcept;

    void compare_pattern(const_view<descriptor, operation::compare_pattern>  dsc) noexcept;

    void create_delta(const_view<descriptor, operation::create_delta>  dsc) noexcept;

    void apply_delta(const_view<descriptor, operation::apply_delta> dsc) noexcept;

    void dualcast(const_view<descriptor, operation::dualcast> dsc) noexcept;

    void crc(const_view<descriptor, operation::crc> dsc) noexcept;

    void copy_crc(const_view<descriptor, operation::copy_crc> dsc) noexcept;

    void dif_check(const_view<descriptor, operation::dif_check> dsc) noexcept;

    void dif_insert(const_view<descriptor, operation::dif_insert> dsc) noexcept;

    void dif_strip(const_view<descriptor, operation::dif_strip> dsc) noexcept;

    void dif_update(const_view<descriptor, operation::dif_update> dsc) noexcept;

    void cache_flush(const_view<descriptor, operation::cache_flush> dsc) noexcept;
}  // namespace dml::core::kernels

#endif  //DML_CORE_OWN_KERNELS_HPP
