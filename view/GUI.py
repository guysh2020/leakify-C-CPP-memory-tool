import tkinter as tk
import tkinter.font as tkFont
from tkinter import Menu
from tkinter import filedialog

class App:
    def __init__(self, root):
        #setting title
        root.title("Leakify")
        #setting window size
        width=1000
        height=650
        screenwidth = root.winfo_screenwidth()
        screenheight = root.winfo_screenheight()
        alignstr = '%dx%d+%d+%d' % (width, height, (screenwidth - width) / 2, (screenheight - height) / 2)
        root.geometry(alignstr)
        root.resizable(width=False, height=False)
        #Exit action
        def _quit():
            root.quit()
            root.destroy()
            exit()
        #Create Menu Bar
        menuBar=Menu(root)
        root.config(menu=menuBar)
        #File Menu
        fileMenu= Menu(menuBar, tearoff=0)
        fileMenu.add_command(label="New")
        fileMenu.add_separator()
        fileMenu.add_command(label="Exit", command=_quit)
        menuBar.add_cascade(label="File", menu=fileMenu)
        #Help Menu
        helpMenu= Menu(menuBar, tearoff=0)
        helpMenu.add_command(label="About")
        menuBar.add_cascade(label="Help", menu=helpMenu)
        def openfile():
            return filedialog.askopenfilename()

        GButton_565=tk.Button(root)
        GButton_565["bg"] = "#111212"
        ft = tkFont.Font(family='Berlin Sans FB Demi',size=18)
        GButton_565["font"] = ft
        GButton_565["fg"] = "#f4f2f2"
        GButton_565["justify"] = "center"
        GButton_565["text"] = "Choose program"
        GButton_565.place(x=270,y=210,width=276,height=202)
        GButton_565["command"] = openfile

        GLabel_800=tk.Label(root)
        ft = tkFont.Font(family='Berlin Sans FB Demi',size=50)
        GLabel_800["font"] = ft
        GLabel_800["fg"] = "#333333"
        GLabel_800["justify"] = "center"
        GLabel_800["text"] = "Leakify"
        GLabel_800.place(x=285,y=60,width=252,height=115)

        GLabel_988=tk.Label(root)
        ft = tkFont.Font(family='Berlin Sans FB Demi',size=14)
        GLabel_988["font"] = ft
        GLabel_988["fg"] = "#333333"
        GLabel_988["justify"] = "center"
        GLabel_988["text"] = "Please insert c/cpp file without compilations errors to start"
        GLabel_988.place(x=110,y=440,width=600,height=30)

if __name__ == "__main__":
    root = tk.Tk()
    app = App(root)
    root.mainloop()
