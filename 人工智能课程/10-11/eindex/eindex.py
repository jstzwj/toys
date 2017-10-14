# -*- coding: cp936 -*-

import re

def readFile(path):
    input = open(path, 'r')
    try:
        all_the_text = input.read()
    finally:
        input.close()
    return all_the_text

def splitWord(text,docID):
    tmptext=text.split()
    rsttext=map(lambda str:str.lower(),tmptext)
    rst=[]
    for word in rsttext:
        rst.append((word,docID))

    return rst

def readAllFiles(prefix,suffix,maxnum):
    rst=[];
    for i in range(maxnum):
        text=readFile(prefix+str(i+1)+suffix)
        rst+=splitWord(text,i+1)

    return rst

def buildDict(words):
    dic={}
    for wordPair in words:
        word=wordPair[0]
        docID=wordPair[1]
        if not(word in dic):
            dic[word]=[0,[]]
        arry=dic[word][1]

        
        for index in range(len(arry)):
            if arry[index]>docID:
               arry.insert(index,docID)
               dic[word][0]=dic[word][0]+1
            elif arry[index]==docID:
                break
            elif index==len(arry)-1:
                arry.insert(len(arry),docID)
                dic[word][0]=dic[word][0]+1

        if len(arry)==0:
            arry.insert(0,docID)
            dic[word][0]=dic[word][0]+1
        
    return dic

def writeIndex(path,dic):
    output = open(path, 'w')
    
    for word in dic:
        output.write(word+" ")
        output.write(str(dic[word][0])+" ")
        for docID in dic[word][1]:
            output.write(str(docID)+" ")
        output.write("\n")
    output.close()

def readIndex(path):
    input = open(path, 'r')
    dic={}

    lines = input.readlines()
    for eachline in lines:
        lst=eachline.split()
        dic[lst[0]]=[lst[1],[]]
        for i in range(2,len(lst)):
            dic[lst[0]][1].append(int(lst[i]))
    input.close()
    return dic


def findInDict(str,dic):
    rst=[]
    if str.strip() in dic:
        rst+=dic[str.strip()][1]
    return rst

def parseAnd(q,dic):
    rst=[]
    exp=re.split('and|AND',q)

    for index in range(len(exp)):
        if index==0:
            rst+=findInDict(exp[index],dic)
        else:
            rst=list(set(rst).intersection(set(findInDict(exp[index],dic))))
    return rst

def parse(q,dic):
    rst=[]
    andExp=re.split('or|OR',q)
    
    for exp in andExp:
        subrst=parseAnd(exp,dic)
        rst=list(set(rst).union(set(subrst)))
    return rst
        
      
words=readAllFiles('files/d','.txt',10)

dic=buildDict(words)

writeIndex("dict.index",dic)
dic=readIndex("dict.index")

while True:
    query=input("please input query:\n")
    print(parse(query,dic))
    


