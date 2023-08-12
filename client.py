import socket

soc = socket.socket()
soc.connect(("127.0.0.1", 9000))
data = soc.recv(1024)
soc.send("Hi(client)".encode("utf8"))
print("Client process", data.decode())