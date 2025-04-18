#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include "Common.h"
#include <string>

// helper function to check if a string contains only letters
bool isAlphaOnly( const std::string& user_string );

// helper function to check if a string contains only digits
bool isDigitsOnly( const std::string& user_string );

// helper function to check if an email address is valid
bool isValidEmail( const std::string& user_string );

// helper function to check if a user password is valid
bool isValidPassword( const std::string& user_string );

// helper function to format a name
std::string formatName( const std::string& user_string );

// helper function to format a phone number
std::string formatPhoneNumber( const std::string& user_string );

// get a valid user id from the user
bank_sys::USER_ID getValidUserId();

// helper function to check if the dollar/cents input is in the correct format
bool isValidDollarFormat( const std::string& user_input );

// helper function to convert a dollar amount string to US_CENTS
bank_sys::US_CENTS convertDollarsToCents( const std::string& user_input );

#endif // INPUT_VALIDATION_H