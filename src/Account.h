#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Utilities.h" // for utils
#include <cstdint> // for fixed-width integer types
#include <unordered_set> // for std::unordered_set

// a unique 9-digit identifier associated with a specific account
typedef uint32_t ACCOUNT_ID;

// generates a random, unique account ID
ACCOUNT_ID GENERATE_ACCOUNT_ID();

// tracks existing account IDs to enforce uniqueness
extern std::unordered_set< ACCOUNT_ID > GENERATED_ACCOUNT_IDS;

// defines the interface for account-related operations
class IAccount
{
public:

	virtual ~IAccount(); // deallocate interface

	// get the unique id associated with this account
	virtual ACCOUNT_ID getAccountId() const = 0;

	// get the current balance of this account
	virtual Utils::US_CENTS getAccountBalance() const = 0;
};

// base account class implementing IAccount interface
class BAccount : public IAccount
{
public:

	// initialize the base account
	BAccount( ACCOUNT_ID account_id, Utils::US_CENTS account_balance = 0 );

	// get the unique id associated with this account
	virtual ACCOUNT_ID getAccountId() const override;

	// get the current balance of this account
	virtual Utils::US_CENTS getAccountBalance() const override;

private:

	ACCOUNT_ID m_account_id; // unique account id

	Utils::US_CENTS m_current_balance; // account balance
};

#endif // ACCOUNT_H