/*
 * CppErrorHandler.h
 *
 *  Created on: 14.12.2019
 *      Author: Fromm
 */

#ifndef CPPERRORHANDLER_H_
#define CPPERRORHANDLER_H_

#include <string>

class CppErrorHandler
{
private:
	/**
	 *  \param  A string that describes the reason for the error.
	 */
	std::string m_what;
	/**
	 *  \param A string that describes where the error occured.
	 */
	std::string m_where;
public:
	/**
	 *  \brief Constructor
	 *  \details Used to create an error message which will be thrown.
	 *  \param [in] what : A string that describes the reason for the error.
	 *  \param [in] where : A string that describes where the error occured.
	 */
	CppErrorHandler(std::string what, std::string where);
	/**
	 *  \brief Method that provides the details of the error after being caught.
	 */
	void report();
};

#endif /* CPPERRORHANDLER_H_ */
