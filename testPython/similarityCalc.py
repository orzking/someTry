import math
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
