'''FUNCTION TO TEST'''
def getShortSongs(maxLength, songsDict):
    shortSongs = []

    for song in songsDict:
        if songsDict[song] <= maxLength:
            shortSongs.append(song)
    return shortSongs

#Test Cases -----------------------------------
songDic = {"Song 1":90, "Song 2":91, "Song 3":92}
empty = {}
def test_getShortSongs_Empty():
    assert getShortSongs(90 , empty) == [] , "Should be []"

def test_getShortSongs_One():
    assert getShortSongs(90 , songDic) == ["Song 1"], "Should be [\"Song 1\"]"

def test_getShortSongs_None():
    assert getShortSongs(89, songDic) == [], "Should be []"

def test_getShortSongs_All():
    assert getShortSongs(92, songDic) == ["Song 1", "Song 2", "Song 3"], "Should be song1 song2 song3"
    
#Running Tests --------------------------------
test_getShortSongs_None
test_getShortSongs_One
test_getShortSongs_None
test_getShortSongs_All
