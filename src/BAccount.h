#ifndef BACCOUNT_H
#define BACCOUNT_H

#include "IAccount.h" // account interface
#include "TransactionRegistry.h" // TransactionRegistry
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

	// deposit money into the account
	bool deposit( bank_sys::US_CENTS deposit_amount ) override;

	// withdraw money from the account
	bool withdraw( bank_sys::US_CENTS withdrawal_amount ) override;

	// TEST_PRINT
	void TEST_PRINT() const override;

private:

	// the unique 9-digit identifier associated with this account
	bank_sys::ACCOUNT_ID m_account_id;

	// the current balance of this account
	bank_sys::US_CENTS m_current_balance;

	// the transaction history associated with this account
	TransactionRegistry m_transaction_registry;
};

#endif // BACCOUNT_H