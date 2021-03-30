users = ["Nicholas Koy","Bill Gates","Doctor Doe"] 
#Doctor has lots of debt and can only deposit
bankAcc = {"Nicholas Koy":1000.00,"Bill Gates":5000000000.00,"Doctor Doe":-45600.00}
state = True

def withdraw(amt,bankFirm,name):
    if amt > bankFirm[name] or amt < 0: #Check that user isn't overdrawing or withdrawing negative money
        print("Insufficient funds or Negative withdrawal\n", bankFirm[name], "left in account")
    else:
        bankFirm[name] -= amt
        print("Remaining funds:",bankFirm[name]) 
def deposit(amt,bankFirm,name):
    if amt > 0:
        bankAcc[name]+= amt #valid amount add it to the user's account
        print("Remaining funds:",bankAcc[name])
    else:
        print("Can't deposit negative money")


while state:
    name = input("Enter your name?\n")  
    try:
         bankAcc[name]+= 0.0 #Checks that the account exists
    except KeyError:
        print("No registered account. Please sign up for one") #Ends program if account doesnt exist
        exit()
    wOrD = True #withdraw or deposit flag
    while(wOrD):
        func = input("withdraw or deposit?\n")
        if func == "withdraw":
            amt = float(input("How much?\n")) #Cast the input as a float for future calculation
            withdraw(amt,bankAcc,name)
            wOrD = False
        elif func == "deposit":
            amt = float(input("How much?\n")) #Cast the input as a float for future calculation
            deposit(amt,bankAcc,name)
            wOrD = False
        else:
            print("Enter a valid response")

    stop = input("Complete another transaction or 'end'?\n")
    if stop == "end": #Program Ends
        state = False