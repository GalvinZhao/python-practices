import sys
print sys.argv
filename = sys.argv[2]
command = sys.argv[1]

if command == 'head':
	f= open(filename).readlines()
	print f[0:2]
elif command == 'tail':
	f= open(filename).readlines()
	print f[-2:]
