'''Function to Test'''

#function takes a 2d list, return whether the list is tall, wide, or square
#tall is when there is a longer outter list than any inner list
#wide is when there is a longer inner list than the whole outter list
#square is when the largest width is the same as the height
def TallOrWide(list):
    maxcolumns = 0
    columns = 0
    rows = 0
    for row in list:
        rows += 1
        for col in row:
            columns += 1
            if maxcolumns < columns:
                maxcolumns = columns
        columns = 0
    if rows > maxcolumns:
        #print(rows, " R:C " ,maxcolumns)
        return "Tall"
    elif rows < maxcolumns:
        #print(rows, " R:C " ,maxcolumns)
        return "Wide"
    else:
        #print(rows, " R:C " ,maxcolumns)
        return "Square"

'''Test Cases'''
def test_TallOrWide_Tall():
    assert TallOrWide([[1,2],[1],[1,2],[0]]) == "Tall", "Should be Tall"
def test_TallOrWide_Wide():
    assert TallOrWide([[1,2,3],[1,2,3,4],[1,2]]) == "Wide", "Should be Wide"
def test_TallOrWide_Square():
    assert TallOrWide([[1,2,3,4],[6,2,8,4],[0,2,8,4],[0,0,0,0]]) == "Square", "Should be Square"
def test_TallOrWide_FunkySquare():
    assert TallOrWide([[0],[1,2,5],[3,9]]) == "Square", "Should be Square"

'''Running Tests'''
test_TallOrWide_Tall()
test_TallOrWide_Wide()
test_TallOrWide_Square()
test_TallOrWide_FunkySquare()
                      
                      
