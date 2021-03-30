import random

gameState = True
randNum = random.randint(1,25) #randomly determined number for the game
guesses = 0 #Initialized to zero and will increment when a guess is made.
while gameState: #Keeps the game going until the guess is made
    
    guess = int(input("Guess a number from 1 to 25 (Inclusive)\n")) # Cast the input to an int for comparison later
    guesses = guesses + 1 #increment the number of guesses by 1. 

    if guess == randNum and guesses > 1: #Correctly guessed the number after multiple attempts.
         print("Guessed",randNum, "in", guesses, "tries")
         gameState = False #End game
    elif guess == randNum and guesses == 1:#Guessed in just 1 attempt. Grammar reasons this was added
         print("Wow! You guessed",randNum, "in just", guesses, "try. Some luck you got")
         gameState = False #End game
   
    
