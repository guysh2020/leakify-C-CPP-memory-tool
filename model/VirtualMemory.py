# from Owner import Owner
# from Allocation import Allocation
# from Algorithem import algorithemInterface
import pandas as pd
import re

class VirtualMemory:
    allocations = []
    ownerShip = {}
    functions = {}  # main: (file_name, line)
    premativeTypes = ["int","float","double","char","bool","void"]
    classTypes = []


    def __init__(self):
        pass

    def findTypes(self):
        text_file = "./testClassName.cpp"
        listClass = list()
        with open(text_file, 'r') as read_text:
            for line in read_text:
                if 'class' in line:
                    listClass.append(line)
        wordClass = re.compile("^class (\w+)")
        for i in listClass:
            m=re.search(wordClass,i)
            if m != None:
                self.classTypes.append(m.group(1))
        # print(self.classTypes)

        # go throghy all files
        # look for class keyword.
        #if present take next word after whitespace.
        # if word exicst all ready, skip
        # save word as new type in this context.


    def findFunctions(self):
        pattern = re.compile("([a-zA-Z_][a-zA-Z0-9_]*)([\n\r\s]+)([a-zA-Z_][a-zA-Z0-9_]*)::([a-zA-Z_][a-zA-Z0-9_]*)\((.*)\)([\n\r\s]+)")
        file1 = open('../testClass.cpp', 'r')
        for line in file1.readlines():
            if re.search(pattern, line):
                print(line)


    def addAllocation(self,aloc):
        self.allocations

    def setFreed(self):
        pass



# ([a-zA-Z_][a-zA-Z0-9_]*)([\n\r\s]+)([a-zA-Z_][a-zA-Z0-9_]*)::([a-zA-Z_][a-zA-Z0-9_]*)\((.*)\)([\n\r\s]+)

a = VirtualMemory()
#a.findFunctions()

a.findTypes()
















