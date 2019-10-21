import os
from datetime import datetime
#curdir=os.path.abspath(os.path.curdir)#执行命令的当前绝对路径
pyfiledir = os.path.dirname(__file__)#当前python文件的路径
print(pyfiledir)
fPath=pyfiledir+r'\hello.txt'
print(fPath)
now=datetime.now()
f=open(fPath,'a+')
f.write(str(now))
f.write('my fist file operate by python\n')
f.close()
f=open(fPath,'r')
s=f.read()
print(s)
f.close()