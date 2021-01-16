from controller.controller import Controller
from view_.GUI import GUI




if __name__ == "__main__":
    controller = Controller()
    # controller.set_view_(GUI(controller))
    controller.run()