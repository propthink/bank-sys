#include "Transaction.h" // implementing Transaction
#include <chrono> // std::chrono
#include <sstream> // std::ostringstream
#include <iomanip> // std::put_time, std::put_money

#include <iostream> // TEST PRINT
#include <locale> // std::locale, std::imbue
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

// initialize the transaction
Transaction::Transaction( bank_sys::ACCOUNT_ID account_id, bank_sys::US_CENTS transaction_amount )

	: m_account_id( account_id ), m_amount( transaction_amount )
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

// TEST PRINT
void Transaction::TEST_PRINT() const
{
	std::cout << "ACCOUNT ID: " << m_account_id;

	std::locale original_locale = std::cout.getloc(); // save current format

	std::cout.imbue( std::locale( "en_US.UTF-8" ) ); // format output

	//std::cout << " | AMOUNT: " << ( m_amount < 0 ? "-$" : "$" )

		//<< std::put_money( std::abs( m_amount ) );

	std::cout << " | AMOUNT: " << ( m_amount < 0 ? "$(" : "$" )

		<< std::put_money( std::abs( m_amount ) )

		<< ( m_amount < 0 ? ")" : "" );

	std::cout.imbue( original_locale ); // restore the original format

	std::cout << " | DESC: " << m_description;

	std::cout << " | TIME: " << m_timestamp << '\n';
}