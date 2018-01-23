#!/usr/bin/python
import subprocess
print 'Content-type: text/html\n\n'
print subprocess.Popen("uptime", shell=True,stdout=subprocess.PIPE).stdout.read()

#used from slides provided in cs316
