/*
 * ErrorWriter.h
 *
 *  Created on: 14.12.2019
 *      Author: Fromm
 */

#ifndef ERRORWRITER_H_
#define ERRORWRITER_H_

#include <string>
#include <iostream>

class ErrorWriter
{
private:
	/**
	 *  \param A reference object of ostream.
	 */
	std::ostream& m_out;
public:
	/**
	 * \brief Constructor
	 * \param [in] stream : A reference object of ostream. 
	 */
	ErrorWriter(std::ostream& stream = std::cerr);
	/**
	 * \brief Functor for writing the data
	 * \details Could also be a specific function
	 * \note Real advantage comes with templated functions or classes, which will allow interchanging function pointers and functors
	 */
	void operator()(std::string message);
	/**
	 *  \brief Destructor
	 */
	~ErrorWriter();
};

#endif /* ERRORWRITER_H_ */
