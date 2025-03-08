#include "Account.h"
#include <random> // for random number generation
#include <iostream> // for std::cout
#include <locale> // for std::locale, std::imbue
#include <iomanip> // for std::put_money

// generates a random, unique account ID
Utils::ACCOUNT_ID GENERATE_ACCOUNT_ID()
{
	// get a random seed from the system
	std::random_device random_device;

	// initialize a random number generator with the seed
	std::mt19937 random_generator( random_device() );

	// define the range for generating 9-digit IDs
	std::uniform_int_distribution<> rng_distribution( 100000000, 999999999 );

	// store the generated account ID for comparison
	Utils::ACCOUNT_ID new_account_id;

	// keep generating a new account ID until it is unique
	do {
		new_account_id = rng_distribution( random_generator );

		// check if the account ID already exists
	} while( GENERATED_ACCOUNT_IDS.find( new_account_id ) != GENERATED_ACCOUNT_IDS.end() );

	// insert the new unique account ID into the set
	GENERATED_ACCOUNT_IDS.insert( new_account_id );

	// return the newly generated unique account ID
	return new_account_id;
}

// tracks existing account IDs to enforce uniqueness
std::unordered_set< Utils::ACCOUNT_ID > GENERATED_ACCOUNT_IDS;

// deallocate interface
IAccount::~IAccount() { }

// initialize the base account
BAccount::BAccount( const Utils::ACCOUNT_ID account_id, const Utils::US_CENTS account_balance )

	: m_account_id( account_id ), m_current_balance( account_balance ) { }

// get the unique id associated with this account
Utils::ACCOUNT_ID BAccount::getAccountId() const
{
	return m_account_id;
}

// get the current balance of this account
Utils::US_CENTS BAccount::getAccountBalance() const
{
	return m_current_balance;
}

// a short text-based description of the account type
std::string BAccount::getAccountType() const
{
	return "BAccount";
}

// adds funds to the account; returns true if successful
bool BAccount::deposit( const Utils::US_CENTS amount )
{
	// check if the deposit amount is valid
	if( amount <= 0 )
	{
		// invalid deposit amount
		return false;
	}
	// update the balance
	m_current_balance += amount;

	// log the deposit transaction
	m_transaction_log.addTransaction(

		Transaction( m_account_id, amount )
	);
	return true; // return
}

// deducts funds from the account; returns true if successful
bool BAccount::withdraw( const Utils::US_CENTS amount )
{
	// check if the withdraw amount is valid
	if( amount <= 0 )
	{
		// invalid withdraw amount
		return false;
	}
	//// check if balance is sufficient for the withdrawal
	//if( m_current_balance < amount )
	//{
	//	// insufficient funds
	//	return false;
	//}
	// update the balance after withdrawal
	m_current_balance -= amount;

	// log the withdrawal transaction
	m_transaction_log.addTransaction(

		Transaction( m_account_id, -amount )
	);
	return true; // return
}

// print account details to the console
void BAccount::printAccount() const
{
	std::cout << "ACCOUNT ID: " << m_account_id;

	std::cout << " | ACCOUNT TYPE: " << getAccountType();

	std::locale original_locale = std::cout.getloc(); // save current format

	std::cout.imbue( std::locale( "en_US.UTF-8" ) ); // format output

	//std::cout << " | BALANCE: " << ( m_current_balance < 0 ? "-$" : "$" )

		//<< std::put_money( std::abs( m_current_balance ) );

	std::cout << " | BALANCE: " << ( m_current_balance < 0 ? "$(" : "$" )

		<< std::put_money( std::abs( m_current_balance ) )

		<< ( m_current_balance < 0 ? ")" : "" ) << '\n';

	std::cout.imbue( original_locale ); // restore the original format

	if( !m_transaction_log.isEmpty() )
	{
		m_transaction_log.printTransactionLog();
	}
}

// overloaded operator adds funds to the account
BAccount& BAccount::operator +=( const Utils::US_CENTS deposit_amount )
{
	// attempt to deposit money
	if( !deposit( deposit_amount ) )
	{
		// deposit failed
	}
	return *this;
}

// overloaded operator deducts funds from the account
BAccount& BAccount::operator -=( const Utils::US_CENTS withdraw_amount )
{
	// attempt to withdraw money
	if( !withdraw( withdraw_amount ) )
	{
		// withdrawal failed
	}
	return *this;
}

// print account details to the output stream
std::ostream& operator<<( std::ostream& output_stream, const BAccount& account )
{
	account.printAccount();

	return output_stream; // return the output stream
}