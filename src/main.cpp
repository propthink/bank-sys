#include "Common.h" // bank_sys
#include "User.h" // User
#include "UserRegistry.h" // UserRegistry

#include <string> // std::string, std::getline,  std::stoul
#include <iostream> // std::cout, std::cin
// std::isalpha, std::isdigit, std::isupper, std::islower, std::ispunct, std::isspace, std::toupper, std::tolower
#include <cctype>
#include <regex> // std::regex

#include <memory>
#include "CheckingAccount.h"
#include "SavingsAccount.h"

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

	return_string[ 0 ] = std::toupper( static_cast< unsigned char > ( return_string[ 0 ] ) );

	for( size_t i = 1; i < return_string.length(); ++i )
	{
		return_string[ i ] = std::tolower( static_cast< unsigned char > ( return_string[ i ] ) );
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

// build the full name from the user input
std::string buildName()
{
	// initialize the substrings for the user name
	std::string user_first { "" }, user_middle { "" }, user_last { "" };

	// input and validate the first name
	while( true )
	{
		std::cout << "Enter first name: ";

		std::getline( std::cin, user_first );

		if( isAlphaOnly( user_first ) )
		{
			break;
		}
		std::cout << "Invalid input detected, please try again \n";
	}
	// input and validate the middle initial
	while( true )
	{
		std::cout << "Enter middle initial: ";

		std::getline( std::cin, user_middle );

		if( isAlphaOnly( user_middle ) )
		{
			break;
		}
		std::cout << "Invalid input detected, please try again \n";
	}
	// input and validate the last name
	while( true )
	{
		std::cout << "Enter last name: ";

		std::getline( std::cin, user_last );

		if( isAlphaOnly( user_last ) )
		{
			break;
		}
		std::cout << "Invalid input detected, please try again \n";
	}
	return { formatName( user_first ) + " " + formatName( user_middle ) + " " + formatName( user_last ) };
}

// build the phone number from the user input
std::string buildPhoneNumber()
{
	// initialize the user input
	std::string user_input { "" };

	// input and validate the phone number
	while( true )
	{
		std::cout << "Enter phone number: ";

		std::getline( std::cin, user_input );

		if( user_input.length() == 10 && isDigitsOnly( user_input ) )
		{
			break;
		}
		std::cout << "Invalid input detected, please try again \n";
	}
	return formatPhoneNumber( user_input );
}

// build the email address from the user input
std::string buildEmailAddress()
{
	// initialize the user input
	std::string user_input { "" };

	// input and validate the email address
	while( true )
	{
		std::cout << "Enter email address: ";

		std::getline( std::cin, user_input );

		if( isValidEmail( user_input ) )
		{
			break;
		}
		std::cout << "Invalid input detected, please try again \n";
	}
	return user_input;
}

// build the password from the user input
std::string buildPassword()
{
	// initialize the user input
	std::string user_input { "" };

	// input and validate the user password
	while( true )
	{
		std::cout << "Please make sure that your new password: \n";

		std::cout << " : is at least 8 characters long \n";

		std::cout << " : contains at least one uppercase letter \n";

		std::cout << " : contains at least one lowercase letter \n";

		std::cout << " : contains at least one digit \n";

		std::cout << " : contains at least one special character (!@#$%^&*?) \n";

		std::cout << " : does not include any spaces \n";

		std::cout << "Enter new password: ";

		std::getline( std::cin, user_input );

		if( isValidPassword( user_input ) )
		{
			break;
		}
		std::cout << "Invalid input detected, please try again \n";
	}
	return user_input;
}

// build the user info from the user input
User::UserInfo buildUserInfo()
{
	return User::UserInfo { buildName(), buildPhoneNumber(), buildEmailAddress() };
}

// build a new user from the user input
User buildUser()
{
	// initialize the new user
	User new_user { User { User::UserInfo { buildUserInfo() }, buildPassword() } };

	// print the user info to the console
	new_user.printUserInfo();

	std::cout << "IMPORTANT: You will need your unique user id [" << new_user.getUserId()

		<< "] and password to access your user profile! \n";

	return new_user;
}

// print the menu header to the console
void printMenuHeader()
{
std::cout << R"(
==============================================
|            Welcome to bank-sys             |
|   A simple banking platform for everyone   |
============================================== 
)" << '\n';
}

