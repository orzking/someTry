import re
import os
import sys
import time
import PyQt5
import serial
import threading
from threading import Thread
from time import ctime,sleep
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

class MainWin_t(QWidget):
	def __init__(self):
		#super().__init__()
		QWidget.__init__()
		self.btn1=QPushButton('quit',self)
		self.mainWinInit()
		
	def mainWinInit(self):
		self.resize(500,300)
		self.setWindowTitle('test')
		self.show()
		self.btn1.move(100,100)
		self.btn1.clicked.connect(QCoreApplication.instance().quit)
		self.btn1.show()
	def closeEvent(self,event):
		reply=QMessageBox.question(self,'Message',"Sure to quit?",
						QMessageBox.Yes|QMessageBox.No,QMessageBox.No)
		if reply==QMessageBox.Yes:
			event.accept()
		else:
			event.ignore()
if __name__ == "__main__":
	print("hello")
	app=QApplication(sys.argv)
	mainWin=MainWin_t()
	sys.exit(app.exec_())