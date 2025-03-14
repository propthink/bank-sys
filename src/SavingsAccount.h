#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "Common.h" // bank_sys
#include "BAccount.h" // BAccount

// savings account (intended for long-term savings)
// minimum balance requirement, limits on withdrawals, interest earned on balance
// no negative balance allowed, no monthly fee
	// historically Reg D specifies 6 withdrawals per month
	// current implementation is 6 withdrawals per session
class SavingsAccount : public BAccount
{
public:

	// initialize savings account
	SavingsAccount() = default;

	// deallocate savings account
	~SavingsAccount() override = default;

	// deposit money into the account
	bool deposit( bank_sys::US_CENTS deposit_amount ) override;

	// withdraw money from the account
	bool withdraw( bank_sys::US_CENTS withdrawal_amount ) override;

	// get the text string associated with the account type (for logging purposes)
	std::string getAccountString() const override;

private:

	// minimum balance requirement, default minimum = $250
	bank_sys::US_CENTS m_minimum_balance = 25000;

	// enforces the maximum allowed number of withdrawals per session
	static const unsigned int sm_MAX_WITHDRAWALS_PER_SESSION = 6;

	// tracks the total number of withdrawals during the current session
	unsigned int m_session_withdrawal_counter = 0;
};

#endif // SAVINGS_ACCOUNT_H