import string, random
#Function takes a list or string and pics num many elements (repeatable)
#from the object. Example chooseFrom("ABC",5) -> "AAAAC"
def chooseFrom(specificList, num):
    finalString = ""
    if type(specificList.__class__) == type(list):
        for x in range(num): #pick a random element from list num times
            y = random.randrange(len(specificList)) #a
            finalString += specificList[y] 
    elif type(specificList.__class__) == type(str):
            for x in range(num): #pick a random element from str num times
                y = random.randrange(specificList.length) #b
                finalString += specificList[y] 
    else:
        print("You didn't put a string or list in arg1")
    return finalString
#random tangent: forgot strings could be indexed similar to lists but too lazy to
#change the code and make it "neater." In my defense, I will say that argument type checking
#still is important practice so just keeping it there. #a and #b shows the case handling difference
#but its not needed

#Lists and strings our program chooses from.
alpha = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"
digit = "0123456789"
special = ["!","@","#","$","%","^","&","*","(",")","-","+"]

#keep asking user to make a new password or quit with 'done'
while input("Create password or 'done\n") != "done":
    #Initialize and reinitialize these variables on repeat.
    tempPass = ""
    finalPass = ""
    howManyL = int(input("How many letters?\n"))
    howManyD = int(input("How many numbers?\n"))
    howManyS = int(input("How many special characters?\n"))

    #Make the password using the function
    tempPass += chooseFrom(alpha,howManyL)
    tempPass += chooseFrom(digit,howManyD)
    tempPass += chooseFrom(special,howManyS)

    #Shuffle takes in a list argument so we cast the string
    tempPass = (list(tempPass)) 
    random.shuffle(tempPass)
    #For each element in the newly shuffled tempPass list,
    #cast each element as a string and concatenate it to an empty string
    #which results in a newly scrambled password of type str.
    for x in tempPass:
        finalPass += str(x)

    print(finalPass)

#program ends
print("thanks")
#I made sure that there were no OBOEs when picking between lists or strings. "0 and 9" and "a  and Z" appear in passwords.
#Happy holidays