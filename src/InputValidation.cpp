#include "InputValidation.h" // implementing
#include <cctype>
#include <regex>
#include <iostream>

// helper function to check if a string contains only letters
bool isAlphaOnly( const std::string& user_string )
{
	for( char current_char : user_string )
	{
		if( !std::isalpha( static_cast<unsigned char>( current_char ) ) )
		{
			return false;
		}
	}
	return true;
}

// helper function to check if a string contains only digits
bool isDigitsOnly( const std::string& user_string )
{
	for( char current_char : user_string )
	{
		if( !std::isdigit( static_cast<unsigned char> ( current_char ) ) )
		{
			return false;
		}
	}
	return true;
}

// helper function to check if an email address is valid
bool isValidEmail( const std::string& user_string )
{
	// define the regex pattern for validating the email address

		// this regex will identify MOST validation issues associated with email addresses,

		// however, it is not fully RFC-compliant and may not handle some very specific edge cases

	std::regex email_regex( R"(^(?!.*\.\.)(?!.*@.*@)[a-zA-Z0-9][a-zA-Z0-9._%+-]*@(?!\.)[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)" );

	// (?!.*\.\.) : prevents consecutive instances of the '.' symbol

	// (?!.*@.*@) : prevents consecutive instances of the '@' symbol

	// [a-zA-Z0-9] : the first character must be a lower case letter, upper case letter, or a digit

	// [a-zA-Z0-9._%+-]* : the rest of the local address is allowed to contain:

		// any combination of letters, digits, and the allowed special characters

	// @ : matches the literal @ symbol, separating the local address and the domain address

	// (?!\.) : ensures that the domain address does not start with the '.' symbol

	// [a-zA-Z0-9.-]+ : the domain address (before the TLD) is allowed to contain:

		// any combination of letters, digits, and the allowed special characters

	// \. : matches the literal dot separating the domain address and the TLD

	// [a-zA-Z]{2,}$ : ensures that the TLD contains only letters and is at least 2 characters long

	// use std::regex to check if the input string matches the regex pattern

	return std::regex_match( user_string, email_regex );
}

// helper function to check if a user password is valid
bool isValidPassword( const std::string& user_string )
{
	// minimum length : 8 characters
	if( user_string.length() < 8 )
	{
		return false;
	}
	// at least one uppercase letter
	for( const char& current_char : user_string )
	{
		// found an uppercase letter
		if( std::isupper( current_char ) )
		{
			break;
		}
		// did not find an uppercase letter
		if( &current_char == &user_string.back() )
		{
			return false;
		}
	}
	// at least one lower-case letter
	for( const char& current_char : user_string )
	{
		// found a lowercase letter
		if( std::islower( current_char ) )
		{
			break;
		}
		// did not find an lowercase letter
		if( &current_char == &user_string.back() )
		{
			return false;
		}
	}
	// at least one numeric digit
	for( const char& current_char : user_string )
	{
		// found a numeric digit
		if( std::isdigit( current_char ) )
		{
			break;
		}
		// did not find a numeric digit
		if( &current_char == &user_string.back() )
		{
			return false;
		}
	}
	// at least one special character
	for( const char& current_char : user_string )
	{
		// found a special character
		if( std::ispunct( current_char ) )
		{
			break;
		}
		// did not find a special character
		if( &current_char == &user_string.back() )
		{
			return false;
		}
	}
	// no spaces allowed
	for( const char& current_char : user_string )
	{
		// found a space
		if( std::isspace( current_char ) )
		{
			return false;
		}
	}
	return true;
}

// helper function to format a name
std::string formatName( const std::string& user_string )
{
	if( user_string.empty() ) return "";

	std::string return_string = user_string;

	return_string[ 0 ] = std::toupper( static_cast<unsigned char> ( return_string[ 0 ] ) );

	for( size_t i = 1; i < return_string.length(); ++i )
	{
		return_string[ i ] = std::tolower( static_cast<unsigned char> ( return_string[ i ] ) );
	}
	return return_string;
}

// helper function to format a phone number
std::string formatPhoneNumber( const std::string& user_string )
{
	return "(" + user_string.substr( 0, 3 ) + ") "

		+ user_string.substr( 3, 3 ) + "-"

		+ user_string.substr( 6, 4 );
}

// get a valid user id from the user
bank_sys::USER_ID getValidUserId()
{
	// initialize the user input
	std::string user_input { "" };

	// input and validate the user id
	while( true )
	{
		std::cout << "Enter a 6-digit user id: ";

		std::getline( std::cin, user_input );

		if( user_input.length() == 6 && isDigitsOnly( user_input ) )
		{
			break;
		}
		std::cout << "Invalid input detected, please try again \n";
	}
	return static_cast<bank_sys::USER_ID>( std::stoul( user_input ) );
}

// helper function to check if the dollar/cents input is in the correct format
bool isValidDollarFormat( const std::string& user_input )
{
	// regex to match the dollar/cents format (i.e., 25.52)
	std::regex dollar_pattern( R"(^\d+\.\d{2}$)" );

	return std::regex_match( user_input, dollar_pattern );
}

// helper function to convert a dollar amount string to US_CENTS
bank_sys::US_CENTS convertDollarsToCents( const std::string& user_input )
{
	// check if the string is in a valid format
	if( !isValidDollarFormat( user_input ) )
	{
		return 0;
	}
	// convert string to float
	float user_dollars = std::stof( user_input );

	// convert dollars to cents
	return static_cast< bank_sys::US_CENTS >( user_dollars * 100 );
}