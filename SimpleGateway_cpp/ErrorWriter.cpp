/*
 * ErrorWriter.cpp
 *
 *  Created on: 14.12.2019
 *      Author: Fromm
 */


#include <iostream>
#include <fstream>
using namespace std;

#include "ErrorWriter.h"

ErrorWriter::ErrorWriter(std::ostream& stream) : m_out(stream)
{
}


void ErrorWriter::operator ()(std::string message)
{
	m_out << message << endl;
}

ErrorWriter::~ErrorWriter()
{
}
