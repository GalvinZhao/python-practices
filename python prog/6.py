#coding=utf-8
import zipfile,os,re
z = zipfile.ZipFile("channel.zip",'r')
value = 90052
findnothing = re.compile(r'(?<=Next nothing is )\d+').search
dir = os.getcwd()
comments=[]
print dir
while True:
	f = open(dir+'\channel\%s.txt'%value)
	comments.append(z.getinfo('%s.txt'%value).comment)
	line = f.readline()
	matches = findnothing(line)
	if not matches:
		break
	else:
		value = matches.group(0)
print value

print ''.join(comments)
