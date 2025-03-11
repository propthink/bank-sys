#include "BAccount.h" // implementing BAccount
#include <random> // random number generation

#include <iostream> // TEST PRINT
#include <iomanip> // std::put_money
#include <locale> // std::locale, std::imbue
#include <cmath> // std::abs

// generates a random, unique account ID
bank_sys::ACCOUNT_ID BAccount::GENERATE_ACCOUNT_ID()
{
	// get a random seed from the system
	static std::random_device random_device;

	// initialize a random number generator with the seed
	static std::mt19937 random_generator( random_device() );

	// define the range for generating 9-digit IDs
	std::uniform_int_distribution<> rng_distribution( 100000000, 999999999 );

	// store the generated account ID for comparison
	bank_sys::ACCOUNT_ID new_account_id;

	do
	{
		// keep generating a new account ID until it is unique
		new_account_id = rng_distribution( random_generator );

		// check if the account ID already exists
	} while( GENERATED_ACCOUNT_IDS.find( new_account_id ) != GENERATED_ACCOUNT_IDS.end() );

	// insert the new unique account ID into the set
	GENERATED_ACCOUNT_IDS.insert( new_account_id );

	// return the newly generated unique account ID
	return new_account_id;
}

// tracks existing account IDs to enforce uniqueness
std::unordered_set< bank_sys::ACCOUNT_ID > BAccount::GENERATED_ACCOUNT_IDS;

// initialize account
BAccount::BAccount()

	: m_account_id( BAccount::GENERATE_ACCOUNT_ID() ), m_current_balance( 0 ) { }

// get the unique id associated with this account
bank_sys::USER_ID BAccount::getAccountId() const
{
	return m_account_id;
}

// deposit money into the account
bool BAccount::deposit( bank_sys::US_CENTS deposit_amount )
{
	// reject invalid deposits
	if( deposit_amount <= 0 )
	{
		return false;
	}
	// add the deposit amount to the current balance
	m_current_balance += deposit_amount;

	// log the transaction
	m_transaction_registry.insertTransaction( Transaction( m_account_id, deposit_amount ) );

	return true;
}

// withdraw money from the account
bool BAccount::withdraw( bank_sys::US_CENTS withdrawal_amount )
{
	// reject invalid withdrawals
	if( withdrawal_amount <= 0 )
	{
		return false;
	}
	// insufficient funds
	//if( withdrawal_amount > m_current_balance )
	//{
		//return false;
	//}
	// subtract the withdrawal amount from the current balance
	m_current_balance -= withdrawal_amount;

	// log the transaction
	m_transaction_registry.insertTransaction( Transaction( m_account_id, -withdrawal_amount ) );

	return true;
}

// TEST PRINT
void BAccount::TEST_PRINT() const
{
	std::cout << "ACCOUNT ID: ";

	std::cout << m_account_id;

	std::cout << " | CURRENT BALANCE: ";

	std::locale original_locale = std::cout.getloc(); // save current format

	std::cout.imbue( std::locale( "en_US.UTF-8" ) ); // format output

	std::cout << ( m_current_balance < 0 ? "$(" : "$" )

		<< std::put_money( std::abs( m_current_balance ) )

		<< ( m_current_balance < 0 ? ")" : "" ) << '\n';

	std::cout.imbue( original_locale ); // restore the original format

	m_transaction_registry.TEST_PRINT();
}