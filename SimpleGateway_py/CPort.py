
from abc import ABC, abstractmethod
from CRingBuffer import CRingBuffer

class CPort(ABC):
    def __init__(self, RxBufferSize : int, TxBufferSize : int) -> None:
        # Initialisor call : RxBufferSize -> The size of the Reception buffer.
        # Initialisor call : TxBufferSize -> The size of the Transmission buffer.
        # return - None
        self.RxRingBuffer = CRingBuffer(RxBufferSize)   # Ring Buffer for Reception.
        self.TxRingBuffer = CRingBuffer(TxBufferSize)   # Ring Buffer for Transmission.

    def writeByteStream(self, data : str) -> str:       # Sends one Byte to the buffer.
        # data -> Byte to be transmitted.
        # return - A string containing the status of the operation.
        # RC_SUCCESS        - byte was transmitted.
        # RC_BUFFEROVERFLOW - in case of full buffer.
        result = 'RC_ERROR'
        
        for i in data:
            result = self.TxRingBuffer.write(i)         # writing the 'data' in to the buffer.
        
        # Fire Tx Interrupt
        self.portTx_isr()

        return result

    def readByteStream(self) -> list:                   # Receive one Byte from the buffer.
        # return - A list containing the string data that was read from the buffer and status of the operation.
        # RC_SUCCESS            - byte was transmitted.
        # RC_BUFFERUNDERFLOW    - in case of empty buffer.
        dataFromDriver = ""
        dataRead = []
        # Fire Rx Interrupt
        self.portRx_isr()

        loop = True
        while loop == True:
            dataRead.clear()
            dataRead = self.RxRingBuffer.read()
            if dataRead[1] == 'RC_SUCCESS':
                dataFromDriver += str(dataRead[0])      # Reading a whole string by appending character-by-character.
            else:
                loop = False

        data = [dataFromDriver, 'RC_SUCCESS']
        return data

    @abstractmethod
    def writeByte_hw(self, data) -> str:                # Sends one Byte to the hardware.
        # data -> Byte to be transmitted.
        # return - A string containing the status of the operation.
        # RC_SUCCESS - byte was transmitted.
        # Device specific ErrorCode - in case of error
        pass

    @abstractmethod
    def readByte_hw(self) -> list:                      # Receive one Byte from the hardware.
        # return - A list containing the data byte that was read and the status of the operation.
        # RC_SUCCESS - byte was received.
        # Device specific ErrorCode - in case of error
        pass

    @abstractmethod
    def writePackage_hw(self, dataBuf : CRingBuffer) -> str:    # Sends one Packet of data to the hardware.
        # dataBuf -> The buffered packet to be transmitted.
        # return - A string containing the status of the operation.
        # RC_SUCCESS - Packet was transmitted.
        # Device specific ErrorCode - in case of error
        pass

    @abstractmethod
    def readPackage_hw(self) -> list:                           # Receive a packet of data from the hardware.
        # return - A list containing the data packet that was read and the status of the operation.
        # RC_SUCCESS - byte was received.
        # Device specific ErrorCode - in case of error
        pass

    @abstractmethod
    def getDriverPackageSize(self) -> int:  # Method to fetch the data packaging capacity of the port.
        # return - the data packaging size of the port.
        pass

    def portTx_isr(self) -> None:                           # Will transmit all data from TX buffer to hardware.
        packageSize = 0
        dataBuf = CRingBuffer(self.getDriverPackageSize())
        dataRead = []

        writeResult = 'RC_ERROR'

        loop = True
        while loop == True:
            # Data packaging logic.
            dataBuf.clear()
            while packageSize < self.getDriverPackageSize():
                dataRead.clear()
                dataRead = self.TxRingBuffer.read()             # Read until end of data from buffer, indicated by an underflow.
                if 'RC_SUCCESS' == dataRead[1]:
                    writeResult = dataBuf.write(dataRead[0])    # Data is packaged. Returns success only when actually written.
                    if 'RC_BUFFEROVERFLOW' == writeResult:
                        print('Insufficient Buffer Size at Port B.')
                elif 'RC_BUFFERUNDERFLOW' == dataRead[1]:
                    loop = False
                    break
                packageSize = packageSize + 1
            
            if 'RC_SUCCESS' == writeResult:
                self.writePackage_hw(dataBuf)                   # Transmit the packaged buffer.
                dataBuf.clear()                                 # Clear Buffer
                packageSize = 0                                 # Reset packing counter.
                writeResult = 'RC_ERROR'                        # Reset the result of writing to error.             

    def portRx_isr(self) -> None:                               # Will transmit all data from RX hardware to buffer.
        dataBuf = CRingBuffer(self.getDriverPackageSize())      # Creating a ring buffer of driver data packing capacity for reception.
        dataRead = []
        outerloop = True
        while outerloop == True:
            dataRead.clear()
            dataRead = self.readPackage_hw()                    # Read the data from HW into the buffer.
            if 'RC_SUCCESS' == dataRead[1]:
                dataBuf = dataRead[0]
                innerloop = True
                while True == innerloop:
                    dataRead2 = dataBuf.read()
                    if 'RC_SUCCESS' == dataRead2[1]:
                        result = self.RxRingBuffer.write(dataRead2[0])
                        if 'RC_BUFFEROVERFLOW' == result:
                            print('Insufficient Buffer Size at Port A.')
                            exit()
                    elif 'RC_BUFFERUNDERFLOW' == dataRead2[1]:
                        innerloop = False
            elif 'RC_NODATA' == dataRead[1]:
                outerloop = False
    
    def printPackage(self, dataBuf : CRingBuffer) -> None :     # Prints the content from a ring buffer.
        # dataBuf -> A ring buffer whose content must be printed.
        print('[ ', end='')
        loop = True
        while True == loop:
            dataRead = dataBuf.read()
            if 'RC_SUCCESS' == dataRead[1]:
                print(str(dataRead[0]), end='')
            else:
                loop = False
        print(' ]')



