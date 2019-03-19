import socket
from Marshalling import *

class Communication_UDP:
    def __init__(self, socket, ip, port):
        self.my_socket = socket
        self.ipAddress = ip
        self.port = port

    def EstablishConnection(self):
        while True:
            try:
                # Send data
                self.my_socket.sendto(Pack(1), (self.ipAddress, self.port))

                # Receive response
                data, server = self.my_socket.recvfrom(4096)
                if data and data[8] == SYN:
                    self.connectionIdentifier = ConvertBytesToNumber([data[0], data[1], data[2], data[3]])
                    print('Connection established')
                    return True
                if type == 1 and not CheckForInvalidPacket(data, self.connectionIdentifier, self.sequenceNumber):
                    return False

            except socket.timeout as timeout:
                print('timeout')
            except Exception as exc:
                if exc != 'timed out':
                    print(exc)

        return False