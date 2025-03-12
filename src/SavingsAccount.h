#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H

#include "BAccount.h" // inherits from BAccount
#include "Common.h" // bank_sys namespace

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

	// deposit money into this account
	bool deposit( bank_sys::US_CENTS deposit_amount ) override;

	// withdraw money from this account
	bool withdraw( bank_sys::US_CENTS withdrawal_amount ) override;

	// apply interest if applicable
	bool applyInterest();

private:

	// manage interest calculations for savings account
	class InterestCalculator
	{
	public:

		// initialize interest rate
		InterestCalculator() = default;

		// calculate and return interest
		bank_sys::US_CENTS calculateInterest( bank_sys::US_CENTS user_balance ) const;

		// calculate the total balance (principal and interest)
		bank_sys::US_CENTS calculateBalance( bank_sys::US_CENTS user_balance ) const;

	private:

		// current interest rate (default 2.5%)
		double m_interest_rate = 0.025;
	};
	// manage interest calculations
	InterestCalculator m_interest_calculator;

	// minimum balance requirement, default minimum = $250
	bank_sys::US_CENTS m_minimum_balance = 25000;

	// enforces the maximum allowed number of withdrawals per session
	static const unsigned int sm_MAX_WITHDRAWALS_PER_SESSION = 6;

	// tracks the total number of withdrawals during the current session
	unsigned int m_session_withdrawal_counter = 0;
};

#endif // SAVINGS_ACCOUNT_H