#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Utilities.h" // for utils

// defines the interface for account-related operations
class IAccount
{
public:

	virtual ~IAccount(); // deallocate interface

	// get the unique id associated with this account
	virtual IdUtils::ACCOUNT_ID getAccountId() const = 0;

	// get the current balance of this account
	virtual BankUtils::US_CENTS getAccountBalance() const = 0;
};

// base account class implementing IAccount interface
class BAccount : public IAccount
{
public:

	// initialize the base account
	BAccount( IdUtils::ACCOUNT_ID account_id, BankUtils::US_CENTS account_balance = 0 );

	// get the unique id associated with this account
	virtual IdUtils::ACCOUNT_ID getAccountId() const override;

	// get the current balance of this account
	virtual BankUtils::US_CENTS getAccountBalance() const override;

private:

	IdUtils::ACCOUNT_ID m_account_id; // unique account id

	BankUtils::US_CENTS m_current_balance; // account balance
};

#endif // ACCOUNT_H