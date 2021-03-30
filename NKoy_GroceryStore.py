myGrocery = {"Eggs":2.15,"Chicken":4.00,"Peanut Butter":3.10,"Bread":2.25,"Goldfish":2.50,"Soda":3.00}
inventory = ["Eggs","Chicken","Peanut Butter","Bread","Goldfish","Soda"]
state = True
total = 0.00
def addToCart(cartTotal,storeInventory,item):
    cartTotal += storeInventory[item]
    return cartTotal
while(state):
    print(inventory)
    item = input("Which items would you like to add to your cart? Or \"done\"\n")
    if item == "done": #Program ends
        state = False 
        print("$",total)
    else:
        try: 
            total = addToCart(total,myGrocery,item) #Item exists if no error so add its cost to the checkout total
        except KeyError:
            print("Please type the item correctly (Case sensitive)") #Item was an error and asks to lost a new one after