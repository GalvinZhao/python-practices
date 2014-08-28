import collections
def word_frequency(words):
    frequency = {}
    for w in words:
        frequency[w] = frequency.get(w, 0) + 1
    return frequency
def read_words(filename):
    return list(open(filename).read())
def main(filename):
    frequency = word_frequency(read_words(filename))
    print frequency
    a = collections.OrderedDict(sorted(frequency.items(),key = lambda x:x[1],reverse = 1));
    for word,count in a.items():
    	print word,count

if __name__ == "__main__":
    import sys
    main(sys.argv[1])