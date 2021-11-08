#!/usr/bin/python
import sys
f=open(sys.argv[1])  
f1=open('output.txt','w')
for x in f.readlines():
    f1.write(x)
f.close()
f1.close()
