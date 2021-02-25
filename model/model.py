from allocations_overloading import AllocationsOverloading
import os

class Model:
    def __init__(self):
        self.path = ''
        self.algorithm = AllocationsOverloading()
        self.lost_allocations = list()
        self.log = []

    def set_path(self, path):
        self.algorithm.set_path(path)

    def find_errors(self):
        self.lost_allocations = self.algorithm.run()
        return self.generate_log()

    def set_interactive(self):
        self.algorithm.set_interactive()

    def save_log(self, path):
        try:
            with open(path+'\\log.txt', 'w') as user_log:
                for line in self.log:
                    user_log.write(line)
        except IOError as exc:
            print("error writing to file")

    def generate_log(self):
        for aloc in self.lost_allocations:
            # self.log.append(self.lost_allocations[aloc])
            self.log.append(f'in module: {self.lost_allocations[aloc].module}, in function: {self.lost_allocations[aloc].function}, in line: {self.lost_allocations[aloc].line}, {self.lost_allocations[aloc].size} Bytes were allocated but never freed\n')
        return self.log
