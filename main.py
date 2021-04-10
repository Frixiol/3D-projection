import pygame
import keyboard
import math
from ownmatrix import matmul

white, black, blue  = (230, 230, 230), (20, 20, 20), (0, 154, 255)
width, height = 800, 800

pygame.init()
pygame.display.set_caption("3D Projection")
screen = pygame.display.set_mode((width, height))
clock = pygame.time.Clock()
fps = 60
scale = 300
cube_position = [width//2, height//2]
distance = 5
angle_x=0
angle_y=0
angle_z=0

font = pygame.font.Font(pygame.font.get_default_font(), 36)

points = [n for n in range(16)]

points[0] = [[-1.5],[-2],[1]]
points[1] = [[1.5],[-2],[1]]
points[2] = [[1.5],[2],[1]]
points[3] = [[0.5],[2],[1]]
points[4] = [[0.5],[1],[1]]
points[5] = [[-0.5],[1],[1]]
points[6] = [[-0.5],[2],[1]]
points[7] = [[-1.5],[2],[1]]
points[8] = [[-1.5],[-2],[-1]]
points[9] = [[1.5],[-2],[-1]]
points[10] = [[1.5],[2],[-1]]
points[11] = [[0.5],[2],[-1]]
points[12] = [[0.5],[1],[-1]]
points[13] = [[-0.5],[1],[-1]]
points[14] = [[-0.5],[2],[-1]]
points[15] = [[-1.5],[2],[-1]]

def connect(i,j,k):
    a = k[i]
    b = k[j]
    pygame.draw.line(screen, white, (a[0], a[1]), (b[0], b[1]), 2)

run = True
while run:
    clock.tick(fps)
    screen.fill(black)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False

    rotation_x = [[1, 0, 0],
                  [0, math.cos(angle_x), -math.sin(angle_x)],
                  [0, math.sin(angle_x), math.cos(angle_x)]]

    rotation_y = [[math.cos(angle_y), 0, -math.sin(angle_y)],
                  [0, 1, 0],
                  [math.sin(angle_y), 0, math.cos(angle_y)]]

    rotation_z = [[math.cos(angle_z), -math.sin(angle_z), 0],
                  [math.sin(angle_z), math.cos(angle_z), 0],
                  [0, 0, 1]]

    text_x = pygame.font.Font.render(font,str(angle_x), True, white)
    screen.blit(text_x, dest=(0, 0))
    text_y = pygame.font.Font.render(font, str(angle_y), True, white)
    screen.blit(text_y, dest=(0, 40))
    text_z = pygame.font.Font.render(font, str(angle_z), True, white)
    screen.blit(text_z, dest=(0, 80))

    index = 0
    projected_points = [j for j in range(len(points))]

    for v in points:

        rotated = matmul(rotation_x, v)
        rotated = matmul(rotation_y, rotated)
        rotated = matmul(rotation_z, rotated)

        z = 1 / (distance - rotated[2][0])
        projection = [[z, 0, 0], [0, z, 0]]

        projected2d = matmul(projection,rotated)
        x = projected2d[0][0]*scale+cube_position[0]
        y = projected2d[1][0]*scale+cube_position[1]
        projected_points[index] = [x,y]
        pygame.draw.circle(screen, blue, [x, y], 5)
        index +=1

    for l in range(8):
        connect(l, (l+1)%8, projected_points)
        connect(l+8, (l + 1) % 8 +8, projected_points)
        connect(l, l + 8, projected_points)

    if keyboard.is_pressed('s'):
        angle_x += 0.02
    if keyboard.is_pressed('z'):
        angle_x -= 0.02
    if keyboard.is_pressed('d'):
        angle_y += 0.02
    if keyboard.is_pressed('q'):
        angle_y -= 0.02
    if keyboard.is_pressed('e'):
        angle_z += 0.02
    if keyboard.is_pressed('a'):
        angle_z -= 0.02

    pygame.display.update()

pygame.quit()
