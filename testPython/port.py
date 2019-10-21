#encoding=utf-8
import tkinter as tk
from tkinter import ttk
import serial as uart
import serial.tools.list_ports as ports
import re
import time
import threading
from threading import Thread



global com


##获取串口列表
def getSerialList():
	comlist=list(ports.comports())##获取可用串口信息
	if len(comlist)==0:
		print("无可用串口")##debug
	else:
		for i in range(0,len(comlist)):
			tempStr=str(comlist[i])
			comlist[i]=re.findall(r'[(](.+?)[)]',tempStr)##从串口信息截取串口号
		return comlist
##串口接收
def serialRecv(ser):
	try:
		print("seial is listing...")
		buff = ser.readline().decode();
		return buff
	except:
		print("serialRecv break")
	
#串口发送
def DWritePort(ser,text):
	try:
		result = ser.write(text.encode())  # 写数据
		print("tx:"+text)
	except:
		print("串口发送失败")
	return result



if __name__=='__main__':
	win=tk.Tk()
	win.geometry("400x150")
	win.title("serial")

	##串口选择
	comSelect=ttk.Combobox(win,height=1,width=6)
	comSelect["state"]="readonly"
	comSelect.place(x=0,y=0)
	##波特率配置
	baudSelect=ttk.Combobox(win,height=1,width=6)
	baudSelect["values"]=("1200","2400","4800","9600","19200","38400","57600","115200")
	baudSelect["state"]="readonly"
	baudSelect.current(3)
	baudSelect.place(x=80,y=0)
	##打开串口按钮
	btnOpen=tk.Button(win,text="打开串口",fg="black")
	btnOpen.place(x=240,y=0)
	##发送区
	textTx=tk.Text(win,height=1,width=30)
	textTx.place(x=0,y=40)	
	##发送按钮
	btnTx=tk.Button(win,text="发送",fg="black")
	btnTx.place(x=230,y=40)
	def comSelect_update():
		if str(comSelect["state"])!="disabled":
			comSelect["values"]=getSerialList()
	def comSelect_update_e(e):
		comSelect_update()
	comSelect.bind("<Button-1>",comSelect_update_e)
	comSelect_update()#启动时查询可用串口，更新列表
	if len(comSelect["values"])!=0:
		comSelect.current(0)#选择默认串口
		
	def comRecv():
		while True:
			buff=serialRecv(com)
			print(buff)
		
	def btnOpen_b1(e):
		global com
		if e.widget["text"]=="打开串口":
			try:
				com=uart.Serial(comSelect.get(),baudSelect.get(),8)
				print(com)#debug
				e.widget["text"]="关闭串口"
				comSelect["state"]="disabled"
				baudSelect["state"]="disabled"
				serialThread=Thread(target=comRecv)#创建接收进程
				serialThread.setDaemon(True);
				serialThread.start()#启动进程
			except:
				print("串口打开失败")##debug
		
		else:
			com.close()
			e.widget["text"]="打开串口"
			comSelect["state"]="readonly"
			baudSelect["state"]="readonly"
	btnOpen.bind("<Button-1>",btnOpen_b1)
	
	def btnTx_b1(e):
		temp=textTx.get("1.0","end")
		try:
			DWritePort(com,temp)
		except:
			print("串口发送失败")
	btnTx.bind("<Button-1>",btnTx_b1)
	
	win.mainloop()

