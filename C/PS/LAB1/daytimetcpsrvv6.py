# Echo server program
import socket
import datetime
import string
import array

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 13              # Arbitrary non-privileged port

try:
    s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen(1)
	
    while True:
        conn, addr = s.accept()
        print('Connected by', addr)
        data = conn.recv(1024)
        today = datetime.datetime.today()
        print( today.ctime())
        data1 = bytearray(today.ctime(),encoding="utf8")
        conn.send(data1)
    #    print("Data received: %s : And send: %s " % (data, data1))
        print("Data received: " + str(data) + ": And send: " + str( data1) )
        conn.close()

except socket.error as e:
    print ("Socket error({0}): {1}".format(e.errno, e.strerror))

except KeyboardInterrupt:
    print ("Closing server")
    conn.close()

except:
    print ("Unexpected error:", sys.exc_info()[0])
    raise
