/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CCANPORT.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CCANPORT_H
#define CCANPORT_H

#include "global.h"
#include "CPort.h"
#include "CRingBuffer.h"
#include "CCanPort_Config.h"
#include <set>

class CCanPort : public CPort {

public:
    /**
     *  \brief Enum : port_t   : CAN ports.
     */
    enum port_t{
    	CAN1,		/**< \brief CAN Port 1. */
		CAN2, 		/**< \brief CAN Port 2. */
		NONE,		/**< \brief default value no valid port. */
    };
    /**
     * \brief Constructor - Will initialize the peripheral port and setup the RX and TX buffers.
     *
     *  Constructor - Will initialize the peripheral port and setup the RX and TX buffers.
     *  Please check the hardware limitations to ensure proper configuration parameters.
     *
     *  \param port_t port = NONE			: IN	The hardware port to be used.
     *  \param uint16_t baudrate = CAN_DEFAULTBAUDRATE	: IN	The baudrate of the device. Check the hardware manual for valid values.
     *  \param uint16_t bufferSizeRx = CAN_DEFAULTBUFFERSIZE : IN 	Size of the Receive Buffer.
     *  \param uint16_t bufferSizeTx = CAN_DEFAULTBUFFERSIZE : IN Size of the Transmit Buffer.
     *  \param uint16_t packageSize = CAN_DEFAULTPACKAGESIZE : IN Packaging capacity of the port.
     */
    CCanPort(port_t port = NONE,
             uint32_t baudrate = CAN_DEFAULTBAUDRATE,
			 uint16_t bufferSizeRx = CAN_DEFAULTBUFFERSIZE,
			 uint16_t bufferSizeTx = CAN_DEFAULTBUFFERSIZE,
			 uint16_t packageSize = CAN_DEFAULTPACKAGESIZE
			 );
    /**
     *  \brief Method that checks if the CAN port to be accessed is already occupied or not.
	 * \details This is a static member function.
     *  \param [in] port The CAN port that must be accessed, provided by CCanPort::port_t.
     *  \return Returns the state of the port to be accessed, provided by CPort::portState_t.
     */	
    static CPort::portState_t isPortAvailable(CCanPort::port_t port);
private:
	/**
	 *  \param A set of occupied CAN ports. 
	 * \details This is a static member attribute.
	 */
    static std::set<CCanPort::port_t> m_occupiedPorts;
	/**
	 *  \param The packaging capacity of a CAN port.
	 */
    uint16_t m_canPackageSize;
    /**
     * \brief Sends one Byte to the hardware
     * \note The function is non-blocking. In case the hardware is occupied, an error code will be returned.
     *       Therefore the function preferably should be called through an ISR
     * \param [in] data	: Byte to be transmitted
     * \return RC_t:
     * 		 RC_SUCCESS - byte was transmitted,
     * 		 RC_PERIPHERALOCCUPIED - peripheral was occupied, no data was transmitted, must be re-send
     */
    RC_t writeByte_hw(uint8_t data);
    /**
     * \brief Receive one Byte from the hardware
     * \note The function is non-blocking. In case the hardware is empty, an error code will be returned.
     *       Therefore the function preferably should be called through an ISR
     * \param [in] data	: Byte received
     * \return RC_t:
     * 		 RC_SUCCESS - byte was received,
     * 		 RC_NODATA - peripheral was empty, no data was received, must be re-queried
     */
    RC_t readByte_hw(uint8_t& data);
    /**
     * \brief Sends a packet of data to the hardware.
     *
     * \note The function is non-blocking. In case the hardware is occupied, an error code will be returned.
     *       Therefore the function preferably should be called through an ISR.
     * \param [in] dataBuf : The buffered packet to be transmitted.
     * \return RC_t:
     * 		 RC_SUCCESS - byte was transmitted,
     * 		 RC_PERIPHERALOCCUPIED - peripheral was occupied, no data was transmitted, must be re-send
     */
    RC_t writePackage_hw(CRingBuffer dataBuf);
    /**
     * \brief Receive a packet of data from the hardware
     *
     * \note The function is non-blocking. In case the hardware is empty, an error code will be returned.
     *       Therefore the function preferably should be called through an ISR
     * \param [in] dataBuf : Reference of the buffered packet to be received.
     * \return RC_t:
     * 		 RC_SUCCESS - byte was received,
     * 		 RC_NODATA - peripheral was empty, no data was received, must be re-queried
     */
    RC_t readPackage_hw(CRingBuffer& data);
    /**
     * \brief Getter method to fetch the data packaging capacity of a CAN port.
     *
     * \return Returns the data packaging size of the CAN port.
     */
    uint16_t getDriverPackageSize() const;
};

#endif /* CCANPORT_H */
