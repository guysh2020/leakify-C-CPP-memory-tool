# from View import  *
import sys
import app as app
from PyQt5.QtWidgets import *

class GUI(QWidget):
    def __init__(self):
        QWidget.__init__(self)

    def displayView(self):
        self.hello = ["Hallo Welt", "你好，世界", "Hei maailma",
                      "Hola Mundo", "Привет мир"]

        self.button = QPushButton("Click me!")
        self.text = QLabel("Hello World")
        self.text.setAlignment(Qt.AlignCenter)

        self.layout = QVBoxLayout()
        self.layout.addWidget(self.text)
        self.layout.addWidget(self.button)
        self.setLayout(self.layout)

    def refreshView(self):
        pass

def main():
    app = QApplication(sys.argv)

    widget = GUI()
    widget.resize(800, 600)
    widget.show()

    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
