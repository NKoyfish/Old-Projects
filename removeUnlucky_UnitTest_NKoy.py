'''FUNCTION TO TEST'''
def removeUnlucky(numList):
    count = numList.count(13)
    for i in range(count):
        numList.remove(13)
    return numList
test1 = []
test2 = [13,13,13]
test3 = [13,13,13,1]
test4 = [-13,-13,1,1]
#Test Cases -----------------------------------
def removeUnlucky_empty():
    assert removeUnlucky(test1) == [], "Should be '[]'"

def removeUnlucky_all13():
    assert removeUnlucky(test2) == [], "Should be '[]'"

def removeUnlucky_allBut1():
    assert removeUnlucky(test3) == [1], "Should be '[1]'"

def removeUnlucky_negative():
    assert removeUnlucky(test4) == [-13,-13,1,1], "Should be '[-13,-13,1,1]'"
    
#Running Tests --------------------------------
removeUnlucky_empty()
removeUnlucky_all13()
removeUnlucky_allBut1()
removeUnlucky_negative()