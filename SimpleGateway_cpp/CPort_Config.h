/*
 * CPort_Config.h
 *
 *  Created on: 05-Feb-2022
 *      Author: JASON
 */

#ifndef CPORT_CONFIG_H_
#define CPORT_CONFIG_H_
/**
 *  \brief Importing all port related includes and configurations.
 */
#include "CPort.h"
#include "CUartPort.h"
#include "CCanPort.h"
#include "CUartPort_Config.h"
#include "CCanPort_Config.h"
/**
 *  \brief Maximum number of allowed UART channels in a gateway.
 */
#define PORT_ASCLINMAX 4
/**
 *  \brief Maximum number of allowed CAN channels in a gateway.
 */
#define PORT_CANNMAX 2

#endif /* CPORT_CONFIG_H_ */
