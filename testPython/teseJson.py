import os
import json
import math

dirpath=os.path.dirname(__file__)
idDataFile=dirpath+r'\iddata.json'
idNameFile=dirpath+r'\idname.json'

def is_id_same(jsonLine,eig):
    try:
        eig_saved=json.loads(jsonLine)
    except:
        print("特征值文件格式错误")
    if(eig['id']==eig_saved['id']):
        print('id: ',eig['id'],' is exist ,data coverage!')
        return True
    else:
        return False

#获取保存位置
def get_put_pos(iddatafile,eig):
    pos=0
    if(False==os.path.exists(iddatafile)):
        f=open(iddatafile,'w')
        f.close()
        return 0
    f=open(iddatafile,'r')
    line=f.readline()
    while(line):
        #print("line=",line.encode())
        #print("tell=",f.tell())
        if(is_id_same(line,eig)):
            break
        line=f.readline()
    pos=f.tell()
    if(line):#find same ID
        pos-=len(line.encode())+1# home tell
    f.close()
    #print("pos=",pos)
    return pos

#保存特征值，每条id数据用一行json保存，避免读入整个json文件，每条id数据需要长度相同
def put_iddata(iddatafile,eig):
    pos=get_put_pos(iddatafile,eig)
    f=open(iddatafile,'r+')
    f.seek(pos)
    jsonStr=json.dumps(eig)
    jsonStr+='\n'
    f.write(jsonStr)
    f.close()
    return
#计算余弦相似度
def similarityCos(model,sample):
    xx = yy = xy = similarity=0.0
    for a,b in zip(model,sample):
        xx+=a*a
        yy+=b*b
        xy+=a*b
    if(xx>0):
        if(yy>0):
            similarity=xy/(math.sqrt(xx)*math.sqrt(yy))
    return similarity
def larger(a,b):
    if a>b:
        return a
    else:
        return b
#根据特征值获取id 和相似度
def get_id_by_data(iddatafile,data):
    #TODO:
    similarity=0.0
    id=None
    if(False==os.path.exists(iddatafile)):
        return None
    f=open(iddatafile,'r')
    line=f.readline()
    while(line):
        similarityOld=similarity
        eig=json.loads(line)
        sample=[int(strhex,16) for strhex in data]
        model0=[int(strhex,16) for strhex in eig['data0']]
        model1=[int(strhex,16) for strhex in eig['data1']]
        model2=[int(strhex,16) for strhex in eig['data2']]
        model3=[int(strhex,16) for strhex in eig['data3']]
        similarity=larger(similarity,similarityCos(model0,sample))
        similarity=larger(similarity,similarityCos(model1,sample))
        similarity=larger(similarity,similarityCos(model2,sample))
        similarity=larger(similarity,similarityCos(model3,sample))
        if similarityOld < similarity:
            id=eig['id']
        line=f.readline()
    return id,similarity


#保存姓名，id姓名用一个json文件保存
def put_idname(idnamefile,idname):
    if(False==os.path.exists(idnamefile)):
        f=open(idnamefile,'w')
        nametable=[]
        nametable.append(idname)
        json.dump(nametable,f,ensure_ascii=False)
        f.close()
        return
    f=open(idNameFile,'r')
    nametable=json.load(f)
    for record in nametable:
        if record['id']==idname['id']:
            record['name']=idname['name']
            break
    else:
        nametable.append(idname)
    f.close()
    f=open(idnamefile,'w')
    json.dump(nametable,f,ensure_ascii=False)
    f.close()


#通过id获取姓名
def get_name(idnamefile,id):
    if(False==os.path.exists(idnamefile)):
        return None
    f=open(idNameFile,'r')
    nametable=json.load(f)
    for record in nametable:
        if record['id']==id:
            return record['name']
    else:
        return None

if __name__=='__main__':
    data0=[str(x%100).zfill(2) for x in range(1,256)]
    data1=[str((x+1)%100).zfill(2) for x in range(1,256)]
    data2=[str((x+2)%100).zfill(2) for x in range(1,256)]
    data3=[str((x+3)%100).zfill(2) for x in range(1,256)]
    data4=[str((x+4)%100).zfill(2) for x in range(1,256)]
    data5=[str((x+5)%100).zfill(2) for x in range(1,256)]
    data6=[str((x+6)%100).zfill(2) for x in range(1,256)]
    data7=[str((x+7)%100).zfill(2) for x in range(1,256)]
    data8=[str((x+8)%100).zfill(2) for x in range(1,256)]
    data9=[str((x+9)%100).zfill(2) for x in range(1,256)]
    data10=[str((x*2)%100).zfill(2) for x in range(1,256)]
    data11=[str((x*3)%100).zfill(2) for x in range(1,256)]
    data12=[str((x*4)%100).zfill(2) for x in range(1,256)]
    data13=[str((x*5)%100).zfill(2) for x in range(1,256)]
    data14=[str((x*6)%100).zfill(2) for x in range(1,256)]
    data15=[str((x*7)%100).zfill(2) for x in range(1,256)]

    eig_test0={'id':'001','data0':data0,'data1':data1,'data2':data2,'data3':data3}
    eig_test1={'id':'002','data0':data4,'data1':data5,'data2':data6,'data3':data7}
    eig_test2={'id':'003','data0':data8,'data1':data9,'data2':data10,'data3':data11}
    eig_test3={'id':'111','data0':data12,'data1':data13,'data2':data14,'data3':data15}
    idname0={'id':'001','name':'张三'}
    idname1={'id':'002','name':'李四'}
    idname2={'id':'003','name':'王五'}
    put_iddata(idDataFile,eig_test0)
    put_iddata(idDataFile,eig_test1)
    put_iddata(idDataFile,eig_test2)
    put_iddata(idDataFile,eig_test1)
    put_iddata(idDataFile,eig_test3)
    put_idname(idNameFile,idname0)
    put_idname(idNameFile,idname1)
    put_idname(idNameFile,idname2)
    print(get_name(idNameFile,'002'))
    idname1={'id':'002','name':'李白'}
    put_idname(idNameFile,idname1)
    id,similarity=get_id_by_data(idDataFile,data9)
    print(id)
    print(get_name(idNameFile,id))





