#!/usr/bin/python
import cgi
import cgitb
#
# Note - not "proper" HTML - shortens the example code! - pjl
# http://www.pythonforbeginners.com/cheatsheet/python-file-handling for file operations
# https://stackoverflow.com/questions/11880430/how-to-write-inline-if-statement-for-print
# https://stackoverflow.com/questions/10588317/python-function-global-variables

#declare user-facing strings
UNKNOWN = 'unknown'
INVALID = 'invalid'

#declare global flags to mark any errors
invalidFlag = False
unknownFlag = False

def translate(word, fromLanguage, toLanguage):
    #open the file
    filename = "xarn_language.txt"
    file = open(filename, "r")
    #for each line in the file, look for the specified language from the user.
    for line in file:
        parsedLine = line.split(',')
	#if there aren't 4 sections in the line, we have a problem.
	if len(parsedLine) != 4:
            global invalidFlag 
	    invalidFlag = True
	    return INVALID
	#if the specified languages are found in the file, we should check for the word.
	if (parsedLine[0]==fromLanguage and parsedLine[2]==toLanguage and parsedLine[1] == word):
	    return parsedLine[3].rstrip()
	elif (parsedLine[0] == toLanguage and parsedLine[2]==fromLanguage and parsedLine[3] == word):
	    return parsedLine[1]
	else:
	    global unknownFlag
	    unknownFlag = True
	    return UNKNOWN

def printHTML(fromLanguage, toLanguage, toTranslate, translated):
    #fill in some empty strings if we got passed null values
    #if (fromLanguage is None) fromLanguage = ""
    #toLanguage = "" if toLangauge is None else ""
    
    print "Content-type:text/html\n\n"
    print "<html>"
    print "<head><style>"
    print ".leftWords{" + ("color: blue;}" if not invalidFlag else "}")
    print ".allWords{" + ("color: red;}" if invalidFlag else "}")
    print ".translatedWord{" + ("color: green;}" if (not unknownFlag and not invalidFlag) else "color: red;}")
    print "</style></head>"
    print "<body>"
    print "<p class=\"allWords\">"
    print "<span class=\"leftWords\"> Origin Language:</span> " + fromLanguage + "<br>"
    print "<span class=\"leftWords\"> Requested Language:</span> " + toLanguage + "<br>"
    print "<span class=\"leftWords\"> Original word:</span> " + toTranslate + "<br>"
    print "<span class=\"leftWords\"> Translation:</span> <span class=\"translatedWord\">" + translated + "</span><br>"
    print "</body></html>"
	

def main():
    cgitb.enable()
    #grab the fields from the html form
    form = cgi.FieldStorage()
    #if the user provided all fields, parse and lower the input.
    toTranslate = form.getvalue('theword')
    toTranslate = "" if (toTranslate is None) else toTranslate.lower()
    fromLanguage = (form.getvalue('fromnative'))
    fromLanguage = "" if (fromLanguage is None) else fromLanguage.lower()
    toLanguage = (form.getvalue('newlanguage'))
    toLanguage = "" if (toLanguage is None) else toLanguage.lower()
    #translate the word (or attempt to) if we got all inputs
    if (toTranslate != "" and fromLanguage != "" and toLanguage != ""):
        translated = translate(toTranslate, fromLanguage, toLanguage)
    else:
        translated = INVALID
        global invalidFlag 
        invalidFlag = True
    
    printHTML(fromLanguage, toLanguage, toTranslate, translated)


if __name__ == "__main__":
    main()
