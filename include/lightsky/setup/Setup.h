/*
 * File:   setup/setup.h
 * Author: Miles Lacey
 *
 * This file contains all preprocessor macros and definitions that will help in
 * in building LightSky and its modules.
 */

#ifndef LS_SETUP_SETUP_H
#define LS_SETUP_SETUP_H

#include <climits>

#include "lightsky/setup/Compiler.h"
#include "lightsky/setup/Arch.h"
#include "lightsky/setup/OS.h"
#include "lightsky/setup/Macros.h"
#include "lightsky/setup/Api.h"



namespace ls
{
namespace platform
{



enum class platform_t
{
    DESKTOP,
    MOBILE
};

/**
 * @brief Get the number of bits per byte on the current platform.
 *
 * @return The number of bits (typically 8) that are natively stored in a
 * single byte on the current platform.
 */
constexpr unsigned get_bit_length()
{
    return CHAR_BIT;
}

/**
 * @brief Retrieve the current platform's byte length.
 *
 * @return An unsigned integer containing the number of bits per byte. This
 * number is typically 8.
 */
constexpr unsigned get_byte_length()
{
    return sizeof(char);
}

/**
 * @brief Retrieve the current platform's pointer size.
 *
 * @return An unsigned integer containing the number of bits that are required
 * to store a pointer. This is typically 32 or 64 bits.
 */
constexpr unsigned get_num_platform_bits()
{
    return sizeof(void*) * get_bit_length();
}

/**
 * @brief Determine if the current platform is 32-bit.
 *
 * @return TRUE if the current platform is 32-bit, FALSE if otherwise.
 */
constexpr bool is_32_bit()
{
    return 32 == get_num_platform_bits();
}

/**
 * @brief Determine if the current platform is 64-bit.
 *
 * @return TRUE if the current platform is 64-bit, FALSE if otherwise.
 */
constexpr bool is_64_bit()
{
    return 64 == get_num_platform_bits();
}



/**
 * @brief Helper function to determine if the current platform is Mobile or
 * Desktop.
 *
 * @return ls::platform::platform_t::DESKTOP if the current build is targeting
 * a desktop platform, MOBILE if otherwise.
 */
platform_t get_target_platform();
} // end platform namespace
} // end ls namespace



/*
 * LS_PLATFORM
 *
 * Defines what platform the current app system is on (mobile or desktop)
 */
#ifndef LS_PLATFORM_DESKTOP
#define LS_PLATFORM_DESKTOP ls::platform::platform_t::DESKTOP
#endif

#ifndef LS_PLATFORM_MOBILE
#define LS_PLATFORM_MOBILE ls::platform::platform_t::MOBILE
#endif

#if defined (LS_OS_WINDOWS) || defined (LS_OS_UNIX) || defined (LS_OS_OSX)
#define LS_PLATFORM LS_PLATFORM_DESKTOP

#elif defined (LS_OS_ANDROID) || defined (LS_OS_IOS)
#define LS_PLATFORM LS_PLATFORM_MOBILE
#endif /* LS_PLATFORM */



#endif /* LS_SETUP_SETUP_H */
