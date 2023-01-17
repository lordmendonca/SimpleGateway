
#include <iostream>
using namespace std;


#include "CCanPort.h"

std::set<CCanPort::port_t> CCanPort::m_occupiedPorts;

CPort::portState_t CCanPort::isPortAvailable(CCanPort::port_t port)
{
	if(1 == m_occupiedPorts.count(port))
		return CPort::NOTAVAILABLE;
	else
		return CPort::AVAILABLE;
}

CCanPort::CCanPort(port_t port, uint32_t baudrate,
		uint16_t bufferSizeRx, uint16_t bufferSizeTx, uint16_t packageSize) : CPort(bufferSizeTx, bufferSizeRx), m_canPackageSize{packageSize}
{
	m_occupiedPorts.insert(port);
}
RC_t CCanPort::writeByte_hw(uint8_t data)
{
	cout << "Just wrote to CAN hardware: " << data << endl;
	return RC_SUCCESS;
}
RC_t CCanPort::readByte_hw(uint8_t &data)
{
	static uint8_t fakeData = 'A';

	static uint16_t counter = 0;

	counter++;

	if (counter >= 20) return RC_NODATA;

	data = fakeData++;

	cout << "Just read from CAN hardware: " << data << endl;

	return RC_SUCCESS;
}

RC_t CCanPort::writePackage_hw(CRingBuffer dataBuf)
{
	cout << "Just wrote to CAN hardware: " << dataBuf << endl;

	return RC_SUCCESS;
}
RC_t CCanPort::readPackage_hw(CRingBuffer& dataBuf)
{
	const uint16_t packageCount = 6; /* Simulating streaming data. */
	string fakeString = "ADVANCED_SOFTWARE_DESIGN_TECHNIQUES."; /* Fake stream data. */
	static uint16_t counter = 0; /* Counting the packages. */
	static uint16_t strPosition = 0;  /* Position counter for the fakeString. */

	counter++;
	counter = counter % packageCount;
	if (0 == counter)
		return RC_NODATA;

	while(RC_SUCCESS == dataBuf.write(fakeString.at(strPosition))) /* Writing fakeString bytes into a buffer packet. */
	{
		strPosition = (strPosition + 1) % fakeString.size();
	}

	cout << "Just read from CAN hardware: " << dataBuf << endl;;

	return RC_SUCCESS;
}

uint16_t CCanPort::getDriverPackageSize() const
{
	return m_canPackageSize;
}
