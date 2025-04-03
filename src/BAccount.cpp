#include "BAccount.h" // implementing BAccount.h
#include <iostream> // std:cout
#include <iomanip> // std::setw, std::setfill, std::put_money
#include <locale> // std::locale
#include <cmath> // std::abs
#include <random> // rng

// initialize account
BAccount::BAccount()

	: m_account_id( GENERATE_ACCOUNT_ID() ), m_current_balance( 0 ) { }

// get the unique id associated with the account
bank_sys::ACCOUNT_ID BAccount::getAccountId() const
{
	return m_account_id;
}

// get the current balance of the account
bank_sys::US_CENTS BAccount::getAccountBalance() const
{
	return m_current_balance;
}

// get the overdraft fee associated with the account (if applicable)
bank_sys::US_CENTS BAccount::getOverdraftProtectionFee() const
{
	return 0;
}

// get the account maintenance fee associated with the account (if applicable)
bank_sys::US_CENTS BAccount::getAccountMaintenanceFee() const
{
	return 0;
}

// calculate the interest amount associated with the account (if applicable)
bank_sys::US_CENTS BAccount::calculateInterest() const
{
	return 0;
}

// log a transaction with the account
void BAccount::logAccountTransaction( Transaction&& account_transaction )
{
	m_transaction_history.insertTransaction( std::move( account_transaction ) );
}

// print the account details to the console
void BAccount::printAccountInfo() const
{
	std::cout << "ACCOUNT ID: " << m_account_id;

	std::cout << " | ACCOUNT TYPE: " << getAccountString();

	std::locale original_locale = std::cout.getloc(); // save current format

	std::cout.imbue( std::locale( "en_US.UTF-8" ) ); // format output

	std::cout << " | CURRENT BALANCE: " << ( m_current_balance < 0 ? "$(" : "$" )

		<< std::put_money( std::abs( m_current_balance ) )

		<< ( m_current_balance < 0 ? ")" : "" ) << '\n';

	std::cout.imbue( original_locale ); // restore the original format

	m_transaction_history.printTransactionRegistry();
}

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
	} while( GENERATED_ACCOUNT_IDS.find( new_account_id ) != GENERATED_ACCOUNT_IDS.end()

		|| new_account_id == bank_sys::VAULT_ID ); // avoid the unique vault id

	// insert the new unique account ID into the set
	GENERATED_ACCOUNT_IDS.insert( new_account_id );

	// return the newly generated unique account ID
	return new_account_id;
}

// tracks existing account IDs to enforce uniqueness
std::unordered_set< bank_sys::ACCOUNT_ID > BAccount::GENERATED_ACCOUNT_IDS;