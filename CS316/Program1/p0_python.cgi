#!/usr/bin/python
import cgi
import cgitb
#
# Note - not "proper" HTML - shortens the example code! - pjl
#

def doit(a, b, c):
    print "Parameters: ", a, " ", b, " ", c

def main():
    print "Content-type:text/html\n\n"
    cgitb.enable()
    form = cgi.FieldStorage()
    Last = (form.getvalue('field1')).lower()
    First = (form.getvalue('field2')).lower()
    Middle = (form.getvalue('field3')).lower()

    output = doit(Last, First, Middle)

if __name__ == "__main__":
    main()
