#include "SavingsAccount.h" // implementing SavingsAccount.h

// deposit money into the account
bool SavingsAccount::deposit( bank_sys::US_CENTS deposit_amount )
{
	// check if the deposit amount is valid
	if( deposit_amount <= 0 )
	{
		// reject invalid deposit
		return false;
	}
	// update the account balance
	m_current_balance += deposit_amount;

	// deposit valid
	return true;
}

// withdraw money from the account
bool SavingsAccount::withdraw( bank_sys::US_CENTS withdrawal_amount )
{
	// check if the withdrawal amount is valid
	if( withdrawal_amount <= 0 )
	{
		// reject invalid withdrawal
		return false;
	}
	// check if the balance is sufficient (including minimum balance requirement)
	if( m_current_balance - withdrawal_amount < m_minimum_balance )
	{
		// reject invalid withdrawal
		return false;
	}
	// check if the account has exceeded the withdrawal limit
	if( m_session_withdrawal_counter >= sm_MAX_WITHDRAWALS_PER_SESSION )
	{
		// reject invalid withdrawal
		return false;
	}
	// update the account balance
	m_current_balance -= withdrawal_amount;

	// increment withdrawal counter
	m_session_withdrawal_counter += 1;

	// withdrawal valid
	return true;
}

// get the text string associated with the account type (for logging purposes)
std::string SavingsAccount::getAccountString() const
{
	return "Savings";
}