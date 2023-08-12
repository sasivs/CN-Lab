import socket
soc = socket.socket()
soc.bind(("127.0.0.1", 9000))
soc.listen(2)
while(1): 
    client, address = soc.accept()
    print(type(client))
    print(client, address)
    client.send("Hi".encode("utf8"))
    print(client.recv(1024).decode())

print("Server terminated")