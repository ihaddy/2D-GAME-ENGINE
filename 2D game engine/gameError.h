#ifndef _GAMEERROR_H //if not defined, then define. this prevents multiple definitions
#define _GAMEERROR_H 
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <exception>

namespace gameErrorNS
{
	//These are the error codes
	//negative numbers imply a fatal error, game MAY shut down
	//positive numbers are warnings, game does NOT shut down

	const int FATAL_ERROR = -1;
	const int WARNING = 1;

}

//This is the game error class. It will be thrown when the engine detects an error
// It inherits from the std exception library
//  The ":" is the Inheritance operator, the "::" is the scope operator

class GameError : public std::exception

{
private:

	int errorCode;
	std::string message;

public:
	//default constructor
	GameError() throw() :errorCode(gameErrorNS::FATAL_ERROR), message("Undefined Error in game.") {}
	//the copy constructor
	GameError(const GameError& e) throw() : std::exception(e), errorCode(e.errorCode), message(e.message) {}
	//the constructor with args
	GameError(int code, const std::string &s) throw() :errorCode(code), message(s) {}
	//assignment operator
	GameError& operator= (const GameError& rhs) throw()
	{
		std::exception::operator=(rhs);
		this->errorCode = rhs.errorCode;
		this->errorCode = rhs.message;

	}

	//Destructor
	virtual ~GameError() throw() {};

	//override what from the base class

	virtual const char* what() const throw() { return this->getMessage(); }

	const char* getMessage() const throw() { return message.c_str(); }
	int getErrorCode() const throw() { return errorCode; }

};

#endif