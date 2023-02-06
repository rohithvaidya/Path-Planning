from tkinter import *

 
top = Tk()  
top.geometry("450x300") 
   
rows = 10
cols = 10

path = [0, 1, 10]

x=10
y=60
ctr=0

for i in range(rows):
    for j in range(cols):
        if(ctr in path):
            temp = Label(top,text = str(ctr), bg= "green", fg= "white", textvariable=ctr,  borderwidth=1, relief="solid").place(x = x,y = y)
        else:
            temp = Label(top,text = str(ctr), bg= "gray51", fg= "white", textvariable=ctr,  borderwidth=1, relief="solid").place(x = x,y = y)
        x+=20
        ctr+=1
    y+=20
    x=10
     
top.mainloop()
