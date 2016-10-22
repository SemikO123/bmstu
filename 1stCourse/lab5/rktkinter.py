from tkinter import *
import tkinter.messagebox as box
textt = ''
root = Tk()
frame = Frame(root)
entry = Entry(frame)
def func1():
    textt = entry.get()
    textt = textt + ' awawaw'
    box.showinfo('okno',textt)
button1 = Button(frame,text='Нажимай',command=func1)
lb = Listbox(frame)
lb.insert(1,'one')
lb.insert(2,'two')
lb.insert(3,'three')
def func2():
    box.showinfo('oknoo',lb.get(lb.curselection()))
button2 = Button(frame,text='select',command=func2)
entry.pack()
frame.pack(padx=100,pady=100)
button1.pack()
root.mainloop()