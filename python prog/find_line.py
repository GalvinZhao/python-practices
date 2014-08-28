def readfiles(filename):
	print filename
	for f in filename:
		for l in open(f):
			yield l
def filt(n,lines):
	return (line for line in lines if len(line)>n)
def printline(lines):
	for line in lines:
		print line
def main(filename):
	lines = readfiles(filename)
	lines = filt(45,lines)
	printline(lines)
main(["da.txt","find_line.py"])