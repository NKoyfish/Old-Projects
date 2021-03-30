CarrieMovies = {"Titanic":3.5, "Mean Girls":4.9, "Finding Nemo":4.7, "Wonder Woman": 4.3}
LeslieMovies = {"Clueless": 3.2, "Spy Kids":4.1, "Black Panther":5.0}

def topMovie(movieList):
    tempBest = ""
    bestRating = -1 #ratings are atleast 0 so this is a safe value
    for movie in movieList: #iteratively go through the dictionary and replace tempBest and bestRating
        if movieList[movie] > bestRating:
            bestRating = movieList[movie]
            tempBest = movie
    return tempBest


CarriesFav = topMovie(CarrieMovies)
LesliesFav = topMovie(LeslieMovies)

print("Carrie's Fav Movie: ",CarriesFav)
print("Leslie's Fav Movie: ",LesliesFav)
