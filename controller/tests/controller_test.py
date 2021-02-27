import unittest

from controller import  Controller
from allocations_overloading import AllocationsOverloading
from model import  Model

class controller_test(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        controller = Controller()
        allocations_overloading = AllocationsOverloading()
        model = Model()

    def test_set_path(self):
        path = "C:\\Study\\ThirdYear\\Leakify\\overloading allocations\\tests\\test_cpp_2\n"
        self.controller.set_path(path)
        response = self.allocations_overloading.get_path()
        self.assertEqual(response[0], path)

    def test_find_leaks(self):
        leaks = self.controller.find_leaks()
        response = self.allocations_overloading.find_leaks()
        self.assertEqual(response[0], leaks)

    def test_save_log(self):
        path = "C:\\Study\\ThirdYear\\Leakify\\overloading allocations\\tests\\test_cpp_2\n"
        self.controller.set_path(path)
        response = self.model.save_log(path)
        self.assertEqual(response[0], path)
