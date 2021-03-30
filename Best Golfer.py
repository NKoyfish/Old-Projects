def bestGolfers(golfDict):
    bestGolfer = ""
    lowestScore = 100 #you want a low score in golf
    for golfer in golfDict:
        if golfDict[golfer] < lowestScore:
            lowestScore = golfDict[golfer]
            bestGolfer = golfer
    return bestGolfer

