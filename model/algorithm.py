
# from Model import model

from .allocation import Allocation


class AlgorithmInterface:
    # returns a list of un-freed allocations
    def run(self):
        pass
