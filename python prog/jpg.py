import os,re

filenames=os.listdir(os.getcwd())
i = 0
print filenames
resutl = re.compile(r'jpg$')

print len(filenames)
for num in xrange(len(filenames)):
	m = resutl.search(filenames[num])
	if m != None:
		print filenames[num]
		os.rename(filenames[num],'0'+str(i)+'.jpg')
		i += 1
	else:
		pass


