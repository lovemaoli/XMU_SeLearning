import re
str ="A34F1#b"
if re.search("a-z",str):
    a=1
else:
    a=0
if re.search("A-Z",str):
    b=1
else:
    b=0
if re.search("0-9",str):
    c=1
else:
    c=0
if '@' or '#' or '$' in str:
    d=1
else:
    d=0
if len(str)>6:
    e=1
else:
    e=0
if a*b*c*d*e==1:
    print("valid")
else:
    print("invalid")
