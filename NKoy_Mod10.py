#Contains the correct answers used for file writing
correctAnswer = ["Q1) 1.645 is the 90% CI multiplier \n",
"Q2) 2 is the 95% CI multiplier \n",
"Q3) 2.576 is the 99% CI multiplier \n",
"Q4) n=1/m^2 is the simplified sample size formula\n",
"Q5) 2 is the range of SD containing 95% of the pop\n",
"Q6) 3 is the range of SD containing 99% of the pop\n"]

#Function takes a question(String) and answer (String) and compares user
#response to answer. If the two are equal return true, false otherwise.
def quiz(question,answer):
    response = input(question)
    return response == answer

score = 0
currentQuestion = 0
file = open("quizAnswer.txt","w")
print("Beginning the STAT100 Section 7 quiz review\n")

if quiz("What is the multiplier used for 90% Confidence Interval? ","1.645"):
    score +=1
else:
    file.write(correctAnswer[currentQuestion])

currentQuestion += 1

if quiz("What is the multiplier used for 95% Confidence Interval? ","2"):
    score += 1
else:
    file.write(correctAnswer[currentQuestion])
    
currentQuestion += 1

if quiz("What is the multiplier used for 99% Confidence Interval? ","2.576"):
    score += 1
else:
    file.write(correctAnswer[currentQuestion])
    
currentQuestion += 1

if quiz("What is the simplified sample size formula used with 95% confidence interval for population proportion? ","n=1/m^2"):
    score += 1
else:
    file.write(correctAnswer[currentQuestion])
    
currentQuestion += 1

if quiz("How many standard deviations account for 95% of a normalized bell curve? ","2"):
    score += 1
else:
    file.write(correctAnswer[currentQuestion])
    
currentQuestion += 1

if quiz("How many standard deviations account for 99% of a normalized bell curve? ","3"):
    score += 1
else:
    file.write(correctAnswer[currentQuestion])
    
currentQuestion += 1

if score < 6:
    print(score,"/6 Check what you got wrong by opening quizAnswer.txt")
else:
    print("6/6 Perfect!")
