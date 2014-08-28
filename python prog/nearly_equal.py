def nearly_equal(s1,s2):
	for s in s1:
		temp = s1.replace(s,"")
		if temp in s2:
			return True
		else:
			return False

print nearly_equal('man', 'woman')