import numpy as np
import time
import random

def UpMassGenerate(n):
    up = np.random.randint(-100,100,n)
    up.sort()
    return up

def DownMassGenerate(n):
    down = np.random.randint(-100,100,n)
    down.sort()
    down = down[::-1]
    return down

def RandMassGenerate(n):
    rand = np.random.randint(-100,100,n)
    return rand

def ShakerSort(mass):
    start = time.time()
    left = 0
    right = len(mass)-1
    while left <= right:
        for i in range(left,right):
            if mass[i] > mass[i+1]:
                mass[i+1],mass[i] = mass[i],mass[i+1]
                right = i+1
        right -= 1
        for i in range(right,left,-1):
            if mass[i-1] > mass[i]:
                mass[i-1],mass[i] = mass[i],mass[i-1]
                left = i-1
        left += 1
    end = time.time()
    timer = end-start                                          
    return timer

def ShakerSortInf(mass):
    start = time.time()
    left = 0
    right = len(mass)-1
    while left <= right:
        for i in range(left,right):
            if mass[i][3] > mass[i+1][3]:
                mass[i+1][0],mass[i][0] = mass[i][0],mass[i+1][0]
                mass[i+1][1],mass[i][1] = mass[i][1],mass[i+1][1]
                mass[i+1][2],mass[i][2] = mass[i][2],mass[i+1][2]
                mass[i+1][3],mass[i][3] = mass[i][3],mass[i+1][3]
                right = i+1
        right -= 1
        for i in range(right,left,-1):
            if mass[i-1][3] > mass[i][3]:
                mass[i-1][0],mass[i][0] = mass[i][0],mass[i-1][0]
                mass[i-1][1],mass[i][1] = mass[i][1],mass[i-1][1]
                mass[i-1][2],mass[i][2] = mass[i][2],mass[i-1][2]
                mass[i-1][3],mass[i][3] = mass[i][3],mass[i-1][3]
                left = i-1
        left += 1
    end = time.time()
    timer = end-start
    return timer

def FirstTab():
    print('{:^75}'.format("Время выполнения программы сортировки Шейкер методом (мс)"))
    print("-"*79)
    print('{:^15}'.format("Количество "),'{:^20}'.format("Упорядоченный"),\
      '{:^20}'.format("Случайный"),'{:^20}'.format("Упорядоченный в "))
    print('{:^15}'.format("элементов "),'{:^20}'.format("массив"),\
      '{:^20}'.format("массив"),'{:^20}'.format("обратном порядке"))
    print("-"*79)
    
def PrintFirstTab(func,t1,t2):
    print('{:^15}'.format(t1),'{:^20}'.format(int(1000*func(UpMassGenerate(t1)))),\
      '{:^20}'.format(int(1000*func(RandMassGenerate(t1)))),\
      '{:^20}'.format(int(1000*func(DownMassGenerate(t1)))))
    print('{:^15}'.format(t2),'{:^20}'.format(int(1000*func(UpMassGenerate(t2)))),\
      '{:^20}'.format(int(1000*func(RandMassGenerate(t2)))),\
      '{:^20}'.format(int(1000*func(DownMassGenerate(t2)))))


def InfMassGenerate(count):
    A = []
    mn = ['Иван','Петр','Максим','Алексей','Евгений','Даниил','Сергей','Павел','Никита']
    mnmn = ['Москва','Санкт-Петербург','Казань','Самара','Волгоград','Екатеринбург','Саратов','Тверь']
    mnmnmn = ['менеджер','продавец','банкир','программист','управляющий','инженер','водитель']
    for i in range(count):
        A.append([])
        A[i].append(random.sample(mn,1))
        A[i].append(random.sample(mnmn,1))
        A[i].append(random.sample(mnmnmn,1))
        A[i].append(random.randint(18,250))
    for i in range(count):
        A[i][0],A[i][3] = A[i][3],A[i][0]
    return A

def InfMassUp(count):
    A = []
    mn = ['Иван','Петр','Максим','Алексей','Евгений','Даниил','Сергей','Павел','Никита']
    mnmn = ['Москва','Санкт-Петербург','Казань','Самара','Волгоград','Екатеринбург','Саратов','Тверь']
    mnmnmn = ['менеджер','продавец','банкир','программист','управляющий','инженер','водитель']
    for i in range(count):
        A.append([])
        A[i].append(random.randint(18,90))
        A[i].append(random.sample(mnmn,1))
        A[i].append(random.sample(mnmnmn,1))
        A[i].append(random.sample(mn,1))
    A.sort()
    for i in range(count):
        A[i][0],A[i][3] = A[i][3],A[i][0]
    return A

def InfMassDown(count):
    A = []
    mn = ['Иван','Петр','Максим','Алексей','Евгений','Даниил','Сергей','Павел','Никита']
    mnmn = ['Москва','Санкт-Петербург','Казань','Самара','Волгоград','Екатеринбург','Саратов','Тверь']
    mnmnmn = ['менеджер','продавец','банкир','программист','управляющий','инженер','водитель']
    for i in range(count):
        A.append([])
        A[i].append(random.randint(18,90))
        A[i].append(random.sample(mn,1))
        A[i].append(random.sample(mnmn,1))
        A[i].append(random.sample(mnmnmn,1))
    A.sort()
    for i in range(count):
        A[i][0],A[i][3] = A[i][3],A[i][0]
    A = A[::-1]
    return A

def SecondTab():
    print('{:^75}'.format("Время выполнения программы в массиве с сопутствующей информацией (мс)"))
    print("-"*79)
    print('{:^15}'.format("Количество "),'{:^20}'.format("Упорядоченный"),\
      '{:^20}'.format("Случайный"),'{:^20}'.format("Упорядоченный в "))
    print('{:^15}'.format("элементов "),'{:^20}'.format("массив"),\
      '{:^20}'.format("массив"),'{:^20}'.format("обратном порядке"))
    print("-"*79)
    
def PrintSecondTab(func,t1,t2):
    print('{:^15}'.format(t1),'{:^20}'.format(int(1000*func(InfMassUp(t1)))),\
      '{:^20}'.format(int(1000*func(InfMassGenerate(t1)))),\
      '{:^20}'.format(int(1000*func(InfMassDown(t1)))))
    print('{:^15}'.format(t2),'{:^20}'.format(int(1000*func(InfMassUp(t2)))),\
      '{:^20}'.format(int(1000*func(InfMassGenerate(t2)))),\
      '{:^20}'.format(int(1000*func(InfMassDown(t2)))))

FirstTab()
PrintFirstTab(ShakerSort,300,300)
print("-"*79)
PrintFirstTab(ShakerSort,3000,3000)
print("-"*79)
#PrintFirstTab(ShakerSort,3000,3000)
#print('')

SecondTab()
PrintSecondTab(ShakerSortInf,300,300)
print("-"*79)
PrintSecondTab(ShakerSortInf,3000,3000)
print("-"*79)
#PrintSecondTab(ShakerSortInf,3000,3000)


    







