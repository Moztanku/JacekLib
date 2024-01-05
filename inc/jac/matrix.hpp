#pragma once

#include "jac/type_defs.hpp"

#include <memory>
#include <array>
#include <vector>
#include <ostream>

namespace jac {
    template<class T, size_t X, size_t Y>
    class matrix {
        public:
            auto operator[](const idx x) noexcept
            {
                return Column(data,x);
            }

            auto operator[](const idx x) const noexcept
            {
                return Column(const_cast<std::array<T, X * Y>&>(data),x);
            }

            auto operator-() const noexcept -> matrix
            {
                matrix result;
                for(idx i = 0; i < X * Y; i++)
                    result.data[i] = -data[i];
                return result;
            }

            friend auto operator<<(std::ostream& os, const matrix& mat) noexcept -> std::ostream&
            {
                os << "{";
                for(idx y = 0; y < Y; y++)
                    os << Row(const_cast<std::array<T, X * Y>&>(mat.data),y) << ",";
                os << "\b}";
                return os;
            }

            auto toString() noexcept -> std::string
            {
                uint maxWidth{};
                uint width{};
                for(auto e : data)
                    if((width = std::to_string(e).length()) > maxWidth)
                        maxWidth = width;

                std::string result;
                for(idx y = 0; y < Y; y++){
                    result += Row(data,y).toString(maxWidth) + "\n";
                }
                return result;
            }

            auto toVector() noexcept -> std::vector<T>
            {
                std::vector<T> result;
                for(auto e : data)
                    result.push_back(e);
                return result;
            }

            auto transpose() const noexcept -> matrix<T, Y, X>
            {
                matrix<T, Y, X> result;
                for(idx y = 0; y < Y; y++)
                    for(idx x = 0; x < X; x++)
                        result[y][x] = (*this)[x][y];
                return result;
            }

            static auto Identity() noexcept -> matrix
            {
                static_assert(X == Y, "Identity matrix must be square!");

                matrix result;
                for(idx i = 0; i < X; i++)
                    result[i][i] = 1;
                return result;
            }
        private:
            std::array<T, X * Y> data{};

            template<bool isColumn>
            struct matrix_slice {
                matrix_slice(std::array<T, X * Y>& data, const idx I) : data(data), I(I) {}
                matrix_slice(const matrix_slice& slice) : data(slice.data), I(slice.I) {}
                
                static constexpr size_t size = isColumn ? Y : X;
                std::array<T, X * Y>& data{};
                idx I{};

                auto operator[](idx i) -> T&
                {
                    if(i >= size)
                        throw std::runtime_error("Index out of bounds!");

                    if constexpr(isColumn)
                        return data[I + i * X];
                    else 
                        return data[I * X + i];
                }

                auto operator[](idx i) const -> const T&
                {
                    if(i >= size)
                        throw std::runtime_error("Index out of bounds!");

                    if constexpr(isColumn)
                        return data[I + i * X];
                    else 
                        return data[I * X + i];
                }

                auto operator=(const std::initializer_list<T>& list) -> matrix_slice&
                {
                    if(list.size() != size)
                        throw std::runtime_error("Invalid initializer list size!");

                    auto it = list.begin();
                    for(idx i = 0; i < size; i++)
                        (*this)[i] = *it++;
                    return *this;
                }

                auto operator=(const matrix_slice& slice) -> matrix_slice&
                {
                    if(&slice == this)
                        return *this;

                    for(idx i = 0; i < size; i++)
                        (*this)[i] = slice[i];
                    return *this;
                }

                auto operator-() -> matrix_slice
                {
                    for(idx i = 0; i < size; i++)
                        (*this)[i] = -(*this)[i];
                    return *this;
                }

                friend auto operator<<(std::ostream& os, const matrix_slice& slice) noexcept -> std::ostream&
                {
                    os << "{";
                    for(idx i = 0; i < size; i++)
                        os << slice[i] << ",";
                    os << "\b}";
                    return os;
                }

                auto reverse() -> matrix_slice&
                {
                    for(idx i = 0; i < size/2; i++)
                        std::swap((*this)[i], (*this)[size - i - 1]);
                    return *this;
                }

                auto toString(uint maxWidth = 0) const noexcept -> std::string
                {
                    if(maxWidth == 0){
                        uint width{};
                        for(auto e : data)
                            if((width = std::to_string(e).length()) > maxWidth)
                                maxWidth = width;
                    }

                    std::string result;
                    for(idx i = 0; i < size; i++){
                        auto e = std::to_string((*this)[i]);
                        auto pr = (maxWidth - e.length() + 1)/2;
                        auto pl = maxWidth - e.length() + 1 - pr;
                        result += std::string(pl,' ') + e + std::string(pr,' ') + " |";
                    }
                    result.pop_back();
                    return result;
                }
            }; // class matrix_slice

            using Column = matrix_slice<true>;
            using Row = matrix_slice<false>;
    }; // class matrix
}   // namespace jac
