'''Function to Test'''

#This function takes a dictionary of stats and return true if the stats
#mean that the TikToker is famous. Famous TikTokers need:
#More than 1 mil views and 60k likes, or 200k shares and 40k favorites
def TikTokStar(dict):
    if (dict["views"] > 1000000 and dict["likes"] > 60000) or (dict["shares"] > 200000 and dict["favorites"] > 40000):
        return True
    else:
        return False

'''Test Cases'''
def test_TikTokStar_full():
    assert TikTokStar({"views":1000005, "likes":60010, "shares":201000, "favorites":42000}) == True, "Should be True"
def test_TikTokStar_highviews():
    assert TikTokStar({"views":1000005, "likes":30000, "shares":1000, "favorites":200}) == False, "Should be False"
def test_TikTokStar_highlikes():
    assert TikTokStar({"views":90000, "likes":70000, "shares":1000, "favorites":200}) == False, "Should be False"
def test_TikTokStar_highshares():
    assert TikTokStar({"views":900000, "likes":9000, "shares":300000, "favorites":200}) == False, "Should be False"
def test_TikTokStar_highfavs():
    assert TikTokStar({"views":900000, "likes":9000, "shares":10000, "favorites":60000}) == False, "Should be False"
def test_TikTokStar_viewlikes():
    assert TikTokStar({"views":1000005, "likes":60010, "shares":1000, "favorites":200}) == True, "Should be True"
def test_TikTokStar_sharefavs():
    assert TikTokStar({"views":900000, "likes":30000, "shares":201000, "favorites":42000}) == True, "Should be True"
def test_TikTokStar_lowall():
    assert TikTokStar({"views":900000, "likes":30000, "shares":1000, "favorites":200}) == False, "Should be False"


'''Running Tests'''
test_TikTokStar_full()
test_TikTokStar_highviews()
test_TikTokStar_highlikes()
test_TikTokStar_highshares()
test_TikTokStar_highfavs()
test_TikTokStar_viewlikes()
test_TikTokStar_sharefavs()
test_TikTokStar_lowall()
