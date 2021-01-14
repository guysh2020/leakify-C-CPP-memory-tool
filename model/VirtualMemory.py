# from Owner import Owner
# from Allocation import Allocation

from enum import Enum


import os
import re
import subprocess

class State(Enum):
    OK = 0
    MAIN_MISSING = 1
    MIXED_EXTENSIONS = 2
    MULTIPLE_MAINS = 3
    COMPILATION_ERRORS = 4


class Allocation:
    def __init__(self, str):
        raw = str.split('=')[1].split(',')
        raw_address = raw[3].split('[')
        self.module = raw[0]
        self.line = raw[1]
        self.function = raw[2]
        self.address = raw_address[0]
        self.size = (raw_address[1])[:-2]

    def __str__(self):
        return f"\33[91min module: {self.module}, in function: {self.function}, on line: {self.line} the program allocated {self.size} bytes at address: {self.address} that was never freed"




class preProcess:
    def __init__(self):
        self.path_to_folder = 'C:\\Users\\guysh\\OneDrive\\Desktop\\test'
        self.files = []
        self.files_type = ""
        self.c_header = '#include"..\\appData\\overloadingAllocations_c.h"\n'
        self.cpp_header = '#include"..\\appData\\overloadingAllocations_cpp.h"\n'
        self.userData = '..\\userData\\'

    def generate_system_error(self):
        pass

    def pre_process(self):

        # list files and validate them, if error generate system log and return to view
        if self.get_files() != State.OK:
            return self.generate_system_error()

        # pick correct header to attach based on files type
        leakify_header = self.c_header if self.files_type == 'c' else self.cpp_header


        summarize = "summerize();\n"
        openFile = "openFile();\n"

        main_pattern = re.compile("\w+\s+main.*?\)")
        return_pattern = re.compile("return.*?;")
        include_pattern = re.compile('#include\s*[<|"]\w+.*[>|"]')

        for file in self.files:
            main = False
            if file[1] == "main.c" or file[1] == "main.cpp":
                main = True

            data = open(file[0] + file[1], 'r')

            content = data.readlines()
            start_includes = False

            if file[1].endswith('.h'):
                new_data = open(self.userData + file[1], 'w')
                new_data.writelines(content)
                continue

            new_data = open(self.userData + "t_" + file[1], 'w')

            for index in range(0, len(content)):
                if re.search(include_pattern, content[index]):
                    start_includes = True
                elif start_includes and len(content[index]) > 1:
                    content.insert(index, leakify_header)
                    break

            seen_main = False
            skopes = 0

            if main:
                while index < len(content):
                    if re.search(main_pattern, content[index]):
                        seen_main = True
                        if '{' in content[index]:
                            content.insert(index+1, openFile)
                        else:
                            content.insert(index + 2, openFile)
                    if seen_main:
                        if '{' in content[index]:
                            skopes += 1
                        if '}' in content[index]:
                            if skopes == 1:
                                content.insert(index, summarize)
                                break
                            skopes -= 1

                        if re.search(return_pattern, content[index]):
                            content.insert(index, summarize)
                            break

                    index+=1

            for line in content:
                new_data.write(line)

            data.close()
            new_data.close()

        return State.OK

    def compare(self):
        allocations = {}
        releases = []

        pattern = re.compile("\w+\[.*\]"
                             )
        with open( self.userData + 'allocations.txt', 'r') as data:
            for line in data:
                if line[0] == '0':
                    tmp = Allocation(line)
                    print(tmp)
                    allocations[tmp.address] = tmp
                else:
                    releases.append(re.search(pattern, line).group(0))

            for relase in releases:
                if relase in allocations:
                    del allocations[relase]

        for item in allocations:
            print(item)

    def get_files(self):
        for root, dirs, files in os.walk(self.path_to_folder):
            for file in files:
                if file.endswith(".cpp") or file.endswith(".c") or file.endswith(".h"):
                    self.files.append((root + '\\', file))

        print(self.files)
        return self.validate_files()

    def validate_files(self):
        c = False
        cpp = False
        main = False

        for file in self.files:
            if file[1].endswith('.c'):
                c = True
            if file[1].endswith('.cpp'):
                cpp = True

            if file[1].startswith('main.'):
                if main:
                    return State.MULTIPLE_MAINS
                else:
                    main = True

            if c and cpp:
                return State.MIXED_EXTENSIONS

        self.files_type = 'c' if c else 'cpp'
        return State.OK

    def compile(self):

        # compiler = "gcc" if self.files_type == 'c' else "g++"

        compile_command = ["gcc" if self.files_type == 'c' else "g++"]

        # for file in self.files:
        #     compile_command.append('..\\userData\\t_' +file[1])

        for file in os.listdir(self.userData):
            if file.endswith(".cpp") or file.endswith(".c"):
                compile_command.append(os.path.join(self.userData, file))


        compile_command.append('-o')
        compile_command.append(self.userData + 'main.exe')
        print(compile_command)

        try:
            process = subprocess.run(compile_command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, check=True)
            print(process.stdout)
        except subprocess.CalledProcessError as suberror:
            print(suberror.stdout.decode("utf-8"))

    def run_user_file(self):
        try:
            process = subprocess.run(self.userData + 'main.exe', stdout=subprocess.PIPE, stderr=subprocess.STDOUT, check=True)
            print(process.stdout)
        except subprocess.CalledProcessError as suberror:
            print(suberror.stdout.decode("utf-8"))

    def run_interactive_user_file(self):
        try:
            process = subprocess.run('start /wait ' + self.userData + './main.exe', stdout=subprocess.PIPE,stderr=subprocess.STDOUT, check=True, shell=True)
            print(process.returncode)
        except subprocess.CalledProcessError as suberror:
            print(suberror.stdout.decode("utf-8"))






# class Error:
#     def __init__(self):
#         self.message = message
#         state = None







a = preProcess()
print(a.pre_process())
a.compile()

a.run_user_file()

a.compare()



# a.list_files()
# print(a.validate_files())
