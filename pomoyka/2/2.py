file = open('in.txt')
text = file.readlines()
right = set()
for i in range(1,len(text)-1,2):
	if text[i+1] == 'YES\n':
		for j in range(len(text[i].split())):
			if int(text[i].split()[j]) <= int(text[0]):
				right.add(text[i].split()[j])
	else:
		for j in range(len(text[i].split())):
			right.discard(text[i].split()[j])	
arr = list(right)
arr.sort()	 
file = open('out.txt','w')
for i in arr:
	file.write(i+' ')
file.close()

