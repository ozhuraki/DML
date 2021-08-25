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

#include "own/definitions.hpp"
#include "own/types.hpp"

#include <dml_ml/compare.hpp>
#include <dml_ml/result.hpp>

#include <core_api.h>

namespace dml::ml
{
    DML_PACKED_STRUCT_DECLARATION_BEGIN(compare_descriptor)
    {
        uint32_t      privilege_control{};        /**< Unused */
        hw_option     general_flags{};            /**< Contains a common flags for different operations */
        uint8_t       operation_specific_flags{}; /**< Contains a specific flags for operation  */
        hw_operation  operation_type{};           /**< Contains an operation type @ref dml_operation_t */
        result *      completion_record_ptr{};    /**< Pointer to the completion record space */
        const byte_t *source_ptr1{};              /**< Pointer to the source 1 */
        const byte_t *source_ptr2{};              /**< Pointer to the source 2 */
        size_t        transfer_size{};            /**< Count of bytes to copy */
        byte_t        reserved_memory1[4]{};      /**< Not used bytes in the descriptor */
        result_t      expected_result{};          /**< Expected result */
        byte_t        reserved_memory2[23]{};     /**< Not used bytes in the descriptor */
    };
    DML_PACKED_STRUCT_DECLARATION_END

    DML_PACKED_STRUCT_DECLARATION_BEGIN(compare_completion_record)
    {
        hw_status status{};            /**< Status of the executed task: success or some Error */
        result_t  result{};            /**< Result of completed operation                      */
        uint8_t   reserved_1[2]{};     /**< Reserved bytes                                     */
        uint32_t  bytes_completed{};   /**< Count of processed elements (bytes, words and etc.)*/
        uint8_t * fault_address_ptr{}; /**< Address of Page Fault */
        uint8_t   reserved_2[16]{};    /**< Reserved bytes        */
    };
    DML_PACKED_STRUCT_DECLARATION_END

    compare::compare(const byte_t *src1, const byte_t *src2, size_t size, equality expect) noexcept: operation_()
    {
        auto &descriptor = *reinterpret_cast<compare_descriptor *>(operation_.data());

        descriptor.operation_type = hw_operation::compare;

        descriptor.source_ptr1   = src1;
        descriptor.source_ptr2   = src2;
        descriptor.transfer_size = size;

        if (expect == equality::equal)
        {
            descriptor.general_flags   = descriptor.general_flags | hw_option::check_result;
            descriptor.expected_result = 0x0;
        }

        if (expect == equality::not_equal)
        {
            descriptor.general_flags   = descriptor.general_flags | hw_option::check_result;
            descriptor.expected_result = 0x1;
        }
    }

    void compare::operator()() const noexcept
    {
        auto dsc    = reinterpret_cast<const compare_descriptor *>(operation_.data());
        auto record = reinterpret_cast<compare_completion_record *>(dsc->completion_record_ptr);

        auto bytes_completed = uint32_t();

        // No fail expected due to range check before
        auto status = dmlc_compare_8u(dsc->source_ptr1, dsc->source_ptr2, dsc->transfer_size, &bytes_completed);
        record->bytes_completed = bytes_completed;

        if (status == DML_COMPARE_STATUS_NE)
        {
            record->result = 1;
        }
        else if (status != DML_STATUS_OK)
        {
            record->status = hw_status::internal_error;
            return;
        }

        if (any(dsc->general_flags, hw_option::check_result))
        {
            record->status =
                (record->result == dsc->expected_result) ? hw_status::success : hw_status::false_predicate_success;
        }
        else
        {
            record->status = hw_status::success;
        }
    }

    result::operator compare_result() const noexcept
    {
        auto record = reinterpret_cast<const compare_completion_record *>(data_);

        auto status          = (record->status == hw_status::success)                   ? status_code::ok
                               : (record->status == hw_status::false_predicate_success) ? status_code::false_predicate
                                                                                        : status_code::execution_failed;
        auto result          = record->result;
        auto bytes_processed = record->bytes_completed;

        return {status, result, bytes_processed};
    }
}  // namespace dml::ml