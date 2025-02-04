/*
 * File:   Types.hpp
 * Author: Miles Lacey
 *
 * This file mimics limited functionality of the standard C++ header
 * <type_traits>.
 */

#ifndef LS_SETUP_TYPES_H
#define LS_SETUP_TYPES_H

namespace ls
{
namespace setup
{



/*-----------------------------------------------------------------------------
 * Helper types to reduce implementation boilerplace
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * EnableIf True Helper
-------------------------------------*/
template <typename data_t>
struct TrueType
{
    typedef data_t value_type;

    static constexpr bool value = true;

    constexpr explicit operator bool() const noexcept
    {
        return true;
    }

    constexpr bool operator() () const noexcept
    {
        return true;
    }
};



/*-------------------------------------
 * EnableIf False Helper
-------------------------------------*/
template <typename data_t>
struct FalseType
{
    typedef data_t value_type;

    static constexpr bool value = false;

    constexpr explicit operator bool() const noexcept
    {
        return false;
    }

    constexpr bool operator() () const noexcept
    {
        return false;
    }
};



/*-----------------------------------------------------------------------------
 * Implementation of std::enable_if
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Base Case
-------------------------------------*/
template<bool val, class T = void>
struct EnableIf
{
};



/*-------------------------------------
 * True Case
-------------------------------------*/
template<class T>
struct EnableIf<true, T>
{
    typedef T type;
};



/*-----------------------------------------------------------------------------
 * Implementation of RemoveReference
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Base Case
-------------------------------------*/
template<typename T>
struct RemoveReference
{
    typedef T type;
};



/*-------------------------------------
 * Reference Case
-------------------------------------*/
template<typename T>
struct RemoveReference<T&>
{
    typedef T type;
};



/*-------------------------------------
 * R-Value Reference
-------------------------------------*/
template<typename T>
struct RemoveReference<T&&>
{
    typedef T type;
};



/*-----------------------------------------------------------------------------
 * Implementation of std::forward
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Reference Forwarding
-------------------------------------*/
template<typename T>
constexpr T&& forward(typename RemoveReference<T>::type& val) noexcept
{
    return static_cast<T&&>(val);
}



/*-------------------------------------
 * R-Value Reference Forwarding
-------------------------------------*/
template<typename T>
constexpr T&& forward(typename RemoveReference<T>::type&& val) noexcept
{
    return static_cast<T&&>(val);
}



/*-------------------------------------
 * Reference Moving
-------------------------------------*/
template<typename T>
constexpr typename RemoveReference<T>::type&& move(T&& val) noexcept
{
    return static_cast<typename RemoveReference<T>::type&&>(val);
}



/*-----------------------------------------------------------------------------
 * Replacement for std::is_same
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * General Case
-------------------------------------*/
template <typename T, typename U>
struct IsSame : public setup::FalseType<bool>
{
};



/*-------------------------------------
 * Same Case
-------------------------------------*/
template <typename T>
struct IsSame<T, T> : public setup::TrueType<bool>
{
};



/*-----------------------------------------------------------------------------
 * Replacement for std::is_base_of
-----------------------------------------------------------------------------*/
template <class B, class D>
struct IsBaseOf
{
  private:
    static constexpr bool _base_value(const B* const) noexcept
    {
        return true;
    }

    static constexpr bool _base_value(const void* const) noexcept
    {
        return false;
    }

  public:


    static constexpr bool value = _base_value(static_cast<const D*>(nullptr));

    constexpr explicit operator bool() const noexcept
    {
        return value;
    }

