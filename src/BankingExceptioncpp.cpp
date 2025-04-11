#include "BankingException.h" // implementing

// initialize banking exception with error message
BankingException::BankingException( const std::string& error_message )

	: m_error_message( error_message ) { }

// get the error message associated with the exception
const char* BankingException::what() const noexcept
{
	return m_error_message.c_str();
}

// initialize the invalid transaction error with error message
InvalidTransactionError::InvalidTransactionError( const std::string& error_message )

	: BankingException( error_message ) { }

// initialize the vault transaction error with error message
VaultTransactionError::VaultTransactionError( const std::string& error_message )

	: BankingException( error_message ) { }

// initialize the account transaction error with error message
AccountTransactionError::AccountTransactionError( const std::string& error_message )

	: BankingException( error_message ) { }

// initialize the insufficient funds error with error message
InsufficientFundsError::InsufficientFundsError( const std::string& error_message )

	: BankingException( error_message ) { }