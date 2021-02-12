
#include <iostream>
#include <type_traits>

#include "lightsky/setup/Types.h"

struct A {};
struct B : A {};
struct C {};



void print_is_integral_results() noexcept
{
    std::cout
        << "std::is_integral<char>::value:                " << std::is_integral<char>::value << '\n'
        << "setup::IsIntegral<char>::value:               " << ls::setup::IsIntegral<char>::value << '\n'
        << "std::is_integral<unsigned char>::value:       " << std::is_integral<unsigned char>::value << '\n'
        << "setup::IsIntegral<unsigned char>::value:      " << ls::setup::IsIntegral<unsigned char>::value << '\n'
        << "std::is_integral<short>::value:               " << std::is_integral<short>::value << '\n'
        << "setup::IsIntegral<short>::value:              " << ls::setup::IsIntegral<short>::value << '\n'
        << "std::is_integral<unsigned short>::value:      " << std::is_integral<unsigned short>::value << '\n'
        << "setup::IsIntegral<unsigned short>::value:     " << ls::setup::IsIntegral<unsigned short>::value << '\n'
        << "std::is_integral<int>::value:                 " << std::is_integral<int>::value << '\n'
        << "setup::IsIntegral<int>::value:                " << ls::setup::IsIntegral<int>::value << '\n'
        << "std::is_integral<unsigned int>::value:        " << std::is_integral<unsigned int>::value << '\n'
        << "setup::IsIntegral<unsigned int>::value:       " << ls::setup::IsIntegral<unsigned int>::value << '\n'
        << "std::is_integral<long>::value:                " << std::is_integral<long>::value << '\n'
        << "setup::IsIntegral<long>::value:               " << ls::setup::IsIntegral<long>::value << '\n'
        << "std::is_integral<unsigned long>::value:       " << std::is_integral<unsigned long>::value << '\n'
        << "setup::IsIntegral<unsigned long>::value:      " << ls::setup::IsIntegral<unsigned long>::value << '\n'
        << "std::is_integral<long long>::value:           " << std::is_integral<long long>::value << '\n'
        << "setup::IsIntegral<long long>::value:          " << ls::setup::IsIntegral<long long>::value << '\n'
        << "std::is_integral<unsigned long long>::value:  " << std::is_integral<unsigned long long>::value << '\n'
        << "setup::IsIntegral<unsigned long long>::value: " << ls::setup::IsIntegral<unsigned long long>::value << '\n'

        << "std::is_integral<float>::value:               " << std::is_integral<float>::value << '\n'
        << "setup::IsIntegral<float>::value:              " << ls::setup::IsIntegral<float>::value << '\n'
        << "std::is_integral<double>::value:              " << std::is_integral<double>::value << '\n'
        << "setup::IsIntegral<double>::value:             " << ls::setup::IsIntegral<double>::value << '\n'
        << "std::is_integral<long double>::value:         " << std::is_integral<long double>::value << '\n'
        << "setup::IsIntegral<long double>::value:        " << ls::setup::IsIntegral<long double>::value << '\n'
        << std::endl;
}



