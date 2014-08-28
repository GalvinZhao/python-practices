import sys
fn = sys.argv[1]
nu = sys.argv[2]

f = open(fn)
r = f.readlines()
for i in r:
	if len(i) > 30:
		i = i[:29] +'\n'+i[29:]
	print i