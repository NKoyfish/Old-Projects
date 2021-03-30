f = open("FakeNames.txt","r")
myDic = {}
initials = []
countInitials = []
#Make an array with each element representing the first initial of each name in the file
for line in f:
    initials.append(line[0])
#Remove duplicates iteratively and keep the order while adding the count of that initial to a new list
initialsUnique = []
for init in initials:
    if init not in initialsUnique:
         initialsUnique.append(init)
         countInitials.append(initials.count(init))
#cross-ref unique initial list element 0 with countInit element 0...1,1 2,2 etc to create the dic
for num in range(len(initialsUnique)):
    myDic[initialsUnique[num]] =countInitials[num]
#return our dictionary
print(myDic)