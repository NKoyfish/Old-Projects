worstChore = "clean bathroom"
bestChore = "sweep kitchen"
choreChart = [['clean rug', 'sweep kitchen'], ['clean bathroom', 'clear gutters'], ['do laundry', 'scrub walls', 'sweep kitchen'], ['clean rug', 'clean bathroom'], ['do laundry', 'take a break', 'sweep kitchen']]

def whatDays(specChore,choreArray):
    dayList = []
    count = -1
    for chores in choreArray:
        count+=1
        for chore in chores:
            if specChore == chore:
                dayList.append(count)
    return dayList

print("You have to ",worstChore," on days ",whatDays(worstChore, choreChart))
print("You have to ",bestChore," on days ",whatDays(bestChore, choreChart))
