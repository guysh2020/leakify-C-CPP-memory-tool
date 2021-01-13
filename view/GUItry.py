import tkinter as tk
import tkinter.font as tkFont

class App:
    def __init__(self, root):
        #setting title
        root.title("Leakify")
        #setting window size
        width=1000
        height=550
        screenwidth = root.winfo_screenwidth()
        screenheight = root.winfo_screenheight()
        alignstr = '%dx%d+%d+%d' % (width, height, (screenwidth - width) / 2, (screenheight - height) / 2)
        root.geometry(alignstr)
        root.resizable(width=False, height=False)

        GButton_651=tk.Button(root)
        GButton_651["bg"] = "#212F3C"
        ft = tkFont.Font(family='Berlin Sans FB Demi',size=16,color="white")
        GButton_651["font"] = ft
        GButton_651["fg"] = "#000000"
        GButton_651["justify"] = "center"
        GButton_651["text"] = "choose folder"
        GButton_651.place(x=50,y=120,width=150,height=75)
        GButton_651["command"] = self.GButton_651_command

        GLineEdit_754=tk.Entry(root)
        GLineEdit_754["borderwidth"] = "1px"
        ft = tkFont.Font(family='Berlin Sans FB Demi',size=10)
        GLineEdit_754["font"] = ft
        GLineEdit_754["fg"] = "#333333"
        GLineEdit_754["justify"] = "center"
        GLineEdit_754["text"] = "Entry"
        GLineEdit_754.place(x=0,y=320,width=998,height=228)

        GButton_122=tk.Button(root)
        GButton_122["bg"] = "#645c5c"
        ft = tkFont.Font(family='Berlin Sans FB Demi',size=23)
        GButton_122["font"] = ft
        GButton_122["fg"] = "#000000"
        GButton_122["justify"] = "center"
        GButton_122["text"] = "Save"
        GButton_122.place(x=420,y=210,width=150,height=80)
        GButton_122["command"] = self.GButton_122_command

        GButton_921=tk.Button(root)
        GButton_921["bg"] = "#424d4c"
        ft = tkFont.Font(family='Berlin Sans FB Demi',size=23)
        GButton_921["font"] = ft
        GButton_921["fg"] = "#000000"
        GButton_921["justify"] = "center"
        GButton_921["text"] = "Run"
        GButton_921.place(x=420,y=90,width=150,height=80)
        GButton_921["command"] = self.GButton_921_command

        GLabel_92=tk.Label(root)
        ft = tkFont.Font(family='Berlin Sans FB Demi',size=16)
        GLabel_92["font"] = ft
        GLabel_92["fg"] = "#333333"
        GLabel_92["justify"] = "center"
        GLabel_92["text"] = "label"
        GLabel_92.place(x=690,y=0,width=207,height=312)

        GLabel_736=tk.Label(root)
        ft = tkFont.Font(family='Berlin Sans FB Demi',size=40)
        GLabel_736["font"] = ft
        GLabel_736["fg"] = "#333333"
        GLabel_736["justify"] = "center"
        GLabel_736["text"] = "Leakify"
        GLabel_736.place(x=397,y=10,width=200,height=60)

    def GButton_651_command(self):
        print("command")


    def GButton_122_command(self):
        print("command")


    def GButton_921_command(self):
        print("command")

if __name__ == "__main__":
    root = tk.Tk()
    app = App(root)
    root.mainloop()
