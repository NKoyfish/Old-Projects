f = open("fruit.txt","r")

newF = open("upperFruit.txt","w")
for line in f:
    newF.write(line.upper())


    