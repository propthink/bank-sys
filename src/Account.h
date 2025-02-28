#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Utility.h" // for utils
#include "Transaction.h" // for TransactionHistory
#include <unordered_set> // for std::unordered_set
#include <string> // for std::string

// generates a random, unique account ID
Utils::ACCOUNT_ID GENERATE_ACCOUNT_ID();

// tracks existing account IDs to enforce uniqueness
extern std::unordered_set< Utils::ACCOUNT_ID > GENERATED_ACCOUNT_IDS;

// defines the interface for account-related operations
class IAccount
{
public:

	// deallocate interface
	virtual ~IAccount();

	// get the unique id associated with this account
	virtual Utils::ACCOUNT_ID getAccountId() const = 0;

	// get the current balance of this account
	virtual Utils::US_CENTS getAccountBalance() const = 0;

	// a short text-based description of the account type
	virtual std::string getAccountType() const = 0;

	// adds funds to the account; returns true if successful
	virtual bool deposit( Utils::US_CENTS amount ) = 0;

	// deducts funds from the account; returns true if successful
	virtual bool withdraw( Utils::US_CENTS amount ) = 0;

	// print account details to the console
	virtual void printAccount() const = 0;
};

// base account class implementing IAccount interface
class BAccount : public IAccount
{
public:

	// initialize the base account
	BAccount( Utils::ACCOUNT_ID account_id, Utils::US_CENTS account_balance = 0 );

	// get the unique id associated with this account
	virtual Utils::ACCOUNT_ID getAccountId() const override;

	// get the current balance of this account
	virtual Utils::US_CENTS getAccountBalance() const override;

	// a short text-based description of the account type
	virtual std::string getAccountType() const override;

	// adds funds to the account; returns true if successful
	virtual bool deposit( Utils::US_CENTS deposit_amount ) override;

	// deducts funds from the account; returns true if successful
	virtual bool withdraw( Utils::US_CENTS withdraw_amount ) override;

	// print account details to the console
	virtual void printAccount() const override;

private:

	// unique account id
	Utils::ACCOUNT_ID m_account_id;

	// account balance
	Utils::US_CENTS m_current_balance;

	// stores the history of all transactions for this account
	TransactionLog m_transaction_log;
};

#endif // ACCOUNT_H