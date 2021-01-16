import os
import tkinter as tk
import tkinter.font as tkFont
from doctest import master
from tkinter import Menu, END
from tkinter import filedialog
from tkinter import filedialog
import tkinter.messagebox as box
import time, threading


# from controller.controller import Controller


class GUI:
    def __init__(self, controller):
        self.controller = controller
        self.root = tk.Tk()

    # nabvar
    def _quit(self):
        self.root.quit()
        self.root.destroy()
        exit()

    def create(self):
        # Create Menu Bar
        menuBar = Menu(self.root)
        self.root.config(menu=menuBar)
        # Help Menu
        helpMenu = Menu(menuBar, tearoff=0)
        helpMenu.add_command(label="About")
        menuBar.add_cascade(label="Help", menu=helpMenu)
        # setting title
        self.root.title("Leakify")
        # setting window size
        width = 1200
        height = 600
        screenwidth = self.root.winfo_screenwidth()
        screenheight = self.root.winfo_screenheight()
        alignstr = '%dx%d+%d+%d' % (width, height, (screenwidth - width) / 2, (screenheight - height) / 2)
        self.root.geometry(alignstr)
        self.root.resizable(width=False, height=False)

        label_leakify = tk.Label(self.root)
        ft = tkFont.Font(family='Copperplate Gothic Light', size=70)
        label_leakify["font"] = ft
        label_leakify["fg"] = "#333333"
        label_leakify["justify"] = "center"
        label_leakify["text"] = "Leakify"
        label_leakify.place(x=440, y=10, width=355, height=110)

        button_folder = tk.Button(self.root, command=self.button_folder_command)
        button_folder["bg"] = "#212F3C"
        ft = tkFont.Font(family='Copperplate Gothic Light', size=23)
        button_folder["font"] = ft
        button_folder["fg"] = "#FDFEFE"
        button_folder["justify"] = "center"
        button_folder["text"] = "choose \n folder"
        button_folder.place(x=70, y=200, width=200, height=100)
        # button_folder["command"] = self.button_folder_command

        label_deatils = tk.Label(self.root)
        ft = tkFont.Font(family='Copperplate Gothic Light', size=20)
        label_deatils["font"] = ft
        label_deatils["fg"] = "#333333"
        label_deatils["justify"] = "left"
        label_deatils["text"] = "Leakify will make your \n coding life easier!"
        label_deatils.place(x=410, y=180, width=400, height=70)

        text_deatils = tk.Label(self.root)
        ft = tkFont.Font(family='Copperplate Gothic Light', size=13)
        text_deatils["font"] = ft
        text_deatils["fg"] = "#333333"
        text_deatils["justify"] = "left"
        text_deatils["text"] = "Requirment for using: \n" \
                               "1. Your program is written in c/c++ \n" \
                               "2. Your program must have main file \n" \
                               "3. Your progrem must compile \n" \
                               "4. Gcc installed on your computer"
        text_deatils.place(x=410, y=250, width=400, height=100)

        c_interactive = tk.Checkbutton(self.root)

        # ft = tkFont.Font(family='Times',size=10)
        # c_interactive["font"] = ft
        # c_interactive["fg"] = "#333333"
        # c_interactive["justify"] = "center"
        # c_interactive["text"] = "CheckBox"
        # c_interactive.place(x=930,y=120,width=70,height=25)
        # c_interactive["offvalue"] = "0"
        # c_interactive["onvalue"] = "1"
        # c_interactive.pack()
        # lbl = tk.Label(self.root)
        # lbl.pack()
        #
        # var = tk.BooleanVar()

        # def update_lbl():
        #     global var
        #     if var.get():
        #         lbl['text'] = str(var.get())
        #     else:
        #         print(var.get())

        # tk.Checkbutton(self.root, variable=var, command=update_lbl).pack()
        button_run = tk.Button(self.root, command=self.button_run_command)

        button_run["bg"] = "#424d4c"
        ft = tkFont.Font(family='Copperplate Gothic Light', size=23)
        button_run["font"] = ft
        button_run["fg"] = "#FDFEFE"
        button_run["justify"] = "center"
        button_run["text"] = "Run"
        button_run.place(x=930, y=200, width=200, height=100)

    def button_folder_command(self):
        folder_path = tk.StringVar()
        filename = filedialog.askdirectory()
        folder_path.set(filename)
        print("path:" + filename)
        listFiles = os.listdir(filename)  # list of files

        self.controller.set_path(filename)

        label_log = tk.Label(self.root)
        ft = tkFont.Font(family='Copperplate Gothic Light', size=15)
        label_log["font"] = ft
        label_log["fg"] = "#333333"
        label_log["justify"] = "center"
        label_log["text"] = f"Files in directory: {filename}"
        label_log.place(x=0, y=380, width=1000, height=35)

        Lb1 = tk.Listbox(self.root)
        Lb1.place(x=0, y=420, width=800, height=228)

        for file in listFiles:
            Lb1.insert(1, file)

    def button_run_command(self):
        label_log = tk.Label(self.root)
        ft = tkFont.Font(family='Copperplate Gothic Light', size=15)
        label_log["font"] = ft
        label_log["fg"] = "#333333"
        label_log["justify"] = "center"
        label_log["text"] = "In Procces"
        label_log.place(x=0, y=380, width=200, height=35)

        Lb1 = tk.Listbox(self.root)
        Lb1.place(x=0, y=420, width=600, height=228)

        errors = self.controller.find_errors()
        for i in errors or []:
            Lb1.insert(1, i)

        button_save = tk.Button(self.root)
        button_save["bg"] = "#645c5c"
        ft = tkFont.Font(family='Copperplate Gothic Light', size=23)
        button_save["font"] = ft
        button_save["fg"] = "#FDFEFE"
        button_save["justify"] = "center"
        button_save["text"] = "Save"
        button_save.place(x=900, y=420, width=150, height=80)
        button_save["command"] = self.button_save_command



    def button_save_command(self):
        folder_path = tk.StringVar()
        filename = filedialog.askdirectory()
        folder_path.set(filename)


        self.controller.save_log(filename)


