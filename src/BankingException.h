#ifndef BANKING_EXCEPTION_H
#define BANKING_EXCEPTION_H

#include <exception> // std::exception
#include <string> // std::string

// a specific implementation of exception handling for banking functionality
class BankingException : public std::exception
{
public:

	// initialize the banking exception with error message
	BankingException( const std::string& error_message );

	// get the error message associated with the exception
	const char* what() const noexcept override;

private:

	// the error message associated with the exception
	std::string m_error_message;
};

// an exception for invalid banking transaction errors
class InvalidTransactionError : public BankingException
{
public:

	// initialize the invalid transaction error with error message
	InvalidTransactionError( const std::string& error_message );
};

// an exception for vault transaction errors
class VaultTransactionError : public BankingException
{
public:

	// initialize the vault transaction error with error message
	VaultTransactionError( const std::string& error_message );
};

// an exception for account transaction errors
class AccountTransactionError : public BankingException
{
public:

	// initialize the account transaction error with error message
	AccountTransactionError( const std::string& error_message );
};

// an exception for insufficient funds error
class InsufficientFundsError : public BankingException
{
public:

	// initialize the insufficient funds error with error message
	InsufficientFundsError( const std::string& error_message );
};

#endif // BANKING_EXCEPTION_H