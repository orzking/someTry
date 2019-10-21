import socket

if __name__=='__main__':
	s=socket.socket()
	host=socket.gethostname()
	port=12345
	
	s.bind((host,port))
	s.listen(5)
	while True:
		c,addr=s.accept()
		print("addr="+str(addr))
		print(c)
		c.send('hello socket'.encode())
		c.close()