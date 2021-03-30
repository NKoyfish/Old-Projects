#define list of numbers
numbersList = [4, 12, 35, 13, 8, 13, 0, 2, 13, 13, 56]

def removeUnlucky(numList):
    count = numList.count(13)
    for i in range(count):
        numList.remove(13)
    



print("Unlucky: ",numbersList)
removeUnlucky(numbersList)
print("Lucky: ", numbersList)
