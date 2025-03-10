#include "Authenticator.h" // implementing Authenticator
#include <iomanip> // std::hex, std::setw, std::setfill
#include <sstream> // std::ostringstream

// Define which hashing method to use (uncomment one of the following)
// simple implementation, uses the standard library, but is not cryptographically secure:
#define USE_STD_HASH
// complex implementation, requires additional dependencies, but is cryptographically secure:
// #define USE_SHA256_HASH

#ifdef USE_STD_HASH
// for std::hash (C++ standard library implementation)
// not cryptographically secure
#include <functional>
#include <random> // for random number generation

// function to hash a password using std::hash
std::string generateHash( const std::string& user_password )
{
	// initialize the hasher
	std::hash< std::string > std_hasher;

	// generate the hash from the user password
	std::size_t hash_value = std_hasher( user_password );

	// convert the hash to a hexadecimal string
	std::ostringstream hex_hash;

	hex_hash << std::hex // output in hexadecimal format

		<< std::setw( std::numeric_limits<std::size_t>::digits / 4 ) // ensures correct hex width

		<< std::setfill( '0' ) // pad with leading 0 if necessary

		<< hash_value; // write the hash value to the stream as a hex string

	// return the hex string
	return hex_hash.str();
}

// generate a random salt for password hashing
std::string generateSalt()
{
	// characters that will be used to generate the salt
	// includes digits (0-9) and lowercase letters (a-f)
	const char salt_chars[] = "0123456789abcdef";

	// initialize an empty string to initialize the salt
	std::string salt_string;

	// get a random seed from the system
	std::random_device random_device;

	// initialize a random number generator with the seed
	std::mt19937 random_generator( random_device() );

	// define the range of valid indices for the characters array
	std::uniform_int_distribution<> rng_distribution( 0, sizeof( salt_chars ) - 2 );

	// generate a 16-character salt
	for( unsigned short int i = 0; i < 16; ++i )
	{
		// for each char in the salt:
		// 1. generate a random index in the range of the available chars
		// 2. add the corresponding char to the salt string
		salt_string += salt_chars[ rng_distribution( random_generator ) ];
	}
	// return the generated salt
	return salt_string;
}
#endif

#ifdef USE_SHA256_HASH
// for OpenSSL (SHA hashing implementation)
// cryptographically secure, requires additional dependencies
#include <openssl/ssl.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

// function to hash a password using SHA-256
std::string generateHash( const std::string& user_password )
{
	// create a context for EVP (SHA-256)
	EVP_MD_CTX* md_ctx = EVP_MD_CTX_new();

	// initialize SHA-256 (using the EVP API)
	if( md_ctx == nullptr || EVP_DigestInit_ex( md_ctx, EVP_sha256(), nullptr ) != 1 )
	{
		// Error initializing SHA-256 context
	}
	// update the hash with the password
	if( EVP_DigestUpdate( md_ctx, user_password.c_str(), user_password.length() ) != 1 )
	{
		// Error updating the SHA-256 hash
	}
	// finalize the hash and get the result
	unsigned char hash[ EVP_MAX_MD_SIZE ];

	unsigned int hash_len = 0;

	if( EVP_DigestFinal_ex( md_ctx, hash, &hash_len ) != 1 )
	{
		// Error finalizing SHA-256 hash
	}
	// convert the hash to a hexadecimal string
	std::ostringstream hex_hash;

	for( unsigned int i = 0; i < hash_len; ++i )
	{
		hex_hash << std::hex // output in hexadecimal format

			<< std::setw( 2 ) // each byte is represented as a 2-character hex value

			<< std::setfill( '0' ) // pad with leading 0 if necessary

			<< (int)hash[ i ]; // convert each byte of the hash to an integer for formatting
	}
	// clean up
	EVP_MD_CTX_free( md_ctx );

	return hex_hash.str();
}

// generate a random salt for password hashing
std::string generateSalt()
{
	// characters that will be used to generate the salt
	// includes digits (0-9) and lowercase letters (a-f)
	const char salt_chars[] = "0123456789abcdef";

	// initialize an empty string to initialize the salt
	std::string salt_string;

	// specify the length of the salt
	const size_t salt_length = 16; // 16 bytes or 32 hex chars

	// buffer to hold random bytes
	unsigned char random_bytes[ salt_length ];

	// use openssl rand_bytes to securely generate random bytes
	if( RAND_bytes( random_bytes, sizeof( random_bytes ) ) != 1 )
	{
		// Error generating cryptographic random bytes
	}
	// convert the random bytes to hex chars and append to salt_string
	for( size_t i = 0; i < salt_length; ++i )
	{
		salt_string += salt_chars[ random_bytes[ i ] % ( sizeof( salt_chars ) - 1 ) ];
	}
	// return the generated salt
	return salt_string;
}
#endif

// initialize the authenticator with the plain text password
Authenticator::Authenticator( const std::string& password_text )

	: m_password_salt( generateSalt() ),
	
	m_password_hash( generateHash( password_text + m_password_salt ) ) { }

// returns true if the authenticator is locked
bool Authenticator::isLocked() const
{
	return m_locked;
}

// unlocks the account by comparing the input password to the user password
bool Authenticator::unlock( const std::string& password_attempt )
{
	// if the authenticator is already unlocked...
	if( !m_locked )
	{
		return true;
	}
	// if the attempted password matches the user password...
	if( generateHash( password_attempt + m_password_salt ) == m_password_hash )
	{
		// unlock the account
		m_locked = false;

		return true;
	}
	return false;
}

// manually locks the authenticator
void Authenticator::lock()
{
	if( !m_locked )
	{
		m_locked = true;
	}
}