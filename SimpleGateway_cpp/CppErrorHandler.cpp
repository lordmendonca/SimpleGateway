/*
 * CppErrorHandler.cpp
 *
 *  Created on: 14.12.2019
 *      Author: Fromm
 */


#include <iostream>
using namespace std;

#include "CppErrorHandler.h"


CppErrorHandler::CppErrorHandler(std::string what, std::string where)
{
	m_what = what;
	m_where = where;
}

void CppErrorHandler::report()
{
	cerr << "ERROR in [" << m_where << "] : " << m_what;
	cerr.flush();
}
