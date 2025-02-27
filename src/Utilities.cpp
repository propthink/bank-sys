#include "Utilities.h"
#include <random> // for random number generation

// tracks existing user IDs to enforce uniqueness
std::unordered_set< IdUtils::USER_ID > IdUtils::GENERATED_USER_IDS;

// tracks existing account IDs to enforce uniqueness
std::unordered_set< IdUtils::ACCOUNT_ID > IdUtils::GENERATED_ACCOUNT_IDS;

// generates a random, unique user ID
IdUtils::USER_ID IdUtils::GENERATE_USER_ID()
{
	// get a random seed from the system
	std::random_device random_device;

	// initialize a random number generator with the seed
	std::mt19937 random_generator( random_device() );

	// define the range for generating 6-digit IDs
	std::uniform_int_distribution<> rng_distribution( 100000, 999999 );

	// store the generated user ID for comparison
	IdUtils::USER_ID new_user_id;

	// keep generating a new user ID until it is unique
	do {
		new_user_id = rng_distribution( random_generator );

		// check if the user ID already exists
	} while( IdUtils::GENERATED_USER_IDS.find( new_user_id ) != GENERATED_USER_IDS.end() );

	// insert the new unique user ID into the set
	IdUtils::GENERATED_USER_IDS.insert( new_user_id );

	// return the newly generated unique user ID
	return new_user_id;
}

// generates a random, unique account ID
IdUtils::ACCOUNT_ID IdUtils::GENERATE_ACCOUNT_ID()
{
	// get a random seed from the system
	std::random_device random_device;

	// initialize a random number generator with the seed
	std::mt19937 random_generator( random_device() );

	// define the range for generating 9-digit IDs
	std::uniform_int_distribution<> rng_distribution( 100000000, 999999999 );

	// store the generated account ID for comparison
	IdUtils::ACCOUNT_ID new_account_id;

	// keep generating a new account ID until it is unique
	do {
		new_account_id = rng_distribution( random_generator );

		// check if the account ID already exists
	} while( IdUtils::GENERATED_ACCOUNT_IDS.find( new_account_id ) != GENERATED_ACCOUNT_IDS.end() );

	// insert the new unique account ID into the set
	IdUtils::GENERATED_ACCOUNT_IDS.insert( new_account_id );

	// return the newly generated unique account ID
	return new_account_id;
}