import socket
from Marshalling import *
from DateTime import DateTime
from Flight import Flight
from Config import *
import random

class Communication_UDP:
    def __init__(self, socket, ip, port, invocation_semantics):
        self.my_socket = socket
        self.ipAddress = ip
        self.port = port
        self.my_socket.settimeout(1)
        self.invocation_semantics = invocation_semantics

        self.simulate_loss_of_packets = True

    def EstablishConnection(self):
        if self.Send([0,self.invocation_semantics]) != False:
            return True
        return False

    def QueryByID(self,id):
        item = self.Send([2,1,INT,id])
        if item != False:
            item = Unpack(item)
            print(item[2].Get_printable_string())
        else:
            print('ERROR MESSAGE: There is no flight with ID:',str(id))

    def QueryNumberOfFlights(self):
        item = self.Send([5,0])
        if item != False:
            item = Unpack(item)
            print('Number of flight currently in the system:',item[2])
        else:
            print("ERROR MESSAGE: There are curently no flights")

    def GiveLike(self, n_of_likes_user_has_given):
        item = self.Send([6,1,INT,n_of_likes_user_has_given])
        if item != False:
            item = Unpack(item)
            print('You have given a like number',item[2])

    def QueryBySourceAndDest(self,source,dest):
        item = self.Send([1,2,STR,STR,source,dest])
        if item != False:
            return item

    def CheckResponse(self, request, reply):
        if len(reply) >= 3 and reply[2] == ERROR:
            return False
        return True

    def CheckSendingMessage(self,message):
        return True

    def Send(self, message):
        if not self.CheckSendingMessage(message):
            return False

        if self.invocation_semantics == AT_LEAST_ONCE:
            return self.Send_at_least(message)
        else:
            return self.Send_at_most(message)

    def Send_at_least(self,message):
        while True:
            try:
                # Send data
                if self.simulate_loss_of_packets and random.randrange(0, 2) == 0:
                    self.my_socket.sendto(Pack(message), (self.ipAddress, self.port))
                elif self.simulate_loss_of_packets == False:
                    self.my_socket.sendto(Pack(message), (self.ipAddress, self.port))
                # Receive response
                data, server = self.my_socket.recvfrom(4096)
                if self.CheckResponse(message,data):
                    return data
                else:
                    return False

            except socket.timeout as timeout:
                print('timeout')
            except Exception as exc:
                if exc != socket.timeout:
                    print(exc)


    def Send_at_most(self,message):
        return self.Send_at_least(message)