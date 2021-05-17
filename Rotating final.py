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

points = [n for n in range(8)]

points[0] = [[-2],[-2],[2]]
points[1] = [[-2],[2],[2]]
points[2] = [[2],[2],[2]]
points[3] = [[2],[-2],[2]]
points[4] = [[-2],[-2],[-2]]
points[5] = [[-2],[2],[-2]]
points[6] = [[2],[2],[-2]]
points[7] = [[2],[-2],[-2]]



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
    canvas.create_line(a[0],a[1],b[0],b[1],width=2)
    

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
    angle_x += 0.1
    angle_y += 0.05
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
    
    list_z = []
    
    left = (projected_points[0][2] + projected_points[1][2] + projected_points[4][2] + projected_points[5][2])/4
    list_z.append(left)
    right = (projected_points[2][2] + projected_points[3][2] + projected_points[7][2] + projected_points[6][2])/4
    list_z.append(right)
    front = (projected_points[1][2] + projected_points[2][2] + projected_points[6][2] + projected_points[5][2])/4
    list_z.append(front)
    back = (projected_points[3][2] + projected_points[0][2] + projected_points[7][2] + projected_points[4][2])/4
    list_z.append(back)
    up = (projected_points[0][2] + projected_points[1][2] + projected_points[2][2] + projected_points[3][2])/4
    list_z.append(up)
    down = (projected_points[4][2] + projected_points[5][2] + projected_points[6][2] + projected_points[7][2])/4
    list_z.append(down)
    list_z.sort()
	

	
    for cote in list_z:
        if cote == left:
            face(0,1,5,4, projected_points, "red")
        elif cote == right:
            face(2,3,7,6, projected_points, "orange")
        elif cote == front:
            face(1,2,6,5, projected_points, "blue")
        elif cote == back:
            face(3,0,4,7, projected_points, "violet")
        elif cote == up:
            face(0,1,2,3, projected_points, "green")
        elif cote == down:
            face(4,5,6,7, projected_points, "yellow")
			
			

   
        
    fen.bind('<Key>', key_press)

    fen.after(20, run)

fen.after(20, run)

fen.mainloop()