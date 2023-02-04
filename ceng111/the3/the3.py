def pattern_search(P, I):
    P0, P90, P180, P270 = P, [], [], []
    pRev = P[::-1]
    #ROTATING90
    a = 0
    while a < len(P[0]):
        P90.append("".join([item[a] for item in pRev])) 
        a += 1
    #ROTATING180    
    pStrRev = [i[::-1] for i in P]
    P180 = pStrRev[::-1]
    #ROTATING270
    b = len(P[0]) - 1 
    while 0 <= b < len(P[0]):
        P270.append("".join([item[b] for item in P])) 
        b = b - 1
    #LOOKING THROUGH IMAGE
    for i in I:
        if i.find(P0[0]) != -1:
            A0 = []
            a = 0 
            while a <= len(i) - len(P0[0]):
                A0.append(i.find(P0[0], a, len(i)))
                checkedList = []
                for c in I[I.index(i):I.index(i)+len(P0)]:
                    listEntry = c[A0[a]:A0[a]+len(P0[0])]
                    checkedList.append(listEntry)
                if checkedList == P0:
                    return (I.index(i), A0[a], 0)
                a += 1
        if i.find(P90[0]) != -1:
            A90 = []
            a = 0 
            while a <= len(i) - len(P90[0]):
                A90.append(i.find(P90[0], a, len(i)))
                checkedList = []
                for c in I[I.index(i):I.index(i)+len(P90)]:
                    listEntry = c[A90[a]:A90[a]+len(P90[0])]
                    checkedList.append(listEntry)
                if checkedList == P90:
                    return (I.index(i), A90[a], 90)
                a += 1
        if i.find(P180[0]) != -1:
            A180 = []
            a = 0 
            while a <= len(i) - len(P180[0]):
                A180.append(i.find(P180[0], a, len(i)))
                checkedList = []
                for c in I[I.index(i):I.index(i)+len(P180)]:
                    listEntry = c[A180[a]:A180[a]+len(P180[0])]
                    checkedList.append(listEntry)
                if checkedList == P180:
                    return (I.index(i), A180[a], 180)
                a += 1
        if i.find(P270[0]) != -1:
            A270 = []
            a = 0 
            while a <= len(i) - len(P270[0]):
                A270.append(i.find(P270[0], a, len(i)))
                checkedList = []
                for c in I[I.index(i):I.index(i)+len(P270)]:
                    listEntry = c[A270[a]:A270[a]+len(P270[0])]
                    checkedList.append(listEntry)
                if checkedList == P270:
                    return (I.index(i), A270[a], 270)
                a += 1
    return False
        



