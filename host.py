import socket

s = socket.socket()
s.bind(("0.0.0.0", 9090))
s.listen(5)

print("In ascolto...")

while True:
    conn, addr = s.accept()
    data = conn.recv(1024).decode()
    print("Dispositivo:", data, "da", addr)
    conn.send(b"OK")
    conn.close()
