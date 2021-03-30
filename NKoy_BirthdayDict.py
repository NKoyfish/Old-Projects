state = True
myDict = {}
while state:
    name = input("Please enter a name or \"stop\" ")
    if name == "stop":
        state = False
    if state:
        bday = input("Enter associated birthday ")
        myDict[name] = bday

#for person in myDict:
   # print(person, " : ",myDict[person])    
print(myDict)