void print_is_float_results() noexcept
{
    std::cout
        << "std::is_floating_point<char>::value:               " << std::is_floating_point<char>::value << '\n'
        << "setup::IsFloat<char>::value:                       " << ls::setup::IsFloat<char>::value << '\n'
        << "std::is_floating_point<unsigned char>::value:      " << std::is_floating_point<unsigned char>::value << '\n'
        << "setup::IsFloat<unsigned char>::value:              " << ls::setup::IsFloat<unsigned char>::value << '\n'
        << "std::is_floating_point<short>::value:              " << std::is_floating_point<short>::value << '\n'
        << "setup::IsFloat<short>::value:                      " << ls::setup::IsFloat<short>::value << '\n'
        << "std::is_floating_point<unsigned short>::value:     " << std::is_floating_point<unsigned short>::value << '\n'
        << "setup::IsFloat<unsigned short>::value:             " << ls::setup::IsFloat<unsigned short>::value << '\n'
        << "std::is_floating_point<int>::value:                " << std::is_floating_point<int>::value << '\n'
        << "setup::IsFloat<int>::value:                        " << ls::setup::IsFloat<int>::value << '\n'
        << "std::is_floating_point<unsigned int>::value:       " << std::is_floating_point<unsigned int>::value << '\n'
        << "setup::IsFloat<unsigned int>::value:               " << ls::setup::IsFloat<unsigned int>::value << '\n'
        << "std::is_floating_point<long>::value:               " << std::is_floating_point<long>::value << '\n'
        << "setup::IsFloat<long>::value:                       " << ls::setup::IsFloat<long>::value << '\n'
        << "std::is_floating_point<unsigned long>::value:      " << std::is_floating_point<unsigned long>::value << '\n'
        << "setup::IsFloat<unsigned long>::value:              " << ls::setup::IsFloat<unsigned long>::value << '\n'
        << "std::is_floating_point<long long>::value:          " << std::is_floating_point<long long>::value << '\n'
        << "setup::IsFloat<long long>::value:                  " << ls::setup::IsFloat<long long>::value << '\n'
        << "std::is_floating_point<unsigned long long>::value: " << std::is_floating_point<unsigned long long>::value << '\n'
        << "setup::IsFloat<unsigned long long>::value:         " << ls::setup::IsFloat<unsigned long long>::value << '\n'

        << "std::is_floating_point<float>::value:              " << std::is_floating_point<float>::value << '\n'
        << "setup::IsFloat<float>::value:                      " << ls::setup::IsFloat<float>::value << '\n'
        << "std::is_floating_point<double>::value:             " << std::is_floating_point<double>::value << '\n'
        << "setup::IsFloat<double>::value:                     " << ls::setup::IsFloat<double>::value << '\n'
        << "std::is_floating_point<long double>::value:        " << std::is_floating_point<long double>::value << '\n'
        << "setup::IsFloat<long double>::value:                " << ls::setup::IsFloat<long double>::value << '\n'
        << std::endl;
}



void print_is_signed_results() noexcept
{
    std::cout
        << "std::is_signed<char>::value:                " << std::is_signed<char>::value << '\n'
        << "setup::IsSigned<char>::value:               " << ls::setup::IsSigned<char>::value << '\n'
        << "std::is_signed<unsigned char>::value:       " << std::is_signed<unsigned char>::value << '\n'
        << "setup::IsSigned<unsigned char>::value:      " << ls::setup::IsSigned<unsigned char>::value << '\n'
        << "std::is_signed<short>::value:               " << std::is_signed<short>::value << '\n'
        << "setup::IsSigned<short>::value:              " << ls::setup::IsSigned<short>::value << '\n'
        << "std::is_signed<unsigned short>::value:      " << std::is_signed<unsigned short>::value << '\n'
        << "setup::IsSigned<unsigned short>::value:     " << ls::setup::IsSigned<unsigned short>::value << '\n'
        << "std::is_signed<int>::value:                 " << std::is_signed<int>::value << '\n'
        << "setup::IsSigned<int>::value:                " << ls::setup::IsSigned<int>::value << '\n'
        << "std::is_signed<unsigned int>::value:        " << std::is_signed<unsigned int>::value << '\n'
        << "setup::IsSigned<unsigned int>::value:       " << ls::setup::IsSigned<unsigned int>::value << '\n'
        << "std::is_signed<long>::value:                " << std::is_signed<long>::value << '\n'
        << "setup::IsSigned<long>::value:               " << ls::setup::IsSigned<long>::value << '\n'
        << "std::is_signed<unsigned long>::value:       " << std::is_signed<unsigned long>::value << '\n'
        << "setup::IsSigned<unsigned long>::value:      " << ls::setup::IsSigned<unsigned long>::value << '\n'
        << "std::is_signed<long long>::value:           " << std::is_signed<long long>::value << '\n'
        << "setup::IsSigned<long long>::value:          " << ls::setup::IsSigned<long long>::value << '\n'
        << "std::is_signed<unsigned long long>::value:  " << std::is_signed<unsigned long long>::value << '\n'
        << "setup::IsSigned<unsigned long long>::value: " << ls::setup::IsSigned<unsigned long long>::value << '\n'

        << "std::is_signed<float>::value:               " << std::is_signed<float>::value << '\n'
        << "setup::IsSigned<float>::value:              " << ls::setup::IsSigned<float>::value << '\n'
        << "std::is_signed<double>::value:              " << std::is_signed<double>::value << '\n'
        << "setup::IsSigned<double>::value:             " << ls::setup::IsSigned<double>::value << '\n'
        << "std::is_signed<long double>::value:         " << std::is_signed<long double>::value << '\n'
        << "setup::IsSigned<long double>::value:        " << ls::setup::IsSigned<long double>::value << '\n'
        << std::endl;
}



