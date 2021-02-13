def maze(m):
    return maze_helper(m, 0, 0)

def maze_helper(m, i = 0, j = 0):

    if(i == len(m) or j == len(m[0])):
        return 0
    if(i == len(m)-1 and j == len(m[0])-1):
        return 1
    if(m[i][j] == "x"):
        return 0
    return maze_helper(m, i+1, j) + maze_helper(m, i, j+1)