import tkinter as tk

from model.model import Model

from view_.GUI import GUI



class Controller():
    def __init__(self):
        self.view = GUI(self)
        self.model = Model()


    def run(self):
        self.view.create()
        self.view.root.mainloop()
        # self.root.mainloop()

    def set_path(self, path):
        self.model.set_path(path)

    def find_errors(self):

        self.model.find_errors()

    def save_log(self, path):
        self.model.save_log(path)

    def set_view_(self,view):
        self.GUI = view

    def set_interactive(self):
        self.model.set_interactive(True)




    def save_log(self, path):
        self.model.save_log(path)

    def mock(self):
        return ['a','b','c']

    def set_view_(self, view):
        self.view = view

    def set_interactive(self):
        self.model.set_interactive(True)
