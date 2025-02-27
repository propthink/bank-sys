#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint> // for fixed-width integer types
#include <unordered_set> // for std::unordered_set

// banking logic and financial operations
namespace BankUtils {

	// the system uses US cents to avoid rounding issues associated with floating point numbers
	typedef int64_t US_CENTS; // e.g. $10.73 = 1073
}

// unique identifiers for users and accounts
namespace IdUtils {

	// a unique 6-digit identifier associated with a specific user
	typedef uint32_t USER_ID;

	// a unique 9-digit identifier associated with a specific account
	typedef uint32_t ACCOUNT_ID;

	// tracks existing user IDs to enforce uniqueness
	extern std::unordered_set< USER_ID > GENERATED_USER_IDS;

	// tracks existing account IDs to enforce uniqueness
	extern std::unordered_set< ACCOUNT_ID > GENERATED_ACCOUNT_IDS;

	// generates a random, unique user ID
	USER_ID GENERATE_USER_ID();

	// generates a random, unique account ID
	ACCOUNT_ID GENERATE_ACCOUNT_ID();
}

#endif // UTILITIES_H