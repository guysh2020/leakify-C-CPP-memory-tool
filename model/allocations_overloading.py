import os
import re
import subprocess
import shutil

from state import State
from allocation import Allocation
# from .release import Release
from algorithm import AlgorithmInterface


class AllocationsOverloading(AlgorithmInterface):
    def __init__(self):
        self.path_to_folder = ''
        # self.path_to_folder = 'C:\\Users\\guysh\\OneDrive\\Desktop\\test'
        self.interactive = False  # set by user
        self.files = []
        self.files_type = ""

        self.C_HEADER = '#include"..\\appData\\overloadingAllocations_c.h"\n'
        self.CPP_HEADER = '#include"..\\appData\\overloadingAllocations_cpp.h"\n'
        self.NEW_DATA_LOCATION = '.\\userData\\'
        self.C_SOURCE = '.\\appData\\overloadingAllocations_c.c'
        self.CPP_SOURCE = '.\\appData\\overloadingAllocations_cpp.cpp'

    def run(self):
        self.pre_process()
        self.compile()
        self.run_interactive_user_file()
        return self.find_leaks()


    def set_path(self, path):
        self.path_to_folder = path

    def set_interactive(self, interactive):
        self.interactive = interactive

    def pre_process(self):

        self.clean_folder()

        # list files and validate them, if error generate system log and return to view
        if self.get_files() != State.OK:
            return State.MULTIPLE_MAINS

        # pick correct header to attach based on files type
        leakify_header = self.C_HEADER if self.files_type == 'c' else self.CPP_HEADER

        include_pattern = re.compile('#include\s*[<|"]\w+.*[>|"]')

        for file in self.files:

            # catch errors related to input files
            try:
                data = open(file['path'] + file['name'], 'r')
            except OSError as exc:
                print(f"input file: {file['name']}, {exc.strerror}")
                return 0  # change to return relevant error

            content = data.readlines()

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

            start_includes = False
            for index in range(0, len(content)):
                if re.search(include_pattern, content[index]):
                    start_includes = True
                elif start_includes and len(content[index]) > 1:
                    content.insert(index, leakify_header)
                    break

            for line in content:
                new_data.write(line)

            data.close()
            new_data.close()

        return State.OK

    def find_leaks(self):
        allocations = {}
        releases = []

        print(os.getcwd())
        with open(self.NEW_DATA_LOCATION + 'allocations.txt', 'r') as data:
            for entry in data:
                if entry.startswith('0'):
                    tmp = Allocation(entry)
                    allocations[tmp.address] = tmp
                else:
                    releases.append(entry.split('=')[1].split('[')[0])

            for release in releases:
                if release in allocations:
                    del allocations[release]

        return allocations

    def get_files(self):
        for root, dirs, files in os.walk(self.path_to_folder):
            for file in files:
                if file.endswith(".cpp") or file.endswith(".c") or file.endswith(".h"):
                    self.files.append({'path': root + '\\', 'name': file})

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

        if not main:
            return State.MAIN_MISSING

        return State.OK

    def compile(self):
        compile_command = ["gcc" if self.files_type == 'c' else "g++"]
        compile_command.append(self.C_SOURCE if self.files_type == 'c' else self.CPP_SOURCE)

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
            if file == '.gitignore':
                continue
            os.remove(os.path.join(self.NEW_DATA_LOCATION, file))
