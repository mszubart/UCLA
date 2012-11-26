#ifndef UEXCEPTION_H
#define UEXCEPTION_H

#include <exception>

namespace UCLA{

	class UException: public std::exception
	{
	public:
		UException(const char *what="unknown"): _what(what){}

		virtual const char *what() const throw(){
			return this->_what;
		}

	private:
		const char *_what;
	};
}

#endif // UEXCEPTION_H
