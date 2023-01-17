/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPORT.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CPORT_H
#define CPORT_H

#include "global.h"
#include "CRingBuffer.h"
#include "CUartPort_Config.h"
#include "CCanPort_Config.h"
#include <string>

class CPort {
public:
    /**
     *  \brief Enum : portState_t : State representation of availability of any port.
     */
    enum portState_t{
    	AVAILABLE, /**< \brief Port is not occupied. */
		NOTAVAILABLE /**< \brief Port is occupied. */
    };
    /**
     *  \brief Enum : portState_t : State representation of availability of any port.
     */
    enum portDefaults{
    	DEFAULTBUFFERSIZE = 10, /**< \brief Port is not occupied. VALUE = 10.*/
		DEFAULTPACKAGESIZE = 1 /**< \brief Port is occupied. VALUE = 1.*/
    };
protected:
    /**
     *  \brief Ring Buffer for Transmission.
     *  @link aggregationByValue
     *
     * @supplierCardinality 1*/
    CRingBuffer m_ringBufferTx;
    /**
     *  \brief Ring Buffer for Reception.
     *  @link aggregationByValue
     *
     * @supplierCardinality 1*/
    CRingBuffer m_ringBufferRx;
public:
    /**
     *  \brief Parameterized Constructor.
     *  
     *  \param [in] txSize Transmission Ring Buffer Size.
     *  \param [in] rxSize Reception Ring Buffer Size.
     *  \param [in] packageSize Packet Size of the Port.
     */
    CPort(uint16_t txSize = CPort::DEFAULTBUFFERSIZE, uint16_t rxSize = CPort::DEFAULTBUFFERSIZE, uint16_t packageSize = CPort::DEFAULTPACKAGESIZE);
    /**
     * \brief Sends one Byte to the buffer.
     *
     * \param [in] data	: Byte to be transmitted.
     * \return RC_t:
     * 		 RC_SUCCESS - byte was transmitted.
     * 		 RC_BUFFEROVERFLOW - in case of full buffer.
     */
    RC_t writeByteStream(std::string const& data);
    /**
     * \brief Receive one Byte from the buffer.
     *
     * \param [in] data : Byte received.
     * \return RC_t:
     * 		 RC_SUCCESS - byte was received.
     * 		 RC_BUFFERUNDERFLOW - in case of empty buffer.
     */
    RC_t readByteStream(std::string& data);
    /**
     * \brief Will transmit all data from TX buffer to hardware.
     * \return
     * 		RC_SUCCESS - all ok.
     * 		Specific error code in case of error.
     */
    RC_t portTx_isr();
    /**
     * \brief Will transmit all data from RX hardware to buffer.
     * \return
     * 		RC_SUCCESS - all ok.
     * 		Specific error code in case of error.
     */
    RC_t portRx_isr();
private:
    /**
     * \brief Sends one Byte to the hardware
     *
     * \param [in] data : Byte to be transmitted
     * \return RC_t:
     * 		 RC_SUCCESS - byte was transmitted
     * 		 Device specific ErrorCode - in case of error
     */
    virtual RC_t writeByte_hw(uint8_t data) = 0;
    /**
     * \brief Receive one Byte from the hardware
     *
     * \param [in] data : Byte received.
     * \return RC_t:
     * 		 RC_SUCCESS - byte was received.
     * 		 Device specific ErrorCode - in case of error.
     */
    virtual RC_t readByte_hw(uint8_t& data) = 0;
    /**
     * \brief Sends one Packet of data to the hardware.
     *
     * \param [in] dataBuf : The buffered packet to be transmitted.
     * \return RC_t:
     * 		 RC_SUCCESS - Packet was transmitted.
     * 		 Device specific ErrorCode - in case of error.
     */
    virtual RC_t writePackage_hw(CRingBuffer dataBuf) = 0;
    /**
     * \brief Receive one Packet of data from the hardware.
     *
     * \param [in] dataBuf : Reference of the buffered packet to be received.
     * \return RC_t:
     * 		 RC_SUCCESS - byte was received.
     * 		 Device specific ErrorCode - in case of error.
     */
    virtual RC_t readPackage_hw(CRingBuffer& dataBuf) = 0;
    /**
     * \brief Getter method to fetch the data packaging capacity of the port.
     *
     * \return Returns the data packaging size of the port.
     */
    virtual uint16_t getDriverPackageSize() const = 0;
};
/********************
**  CLASS END
*********************/
#endif /* CPORT_H */
