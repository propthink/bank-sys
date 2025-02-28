#ifndef UTILITY_H
#define UTILITY_H

#include <cstdint> // for fixed-width integer types

// utility namespace
namespace Utils {

	// the system uses US cents to avoid rounding issues associated with floating point numbers
	typedef int64_t US_CENTS; // e.g. $10.73 = 1073

	// a unique 6-digit identifier associated with a specific user
	typedef uint32_t USER_ID;

	// a unique 9-digit identifier associated with a specific account
	typedef uint32_t ACCOUNT_ID;
}

#endif // UTILITY_H