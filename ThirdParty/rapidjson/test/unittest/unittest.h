#ifndef UNITTEST_H_
#define UNITTEST_H_


// gtest indirectly included inttypes.h, without __STDC_CONSTANT_MACROS.
#ifndef __STDC_CONSTANT_MACROS
#  define __STDC_CONSTANT_MACROS 1 // required by C++ standard
#endif

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#pragma warning(disable : 4996) // 'function': was declared deprecated
#endif

#if defined(__clang__) || defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2))
#if defined(__clang__) || (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Weffc++"
#endif

#include "gtest/gtest.h"

#if defined(__clang__) || defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6))
#pragma GCC diagnostic pop
#endif

template <typename Ch>
inline unsigned StrLen(const Ch* s) {
	const Ch* p = s;
	while (*p) p++;
	return unsigned(p - s);
}

template<typename Ch>
inline int StrCmp(const Ch* s1, const Ch* s2) {
	while(*s1 && (*s1 == *s2)) { s1++; s2++; }
	return (unsigned)*s1 < (unsigned)*s2 ? -1 : (unsigned)*s1 > (unsigned)*s2;
}

template <typename Ch>
inline Ch* StrDup(const Ch* str) {
	size_t bufferSize = sizeof(Ch) * (StrLen(str) + 1);
	Ch* buffer = (Ch*)malloc(bufferSize);
	memcpy(buffer, str, bufferSize);
	return buffer;
}

inline void TempFilename(char *filename) {
	filename = tmpnam(filename);

	// For Visual Studio, tmpnam() adds a backslash in front. Remove it.
	if (filename[0] == '\\')
		for (int i = 0; filename[i] != '\0'; i++)
			filename[i] = filename[i + 1];
}

// Use exception for catching assert
#if _MSC_VER
#pragma warning(disable : 4127)
#endif

class AssertException : public std::exception {
public:
	AssertException(const char* w) : what_(w) {}
	AssertException(const AssertException& other) : what_(other.what_) {}
	AssertException& operator=(const AssertException& rhs) { what_ = rhs.what_; return *this;  }
	virtual const char* what() const throw() { return what_; }

private:
	const char* what_;
};

#define RAPIDJSON_ASSERT(x) if (!(x)) throw AssertException(RAPIDJSON_STRINGIFY(x))

#endif // UNITTEST_H_
