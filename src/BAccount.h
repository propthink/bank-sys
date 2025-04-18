#ifndef BACCOUNT_H
#define BACCOUNT_H

#include "Common.h" // bank_sys
#include "IAccount.h" // IAccount
#include "TransactionRegistry.h" // TransactionRegistry
#include <unordered_set> // std::unordered_set

// an abstract base class for shared implementation between derived account types
class BAccount : public IAccount
{
public:

	// initialize account
	BAccount();

	// deallocate account
	~BAccount() override = default;

	// get the unique id associated with the account
	bank_sys::ACCOUNT_ID getAccountId() const override;

	// get the current balance of the account
	bank_sys::US_CENTS getAccountBalance() const override;

	// get the overdraft fee associated with the account (if applicable)
	bank_sys::US_CENTS getOverdraftProtectionFee() const override;

	// get the account maintenance fee associated with the account (if applicable)
	bank_sys::US_CENTS getAccountMaintenanceFee() const override;

	// calculate the interest amount associated with the account (if applicable)
	bank_sys::US_CENTS calculateInterest() const override;

	// log a transaction with the account
	void logAccountTransaction( Transaction&& account_transaction ) override;

	// print the account details to the console
	void printAccountInfo() const override;

	// print the transaction history to the console
	void printTransactionHistory() const override;

protected:

	// generates a random, unique account ID
	static bank_sys::ACCOUNT_ID GENERATE_ACCOUNT_ID();

	// tracks existing account IDs to enforce uniqueness
	static std::unordered_set< bank_sys::ACCOUNT_ID > GENERATED_ACCOUNT_IDS;

	// the unique 9-digit identifier associated with the account
	bank_sys::ACCOUNT_ID m_account_id;

	// the current balance of the account
	bank_sys::US_CENTS m_current_balance;

	// the transaction history associated with the account
	TransactionRegistry m_transaction_history;
};

#endif // BACCOUNT_H