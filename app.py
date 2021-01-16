from controller.controller import Controller
from view_.GUI import GUI
if __name__ == "__main__":
    controller = Controller()
    view = GUI(controller)
    controller.run()