void print_is_unsigned_results() noexcept
{
    std::cout
        << "std::is_unsigned<char>::value:                " << std::is_unsigned<char>::value << '\n'
        << "setup::IsUnsigned<char>::value:               " << ls::setup::IsUnsigned<char>::value << '\n'
        << "std::is_unsigned<unsigned char>::value:       " << std::is_unsigned<unsigned char>::value << '\n'
        << "setup::IsUnsigned<unsigned char>::value:      " << ls::setup::IsUnsigned<unsigned char>::value << '\n'
        << "std::is_unsigned<short>::value:               " << std::is_unsigned<short>::value << '\n'
        << "setup::IsUnsigned<short>::value:              " << ls::setup::IsUnsigned<short>::value << '\n'
        << "std::is_unsigned<unsigned short>::value:      " << std::is_unsigned<unsigned short>::value << '\n'
        << "setup::IsUnsigned<unsigned short>::value:     " << ls::setup::IsUnsigned<unsigned short>::value << '\n'
        << "std::is_unsigned<int>::value:                 " << std::is_unsigned<int>::value << '\n'
        << "setup::IsUnsigned<int>::value:                " << ls::setup::IsUnsigned<int>::value << '\n'
        << "std::is_unsigned<unsigned int>::value:        " << std::is_unsigned<unsigned int>::value << '\n'
        << "setup::IsUnsigned<unsigned int>::value:       " << ls::setup::IsUnsigned<unsigned int>::value << '\n'
        << "std::is_unsigned<long>::value:                " << std::is_unsigned<long>::value << '\n'
        << "setup::IsUnsigned<long>::value:               " << ls::setup::IsUnsigned<long>::value << '\n'
        << "std::is_unsigned<unsigned long>::value:       " << std::is_unsigned<unsigned long>::value << '\n'
        << "setup::IsUnsigned<unsigned long>::value:      " << ls::setup::IsUnsigned<unsigned long>::value << '\n'
        << "std::is_unsigned<long long>::value:           " << std::is_unsigned<long long>::value << '\n'
        << "setup::IsUnsigned<long long>::value:          " << ls::setup::IsUnsigned<long long>::value << '\n'
        << "std::is_unsigned<unsigned long long>::value:  " << std::is_unsigned<unsigned long long>::value << '\n'
        << "setup::IsUnsigned<unsigned long long>::value: " << ls::setup::IsUnsigned<unsigned long long>::value << '\n'

        << "std::is_unsigned<float>::value:               " << std::is_unsigned<float>::value << '\n'
        << "setup::IsUnsigned<float>::value:              " << ls::setup::IsUnsigned<float>::value << '\n'
        << "std::is_unsigned<double>::value:              " << std::is_unsigned<double>::value << '\n'
        << "setup::IsUnsigned<double>::value:             " << ls::setup::IsUnsigned<double>::value << '\n'
        << "std::is_unsigned<long double>::value:         " << std::is_unsigned<long double>::value << '\n'
        << "setup::IsUnsigned<long double>::value:        " << ls::setup::IsUnsigned<long double>::value << '\n'
        << std::endl;
}


void print_is_same_results() noexcept
{
    std::cout
        << "std::is_same<A, A>::value:  " << std::is_same<A, A>::value << '\n'
        << "setup::IsSame<A, A>::value: " << ls::setup::IsSame<A, A>::value << '\n'
        << "std::is_same<A, B>::value:  " << std::is_same<A, B>::value << '\n'
        << "setup::IsSame<A, B>::value: " << ls::setup::IsSame<A, B>::value << '\n'
        << "std::is_same<A, C>::value:  " << std::is_same<A, C>::value << '\n'
        << "setup::IsSame<A, C>::value: " << ls::setup::IsSame<A, C>::value << '\n'
        << std::endl;
}



void print_is_base_of_results() noexcept
{
    std::cout
        << "std::is_base_of<A, A>::value: " << std::is_base_of<A, A>::value << '\n'
        << "setup::IsBaseOf<A, A>::value: " << ls::setup::IsBaseOf<A, A>::value << '\n'
        << "std::is_base_of<A, B>::value: " << std::is_base_of<A, B>::value << '\n'
        << "setup::IsBaseOf<A, B>::value: " << ls::setup::IsBaseOf<A, B>::value << '\n'
        << "std::is_base_of<A, C>::value: " << std::is_base_of<A, C>::value << '\n'
        << "setup::IsBaseOf<A, C>::value: " << ls::setup::IsBaseOf<A, C>::value << '\n'
        << std::endl;
}



int main()
{
    print_is_integral_results();
    print_is_float_results();
    print_is_signed_results();
    print_is_unsigned_results();

    print_is_same_results();
    print_is_base_of_results();

    return 0;
}
