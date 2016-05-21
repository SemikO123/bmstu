import pygame as pg
from math import cos, radians, sin

pg.init()
screen = pg.display.set_mode((1300, 880), 0, 32)
pg.display.set_caption('PyGame Lab')
clock = pg.time.Clock()
bg = pg.image.load("city-road-vector.jpg").convert()
sun = pg.image.load("sun1.png").convert_alpha()
bus = pg.image.load("bus2.png").convert_alpha()
girl = pg.image.load("girl.png").convert_alpha()
boy1 = pg.image.load("boy1.png").convert_alpha()
boy2 = pg.image.load("boy2.png").convert_alpha()
station = pg.image.load("station.png").convert_alpha()
cloud1 = pg.image.load("cloud2.png").convert_alpha()
cloud2 = pg.image.load("cloud1.png").convert_alpha()
k = 0
x_sun, y_sun = 300, 250
len_sun = 495
x0_sun, y0_sun = 650, 600
alpha = 45
x_bus, y_bus = 1500, 550
girl_x, girl_y = 440, 490
boy_x, boy_y = -100, 490
cloud1_x, cloud1_y = 200, 110
cloud2_x, cloud2_y = 1000, 200
hvjhhjb


def sunrun(x, y):
    pg.draw.circle(screen, (255, 255, 0), (int(x + 40), int(y + 40)), 40, 0)
    pg.draw.line(screen, (255, 255, 0), (int(x - 15), int(y - 15)), (int(x + 95), int(y + 95)), 5)
    pg.draw.line(screen, (255, 255, 0), (int(x - 15), int(y - 15)), (int(x + 95), int(y + 95)), 5)
    pg.draw.line(screen, (255, 255, 0), (int(x + 95), int(y - 15)), (int(x - 15), int(y + 95)), 5)
    pg.draw.line(screen, (255, 255, 0), (int(x + 40), int(y - 40)), (int(x + 40), int(y + 120)), 5)
    pg.draw.line(screen, (255, 255, 0), (int(x - 40), int(y + 40)), (int(x + 120), int(y + 40)), 5)


def cloud(x, y):
    radius = 20
    pg.draw.ellipse(screen, (191, 239, 255), [x + radius * 0.1, y + radius * 0.1, x - radius, y + radius * 0.7])
    pg.draw.ellipse(screen, (191, 239, 255), [x - radius * 0.1, y + radius * 0.1, x + radius, y + radius * 0.7])
    pg.draw.ellipse(screen, (191, 239, 255), [x + radius * 0.1, y - radius * 0.1, x - radius, y - radius * 0.7])
    pg.draw.ellipse(screen, (191, 239, 255), [x - radius * 0.1, y - radius * 0.1, x + radius, y - radius * 0.7])
    pg.draw.ellipse(screen, (191, 239, 255), [x - radius * 0.5, y - radius * 0.4, x - radius * 1.5, y + radius * 0.4])
    pg.draw.ellipse(screen, (191, 239, 255), [x + radius * 0.5, y - radius * 0.4, x + radius * 1.5, y + radius * 0.4])
    pg.draw.ellipse(screen, (191, 239, 255), [x - radius * 0.5, y - radius * 0.5, x + radius * 0.5, y + radius * 0.5])


def busrun(x, y):
    screen.blit(bus, [x, y])


done = False
while done == False:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            done = True
    k += 1
    screen.blit(bg, [-44, 0])
    screen.blit(station, [350, 450])

    # ------ boy and girl ----------
    if girl_y <= 585:
        screen.blit(girl, [girl_x, girl_y])
    boy_x += 3
    if boy_x <= 370:
        if boy_x % 10 != 0:
            screen.blit(boy1, [boy_x, boy_y])
        if boy_x % 10 == 0:
            screen.blit(boy2, [boy_x, boy_y])
    if (boy_x > 370) and (x_bus > 450):
        boy_x = 370
        screen.blit(boy2, [370, 490])
    if (x_bus <= 450) and girl_y <= 585:
        girl_x += 2
        girl_y += 2
        boy_x += 2
        boy_y += 2
        screen.blit(boy2, [boy_x, boy_y])
    # -----------------------------

    # -------- sun motion ---------
    alpha += 0.1
    x_sun = x0_sun - len_sun * cos(radians(alpha))
    y_sun = y0_sun - len_sun * sin(radians(alpha))
    if x_sun > 1000:
        x_sun = 300
        y_sun = 250
        alpha = 45
    sunrun(x_sun, y_sun)
    # ----------------------------

    # -------- bus motion --------
    x_bus -= 5
    if x_bus >= 450:
        busrun(x_bus, y_bus)
    if (x_bus < 450) and (x_bus > 165):
        busrun(450, 550)
    if x_bus <= 165:
        busrun(x_bus + 285, y_bus)
    # ----------------------------

    # ------- clouds motion -------
    cloud1_x += 3
    cloud2_x -= 2

    cloud(cloud1_x,cloud1_y)
    # x = cloud1_x
    # y = cloud1_y
    # radius = 5
    # pg.draw.ellipse(screen, (191, 239, 255), [10, 10, -100, 70])
    if cloud1_x > 1300:
        cloud1_x = -150
    if cloud2_x < -200:
        cloud2_x = 1500


    # ----------------------------



    pg.display.flip()
    clock.tick(30)

pg.quit()
