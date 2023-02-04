def createNode(function, operator, left = [], right = []):
    return [function, operator, left, right]
def construct_function(defs, function):
    ops = ["+", "-", "*", "^"]
    functions = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "y", "z"]
    constants = ["1", "2", "3", "4", "5", "6", "7", "8", "9"]
    i = 0
    while i < len(defs):
        if defs[i][0] == function:
            if defs[i][5] == "x":
                if defs[i][7] in functions:
                    return createNode(function, defs[i][6], ['x'], construct_function(defs, defs[i][7]))
                else:
                    return createNode(function, defs[i][6], ['x'], [defs[i][7::]])
            if defs[i][5] in functions:
                if defs[i][10] in functions:
                    return createNode(function, defs[i][9], construct_function(defs, defs[i][5]), construct_function(defs, defs[i][10]))
                else:
                    return createNode(function, defs[i][9], construct_function(defs, defs[i][5]), [defs[i][10::]])
            if defs[i][5] in constants:
                b = 0
                while b < len(ops):
                    index = defs[i].find(ops[b])
                    if index != -1:
                        if defs[i][index+1] in functions:
                            return createNode(function, defs[i][index], [defs[i][5:index]], construct_function(defs, defs[i][index+1]))
                        else:
                            return createNode(function, defs[i][index], [defs[i][5:index]], [defs[i][index+1:]])
                    b += 1                
        i += 1
def is_Top(defs, function):
    copy = defs[::]
    t = 0
    while t < len(copy):
        index = copy[t].find(function)
        if index == 0:
            copy.remove(copy[t])
        t += 1
    i = 0        
    while i < len(copy):
        if function in copy[i]:
            return False
        i += 1
    return True       
def construct_forest(defs):
    result = []
    #removing the spaces
    a = 0
    while a < len(defs):
        defs[a] = defs[a].replace(" ", "")
        a += 1
    i = 0
    while i < len(defs):
        if is_Top(defs, defs[i][0]):
            result.append(construct_function(defs, defs[i][0]))
        i += 1
    return result

