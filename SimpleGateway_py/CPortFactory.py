
from CPort import CPort
from CUartPort import CUartPort
from CCanPort import CCanPort

from CUartPort import UART_DEFAULTBUFFERSIZE, UART_DEFAULTPACKAGESIZE
from CCanPort import CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTPACKAGESIZE

class CPortFactory:
    def createCanPort(self, port, baudrate, RxBufferSize, TxBufferSize, packageSize) -> CCanPort:
        # port          -> The hardware port to be used.
        # baudrate      -> The baudrate of the device. Check the hardware manual for valid values.
        # RxBufferSize  -> The size of the Reception buffer.
        # TxBufferSize  -> The size of the Transmission buffer.
        # packageSize   -> Packaging capacity of the port.
        # return - An object of type CCanPort.
        canPort = CCanPort(port, baudrate, RxBufferSize, TxBufferSize, packageSize)
        return canPort
    
    def createUartPort(self, port, baudrate, bits, parity, stopbits, RxBufferSize, TxBufferSize, packageSize) -> CUartPort:
        # port          -> The hardware port to be used.
        # baudrate      -> The baudrate of the device. Check the hardware manual for valid values.
        # bits          -> The number of data bits, typically 7 or 8.
        # parity        -> Parity, ODD, EVEN or NONE.
        # stopbits      -> TNumber of Stopbits, 1 or 2.
        # RxBufferSize  -> The size of the Reception buffer.
        # TxBufferSize  -> The size of the Transmission buffer.
        # packageSize   -> Packaging capacity of the port.
        # return - An object of type CUartPort.
        uartPort = CUartPort(port, baudrate, bits, parity, stopbits, RxBufferSize, TxBufferSize, packageSize)
        return uartPort

    def createPort(self, port):
        # port          -> The hardware port to be used.
        if port == 'CAN':
            # return - An object of type CCanPort.
            return self.createCanPort('CanPort 1', 100, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTPACKAGESIZE)
        elif port == 'UART':
            # return - An object of type CUartPort.
            return self.createUartPort('UartPort 1', 115200, 8, 1, 1, UART_DEFAULTBUFFERSIZE, UART_DEFAULTBUFFERSIZE, UART_DEFAULTPACKAGESIZE)

'''cpf = CPortFactory()
cp = cpf.createCanPort('NONE', 115200, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTBUFFERSIZE)
data = cp.readByte_hw()
print(data)
data = cp.readByte_hw()
print(data)
data = cp.readByte_hw()
print(data)

cpf2 = CPortFactory()
cp = cpf2.createCanPort('NONE', 115200, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTBUFFERSIZE)
data = cp.readByte_hw()
print(data)
data = cp.readByte_hw()
print(data)
data = cp.readByte_hw()
print(data)

cpf3 = CPortFactory()
up = cpf.createUartPort('NONE', 115200, 8, 'NOPARITY', 1, UART_DEFAULTBUFFERSIZE, UART_DEFAULTBUFFERSIZE)
data = up.readByte_hw()
print(data)
data = up.readByte_hw()
print(data)
data = up.readByte_hw()
print(data)'''