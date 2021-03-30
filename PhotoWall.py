'''The Photo Wall program generates a random collect of photo sizes.
A decorator can use these randomly generated sizes to design the photo wall.
Decorator picks how many photos and the generator gives that many sizes.
'''
#----Initializing Variables----
import random
listOfSizes = ["small", "med", "large", "x-large"]
userChoice = ''

#----Defining Functions----
#takes size list, returns one random item from list
def pickFromList(sList):
    randIndex = random.randint(0,len(sList)-1)
    pick = sList[randIndex]
    return pick

#takes size list and num of pictures, returns list of sizes
def makeSizeList(sList, num):
    picList = []
    for i in range(num):
        newPic = pickFromList(sList)
        picList.append(newPic)
    return picList


#----Main Code----

userChoice = input("How many pictures (or done)?")
while userChoice != 'done':
    pictureList = makeSizeList(listOfSizes, int(userChoice))
    print(pictureList)
    userChoice = input("How many pictures (or done)?")

print("Thank you! Goodbye!")
