#coding=utf-8
import pickle
f=open("banner.p",'r')
obj = pickle.load(f)
for item in obj:
	print "".join(map(lambda p: p[0]*p[1], item))
#对 item中的每一个元素进行p处理，组成一个列表，把他们连接起来