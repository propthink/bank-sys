#ifndef IACCOUNT_H
#define IACCOUNT_H

#include "Common.h" // for bank_sys namespace

// a shared interface for interacting with derived account types
class IAccount
{
public:

	// initialize account
	IAccount() = default;

	// deallocate account
	virtual ~IAccount() = default;

	// get the unique id associated with this account
	virtual bank_sys::ACCOUNT_ID getAccountId() const = 0;
};

#endif // IACCOUNT_H