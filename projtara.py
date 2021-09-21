from tkinter import *
import math

fen = Tk()
width, height = 600, 600
fen.title("fenetre")
fen.geometry("600x600")
fen.configure(bg='#D8D5E4')

canvas = Canvas(fen, width=width, height=height)
canvas.place(x=0,y=0)

scale = 200
cube_position = [width//2, height//2]
distance = 5
angle_x=0
angle_y=0
angle_z=0
angle = 0

points = [n for n in range(16)]

points[0] = [[-2],[-2],[2]]
points[1] = [[-2],[2],[2]]
points[2] = [[2],[2],[2]]
points[3] = [[2],[-2],[2]]
points[4] = [[-2],[-2],[-2]]
points[5] = [[-2],[2],[-2]]
points[6] = [[2],[2],[-2]]
points[7] = [[2],[-2],[-2]]

points[8] = [[-0.5],[-0.5],[0.5]]
points[9] = [[-0.5],[0.5],[0.5]]
points[10] = [[0.5],[0.5],[0.5]]
points[11] = [[0.5],[-0.5],[0.5]]
points[12] = [[-0.5],[-0.5],[-0.5]]
points[13] = [[-0.5],[0.5],[-0.5]]
points[14] = [[0.5],[0.5],[-0.5]]
points[15] = [[0.5],[-0.5],[-0.5]]



def matmul(a,b):
    colsA = len(a[0]) #3
    rowsA = len(a)    #2
    colsB = len(b[0]) #1
    rowsB = len(b)    #3

    if (colsA != rowsB):
        print("colsA must match rowsB")

    result = [[j for j in range(colsB)] for i in range(rowsA)]



    for x in range(rowsA):
        for y in range(colsB):
            sum = 0
            for k in range(colsA):
                sum += a[x][k] * b[k][y]
            result[x][y] = sum
    return result

def connect(i,j,k):
    a = k[i]
    b = k[j]
    canvas.create_line(a[0],a[1],b[0],b[1],width=1)
    

def face(i,j,l,m,k, color):
    a = k[i]
    b = k[j]
    c = k[l]
    d = k[m]
    canvas.create_polygon(a[0],a[1],b[0],b[1],c[0],c[1],d[0],d[1], fill=color)

def key_press(event):
    global angle_x, angle_y, angle_z
    key = event.char

    if key == 's':
        angle_x += 0.1
    if key == 'z':
        angle_x -= 0.1
    if key == 'd':
        angle_y += 0.1
    if key == 'q':
        angle_y -= 0.1
    if key == 'e':
        angle_z += 0.1
    if key == 'a':
        angle_z -= 0.1

def run():
    global angle_x,angle_y,angle_z,width, height
    width, height = fen.winfo_width(), fen.winfo_height()
    canvas.config(width=width, height=height)
    cube_position = [width//2, height//2]
    print(width)
    
    angle_x += 0.02
    angle_y += 0.02
    angle_z += 0.02
    
    rotation_x = [[1, 0, 0],[0, math.cos(angle_x), -math.sin(angle_x)],[0, math.sin(angle_x), math.cos(angle_x)]]

    rotation_y = [[math.cos(angle_y), 0, -math.sin(angle_y)],[0, 1, 0],[math.sin(angle_y), 0, math.cos(angle_y)]]

    rotation_z = [[math.cos(angle_z), -math.sin(angle_z), 0],[math.sin(angle_z), math.cos(angle_z), 0],[0, 0, 1]]
    index = 0
    projected_points = [j for j in range(len(points))]

    for v in points:

        rotated = matmul(rotation_x, v)
        rotated = matmul(rotation_y, rotated)
        rotated = matmul(rotation_z, rotated)

        z = 1 / (distance - rotated[2][0])
        projection = [[z, 0, 0], [0, z, 0],[0,0,1]]

        projected2d = matmul(projection,rotated)
        x = projected2d[0][0]*scale+cube_position[0]
        y = projected2d[1][0]*scale+cube_position[1]
        z = projected2d[2][0]
        projected_points[index] = [x,y,z]
  
        index +=1
        canvas.delete('all')
    
    
    connect(0,1,projected_points)
    connect(1,2,projected_points)
    connect(2,3,projected_points)
    connect(3,0,projected_points)
    connect(4,5,projected_points)
    connect(5,6,projected_points)
    connect(6,7,projected_points)
    connect(7,4,projected_points)
    connect(0,4,projected_points)
    connect(1,5,projected_points)
    connect(2,6,projected_points)
    connect(3,7,projected_points)
    
    connect(8,9,projected_points)
    connect(9,10,projected_points)
    connect(10,11,projected_points)
    connect(11,8,projected_points)
    connect(12,13,projected_points)
    connect(13,14,projected_points)
    connect(14,15,projected_points)
    connect(15,12,projected_points)
    connect(8,12,projected_points)
    connect(9,13,projected_points)
    connect(10,14,projected_points)
    connect(11,15,projected_points)
	
    connect(0,8,projected_points)
    connect(1,9,projected_points)
    connect(2,10,projected_points)
    connect(3,11,projected_points)
    connect(4,12,projected_points)
    connect(5,13,projected_points)
    connect(6,14,projected_points)
    connect(7,15,projected_points)
   
			
			

   
        
    fen.bind('<Key>', key_press)

    fen.after(20, run)

fen.after(20, run)

fen.mainloop()
