from model.allocations_overloading import AllocationsOverloading


class Model:
    def __init__(self):
        self.path = ''
        self.algorithm = AllocationsOverloading()
        self.lost_allocations = []
        self.log = []

    def set_path(self, path):
        self.algorithm.set_path(path)
        print(path)

    def find_errors(self):
        self.lost_allocations = self.algorithm.run()
        self.generate_log()

    def set_interactive(self, interactive):
        self.algorithm.set_interactive(interactive)

    def save_log(self, path):
        pass

    def generate_log(self):
        for aloc in self.lost_allocations:
            self.log.append(f'in module: {aloc.module}, in function: {aloc.function}, in line: {aloc.line}, {aloc.size} Bytes were allocated but never freed')
