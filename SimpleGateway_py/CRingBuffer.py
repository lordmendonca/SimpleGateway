
class CRingBuffer:
    def __init__(self, size : int) -> None:
            # Initialisor call : size -> The size of the buffer.
            # return - None
            self.size          =   size         # The size of the Ring Buffer.
            self.readIdx       =   0            # The index to read the buffer that points to most recent position on the buffer.
            self.writeIdx      =   0            # The index to write the buffer that points to most recent position on the buffer.
            self.fillLevel     =   0            # The incremental capacity indicator when the buffer is either written into or read from.
            self.buffer        =   [None]*size  # List that store bytes of data upto size 'size'.

    def clear(self) -> str:                     # Method used to clear the buffer.
        # return - A string containing the status of clear operation.
        self.readIdx    = 0
        self.writeIdx   = 0
        self.fillLevel  = 0
        return 'RC_SUCCESS'                     # RC_SUCCESS	- Clearing the buffer was successful.
    
    def BufferSize(self) -> int:                # Method to read the buffer size
        # return -  the size of the buffer.         
        return self.size                        

    def read(self) -> list:                     # Method used to read the content from the buffer.
        # return - A list containing the data that was read and the status of read operation.
        if self.fillLevel > 0:
            dataRead = self.buffer.pop(self.readIdx)
            self.buffer.insert(self.readIdx,None)
            self.readIdx = self.readIdx + 1
            self.readIdx = self.readIdx % self.size
            self.fillLevel = self.fillLevel - 1
            data = [dataRead, 'RC_SUCCESS']     # dataRead -> A byte of data that was read from buffer.
            return data                         # RC_SUCCESS            - Reading from buffer was successful.
        else:
            data = [None, 'RC_BUFFERUNDERFLOW']
            return data                         # RC_BUFFERUNDERFLOW    - The buffer was empty.

    def write(self,dataWrite) -> str:           # Method used to write the content into the buffer.
        # return - A string containing the status of write operation.
        if self.fillLevel < self.size:
            self.buffer.pop(self.writeIdx)
            self.buffer.insert(self.writeIdx,dataWrite) # dataWrite -> A byte of data that has to be written into the buffer.
            self.writeIdx = self.writeIdx + 1
            self.writeIdx = self.writeIdx % self.size
            self.fillLevel = self.fillLevel + 1
            return 'RC_SUCCESS'                 # RC_SUCCESS        - Reading from buffer was successful.
        else:
            return 'RC_BUFFEROVERFLOW'          # RC_BUFFEROVERFLOW - The buffer was overflown.

'''def CRB_test():
    e = CRingBuffer(3)
    #print()
    bufferIn = 1
    returnMsg = e.write(bufferIn)
    #print(returnMsg)
    returnMsg = e.read()
    #print(returnMsg)
    #print()

    bufferIn = 2
    returnMsg = e.write(bufferIn)
    #print(returnMsg)
    bufferIn = 3
    returnMsg = e.write(bufferIn)
    #print(returnMsg)
    #print()
    e.clear()
    #print()

    print('-')
    bufferIn = 4
    returnMsg = e.write(bufferIn)
    #print(returnMsg)
    bufferIn = 5
    returnMsg = e.write(bufferIn)
    #print(returnMsg)
    returnMsg = e.read()
    #print(returnMsg)
    bufferIn = 6
    returnMsg = e.write(bufferIn)
    #print(returnMsg)
    bufferIn = 7
    returnMsg = e.write(bufferIn)
    #print(returnMsg)
    print('--')

    returnMsg = e.read()
    print(returnMsg)
    returnMsg = e.read()
    print(returnMsg)
    returnMsg = e.read()
    print(returnMsg)
    returnMsg = e.read()
    print(returnMsg)

def main():
    print('Test for Ring Buffer')
    CRB_test()

if __name__ == '__main__':
    main()'''
