#pragma once

#include <functional>
#include <type_traits>

namespace jac {
    template <typename T>
    class Property 
    {
        public:
            using const_t = 
                std::conditional_t<std::is_fundamental_v<T>, const T, const T&>;
            using mutable_t = T&;


            using Getter = std::function<const_t(const_t)>;
            using Setter = std::function<void(mutable_t, const_t)>;

            Property(T& value, const Getter getter, const Setter setter) :
                m_value{value},
                m_getter{getter},
                m_setter{setter}
            {}

            operator const_t() const {
                return m_getter(m_value);
            }

            auto operator=(const_t other) -> Property& {
                m_setter(m_value, other);
                return *this;
            }
        private:
            T& m_value;
            const Getter m_getter;
            const Setter m_setter;
    };  // class Property
};  // namespace jac

/******************************************************************************************/
// Example usage:
//
//  #include "jac/properties.hpp"
//  #include <iostream>
//  #include <format>
//  
//  auto IntGetter(const int member) -> const int {
//      std::cout << std::format("Getter: {}\n", member);
//      return member;
//  }
//  
//  auto IntSetter(int& member, const int other) -> void {
//      std::cout << std::format("Setter: {} -> {}\n", member, other);
//      member = other;
//  }
//  
//  class Example
//  {
//      public:
//          jac::Property<int> Member
//          {
//              m_member,
//              IntGetter,
//              IntSetter
//          };
//      private:
//          int m_member{};
//  };
//  
//  int main() {
//      Example e;
//      e.Member = 5;   // :> Setter: 0 -> 5
//  
//      int x = e.Member;  // :> Getter: 5
//  
//      std::cout << e.Member << '\n';  // :> Getter: 5 \n 5
//  }
/******************************************************************************************/
