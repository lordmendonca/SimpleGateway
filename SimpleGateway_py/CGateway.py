
from CPort import CPort
from CPortFactory import CPortFactory
from CCanPort import CCanPort, CAN_DEFAULTBUFFERSIZE
from CUartPort import CUartPort, UART_DEFAULTBUFFERSIZE

class CGateway:
    def __init__(self, portA : CPort, portB : CPort) -> None:
        self.portA = portA
        self.portB = portB
        #print(type(portA))
        #print(type(portB))

    def transmitFromAToB(self) -> None:
        data = self.portA.readByteStream()
        self.portB.writeByteStream(data[0])
         

'''cp1 = CCanPort('NONE', 115200, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTBUFFERSIZE)
cp2 = CCanPort('NONE', 115200, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTBUFFERSIZE)

cg = CGateway(cp1, cp2)
cg.transmitFromAToB()'''

'''up1 = CUartPort('NONE', 115200, 8, 'NOPARITY', 1, UART_DEFAULTBUFFERSIZE, UART_DEFAULTBUFFERSIZE)
up2 = CUartPort('NONE', 115200, 8, 'NOPARITY', 1, UART_DEFAULTBUFFERSIZE, UART_DEFAULTBUFFERSIZE)
cg2 = CGateway(up1, up2)
cg2.transmitFromAToB()'''

'''cp3 = CCanPort('NONE', 115200, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTBUFFERSIZE)
up3 = CUartPort('NONE', 115200, 8, 'NOPARITY', 1, UART_DEFAULTBUFFERSIZE, UART_DEFAULTBUFFERSIZE)
cg3 = CGateway(up3, cp3)
cg3.transmitFromAToB()'''

'''cp4 = CCanPort('NONE', 115200, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTBUFFERSIZE)
up4 = CUartPort('NONE', 115200, 8, 'NOPARITY', 1, UART_DEFAULTBUFFERSIZE, UART_DEFAULTBUFFERSIZE)
cg4 = CGateway(up4, cp4)
cg4.transmitFromAToB()'''
