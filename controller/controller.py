import tkinter as tk

# from model.model import model
# from view_.view import view
from view_.GUI import GUI

class controller():
    def __init__(self):
        # self.model = model()
        root = tk.Tk()
        self.view = GUI(root)
        root.mainloop()

if __name__ == "__main__":
    # Create an instance of Tk. This is popularly called 'root' But let's
    # call it mainwin (the 'main window' of the application. )
    _controller = controller()



