#!/usr/bin/python
'''
Author: Tristan Basil
Instructor/Class: Paul Linton, CS316-001
Assignment: Program 1

Works cited:
-This file started from the base file p0_python.cgi example provided by Paul Linton
-http://www.pythonforbeginners.com/cheatsheet/python-file-handling for file operations - used to reference how to open/read files
-https://stackoverflow.com/questions/11880430/how-to-write-inline-if-statement-for-print - used to reference how to print css attributes inline
-https://stackoverflow.com/questions/10588317/python-function-global-variables - used to reference how to declare and properly use global variables
'''

import cgi
import cgitb

#declare name of file
FILENAME = "xarn_language.txt"

#declare user-facing strings
UNKNOWN = 'unknown'
INVALID = 'invalid'
INVALID_FILE = 'Invalid file format. Please verify format of xarn_language.txt and try again.'
FILE_NOT_FOUND = FILENAME + ' could not be found.'

#declare global flags to mark any errors
invalidNumFields = False
invalidFlagSourceLang = False
invalidFlagToLang = False
invalidFlagWord = False
invalidFlagTranslated = False
unknownFlag = False

''' translate(word, fromLanguage, toLanguage)
inputs: word - the word to translate
        fromLanguage - the language from which to translate
        toLanguage - the language to which to translate
outputs: the translated word in the toLanguage, INVALID string if file invalid, UNKNOWN string if word not found
'''
def translate(word, fromLanguage, toLanguage):
    #open the file
    global invalidNumFields 
    file = None
    try:
        file = open(FILENAME, "r")
    except:     
        invalidNumFields = True
        return FILE_NOT_FOUND

    #for each line in the file, look for the specified language from the user.
    for line in file:
        parsedLine = line.split(',')
        #if there aren't 4 sections in the line, we have a bad file.
        if len(parsedLine) != 4:
            invalidNumFields = True
            return INVALID_FILE
        #if the specified languages are found in the file, we should check for the word.
        if (parsedLine[0]==fromLanguage and parsedLine[2]==toLanguage and parsedLine[1] == word):
            return parsedLine[3].rstrip()
        elif (parsedLine[0] == toLanguage and parsedLine[2]==fromLanguage and parsedLine[3].rstrip() == word):
            return parsedLine[1]
    global unknownFlag
    unknownFlag = True
    return UNKNOWN
    
''' printHTML(fromLanguage, toLanguage, toTranslate, translated)
inputs: fromLanguage - the language from which to translate
        toLanguage - the language to which to translate
        toTranslate - the word to translate
        translated - the translated word
outputs: none, but prints HTML containing each field and that is dynamically colored based on the global error flags.
'''
def printHTML(fromLanguage, toLanguage, toTranslate, translated):
    #output the html, using the global flags to determine colors on the output. 
    print "Content-type:text/html\n\n"
    print "<html>"
    print "<head><style>"
    print ".allWords{color: blue;}"
    print ".sourceLang{" + ("color: red;}" if invalidFlagSourceLang else "}")
    print ".toLang{" + ("color: red;}" if invalidFlagToLang else "}")
    print ".word{" + ("color: red;}" if invalidFlagWord else "}")
    print ".translated{" + ("color: red;}" if invalidFlagTranslated else "}")
    print ".translatedWord{" + ("color: green;}" if (not unknownFlag and not invalidFlagTranslated and not invalidNumFields) else "color: red;}")
    print "</style></head>"
    print "<title>Translation result</title>"
    print "<body>"
    print "<p class=\"allWords\">"
    print "<span class=\"sourceLang\"> Origin Language: " + fromLanguage + "</span><br>"
    print "<span class=\"toLang\"> Requested Language: " + toLanguage + "</span><br>"
    print "<span class=\"word\"> Original word: " + toTranslate + "</span><br>"
    print "<span class=\"translated\"> Translation: <span class=\"translatedWord\">" + translated + "</span></span><br>"
    print "</p></body></html>"
    
def main():
    cgitb.enable()
    #grab the fields from the html form
    form = cgi.FieldStorage()
    #parse and lower the user input, if the user provided it. otherwise mark the respective error flags and set word to 'invalid'.
    toTranslate = form.getvalue('theword')
    if (toTranslate is None):
        toTranslate=INVALID
        global invalidFlagWord
        invalidFlagWord = True
    else:
        toTranslate = toTranslate.lower()
    fromLanguage = (form.getvalue('fromnative'))
    if (fromLanguage is None):
        fromLanguage=INVALID
        global invalidFlagSourceLang
        invalidFlagSourceLang = True
    else:
        fromLanguage = fromLanguage.lower()
    toLanguage = (form.getvalue('newlanguage'))
    if (toLanguage is None):
        toLanguage=INVALID
        global invalidFlagToLang
        invalidFlagToLang = True
    else:
        toLanguage = toLanguage.lower()
    #translate the word (or attempt to) if we got all inputs
    if (not invalidFlagWord and not invalidFlagSourceLang and not invalidFlagToLang):
        translated = translate(toTranslate, fromLanguage, toLanguage)
    else:
        translated = INVALID
        global invalidFlagTranslated 
        invalidFlagTranslated = True
    #print our output
    printHTML(fromLanguage, toLanguage, toTranslate, translated)

if __name__ == "__main__":
    main()

