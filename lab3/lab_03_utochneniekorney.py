# -*- coding: utf-8 -*-
from math import sqrt, sin, cos, pi
import matplotlib.pyplot as plt
import numpy as np

def func(x):
    if x == 0:
        return 1
    y = sin(x)/x
    return y

def func2(x):
    y = 0.02*x**2-4
    return y

def func2func(x):
    return func(x) - func2(x)

def fi(x):
    yi = (func(x+0.00001)-func(x))/0.00001
    return yi

def fi2(x):
    yii = (fi(x+0.00001)-fi(x))/0.00001
    return yii
    

def Test():
   a,b,h,eps,epsy,maxiter = -20,20,1,1e-8,1,100
   return(a,b,h,eps,epsy,maxiter)

def Input():
    a = float(input('Введите нижнюю границу интервала: '))
    b = float(input('Введите верхнюю границу интервала: '))
    h = float(input('Введите шаг h: '))
    eps = float(input('Введите точность eps для x: '))
    epsy = float(input('Введите точность eps для F(x): '))
    maxiter = int(input('Введите максимальное число итераций: ')) 
    return(a,b,h,eps,epsy,maxiter)
    

def ErrorTab():
    print()
    print('{:^60}'.format("ТАБЛИЦА ОШИБОК"))
    print()
    print('{:^15}'.format('Код ошибки'),'{:^45}'.format('Описание ошибки'))
    print('-'*70)
    print('{:^15}'.format('0'),'{:<45}'.format('Значение на отрезке получено верно'))
    print('-'*70)
    print('{:^15}'.format('1'),'{:<45}'.format('Превышено максимальное количество итераций'))
    print('-'*70)
    print('{:^15}'.format('2'),'{:<45}'.format('Неустойчивость метода относительно ошибок округления'))

def Graph(X,a,b,h):
    MAXMIN = []
    xper = np.arange(min(Xp),max(Xp),0.01)
    x1 = np.arange(a,b,0.001) # Массив от а до б с шагом
    y1 = [func(i) for i in x1]
    yper1 = [func(i) for i in xper]
    y2 = [func2(i) for i in x1]
    yper2 = [func2(i) for i in xper]
    plt.plot([a,b],[0,0],color='red')
    plt.plot(x1,y1,label='$sin(x)/x$')
    plt.legend()
    plt.plot(x1,y2,label='$0.02x^2-4$')
    plt.legend()
    plt.grid(True)
    plt.xlabel('$x$')
    plt.ylabel('$f(x)$')
    plt.fill_between(xper,yper1,yper2,color = 'purple',alpha = 0.25)
    plt.axis([a-0.4,b+0.4,min(y1)-0.4,max(y1)+0.7]) # границы осей
    if abs(a-b)/h <20:
        plt.xticks(np.arange(a,b,h)) # засечки на осях
    Y = [func(i) for i in X]
    plt.plot(X,Y,'go',color='blue',label='$radicals$')
    plt.legend()
    Yi = [func(i) for i in Xi]
    plt.plot(Xi,Yi,'go',color='red',label='$extremums$')
    plt.legend()
    for i in range(len(Xi)):
        if (func(Xi[i]) == max(Yi)):
            MAXMIN.append(Xi[i])
        if (func(Xi[i]) == min(Yi)):
            MAXMIN.append(Xi[i])
            MAXMIN.append(Xi[i]*(-1.001))
    Yt = [func(i) for i in Xt]
    plt.plot(Xt,Yt,'go',color='green',label='$inflection points$')
    plt.legend()
    MAXmin = [func(i) for i in MAXMIN]
    plt.plot(MAXMIN,MAXmin,'go',color='yellow',label='$max/min$')
    plt.legend()
    plt.show()

