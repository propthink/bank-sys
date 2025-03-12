#include "SavingsAccount.h" // implementing SavingsAccount.h

// deposit money into account
bool SavingsAccount::deposit( bank_sys::US_CENTS deposit_amount )
{
	// check if the deposit amount is valid
	if( deposit_amount <= 0 )
	{
		// reject invalid deposit
		return false;
	}
	// update balance
	m_current_balance += deposit_amount;

	// log transaction
	m_transaction_registry.insertTransaction(

		Transaction( BAccount::m_account_id, deposit_amount ) );

	// transaction successful
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
	// check if the account has sufficient funds
	if( BAccount::m_current_balance < withdrawal_amount )
	{
		// reject invalid withdrawal
		return false;
	}
	// check if the withdrawal would bring the balance below the minimum
	if( BAccount::m_current_balance - withdrawal_amount < m_minimum_balance )
	{
		// reject invalid withdrawal
		return false;
	}
	// check if the withdrawal limit has been exceeded
	if( m_session_withdrawal_counter >= sm_MAX_WITHDRAWALS_PER_SESSION )
	{
		// reject invalid withdrawal
		return false;
	}
	// update balance
	m_current_balance -= withdrawal_amount;

	// log transaction
	m_transaction_registry.insertTransaction(

		Transaction( BAccount::m_account_id, -withdrawal_amount ) );

	// update session withdrawal counter
	m_session_withdrawal_counter += 1;

	// transaction successful
	return true;
}

// apply interest to savings account balance
bool SavingsAccount::applyInterest()
{
	// check that the balance meets the minimum requirement and is not negative
	if( BAccount::m_current_balance < m_minimum_balance || m_current_balance < 0 )
	{
		// reject the transaction if minimum requirements are not met
		return false;
	}
	// calculate the interest amount
	bank_sys::US_CENTS interest_amount = m_interest_calculator.calculateInterest(

		BAccount::m_current_balance );

	// deposit only the interest amount
	if( !deposit( interest_amount ) )
	{
		// deposit was rejected
		return false;
	}
	// transaction successful
	return true;
}

// calculate and return interest
bank_sys::US_CENTS SavingsAccount::InterestCalculator::calculateInterest( bank_sys::US_CENTS user_balance ) const
{
	// use floating-point arithmetic to calculate interest amount
	double interest_amount = user_balance * m_interest_rate;

	// add 0.5 before casting to ensure rounding to the nearest integer
	return static_cast<bank_sys::US_CENTS>( interest_amount + 0.5 );
}

// calculate the total balance (principal and interest)
bank_sys::US_CENTS SavingsAccount::InterestCalculator::calculateBalance( bank_sys::US_CENTS user_balance ) const
{
	return user_balance + calculateInterest( user_balance );
}