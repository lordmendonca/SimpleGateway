

/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRINGBUFFER.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>
using namespace std;

//Own Include Files
#include "CRingBuffer.h"
#include "err_hdl.h"

CRingBuffer::CRingBuffer(uint16_t size)
{
	m_fillLevel = 0;
	m_readIdx = 0;
	m_writeIdx = 0;
	try
	{
		/* Handling extreme sizes of a buffer. */
		if(size > CRingBuffer::MAXSIZE)
			throw CppErrorHandler("Too large. Set to default size of 20 bytes.", "BUFFER SIZE");
		else if(size < CRingBuffer::MINSIZE)
			throw CppErrorHandler("Too low. Set to default size of 20 bytes.", "BUFFER SIZE");
		m_size = size;
	}
	catch(CppErrorHandler& err)
	{
		err.report();
		m_size = CRingBuffer::DEFAULT;

	}
	m_pBuffer = new uint8_t[size];
}

CRingBuffer::CRingBuffer(const CRingBuffer& rop)
{
	this->m_fillLevel = rop.m_fillLevel;
	this->m_readIdx = rop.m_readIdx;
	this->m_writeIdx = rop.m_writeIdx;
	this->m_size = rop.m_size;
	this->m_pBuffer = new uint8_t[rop.m_size];
	for(uint16_t idx = 0; idx < m_size; idx++)
	{
		this->m_pBuffer[idx] = rop.m_pBuffer[idx];
	}
}

CRingBuffer::~CRingBuffer()
{
	delete[] m_pBuffer;
}

RC_t CRingBuffer::read(uint8_t& data)
{
	if (m_fillLevel > 0)
	{
		data = m_pBuffer[m_readIdx++];

		m_readIdx %= m_size;
		m_fillLevel--;

		return RC_SUCCESS;
	}
	else
	{
		return RC_BUFFERUNDERFLOW;
	}

}

RC_t CRingBuffer::write(uint8_t data)
{
	if (m_fillLevel < m_size)
	{
		m_pBuffer[m_writeIdx++] = data;

		m_writeIdx %= m_size;
		m_fillLevel++;

		return RC_SUCCESS;
	}
	else
	{
		return RC_BUFFEROVERFLOW;
	}
}

RC_t CRingBuffer::clear()
{
	m_fillLevel = 0;
	m_readIdx = 0;
	m_writeIdx = 0;

	return RC_SUCCESS;
}

std::ostream& operator << (std::ostream& out, CRingBuffer rop)
{
	uint8_t data;
	out << "Package : [ " ;
	while(rop.read(data) ==  RC_SUCCESS)
		out << data;
	out << " ]";
	return out;
}