def Main(m,n,eps,h,X,q,func):
    errorCode = 0
    if func(m)*func(n)<0:
        const = (1+ sqrt(5))/2
        m0,n0 = m,n
        k = 0
        x1 = n0 - (n0-m0)/const
        x2 = m + (n0-m0)/const
        y1 = func(x1)
        y2 = func(x2)
        diff = abs(n0-m0)
        while abs(n0-m0) > eps:
            #print('n0 =', n0,'\nm0=', m0)
            if abs(n0-m0) > diff:
                errorCode = 2
                break
            else:
                diff = abs(n0-m0)
            diff = abs(n0-m0)

            if k>= maxiter:
                errorCode = 1
                break
            k += 1
            if abs(y1)<abs(y2):
                n0 = x2
                x2 = x1
                x1 = m0 + (n0-x2)
                y1 = func(x1)
                y2 = func(x2)
            else:
                m0 = x1
                x1 = x2
                x2 = n0 - (x1-m0)
                y2 = func(x2)
                y1 = func(x1)
        x = (m0+n0)/2
        y = func(x)
        X.append(x)
        
        print('-'*65)
        q += 1
        print('{:^8}'.format(q),'{:^5}'.format(m), '{:^5}'.format(n),\
         '{:^12}'.format('{:0.7f}'.format(x)),'{:^11}'.format('{:0.1e}'.format(y)),\
         '{:^9}'.format(k),'{:^6}'.format(errorCode))
    elif func(m) == 0:
        x = m
        y = func(x)
        k = 0
        X.append(x)
        print('-'*65)
        q += 1
        print('{:^8}'.format(q),'{:^5}'.format(m), '{:^5}'.format(n),\
         '{:^12}'.format('{:0.7f}'.format(x)),'{:^11}'.format('{:0.1e}'.format(y)),\
         '{:^9}'.format(k),'{:^6}'.format(errorCode))
    else:
        m+=h
        n+=h
    return q

def Extrem(m,n,eps,h,X,q,func):
    if func(m)*func(n)<0:
        const = (1+ sqrt(5))/2
        m0,n0 = m,n
        k = 0
        x1 = n0 - (n0-m0)/const
        x2 = m + (n0-m0)/const
        y1 = func(x1)
        y2 = func(x2)
        diff = abs(n0-m0)
        while abs(n0-m0) > eps:
            #print('n0 =', n0,'\nm0=', m0)
            if abs(n0-m0) > diff:
                errorCode = 2
                break
            else:
                diff = abs(n0-m0)
            diff = abs(n0-m0)

            if k>= maxiter:
                errorCode = 1
                break
            k += 1
            if abs(y1)<abs(y2):
                n0 = x2
                x2 = x1
                x1 = m0 + (n0-x2)
                y1 = func(x1)
                #print(x1)
                y2 = func(x2)
            else:
                m0 = x1
                x1 = x2
                x2 = n0 - (x1-m0)
                y2 = func(x2)
                y1 = func(x1)
        x = (m0+n0)/2
        y = func(x)
        X.append(x)

def trapecia(h,n):
    mass = []
    for i in range(n):
        mass.append(min(Xp)+h*i)
    summa = 0
    for i in range(len(mass)):
        summa += abs(func2func(mass[i]))
    Int = summa * h
    return(Int)





#######ТЕЛО ПРОГРАММЫ########
X,Xi,Xp,Xt =[],[0],[],[]
#a,b,h,eps,epsy,maxiter = Input()
a,b,h,eps,epsy,maxiter = Test()
kol = int((b-a)/h)
qq,qqq,qqqq,qqqqq = 0,0,0,0
m = a
n = a+h
print('{:^60}'.format("ТАБЛИЦА КОРНЕЙ"))
print('{:^8}'.format('Номер'),'{:^5}'.format('A'),\
'{:^5}'.format('B'),'{:^12}'.format('x'),'{:^11}'.format('F(x)'),\
'{:^9}'.format('Итераций'),'{:^6}'.format('Ошибка'))
for i in range(kol):
    qq = Main(m,n,eps,h,X,qq,func)
    qqq = Extrem(m,n,eps,h,Xi,qqq,fi)
    qqqq = Extrem(m,n,eps,h,Xp,qqqq,func2func)
    qqqqq = Extrem(m,n,eps,h,Xt,qqqqq, fi2)
    #print(m,n,x,y)
    m += h
    n += h
# для последнего отрезка, длина которого меньше шага
if (b-a) % h != 0:
    m = a+kol*h
    n = b
    qq = Main(m,n,eps,h,X,qq,func)
    qqq = Extrem(m,n,eps,h,Xi,qqq,fi)
    qqqq = Extrem(m,n,eps,h,Xp,qqqq,func2func)
    qqqqq = Extrem(m,n,eps,h,Xt,qqqqq, fi2)
#ErrorTab()

n = 1000
step = (max(Xp)-min(Xp))/n
print("\nПлощадь закрашенной области:",'{:3.5f}'.format(trapecia(step,n)))
Graph(X,a,b,h)

