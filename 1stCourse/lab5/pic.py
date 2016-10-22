from tkinter import *
from math import tan, atan, degrees, radians
root = Tk()
canv = Canvas(root,width=1000,height=850,bg='#FFFAF0')
canv.create_polygon([240,500],[215,580],[690,580],[665,500],fill='#BDBDBD',outline='#A4A4A4',width=2) #подставка
canv.create_oval([320,460],[580,540],fill='#BDBDBD',outline='#A4A4A4',width=2)   #палка подставка
canv.create_rectangle(100,100,800,500,fill='#BDBDBD',outline='#A4A4A4',width=2)  #монитор
canv.create_rectangle(130,130,770,445,fill='#EFF2FB',outline='#A4A4A4',width=3)  #экран
canv.create_rectangle(650,465,710,480,fill='#424242',outline='#2E2E2E',width=1)  #кнопки
canv.create_rectangle(725,465,740,480,fill='#424242',outline='#2E2E2E',width=1)
canv.create_rectangle(755,465,770,480,fill='#F78181',outline='#FA5858',width=1)
canv.create_polygon([150,580],[90,740],[810,740],[750,580],fill='#BDBDBD',outline='#A4A4A4',width=2.5)  #тело клавы
canv.create_polygon([170,603],[130,717],[550,717],[540,603],fill='#D8D8D8',outline='#A4A4A4',width=2)   #клава1
canv.create_polygon([595,603],[730,603],[760,717],[610,717],fill='#D8D8D8',outline='#A4A4A4',width=2)   #клава2
alfa,x,key1 = radians(70.6),130,170
for i in range(12):
    alfa += radians(1.88)
    key1 += 28.45
    x = key1-114/tan(alfa)
    canv.create_line(key1,603,x,717,fill='#A4A4A4')  #разлиновка клавы1
left,begu,endu = 603,170,540
for i in range(5):
    left += 22.8
    begu -= 8
    endu +=2
    canv.create_line(begu,left,endu,left,fill='#A4A4A4')

alfa,x,key1 = radians(97.5),610,595
for i in range(3):
    alfa += radians(2.41)
    key1 += 45
    x = key1-114/tan(alfa)
    canv.create_line(key1,603,x,717,fill='#A4A4A4')  #разлиновка клавы2
left,begu,endu = 603,595,730
for i in range(3):
    left += 38
    begu += 5
    endu += 10
    canv.create_line(begu,left,endu,left,fill='#A4A4A4')

canv.create_text(800, 540, text='1',font='Verbana 20' ,justify=CENTER, anchor='se', fill='green')
# мышка
canv.create_line([755,590],[850,575],[870,680],fill='#424242',width=4,smooth=1)
canv.create_oval(839,680,905,770,fill='#D8D8D8',outline='#A4A4A4',width=2)
canv.create_line([840,720],[872,725],[905,715],fill='#A4A4A4',width=2,smooth=1)
canv.create_line(870,680,878,722,fill='#A4A4A4',width=2)
canv.create_rectangle(872,705,880,722,fill='#424242',width=1)

#змея
canv.create_polygon([379,358],[399,378],[440,270],fill='#31B404',outline='#298A08',width=2) #хвост
canv.create_oval(200,355,415,410,fill='#04B431',outline='#298A08',width=2) #тело низ
canv.create_oval(275,215,325,362,fill='#04B404',outline='#298A08',width=2) #шея
canv.create_oval(210,330,405,380,fill='#31B404',outline='#298A08',width=2) #тело верх
canv.create_line([270,332],[280,340],[290,345],[300,348],[320,350],[370,340],fill='#298A08',width=2)
canv.create_oval(283,208,299,230,fill='#F5FBEF',outline='#298A08',width=2) #глаз
canv.create_oval(298,208,314,230,fill='#F5FBEF',outline='#298A08',width=2) #глаз
canv.create_oval(286,216,296,229,fill='#00BFFF',outline='#0174DF',width=1) #голубой глаз
canv.create_oval(301,216,311,229,fill='#00BFFF',outline='#0174DF',width=1) #голубой глаз
canv.create_oval(303,220,309,228,fill='#0B3B2E') #зрачок
canv.create_oval(288,220,294,228,fill='#0B3B2E') #зрачок
canv.create_oval(262,226,310,258,fill='#31B404',outline='#298A08',width=2) #нос
canv.create_line([266,250],[288,249],[300,243],fill='#0B6121',width=2,smooth=1) #рот
canv.create_line([278,250],[264,262],[266,266],fill='#DF0101',width=3,smooth=1) #язык
canv.create_text(400,240,text='Hungry \nPython',justify=CENTER,anchor='se',fill = 'green')

#облако
canv.create_oval(470,165,740,340,fill='#F6CEE3',outline='#F6CEE3')
canv.create_polygon([410,250],[480,225],[480,245],fill='#F6CEE3',outline='#F6CEE3')

#торт
canv.create_polygon([530,300],[520,250],[680,240],[680,300],fill='#F7F2E0',outline='#F5A9A9',width=3)
canv.create_polygon([520,250],[625,210],[680,240],fill='#F3E2A9',outline='#F5A9A9',width=3)
canv.create_line([620,210],[660,220],[679,242],fill='#F78181',width=9,smooth=1)
canv.create_line(680,300,680,240,fill='#F78181',width=6)
canv.create_line(680,260,523,266,fill='#F78181',width=8)
canv.create_line(680,280,526,283,fill='#F78181',width=8)
canv.create_oval([590,210],[620,235],fill='#DF013A',outline='#B43104',width=2.5)
canv.create_line([605,217],[598,200],[603,194],fill='#088A29',width=4,smooth=1)















canv.pack()
root.mainloop()
