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

    # def findTypes(self):
    #     text_file = "./testClassName.cpp"
    #     listClass = list()
    #     with open(text_file, 'r') as read_text:
    #         for line in read_text:
    #             if 'class' in line:
    #                 listClass.append(line)
    #     wordClass = re.compile("^class (\w+)")
    #     for i in listClass:
    #         m=re.search(wordClass,i)
    #         if m != None:
    #             self.classTypes.append(m.group(1))
    #     # print(self.classTypes)
    #
    #     # go throghy all files
    #     # look for class keyword.
    #     #if present take next word after whitespace.
    #     # if word exicst all ready, skip
    #     # save word as new type in this context.
    #
    #
    # def findFunctions(self):
    #     pattern = re.compile("([a-zA-Z_][a-zA-Z0-9_]*)([\n\r\s]+)([a-zA-Z_][a-zA-Z0-9_]*)::([a-zA-Z_][a-zA-Z0-9_]*)\((.*)\)([\n\r\s]+)")
    #     file1 = open('../testClass.cpp', 'r')
    #     for line in file1.readlines():
    #         if re.search(pattern, line):
    #             print(line)
    #
    #
    # def addAllocation(self,aloc):
    #     self.allocations
    #
    # def setFreed(self):
    #     pass

    def pre_process(self, files):
        include_pattern = re.compile("^#include\s*<\w+.*>\n")

        leakify = "#include<leakify.h>\n"
        summarize = "summarize()\n"

        main_pattern = re.compile("\w+\s+main.*?\)")
        return_pattern = re.compile("return.*?;")

        for file in files:
            main = True
            if file == "main.c" or file == "main.cpp":
                main = True

            data = open(file, 'r')
            new_data = open("t_" + file, 'w')

            content = data.readlines()
            start_includes = False

            for i in range(0, len(content)):
                if re.search(include_pattern, content[i]):
                    start_includes = True
                elif start_includes and len(content[i]) > 1:
                    content.insert(i, leakify)
                    break

            seen_main = False
            skopes = 0

            if main:
                for i in range(0, len(content)):
                    if re.search(main_pattern, content[i]):
                        seen_main = True
                        continue
                    if seen_main:
                        if re.search(return_pattern, content[i]):
                            content.insert(i, summarize)
                            break
                        if '{' in content[i]:
                            skopes += 1
                        if '}' in content[i]:
                            if skopes == 1:
                                content.insert(i, summarize)
                                break
                            skopes -= 1

            for line in content:
                new_data.write(line)

            data.close()
            new_data.close()


    def compare(self):
        allocations = {}
        releases = []

        pattern = re.compile("\w+\[.*\]"
                             )
        with open('./allocations.txt','r') as data:
            for line in data:
                if line[0] == '0':
                    split = line.split('#')
                    allocations[re.search(pattern,line).group(0)] = split[0][2:]
                else:
                    releases.append(re.search(pattern,line).group(0))

            for relase in releases:
                if relase in allocations:
                    del allocations[relase]


        for item in allocations:
            print(item)



# ([a-zA-Z_][a-zA-Z0-9_]*)([\n\r\s]+)([a-zA-Z_][a-zA-Z0-9_]*)::([a-zA-Z_][a-zA-Z0-9_]*)\((.*)\)([\n\r\s]+)

a = VirtualMemory()
#a.findFunctions()

a.findTypes()
















