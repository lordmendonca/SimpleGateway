
from CGateway import CGateway
from CPortFactory import CPortFactory

print('CONFIGURE YOUR GATEWAY.')
print('Choose Ports as CAN or UART')

portA = input('Define Port A : ')
portB = input('Define Port B : ')

cpf = CPortFactory()

pA = cpf.createPort(portA)
pB = cpf.createPort(portB)

g = CGateway(pA, pB)
g.transmitFromAToB()

print('YOUR GATEWAY WAS SUCCESSFULLY CONFIGURED.')