#ifndef COMMON_H
#define COMMON_H

#include <cstdint> // int64_t, uint32_t

// common types and definitions used across the banking system
namespace bank_sys
{
	// the system uses US cents to avoid rounding issues associated with floating point numbers
	typedef int64_t US_CENTS; // e.g. $10.73 = 1073 cents

	// a unique 6-digit identifier associated with a specific user
	typedef uint32_t USER_ID;

	// a unique 9-digit identifier associated with a specific account
	typedef uint32_t ACCOUNT_ID;
}
#endif // COMMON_H