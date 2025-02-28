#include "Transaction.h"
#include <chrono> // for std::chrono
#include <ctime> // for localtime_s
#include <sstream> // for std::ostringstream
#include <iomanip> // for std::put_time and std::put_money
#include <iostream> // for std::cout and std::locale
#include <locale> // for std::locale and std::imbue
#include <cstdlib> // for std::abs (used for absolute value)

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

// initialize transaction
Transaction::Transaction( Utils::ACCOUNT_ID account_id, Utils::US_CENTS transaction_amount )

	: m_account_id( account_id ), m_amount( transaction_amount )
{
	// generate description
	if( transaction_amount == 0 )
	{
		// TODO: invalid transaction
	}
	else
	{
		m_description = ( transaction_amount < 0 ) ? "Withdraw" : "Deposit";
	}
	// generate timestamp
	m_timestamp = generateTimestamp();
}

// print the transaction details to the console
void Transaction::printTransaction() const
{
	std::cout << "ACCOUNT #: " << m_account_id;

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

// initialize transaction node
TransactionNode::TransactionNode( const Transaction& transaction )

	: m_transaction( std::make_unique< Transaction >( transaction ) ),

	m_next( nullptr ), m_prev( nullptr ) { }

// initialize
TransactionLog::TransactionLog()

	: m_head( nullptr ), m_tail( nullptr ) { }

// add a new transaction at the end of the list
void TransactionLog::addTransaction( const Transaction& transaction )
{
	// create a new node to store the transaction
	auto new_node = std::make_unique< TransactionNode >( transaction );

	// if the list is empty...
	if( !m_head )
	{
		// make the new node both the head and tail
		m_head = std::move( new_node );

		m_tail = m_head.get();
	}
	else // add the new node at the end of the list
	{
		// attach the new node to the current tail
		m_tail -> m_next = std::move( new_node );

		// the prev pointer of the new node is the current tail
		m_tail -> m_next -> m_prev = m_tail;

		// update the tail pointer to the newly added node
		m_tail = m_tail -> m_next.get();
	}
}

// print the entire transaction history
void TransactionLog::printTransactionLog() const
{
	// check if the list is empty
	if( !m_head )
	{
		// there is nothing to print
		return;
	}
	// start from the head of the list
	TransactionNode* current_transaction = m_head.get();

	// iterate through the list and print each transaction
	while( current_transaction )
	{
		current_transaction -> m_transaction -> printTransaction(); // print transaction details

		current_transaction = current_transaction -> m_next.get(); // step
	}
}