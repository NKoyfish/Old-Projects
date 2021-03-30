import urllib.request, urllib.parse, urllib.error
import re
import ssl
# Ignore SSL certificate errors
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE
url = "http://istodayfridaythe13th.com/"
html = urllib.request.urlopen(url, context=ctx).read()
print("Is today friday the 13th?\n")
#Checks if today is Friday the 13th
#convert object into string, then split into list
fullPage = str(html).split("\\n")
for line in fullPage:
    if "<h1" in line and "logo" not in line: #Filters for lines with just "<h1>" and not containing "logo"
        line = (line.split(">")[3])
        print(line.split("<")[0])



