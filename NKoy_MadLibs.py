import random
file = open("MadLib Sentences.txt","r")
wordSubs = []
madLibInputs = []
#Make a list of all lines and randomly choose a sentence to madlib
sentences = list(file)
sent = random.randrange(0,len(sentences))
sentence = str(sentences[sent])

tempSentence = sentence
finalSentence = sentence
madlibCount = sentence.count("<")
#Based on the count of '<' we scrape the MadLib needed to be filled in and
#add it to a list
for x in range(madlibCount):
    firstClip = tempSentence.index("<")
    secondClip = tempSentence.index(">")
    wordSubs.append(tempSentence[firstClip+1:secondClip])
    tempSentence = tempSentence[secondClip+1:] 
    #move through the string to find the next set of <>

#Now ask for word replacements based off wordSubs
for word in wordSubs:
    tempWord = input(f'Enter a(n) {word}: ')
    madLibInputs.append(tempWord)
#Replace every '<madlib>' with user input for that category
for x in range(madlibCount):
    finalSentence = finalSentence.replace(wordSubs[x],madLibInputs[x],1) 
    #replaces only the first occurrence of a madlib type. Ex) <color> is asked twice and wont fill in <red> for both
print(finalSentence)