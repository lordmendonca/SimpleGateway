
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CUARTPORT.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


#include <iostream>
using namespace std;
#include "CUartPort.h"
#include "CRingBuffer.h"

std::set<CUartPort::port_t> CUartPort::m_occupiedPorts;

CPort::portState_t CUartPort::isPortAvailable(CUartPort::port_t port)
{
	if(1 == m_occupiedPorts.count(port))
		return CPort::NOTAVAILABLE;
	else
		return CPort::AVAILABLE;
}

CUartPort::CUartPort(port_t port, uint32_t baudrate, uint8_t bits,
		parity_t parity, uint8_t stopbits, uint16_t bufferSizeRx,
		uint16_t bufferSizeTx, uint16_t packageSize) : CPort(bufferSizeTx, bufferSizeRx, packageSize), m_uartPackageSize{packageSize}
{
	m_occupiedPorts.insert(port);
}

RC_t CUartPort::writeByte_hw(uint8_t data)
{
	cout << "Just wrote to UART hardware: " << data << endl;
	return RC_SUCCESS;
}

RC_t CUartPort::readByte_hw(uint8_t &data)
{
	static uint8_t fakeData = 'a';
	static uint16_t counter = 0;

	counter++;

	if (counter >= 20) return RC_NODATA;

	data = fakeData++;

	cout << "Just read from UART hardware: " << data << endl;

	return RC_SUCCESS;
}

RC_t CUartPort::writePackage_hw(CRingBuffer dataBuf)
{
	cout << "Just wrote to UART hardware: " << dataBuf << endl;

	return RC_SUCCESS;
}
RC_t CUartPort::readPackage_hw(CRingBuffer& dataBuf)
{
	const uint16_t packageCount = 21; /* Simulating streaming data. */
	string fakeString = "advanced_software_design_techniques."; /* Fake stream data. */
	static uint16_t counter = 0; /* Counting the packages. */
	static uint16_t strPosition = 0; /* Position counter for the fakeString. */

	counter++;
	counter = counter % packageCount;
	if (0 == counter)
		return RC_NODATA;

	while(RC_SUCCESS == dataBuf.write(fakeString.at(strPosition))) /* Writing fakeString bytes into a buffer packet. */
	{
		strPosition = (strPosition + 1) % fakeString.size();
	}

	cout << "Just read from UART hardware: " << dataBuf << endl;;

	return RC_SUCCESS;
}

uint16_t CUartPort::getDriverPackageSize() const
{
	return m_uartPackageSize;
}
