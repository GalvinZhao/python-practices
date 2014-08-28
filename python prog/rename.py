import os
filenames = os.listdir(os.getcwd())
print filenames
for name in filenames:
	filenames[filenames.index(name)] = name[:-3]
out = open('filename.txt','w')
for name in filenames:
	out.write(name+'\n')
out.close()