file = open('file.txt')
text = file.readlines()
l_text = list()
for i in text:
	l_text += [j for j in i.split()]
print(l_text)
s_text = set(l_text) 
MyData = [[l_text.count(x), x] for x in s_text]
print(MyData)
MyData.sort(key=lambda i: i[1])
print(MyData)
ResData = MyData[0]
for txt1 in MyData: 
	if txt1[0] > ResData[0]: 
		ResData = txt1 
file = open('file1.txt', 'w')
file.write(ResData[1])
print(ResData[1])
file.close()
