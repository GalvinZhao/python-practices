
import sys
print sys.argv
filename = sys.argv[1]
command = sys.argv[0]

if command == 'head':
	f= open(filename).readlines().split()
	print f[:10]
elif command == 'tail':
	f= open(filename).readlines().split()
	print f[:-10]
f = open(filename).readlines()

for i in f:
	print i[::-1]