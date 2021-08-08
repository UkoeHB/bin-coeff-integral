// is_multiprecision_int<T> type trait
// adapted from: https://stackoverflow.com/questions/61623438/type-trait-for-boost-multiprecision-integers

#pragma once

//local headers

//third party headers
#include "boost/multiprecision/cpp_int.hpp"

//standard headers
#include <type_traits>


//helper struct for checking if type is cpp_int_backend at compile time using function overloading
template <typename T>
struct is_cpp_int_backend
{
    //this template will trigger for pointer to any 
    //  specialisation of cpp_int_backend. Pass by pointer instead
    //  of value, for more generic usage (passing by value will
    //  only work if cpp_int_backend has move constructor defined,
    //  whereas pass-by-pointer will work regardless). References
    //  are also acceptable, however, using pointers will result in
    //  compile error if value is passed, whereas references may give
    //  unexpected behaviour. For these reasons, prefer pointers. 
    template <uint A,
        uint B,
        boost::multiprecision::cpp_integer_type CIT,
        boost::multiprecision::cpp_int_check_type C,
        typename TT>
    constexpr static std::true_type test(boost::multiprecision::cpp_int_backend<A, B, CIT, C, TT>*);

    //this overload has the lowest precedence during overload
    //  resolution, but will accept any argument.  
    constexpr static std::false_type test(...);

    //type will be std::true_type or std::false_type depending
    //  on which overload is selected. If T is a specialisation
    //  of cpp_int_backend, it will be true_type, else false_type
    using type = decltype(test(std::declval<T*>())); 
    constexpr static bool value = type::value;
};

template <typename T>
struct is_multiprecision_int
{
    //enable this template, if T is a specialisation of 'number'
    //  in boost::multiprecision, and the nested template parameter
    //  is a cpp_int_backend. Use pointers for similar reason as 
    //  above
    template <typename TT, typename std::enable_if<is_cpp_int_backend<TT>::value, bool>::type = true>
    constexpr static std::true_type test(boost::multiprecision::number<TT>*);

    //again, lowest order of precedence, but will trigger for
    //  anything the above function template does not trigger for
    constexpr static std::false_type test(...);

    //get type depending on T
    using type = decltype(test(std::declval<T*>()));
    constexpr static bool value = type::value; 
};
