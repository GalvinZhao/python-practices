import re
from urllib import urlopen
parttern = r'(?<=and the next nothing is )\d+'
#tmp = r'http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing={0}'
value = 37278
while True:
	url_file = urlopen("http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=%s"%value)
	line = url_file.readline()
	matches = re.search(parttern,line)
	if not matches:
		break
	else:
		print line
		value = matches.group(0)
print int(value)/2
#line = list(url_file.readline())[-1].decode()
#print line
#words = line.split()
#number = int(words[-1])
#print number