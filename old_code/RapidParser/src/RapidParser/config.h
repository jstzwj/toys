#pragma once
#ifndef RAPIDPARSER_CONFIG
#define RAPIDPARSER_CONFIG
#include<string>
#include<cctype>
#include<locale>
#include<codecvt>

//判断系统
#ifdef __CYGWIN__
#define RPR_OS_CYGWIN 1
#elif defined __SYMBIAN32__
# define RPR_OS_SYMBIAN 1
#elif defined _WIN32
# define RPR_OS_WINDOWS 1

#ifdef _WIN32_WCE
#define RPR_OS_WINDOWS_MOBILE 1
#elif defined(__MINGW__) || defined(__MINGW32__)
#define RPR_OS_WINDOWS_MINGW 1
#else
#define RPR_OS_WINDOWS_DESKTOP 1
#endif  // _WIN32_WCE

#elif defined __APPLE__
#define RPR_OS_MAC 1

#if TARGET_OS_IPHONE
#define RPR_OS_IOS 1
#if TARGET_IPHONE_SIMULATOR
#define RPR_OS_IOS_SIMULATOR 1
#endif

#endif

#elif defined __linux__
#define RPR_OS_LINUX 1
#if defined __ANDROID__
#define RPR_OS_LINUX_ANDROID 1
#endif
#elif defined __MVS__
#define RPR_OS_ZOS 1
#elif defined(__sun) && defined(__SVR4)
#define RPR_OS_SOLARIS 1
#elif defined(_AIX)
#define RPR_OS_AIX 1
#elif defined(__hpux)
#define RPR_OS_HPUX 1
#elif defined __native_client__
#define RPR_OS_NACL 1
#elif defined __OpenBSD__
#define RPR_OS_OPENBSD 1
#elif defined __QNX__
#define RPR_OS_QNX 1
#endif  // __CYGWIN__

//判断环境是否完全支持c++11
#ifndef RPR_LANG_CXX11
# if __GXX_EXPERIMENTAL_CXX0X__ || __cplusplus >= 201103L
// Compiling in at least C++11 mode.
#  define RPR_LANG_CXX11 1
# else
#  define RPR_LANG_CXX11 0
# endif
#endif

//判断系统是32位还是64位
#ifdef RPR_OS_WINDOWS
#	ifdef _WIN64
#	define RPR_OS_64
#	elif defined _WIN32
#	define RPR_OS_32
#	endif
#endif // RPR_OS_WINDOWS

namespace rpr
{
	//定义整数
	typedef int8_t rpr_int8_t;
	typedef int16_t rpr_int16_t;
	typedef int32_t rpr_int32_t;
	typedef int64_t rpr_int64_t;
#ifdef RPR_OS_32
	typedef int32_t rpr_int;
#endif // RPR_OS_32
#ifdef RPR_OS_64
	typedef int64_t rpr_int;
#endif // RPR_OS_64

	//定义字符集
#define RPR_ASCII
#ifdef RPR_UTF_8
	typedef char rpr_char;
	typedef std::string rpr_string;
#define T(x) u8##x

#elif defined RPR_UTF_16
	typedef  char16_t rpr_char;
	typedef std::u16string rpr_string;
#define T(x) u##x

#elif defined RPR_UCS4
	typedef  char32_t rpr_char;
	typedef std::u32string rpr_string;
#define T(x) U##x

#elif defined RPR_ASCII
	typedef char rpr_char;
	typedef std::string rpr_string;
#define T(x) x

#endif // RPR_UTF_8
}

#endif // !RAPIDPARSER_CONFIG
