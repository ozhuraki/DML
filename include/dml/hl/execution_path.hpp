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

/**
 * @date 05/20/2021
 * @brief Contains execution path abstractions
 */

#ifndef DML_EXECUTION_PATH_HPP
#define DML_EXECUTION_PATH_HPP

#include <dml/detail/ml/execution_path.hpp>
#include <thread>

namespace dml
{
    /**
     * @defgroup dmlhl_aux_path Execution Path
     * @ingroup dmlhl_api
     * @brief Execution paths description
     * @{
     */

    /**
     * @brief Represent software execution path
     *
     * Specifies that an operation is executed on a CPU.
     */
    struct software
    {
        /**
         * @brief Default thread spawner for the software execution path
         */
        struct default_thread_spawner
        {
            /**
             * @brief Starts a task in a detached standard thread
             *
             * @tparam task_t Type of callable task
             * @param task    Instance of a callable task
             */
            template <typename task_t>
            void operator()(task_t &&task) const
            {
                std::thread(std::forward<task_t>(task)).detach();
            }
        };

        /**
         * @brief Default allocator type for software execution path
         */
        using default_allocator = std::allocator<byte_t>;

        /**
         * @brief Proxy for lower level execution path
         */
        using execution_path = detail::ml::execution_path::software;
    };

    /**
     * @brief Represent hardware execution path
     *
     * Specifies that an operation is executed on a dedicated hardware.
     */
    struct hardware
    {
        /**
         * @brief Default thread spawner for the hardware execution path
         */
        struct default_thread_spawner
        {
            /**
             * @brief Starts a task directly (assume the hardware is asynchronous)
             *
             * @tparam task_t Type of callable task
             * @param task    Instance of a callable task
             *
             * @return Task return value (if present)
             */
            template <typename task_t>
            decltype(auto) operator()(task_t &&task) const noexcept(noexcept(task()))
            {
                return task();
            }
        };

        /**
         * @brief Default allocator type for hardware execution path
         */
        using default_allocator = std::allocator<byte_t>;

        /**
         * @brief Proxy for lower level execution path
         */
        using execution_path = detail::ml::execution_path::hardware;
    };

    /**
     * @}
     */
}  // namespace dml

#endif  //DML_EXECUTION_PATH_HPP
