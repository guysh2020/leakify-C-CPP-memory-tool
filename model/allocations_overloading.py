import os
import re
import subprocess

from model.state import State
from model.allocation import Allocation
from .release import Release
from model.algorithm import AlgorithmInterface


class AllocationsOverloading(AlgorithmInterface):
    def __init__(self, path):
        self.path_to_folder = 'C:\\Users\\guysh\\OneDrive\\Desktop\\test'
        # self.path_to_folder = path
        self.files = []
        self.files_type = ""

        self.C_HEADER = '#include"..\\appData\\overloadingAllocations_c.h"\n'
        self.CPP_HEADER = '#include"..\\appData\\overloadingAllocations_cpp.h"\n'
        self.NEW_DATA_LOCATION = '..\\userData\\'

    def run(self):
        if self.pre_process() == State.OK:
            print('preeprocess done')
        else:
            print('error at preprocess')




    def pre_process(self):

        self.clean_folder()

        # list files and validate them, if error generate system log and return to view
        if self.get_files() != State.OK:
            return State.MULTIPLE_MAINS

        # pick correct header to attach based on files type
        leakify_header = self.C_HEADER if self.files_type == 'c' else self.CPP_HEADER

        summarize = "summerize();\n"
        open_file_function = "openFile();\n"

        main_pattern = re.compile("\w+\s+main.*?\)")
        return_pattern = re.compile("return.*?;")
        include_pattern = re.compile('#include\s*[<|"]\w+.*[>|"]')

        for file in self.files:
            main = False
            if file['name'] == "main.c" or file['name'] == "main.cpp":
                main = True

            # catch errors related to input files
            try:
                data = open(file['path'] + file['name'], 'r')
            except OSError as exc:
                print(f"input file: {file['name']}, {exc.strerror}")
                return 0  # change to return relevant error

            content = data.readlines()
            start_includes = False

            # catch errors related to output files
            try:
                if file['name'].endswith('.h'):
                    new_data = open(self.NEW_DATA_LOCATION + file['name'], 'w')
                    new_data.writelines(content)
                    continue

                new_data = open(self.NEW_DATA_LOCATION + "t_" + file['name'], 'w')

            except OSError as exc:
                print(f"output file: {file['name']}, {exc.strerror}")
                return 0  # change to return relevant error

            for index in range(0, len(content)):
                if re.search(include_pattern, content[index]):
                    start_includes = True
                elif start_includes and len(content[index]) > 1:
                    content.insert(index, leakify_header)
                    break

            seen_main = False
            scopes = 0

            if main:
                while index < len(content):
                    if re.search(main_pattern, content[index]):
                        seen_main = True
                        if '{' in content[index]:
                            content.insert(index + 1, open_file_function)
                        else:
                            content.insert(index + 2, open_file_function)
                    if seen_main:
                        if '{' in content[index]:
                            scopes += 1
                        if '}' in content[index]:
                            if scopes == 1:
                                content.insert(index, summarize)
                                break
                            scopes -= 1

                        if re.search(return_pattern, content[index]):
                            content.insert(index, summarize)
                            break

                    index += 1

            for line in content:
                new_data.write(line)

            data.close()
            new_data.close()

        return State.OK

    # def find_leaks(self):
    #     allocations = {}
    #     releases = []
    #
    #     pattern = re.compile("\w+\[.*\]")
    #     with open(self.NEW_DATA_LOCATION + 'allocations.txt', 'r') as data:
    #         for line in data:
    #             if line.startswith('0') =:
    #                 tmp = Allocation(line)
    #                 print(tmp)
    #                 allocations[tmp.address] = tmp
    #             else:
    #                 releases.append(re.search(pattern, line).group(0))
    #
    #         for relase in releases:
    #             if relase in allocations:
    #                 del allocations[relase]
    #
    #     for item in allocations:
    #         print(item)


    def find_leaks(self):
        allocations = {}
        releases = []

        pattern = re.compile("\w+\[.*\]")
        with open(self.NEW_DATA_LOCATION + 'allocations.txt', 'r') as data:
            for entry in data:
                if entry.startswith('0'):
                    tmp = Allocation(entry)
                    allocations[tmp.address] = tmp
                else:
                    releases.append(entry.split('=')[1].split(',')[3].split('[')[0])

            for release in releases:
                if release in allocations:
                    del allocations[release]

        for item in allocations:
            print(item)

    def get_files(self):
        for root, dirs, files in os.walk(self.path_to_folder):
            for file in files:
                if file.endswith(".cpp") or file.endswith(".c") or file.endswith(".h"):
                    # self.files.append((root + '\\', file))
                    self.files.append({'path': root + '\\', 'name': file})

        print(self.files)
        return self.validate_files()

    def validate_files(self):
        c = False
        cpp = False
        main = False

        for file in self.files:
            if file['name'].endswith('.c'):
                c = True
            if file['name'].endswith('.cpp'):
                cpp = True

            if file['name'].startswith('main.'):
                if main:
                    return State.MULTIPLE_MAINS
                else:
                    main = True

            if c and cpp:
                return State.MIXED_EXTENSIONS

        self.files_type = 'c' if c else 'cpp'
        return State.OK

    def compile(self):
        compile_command = ["gcc" if self.files_type == 'c' else "g++"]

        for file in os.listdir(self.NEW_DATA_LOCATION):
            if file.endswith(".cpp") or file.endswith(".c"):
                compile_command.append(os.path.join(self.NEW_DATA_LOCATION, file))

        compile_command.append('-o')
        compile_command.append(self.NEW_DATA_LOCATION + 'main.exe')
        print(compile_command)

        try:
            process = subprocess.run(compile_command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, check=True)
            print(process.stdout)
        except subprocess.CalledProcessError as suberror:
            print(suberror.stdout.decode("utf-8"))

    def run_user_file(self):
        try:
            process = subprocess.run(self.NEW_DATA_LOCATION + 'main.exe', stdout=subprocess.PIPE,
                                     stderr=subprocess.STDOUT,
                                     check=True)
            print(process.stdout)
        except subprocess.CalledProcessError as suberror:
            print(suberror.stdout.decode("utf-8"))

    def run_interactive_user_file(self):
        try:
            process = subprocess.run('start /wait ' + self.NEW_DATA_LOCATION + './main.exe', stdout=subprocess.PIPE,
                                     stderr=subprocess.STDOUT, check=True, shell=True)
            print(process.returncode)
        except subprocess.CalledProcessError as suberror:
            print(suberror.stdout.decode("utf-8"))

    def clean_folder(self):
        for file in os.listdir(self.NEW_DATA_LOCATION):
            os.remove(os.path.join(self.NEW_DATA_LOCATION, file))



a = AllocationsOverloading()
a.run()