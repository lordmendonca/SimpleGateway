
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPORT.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


/* System Include Files. */
#include <iostream>
using namespace std;
/* Project include files. */
#include "CPort.h"
#include "err_hdl.h"

CPort::CPort(uint16_t txSize, uint16_t rxSize, uint16_t packageSize)
					: m_ringBufferTx(txSize), m_ringBufferRx(rxSize)
{
}

RC_t CPort::writeByteStream(string const& data)
{
	try
	{
		for (uint16_t i = 0; i < data.length(); i++)
		{
			/* Handling buffer overflow. */
			if(RC_BUFFEROVERFLOW == m_ringBufferTx.write(data[i])) /* A byte is written into the buffer only if successful. */
				throw CppErrorHandler("Insufficient Buffer Size.", "Port B");
		}
		/* Fire TX interrupt. */
		portTx_isr();
	}
	/* Cathcing when buffer overflow. */
	catch(CppErrorHandler& err)
	{
		cErrHdlr.report(CEH_BUFFEROVERRUN);
		err.report();
		terminate();
	}

	return RC_SUCCESS;
}

RC_t CPort::readByteStream(string &data)
{
	string dataFromDriver="";

	RC_t result = RC_ERROR;
	do
	{
		uint8_t ldata = 0;
		result = m_ringBufferRx.read(ldata);
		if (RC_SUCCESS == result)
			dataFromDriver += (char)ldata; /* Reading a whole string by appending character-by-character. */
	} while (RC_SUCCESS == result);

	data = dataFromDriver;

	return RC_SUCCESS;
}

RC_t CPort::portTx_isr()
{
	RC_t result = RC_ERROR;
	RC_t writeResult = RC_ERROR;
	int packageSize = 0; /* Packing counter. */
	CRingBuffer dataBuf(getDriverPackageSize()); /* Creating a ring buffer of driver data packing capacity for transmission. */
	string portType = (getDriverPackageSize() == CAN_DEFAULTPACKAGESIZE)? "CAN" : ((getDriverPackageSize() == UART_DEFAULTPACKAGESIZE)? "UART" : "UNKOWN PORT.");
	cout << endl << "Writing " << getDriverPackageSize() << " byte(s) packages to " << portType << "." << endl;
	do
	{
		uint8_t data;
		/* Data packaging logic. */
		while(packageSize < getDriverPackageSize()) 
		{
			data = 0;
			result = m_ringBufferTx.read(data); /* Read until end of data from buffer, indicated by an underflow. */
			if (RC_SUCCESS == result)
			{
				writeResult = dataBuf.write(data); /* Data is packaged. Returns success only when actually written. */
			}
			packageSize++;
		}
		if(RC_SUCCESS == writeResult)
		{
			writePackage_hw(dataBuf); 	/* Transmit the packaged buffer. */
			dataBuf.clear(); /* Clear Buffer*/
			packageSize = 0; /* Reset packing counter.*/
			writeResult = RC_ERROR; /* Reset teh result of writing to error.*/
		}

	} while (RC_SUCCESS == result);
	return RC_SUCCESS;
}

RC_t CPort::portRx_isr()
{
	RC_t result = RC_ERROR;
	CRingBuffer dataBuf(getDriverPackageSize()); /* Creating a ring buffer of driver data packing capacity for reception. */
	string portType = (getDriverPackageSize() == CAN_DEFAULTPACKAGESIZE)? "CAN" : ((getDriverPackageSize() == UART_DEFAULTPACKAGESIZE)? "UART" : "UNKOWN PORT.");
	cout << endl << "Reading " << getDriverPackageSize() << " byte(s) packages from " << portType << "." << endl;
	try
	{
	do
	{
		uint8_t data = 0;
		result = readPackage_hw(dataBuf); /* Read the data from HW into the buffer. */
		if (RC_SUCCESS == result)
		{
			while(dataBuf.read(data) == RC_SUCCESS) /* Read the buffer data byte-by-byte to be added to the reception buffer. */
			{
				/* Handling buffer overflow. */
				if(RC_BUFFEROVERFLOW ==  m_ringBufferRx.write(data)) /* A byte is written into the buffer only if successful. */
					throw CppErrorHandler("Insufficient Buffer Size.", "Port A");
			}
		}

	} while (RC_SUCCESS == result);
	}
	/* Catching when buffer overflow. */
	catch(CppErrorHandler& err)
	{
		cErrHdlr.report(CEH_BUFFEROVERRUN);
		err.report();
		terminate();
	}

	return RC_SUCCESS;
}
