v = [100,75,50]

def vecToMatrix(v):

    m = [[0],[0],[0]]

    m[0][0] = v[0]
    m[1][0] = v[1]
    m[2][0] = v[2]
    return m

def matrixToVec(m):

    if len(m) > 2:
        v = [[0],[0],[0]]
        v[0] = m[0][0]
        v[1] = m[1][0]
        v[2] = m[2][0]
    else:
        v = [[0],[0],0]
        v[0] = m[0][0]
        v[1] = m[1][0]

    return v

projection = [[1, 0, 0],[0, 1, 0]]


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

def logmatrix(m):
    cols = len(m[0])
    rows = len(m)
    print("rows x columns: ",rows, "x", cols)

    for x in range(rows):
        for y in range(cols):
            print(m[x][y], end="  ")
        print()
    print("------------------")


print(v)
logmatrix(projection)
point = vecToMatrix(v)
result = matmul(projection, point)
logmatrix(point)
logmatrix(result)
v = matrixToVec(result)
print(v)
