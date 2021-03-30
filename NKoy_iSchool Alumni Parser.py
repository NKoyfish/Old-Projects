import urllib.request, urllib.parse, urllib.error
import re
import ssl

myURL = "https://ischool.umd.edu/alumni/alumni-spotlight"
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

#____FUNCTIONS_____

#takes URL, returns the list of the rows of code
def getHTML(webpage):
    html = urllib.request.urlopen(webpage, context = ctx).read()
    fullPage = str(html).split("\\n")
    return fullPage

#takes list of rows of code, returns dict of alumni and grad year
def makeAlumniDict(fullPage):
    alumDict = {}
    year = 0
    for line in fullPage:
        if "<h3" and "Class" in line: #Filters to include only h3 headers with "Class"
            line = line.replace("<h3>","")
            line = line.replace("</h3>","")
            year = int((line[-4:])) 
            alumDict[(line.split(",")[0])] = year
    return alumDict
            

#takes dictionary of alumni and years, returns list of alumni grads between years (inclusive)
def betweenYears(alumDict):
    betweenList = []
    min = int(input("Start Year: "))
    max = int(input("End Year: "))
    for key in alumDict:
        if int(alumDict[key]) >= min and int(alumDict[key]) <= max:
            betweenList.append(key)
    return betweenList
#MAIN CODE
page = getHTML(myURL)
webPageAlumDict = makeAlumniDict(page)
print(betweenYears(webPageAlumDict))
    
