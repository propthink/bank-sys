#include "Transaction.h" // implementing Transaction.h
#include <chrono> // std::chrono
#include <ctime> // std::tm, std::localtime_s
#include <sstream> // std::ostringstream
#include <iomanip> // std::setw, std::setfill, std::put_time, std::put_money
#include <iostream> // std::cout
#include <locale> // std::locale
#include <cmath> // std::abs

// generates a timestamp string based on the current local time
std::string generateTimestamp()
{
	// get the current time as a time_point
	auto current_time = std::chrono::system_clock::now();

	// convert the current time to time_t
	auto time_t = std::chrono::system_clock::to_time_t( current_time );

	// create a tm struct to hold the broken-down time
	std::tm tm_struct { };

	// use std::localtime_s to fill the tm struct with local time
	localtime_s( &tm_struct, &time_t );

	// create a stringstream to build the timestamp
	std::ostringstream string_stream;

	string_stream << std::put_time( &tm_struct, "%Y-%m-%d %H:%M:%S" );

	// capture the formatted string from the stringstream
	std::string timestamp_str = string_stream.str();

	// return the formatted timestamp
	return timestamp_str;
}

// initialize a transaction between two accounts
Transaction::Transaction( bank_sys::ACCOUNT_ID from_account, bank_sys::ACCOUNT_ID to_account,

	bank_sys::US_CENTS transaction_amount )

	: m_from_account( from_account ), m_to_account( to_account ), m_transaction_amount( transaction_amount )
{
	// invalid transaction
	if( transaction_amount == 0 )
	{
		// handle error
	}
	// generate text description
	m_description = ( transaction_amount < 0 ) ? "Withdrawal" : "Deposit";

	// generate timestamp
	m_timestamp = generateTimestamp();
}

// initialize a transaction with a single account
Transaction::Transaction( bank_sys::ACCOUNT_ID account_id, bank_sys::US_CENTS transaction_amount )

	: m_from_account( 0 ), m_to_account( 0 ), m_transaction_amount( transaction_amount )
{
	// invalid transaction
	if( transaction_amount == 0 )
	{
		// handle error
	}
	// generate text description
	// initialize account id
	if( transaction_amount < 0 )
	{
		m_description = "Withdrawal";

		m_from_account = account_id;
	}
	else if( transaction_amount > 0 )
	{
		m_description = "Deposit";

		m_to_account = account_id;
	}
	// generate timestamp
	m_timestamp = generateTimestamp();
}

// print the transaction details to the console
void Transaction::printTransactionInfo() const
{
	std::cout << "FROM ACCOUNT: " << std::setw( 9 ) << std::setfill( '0' ) << m_from_account;

	std::cout << " | TO ACCOUNT: " <<  std::setw( 9 ) << std::setfill( '0' ) << m_to_account;

	std::locale original_locale = std::cout.getloc(); // save current format

	std::cout.imbue( std::locale( "en_US.UTF-8" ) ); // format output

	//std::cout << " | AMOUNT: " << ( m_amount < 0 ? "-$" : "$" )

		//<< std::put_money( std::abs( m_amount ) );

	std::cout << " | AMOUNT: " << ( m_transaction_amount < 0 ? "$(" : "$" )

		<< std::put_money( std::abs( m_transaction_amount ) )

		<< ( m_transaction_amount < 0 ? ")" : "" );

	std::cout.imbue( original_locale ); // restore the original format

	std::cout << " | DESC: " << m_description;

	std::cout << " | TIME: " << m_timestamp << '\n';
}