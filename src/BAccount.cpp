#include "BAccount.h" // implementing BAccount
#include <random> // for random number generation

// generates a random, unique account ID
bank_sys::ACCOUNT_ID BAccount::GENERATE_ACCOUNT_ID()
{
	// get a random seed from the system
	static std::random_device random_device;

	// initialize a random number generator with the seed
	static std::mt19937 random_generator( random_device() );

	// define the range for generating 9-digit IDs
	std::uniform_int_distribution<> rng_distribution( 100000000, 999999999 );

	// store the generated account ID for comparison
	bank_sys::ACCOUNT_ID new_account_id;

	do
	{
		// keep generating a new account ID until it is unique
		new_account_id = rng_distribution( random_generator );

		// check if the account ID already exists
	} while( GENERATED_ACCOUNT_IDS.find( new_account_id ) != GENERATED_ACCOUNT_IDS.end() );

	// insert the new unique account ID into the set
	GENERATED_ACCOUNT_IDS.insert( new_account_id );

	// return the newly generated unique account ID
	return new_account_id;
}

// tracks existing account IDs to enforce uniqueness
std::unordered_set< bank_sys::ACCOUNT_ID > BAccount::GENERATED_ACCOUNT_IDS;

// initialize account
BAccount::BAccount()

	: m_account_id( BAccount::GENERATE_ACCOUNT_ID() ), m_current_balance( 0 ) { }

// get the unique id associated with this account
bank_sys::ACCOUNT_ID BAccount::getAccountId() const
{
	return m_account_id;
}