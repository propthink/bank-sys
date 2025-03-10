#ifndef BACCOUNT_H
#define BACCOUNT_H

#include "IAccount.h" // account interface
#include <unordered_set> // std::unordered_set

// an abstract base class for shared implementation between derived account types
class BAccount : public IAccount
{
public:

	// generates a random, unique account ID
	static bank_sys::ACCOUNT_ID GENERATE_ACCOUNT_ID();

	// tracks existing account IDs to enforce uniqueness
	static std::unordered_set< bank_sys::ACCOUNT_ID > GENERATED_ACCOUNT_IDS;

	// initialize account
	BAccount();

	// deallocate account
	~BAccount() override = default;

	// get the unique id associated with this account
	bank_sys::ACCOUNT_ID getAccountId() const override;

private:

	// the unique 9-digit identifier associated with this account
	bank_sys::ACCOUNT_ID m_account_id;

	// the current balance of this account
	bank_sys::US_CENTS m_current_balance;
};

#endif // BACCOUNT_H