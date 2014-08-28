import types,string

def sum1(l):
	for i in l:
		if type(i) is types.IntType:
			sum =0
		elif type(i) is types.StringType:
			sum = ""
	for i in l:
		sum += i
	return sum

def reverse(l):
	num = len(l)
	tmp = []
	while num > 0 :
		tmp.append(l[num-1])
		num -= 1
	return tmp
a = reverse(reverse([7,2,3,4,5]))
a.sort(reverse=True)
print a
def cumulative_sum(l):
	index = 0
	tmp = []
	value = 0
	for i in l:
		value += i
		tmp.append(value)
	return tmp
print cumulative_sum(a)
def unique(l,key):
	#tmp = l
	tmp = set([key(i) for i in l])
	return tmp
print unique(["python", "java", "Python", "Java"],key=lambda x:x.lower())


def dups(l):
	tmp = []
	for i in l:
		if l.count(i)>1:
			tmp.append(i)

	tmp.sort()
	return tmp
#print unique(dups([1, 2, 1, 3, 2, 5]))

def group(l,n):
	a = [l[i:i+n] for i in range(0,len(l),n)]
	return a
l=[1, 2, 3, 4, 5, 6, 7, 8, 9]
print range(0,9,4)
for i in range(0,9,4):
	print l[i:i+4]

def lensort(l):
	return sorted(l,key=lambda x:len(x))
print lensort(['python', 'perl', 'java', 'c', 'haskell', 'ruby'])