// print the top-level menu to the console, capture and return the user input
std::string printTopLevelMenu()
{
	// buffer for user input
	std::string user_input { "" };

	// print the top-level menu to the console
	std::cout << "Please choose one of the following options: \n";

	std::cout << "\nCreate a [n]ew user profile \n";

	std::cout << "Access an [e]xisting user profile \n";

	std::cout << "[Q]uit the application \n";

	std::cout << "\nEnter your selection here: ";

	// capture the user input
	std::getline( std::cin, user_input );

	// return the user input
	return user_input;
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

// get a valid password from the user
std::string getUserPassword()
{
	// initialize the user input
	std::string user_input { "" };

	// input the user password
	std::cout << "Enter your password: ";

	// do not validate
	std::getline( std::cin, user_input );

	return user_input;
}

// access an existing user in the user registry
User* accessExistingUser( const UserRegistry& user_registry )
{
	// initialize the current user
	User* current_user { nullptr };

	// find the current user in the user registry
	current_user = user_registry.findUser( getValidUserId() );

	if( !current_user )
	{
		std::cout << "User not found \n";
	}
	else
	{
		// max password attempts
		const int MAX_ATTEMPTS { 5 };

		// current password attempts
		int password_attempts { 0 };

		// attempt to access the current user profile
		while( password_attempts < MAX_ATTEMPTS )
		{
			password_attempts += 1;

			if( !current_user -> unlockAuthenticator( getUserPassword() ) )
			{
				std::cout << "Password incorrect. You have " << MAX_ATTEMPTS - password_attempts

					<< " password attempts remaining \n";
			}
			else
			{
				if( !current_user -> authenticatorLocked() )
				{
					return current_user;
				}
			}
		}
		std::cout << "User profile locked \n";
	}
	return nullptr;
}

// print the existing user menu to the console, capture and return the user input
std::string printExistingUserMenu()
{
	// buffer for user input
	std::string user_input { "" };

	// print the top-level menu to the console
	std::cout << "Please choose one of the following options: \n";

	std::cout << "\nView [u]ser profile \n";

	std::cout << "[E]dit user profile \n";

	std::cout << "View [a]ccount info \n";

	std::cout << "Add a [n]ew account \n";

	std::cout << "[D]eposit funds \n";

	std::cout << "[W]ithdraw funds \n";

	std::cout << "Return to the [m]ain menu \n";

	std::cout << "\nEnter your selection here: ";

	// capture the user input
	std::getline( std::cin, user_input );

	// return the user input
	return user_input;
}

// attach a new account to an existing user profile
bool attachNewAccount( User& current_user )
{
	// initialize the user input
	std::string user_input { "" };

	//
	while( true )
	{
		std::cout << "Please choose one of the following options: \n";

		std::cout << "\n[C]hecking account \n";

		std::cout << "[S]avings account \n";

		std::cout << "\nEnter your selection here: ";

		// capture the user input
		std::getline( std::cin, user_input );

		// proceed based on the user input
		if( user_input == "C" || user_input == "c" )
		{
			current_user.addAccount( std::make_unique< CheckingAccount >() ); return true;
		}
		else if( user_input == "S" || user_input == "s" )
		{
			current_user.addAccount( std::make_unique< SavingsAccount >() ); return true;
		}
		else
		{
			std::cout << "Invalid input detected, please try again \n";
		}
	}
	return false;
}

//// testing main
//int main()
//{
//	//
//}

// enter main
int main()
{
	// initialize the user registry
	UserRegistry user_registry;

	// sentinel value
	const std::string sentinel_value { "-1" };

	// buffer for user input
	std::string user_input { "" };

	// main loop
	while( user_input != sentinel_value )
	{
		// output the top-level menu
		printMenuHeader();

		user_input = printTopLevelMenu(); // capture the user input

		// proceed based on the user input
		if( user_input == "N" || user_input == "n" )
		{
			// initialize the new user
			user_registry.insertUser( buildUser() );
		}
		else if( user_input == "E" || user_input == "e" )
		{
			// attempt to access an existing user
			User* current_user = accessExistingUser( user_registry );

			if( !current_user )
			{
				std::cout << "Unable to access existing user account \n";
			}
			else
			{
				// existing user loop
				while( user_input != "M" && user_input != "m" )
				{
					// output the existing user menu
					printMenuHeader();

					user_input = printExistingUserMenu(); // capture the user input

					// proceed based on the user input
					if( user_input == "U" || user_input == "u" )
					{
						current_user -> printUserInfo();
					}
					else if( user_input == "E" || user_input == "e" )
					{
						current_user -> updateUserInfo( buildUserInfo() );
					}
					else if( user_input == "A" || user_input == "a" )
					{
						current_user -> printAccountInfo();
					}
					else if( user_input == "N" || user_input == "n" )
					{
						if( attachNewAccount( *current_user ) )
						{
							std::cout << "Successfully added new account to user profile \n";
						}
						else
						{
							std::cout << "Unable to add new account to user profile \n";
						}
					}
					else if( user_input == "D" || user_input == "d" )
					{
						// Deposit funds here
					}
					else if( user_input == "W" || user_input == "w" )
					{
						// Withdraw funds here
					}
					else if( user_input == "M" || user_input == "m" )
					{
						// lock the current user profile before returning to the main menu
						current_user -> lockAuthenticator();
					}
					else
					{
						std::cout << "Invalid input detected, please try again \n";
					}
				}
			}
		}
		else if( user_input == "Q" || user_input == "q" )
		{
			user_input = "-1"; // quit the application
		}
		else
		{
			std::cout << "Invalid input detected, please try again \n";
		}
	}
	// return to OS
	return 0;
}