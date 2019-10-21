import socket

if __name__=='__main__':
	c=socket.socket()
	host=socket.gethostname()#服务器主机，此处服务器和客户端再同一电脑
	port=12345#服务器端口号
	c.connect((host,port))
	print(c.recv(1024))
	c.close()