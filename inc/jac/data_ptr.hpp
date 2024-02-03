#pragma once

#include <memory>

#include <jac/type_defs.hpp>

namespace jac
{
    struct DataPtr
    {
        constexpr static uint64 memory_alignment = 0b11;
        constexpr static uint64 upper_bits = 0xFFFF'FFFF'0000'0000;
        constexpr static uint64 max_data = 0b111111111111111111;

        using uint18 = uint32;
        public:
            constexpr DataPtr(const void* ptr = nullptr, uint18 data = 0) noexcept
            {
                setPtr(ptr);
                setData(data);
            }

            [[nodiscard]] constexpr auto getPtr() const noexcept -> const void* {
                return reinterpret_cast<void*>(m_ptr & ~upper_bits & ~memory_alignment);
            }

            constexpr auto setPtr(const void* ptr) noexcept -> void {
                m_ptr &= upper_bits | memory_alignment;
                m_ptr |= reinterpret_cast<uint64>(ptr);
            }

            [[nodiscard]] constexpr auto getData() const noexcept -> uint18 {
                return (m_ptr & memory_alignment) + (m_ptr & upper_bits) >> 46;
            }

            constexpr auto setData(uint18 data) noexcept -> void {
                data &= max_data;

                m_ptr &= ~memory_alignment & ~upper_bits;
                m_ptr |= (data & memory_alignment) + ((data & ~memory_alignment) << 46);
            }

        // private:
            //############################################################################################################
            // Pointer in memory (in 64 bit system)
            // XXXXXXXX XXXXXXXX 01234567 01234567 01234567 01234567 01234567 012345XX
            //                   ||                                                |             
            //                   ||                                           Memory alignment
            //                48-bit address space
            //                   |
            //            User/Kernel space bit
            //
            // Xs are unused bits that can be used to store data
            // 
            //############################################################################################################
            uint64 m_ptr = 0;
    };
}   // namespace jac