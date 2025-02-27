#include "Account.h"

// deallocate interface
IAccount::~IAccount() { }

// initialize the base account
BAccount::BAccount( IdUtils::ACCOUNT_ID account_id, BankUtils::US_CENTS account_balance )

	: m_account_id( account_id ), m_current_balance( account_balance ) { }

// get the unique id associated with this account
IdUtils::ACCOUNT_ID BAccount::getAccountId() const
{
	return m_account_id;
}

// get the current balance of this account
BankUtils::US_CENTS BAccount::getAccountBalance() const
{
	return m_current_balance;
}