    constexpr bool operator() () const noexcept
    {
        return value;
    }
};



/*-----------------------------------------------------------------------------
 * Replacement for std::is_pointer
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * General Case
-------------------------------------*/
template <typename data_t>
struct IsPointer : public setup::FalseType<data_t>
{
};



/*-------------------------------------
 * Regular Pointer
-------------------------------------*/
template <typename data_t>
struct IsPointer<data_t*> : public setup::TrueType<data_t*>
{
};



/*-------------------------------------
 * Const Pointer
-------------------------------------*/
template <typename data_t>
struct IsPointer<data_t* const> : public setup::TrueType<data_t* const>
{
};



/*-------------------------------------
 * Volatile Pointer
-------------------------------------*/
template <typename data_t>
struct IsPointer<data_t* volatile> : public setup::TrueType<data_t* volatile>
{
};



/*-------------------------------------
 * Const Volatile Pointer
-------------------------------------*/
template <typename data_t>
struct IsPointer<data_t* const volatile> : public setup::TrueType<data_t* const volatile>
{
};



/*-----------------------------------------------------------------------------
 * Replacement for std::is_integral
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * General Case
-------------------------------------*/
template <typename data_t>
struct IsIntegral : public setup::TrueType<data_t>
{
};



/*-------------------------------------
 * Float Specialization
-------------------------------------*/
template <>
struct IsIntegral<float> : public setup::FalseType<float>
{
};



/*-------------------------------------
 * Double Specialization
-------------------------------------*/
template <>
struct IsIntegral<double> : public setup::FalseType<double>
{
};



/*-------------------------------------
 * Long Double Specialization
-------------------------------------*/
template <>
struct IsIntegral<long double> : public setup::FalseType<long double>
{
};



/*-----------------------------------------------------------------------------
 * Replacement for std::is_floating_point
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * General Case
-------------------------------------*/
template <typename data_t>
struct IsFloat : public setup::FalseType<data_t>
{
};



/*-------------------------------------
 * Float Specialization
-------------------------------------*/
template <>
struct IsFloat<float> : public setup::TrueType<float>
{
};



/*-------------------------------------
 * Double Specialization
-------------------------------------*/
template <>
struct IsFloat<double> : public setup::TrueType<double>
{
};



/*-------------------------------------
 * Long Double Specialization
-------------------------------------*/
template <>
struct IsFloat<long double> : public setup::TrueType<long double>
{
};



/*-----------------------------------------------------------------------------
 * Replacement for std::is_signed
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * General Implementation
-------------------------------------*/
template <typename data_t>
struct IsSigned : public setup::TrueType<data_t>
{
};



/*-------------------------------------
 * Unsigned Specializations
-------------------------------------*/
template <>
struct IsSigned<unsigned char> : public setup::FalseType<unsigned char>
{
};



template <>
struct IsSigned<unsigned short> : public setup::FalseType<unsigned short>
{
};



template <>
struct IsSigned<unsigned int> : public setup::FalseType<unsigned int>
{
};



template <>
struct IsSigned<unsigned long> : public setup::FalseType<unsigned long>
{
};



template <>
struct IsSigned<unsigned long long> : public setup::FalseType<unsigned long long>
{
};



/*-----------------------------------------------------------------------------
 * Replacement for std::is_unsigned
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * General Implementation
-------------------------------------*/
template <typename data_t>
struct IsUnsigned : public TrueType<data_t>
{
};



template <>
struct IsUnsigned<char> : public setup::FalseType<char>
{
};



template <>
struct IsUnsigned<signed char> : public setup::FalseType<signed char>
{
};



template <>
struct IsUnsigned<signed short> : public setup::FalseType<signed short>
{
};



template <>
struct IsUnsigned<signed int> : public setup::FalseType<signed int>
{
};



template <>
struct IsUnsigned<signed long> : public setup::FalseType<signed long>
{
};



template <>
struct IsUnsigned<signed long long> : public setup::FalseType<signed long long>
{
};



template <>
struct IsUnsigned<float> : public setup::FalseType<float>
{
};



template <>
struct IsUnsigned<double> : public setup::FalseType<double>
{
};



template <>
struct IsUnsigned<long double> : public setup::FalseType<long double>
{
};



} // end setup namespace
} // end ls namespace

#endif /* LS_SETUP_TYPES_H */
