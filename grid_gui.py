from tkinter import *

 
top = Tk()  
top.geometry("1000x1000") 
   
rows = 10
cols = 10

ob = [41,67,34,0,69,24,78,58,62,64]

f=open("f.txt", "r")
path=[]
for i in f.readlines():
    if(i=="\n"):
        continue
    path.append(int(i))

print(path)

x=10
y=60
ctr=0

for i in range(rows):
    for j in range(cols):
        if(ctr in ob):
            temp = Label(top,text = str(ctr), bg= "yellow", fg= "white", textvariable=ctr,  borderwidth=1, relief="solid").place(x = x,y = y)
            x+=20
            ctr+=1
            continue
        if(ctr in path):
            temp = Label(top,text = str(ctr), bg= "green", fg= "white", textvariable=ctr,  borderwidth=1, relief="solid").place(x = x,y = y)
        else:
            temp = Label(top,text = str(ctr), bg= "gray51", fg= "white", textvariable=ctr,  borderwidth=1, relief="solid").place(x = x,y = y)
        x+=20
        ctr+=1
    y+=20
    x=10
     
top.mainloop()
