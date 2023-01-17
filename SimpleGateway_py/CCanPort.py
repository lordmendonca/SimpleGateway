
from copy import deepcopy
from CRingBuffer import CRingBuffer
from CPort import CPort

CAN_DEFAULTBUFFERSIZE = 64
CAN_DEFAULTPACKAGESIZE = 8

class CCanPort(CPort):
    fakeData        =   0                                           # Fake byte data.
    counter         =   0                                           # Counting the packages.
    packageCount    =   6                                           # Simulating streaming data.
    fakeString      =   "ADVANCED_SOFTWARE_DESIGN_TECHNIQUES."      # Fake stream data.
    strPosition     =   0                                           # Position counter for the fakeString.
    
    def __init__(self, port, baudrate : int, RxBufferSize : int, TxBufferSize : int, packageSize : int) -> None:
        # Initialisor call : port -> The hardware port to be used.
        # Initialisor call : baudrate -> The baudrate of the device. Check the hardware manual for valid values.
        # Initialisor call : RxBufferSize -> The size of the Reception buffer.
        # Initialisor call : TxBufferSize -> The size of the Transmission buffer.
        # Initialisor call : packageSize -> Packaging capacity of the port.
        # return - None
        self.port           =   port
        self.baudrate       =   baudrate
        self.RxBufferSize   =   RxBufferSize
        self.TxBufferSize   =   TxBufferSize
        self.packageSize    =   packageSize
        CPort.__init__(self, RxBufferSize, TxBufferSize) #invoking the __init__ of the parent class

    def writePackage_hw(self, dataBuf : CRingBuffer) -> str:    # Sends one Packet of data to the hardware.
        # dataBuf -> The buffered packet to be transmitted.
        # return - A string containing the status of the operation.
        # RC_SUCCESS - Packet was transmitted.
        # Device specific ErrorCode - in case of error
        print(f"Just wrote to CAN hardware : ", end='')
        self.printPackage(deepcopy(dataBuf))
        return 'RC_SUCCESS'

    def readPackage_hw(self) -> list:                           # Receive a packet of data from the hardware.
        # return - A list containing the data packet that was read and the status of the operation.
        # RC_SUCCESS - byte was received.
        # Device specific ErrorCode - in case of error
        self.counter = self.counter + 1
        self.counter = self.counter % self.packageCount

        dataBuf = CRingBuffer(self.getDriverPackageSize())

        if 0 == self.counter:
            return [dataBuf, 'RC_NODATA']
        
        loop = True
        while True == loop:
            result = dataBuf.write(self.fakeString[self.strPosition])               # Writing fakeString bytes into a buffer packet.
            if 'RC_SUCCESS' == result:
                self.strPosition = (self.strPosition + 1) % len(self.fakeString)
            else:
                loop = False

        print("Just read from CAN hardware : ", end='')
        self.printPackage(deepcopy(dataBuf))
        return [dataBuf, 'RC_SUCCESS']

    def getDriverPackageSize(self) -> int:  # Method to fetch the data packaging capacity of the port.
        # return - the data packaging size of the port.
        return self.packageSize

    def writeByte_hw(self, data) -> str:                # Sends one Byte to the hardware.
        # data -> Byte to be transmitted.
        # return - A string containing the status of the operation.
        # RC_SUCCESS - byte was transmitted.
        # Device specific ErrorCode - in case of error
        print('Just wrote to CAN Hardware : ')
        print(data)
        return 'RC_SUCCESS'

    def readByte_hw(self) -> list:                      # Receive one Byte from the hardware.
        # return - A list containing the data byte that was read and the status of the operation.
        # RC_SUCCESS - byte was received.
        # Device specific ErrorCode - in case of error
        self.counter = self.counter + 1
        if self.counter >= 20:
            data = [None, 'RC_NODATA']
            return data
        else:
            self.fakeData = self.fakeData + 1
            print('Just read from CAN Hardware : ')
            self.TxRingBuffer.write(self.fakeData)
            data = [self.fakeData, 'RC_SUCCESS']
            print(data)
            return data


'''cp = CCanPort('NONE', 115200, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTPACKAGESIZE)
#data = cp.readByte_hw()
#cp.writeByte_hw(data)
#data = cp.readByte_hw()
#cp.writeByte_hw(data)

data = cp.readPackage_hw()
cp.writePackage_hw(data[0])
data = cp.readPackage_hw()
cp.writePackage_hw(data[0])
data = cp.readPackage_hw()
cp.writePackage_hw(data[0])'''

'''cp2 = CCanPort('NONE', 115200, CAN_DEFAULTBUFFERSIZE, CAN_DEFAULTBUFFERSIZE)
data = cp2.readByte_hw()
print(data)
data = cp2.readByte_hw()
print(data)'''
