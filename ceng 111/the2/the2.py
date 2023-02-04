dataList = eval(input())

dataListX = list(list(zip(*dataList))[0])
dataListY = list(list(zip(*dataList))[1])

#defining variables
x0 = dataListX[0] 
x1 = dataListX[1]
x2 = dataListX[2]
x3 = dataListX[3]
y0 = dataListY[0]
y1 = dataListY[1]
y2 = dataListY[2]
y3 = dataListY[3]

dataListX_sorted = sorted(dataListX)
dataListY_sorted = sorted(dataListY, key=abs)

xMin = dataListX_sorted[0]
xMax = dataListX_sorted[3]

toplamAlan = 0

xMinY = dataListY[dataListX.index(dataListX_sorted[0])]
xMaxY = dataListY[dataListX.index(dataListX_sorted[3])]

#prequisites
if dataListX_sorted[0] == dataListX_sorted[1] and not dataListX_sorted[2] == dataListX_sorted[3] :
    if x0 == x2 :
        xMinY = min(y0, y2, key=abs)
    elif x0 == x1 :
        xMinY = min(y0, y1, key=abs)
    elif x0 == x3 :
        xMinY = min(y0, y3, key=abs)
    elif x3 == x1 :
        xMinY = min(y1, y3, key=abs)
    elif x2 == x3 :
        xMinY = min(y2, y3, key=abs)
    elif x2 == x1 :
        xMinY = min(y1, y2, key=abs)
elif not dataListX_sorted[0] == dataListX_sorted[1] and dataListX_sorted[2] == dataListX_sorted[3] :
    if x0 == x2 :
        xMaxY = min(y0, y2, key=abs)
    elif x0 == x1 :
        xMaxY = min(y0, y2, key=abs)
    elif x0 == x3 :
        xMaxY = min(y0, y3, key=abs)
    elif x3 == x1 :
        xMaxY = min(y1, y3, key=abs)
    elif x2 == x3 :
        xMaxY = min(y2, y3, key=abs)
    elif x2 == x1 :
        xMaxY = min(y1, y2, key=abs)
elif dataListX_sorted[0] == dataListX_sorted[1] and dataListX_sorted[2] == dataListX_sorted[3] :
    if (x0 == x1 and x2 == x3) and x1 < x3 :
        xMinY = min(y1, y0, key=abs)
        xMaxY = min(y3, y2, key=abs)
    elif (x0 == x1 and x2 == x3) and x1 > x3 :
        xMinY = min(y3, y2, key=abs)
        xMaxY = min(y1, y0, key=abs)
    elif (x0 == x3 and x1 == x2) and x1 < x3 :
        xMinY = min(y1, y2, key=abs)
        xMaxY = min(y3, y0, key=abs)
    elif (x0 == x3 and x2 == x1) and x1 > x3 :
        xMinY = min(y3, y0, key=abs)
        xMaxY = min(y1, y2, key=abs)

m = (xMaxY - xMinY) / (xMax - xMin)

yamukAlan = (xMax - xMin) * (abs(xMaxY) +  abs(xMinY)) / 2

checkedPoints = dataList[:]
checkedPoints.remove((xMax,xMaxY))
checkedPoints.remove((xMin,xMinY))

xMaxIndex = dataList.index((xMax,xMaxY))
xMinIndex = dataList.index((xMin,xMinY))

#case 1 & 5
if abs(checkedPoints[0][1]) > abs(m * checkedPoints[0][0] - m * xMin + xMinY) and abs(checkedPoints[1][1]) > abs(m * checkedPoints[1][0] - m * xMin + xMinY):
    #case 1
    if int(abs(xMinIndex - xMaxIndex) == 3) ^ int(abs(xMinIndex - xMaxIndex) == 1):
        toplamAlan = yamukAlan
    #case 5
    elif abs(xMinIndex - xMaxIndex) == 2:
        if (xMax,xMaxY) == (x0,y0) :
            if y0 <= 0 and y1 <= 0 and y2 <= 0:
                toplamAlan = yamukAlan + 0.5 * (abs((x0*y2 + x2*y3 + x3*y0) - (y0*x2 + y2*x3 + y3*x0))) 
            elif y0 >= 0 and y1 >= 0 and y2 >= 0:
                toplamAlan = yamukAlan + 0.5 * (abs((x0*y2 + x2*y1 + x1*y0) - (y0*x2 + y2*x1 + y1*x0))) 
        elif (xMin,xMinY) == (x0,y0) :
            if y0 <= 0 and y1 <= 0 and y2 <= 0:
                toplamAlan = yamukAlan + 0.5 * (abs((x0*y2 + x2*y1 + x1*y0) - (y0*x2 + y2*x1 + y1*x0))) 
            elif y0 >= 0 and y1 >= 0 and y2 >= 0:
                toplamAlan = yamukAlan + 0.5 * (abs((x0*y2 + x2*y3 + x3*y0) - (y0*x2 + y2*x3 + y3*x0))) 
        elif xMin <= x0 <= xMax and abs(y2 - (m * x2 - m * xMin + xMinY)) > abs(y0 - (m * x0 - m * xMin + xMinY)) :
            toplamAlan = yamukAlan + 0.5 * (abs((x0*y1 + x1*y3 + x3*y0) - (y0*x1 + y1*x3 + y3*x0))) 
        elif xMin <= x0 <= xMax and abs(y2 - (m * x2 - m * xMin + xMinY)) < abs(y0 - (m * x0 - m * xMin + xMinY)) :
            toplamAlan = yamukAlan + 0.5 * (abs((x2*y1 + x1*y3 + x3*y2) - (y2*x1 + y1*x3 + y3*x2))) 
#case 2 & 3
elif abs(checkedPoints[0][1]) < abs(m * checkedPoints[0][0] - m * xMin + xMinY) and abs(checkedPoints[1][1]) < abs(m * checkedPoints[1][0] - m * xMin + xMinY) :
    if int(abs(xMinIndex - xMaxIndex) == 3) ^ int(abs(xMinIndex - xMaxIndex) == 1):
        #case 2
        if (xMin,xMinY) == (x0,y0) :
            if abs(xMinIndex - xMaxIndex) == 1 :
                toplamAlan = yamukAlan - (0.5 * (abs((x3*y1 + x1*y0 + x0*y3) - (y3*x1 + y1*x0 + y0*x3)) + abs((x3*y1 + x1*y2 + x2*y3) - (y3*x1 + y1*x2 + y2*x3))))
            elif abs(y1 - (m * x1 - m * xMin + xMinY)) < abs(y2 - (m * x2 - m * xMin + xMinY)):
                toplamAlan = yamukAlan - (0.5 * (abs((x3*y1 + x1*y0 + x0*y3) - (y3*x1 + y1*x0 + y0*x3)) + abs((x3*y1 + x1*y2 + x2*y3) - (y3*x1 + y1*x2 + y2*x3))))
            elif abs(y1 - (m * x1 - m * xMin + xMinY)) > abs(y2 - (m * x2 - m * xMin + xMinY)):
                toplamAlan = yamukAlan - (0.5 * (abs((x3*y1 + x1*y0 + x0*y3) - (y3*x1 + y1*x0 + y0*x3)) + abs((x3*y1 + x1*y2 + x2*y3) - (y3*x1 + y1*x2 + y2*x3))))
        elif (xMax,xMaxY) == (x0,y0) :
            if abs(xMinIndex - xMaxIndex) == 3 :
                toplamAlan = yamukAlan - (0.5 * (abs((x2*y1 + x1*y0 + x0*y2) - (y2*x1 + y1*x0 + y0*x2)) + abs((x3*y0 + x0*y2 + x2*y3) - (y3*x0 + y0*x2 + y2*x3))))
            elif abs(y2 - (m * x2 - m * xMin + xMinY)) > abs(y3 - (m * x3 - m * xMin + xMinY)):
                toplamAlan = yamukAlan - (0.5 * (abs((x3*y1 + x1*y0 + x0*y3) - (y3*x1 + y1*x0 + y0*x3)) + abs((x3*y1 + x1*y2 + x2*y3) - (y3*x1 + y1*x2 + y2*x3))))
            elif abs(y2 - (m * x2 - m * xMin + xMinY)) < abs(y3 - (m * x3 - m * xMin + xMinY)):
                toplamAlan = yamukAlan - (0.5 * (abs((x2*y1 + x1*y0 + x0*y2) - (y2*x1 + y1*x0 + y0*x2)) + abs((x3*y0 + x0*y2 + x2*y3) - (y3*x0 + y0*x2 + y2*x3))))
        elif xMinIndex == 3 :
            if xMin <= x0 <= xMax and abs(y1 - (m * x1 - m * xMin + xMinY)) >= abs(y0 - (m * x0 - m * xMin + xMinY)) :
                toplamAlan = yamukAlan - (0.5 * (abs((x0*y2 + x2*y1 + x1*y0) - (y0*x2 + y2*x1 + y1*x0)) + abs((x0*y2 + x2*y3 + x3*y0) - (y0*x2 + y2*x3 + y3*x0))))
            elif xMin <= x0 <= xMax and abs(y1 - (m * x1 - m * xMin + xMinY)) < abs(y0 - (m * x0 - m * xMin + xMinY)) :
                toplamAlan = yamukAlan - (0.5 * (abs((x3*y0 + x0*y1 + x1*y3) - (y3*x0 + y0*x1 + y1*x3)) + abs((x2*y1 + x1*y3 + x3*y2) - (y2*x1 + y1*x3 + y3*x2))))
        elif xMinIndex == 1 :
            if xMin <= x0 <= xMax and abs(y3 - (m * x3 - m * xMin + xMinY)) >= abs(y0 - (m * x0 - m * xMin + xMinY)) :
                toplamAlan = yamukAlan - (0.5 * (abs((x0*y2 + x2*y1 + x1*y0) - (y0*x2 + y2*x1 + y1*x0)) + abs((x0*y2 + x2*y3 + x3*y0) - (y0*x2 + y2*x3 + y3*x0))))
            elif xMin <= x0 <= xMax and abs(y3 - (m * x3 - m * xMin + xMinY)) < abs(y0 - (m * x0 - m * xMin + xMinY)) :
                toplamAlan = yamukAlan - (0.5 * (abs((x3*y2 + x2*y1 + x1*y3) - (y3*x2 + y2*x1 + y1*x3)) + abs((x0*y1 + x1*y3 + x3*y0) - (y0*x1 + y1*x3 + y3*x0))))
        elif xMinIndex == 2 :
            if xMin <= x0 <= xMax and abs(y3 - (m * x3 - m * xMin + xMinY)) >= abs(y0 - (m * x0 - m * xMin + xMinY)) :
                toplamAlan = yamukAlan - (0.5 * (abs((x0*y3 + x3*y2 + x2*y0) - (y0*x3 + y3*x2 + y2*x0)) + abs((x1*y2 + x2*y0 + x0*y1) - (y1*x2 + y2*x0 + y0*x1))))
            elif xMin <= x0 <= xMax and abs(y3 - (m * x3 - m * xMin + xMinY)) < abs(y0 - (m * x0 - m * xMin + xMinY)) :
                toplamAlan = yamukAlan - (0.5 * (abs((x0*y3 + x3*y1 + x1*y0) - (y0*x3 + y3*x1 + y1*x0)) + abs((x1*y2 + x2*y3 + x3*y1) - (y1*x2 + y2*x3 + y3*x1))))
    elif abs(xMinIndex - xMaxIndex) == 2:
        #case 3
        if (xMax,xMaxY) == (x0,y0) :
            toplamAlan = yamukAlan - 0.5 * (abs((x0*y2 + x2*y1 + x1*y0) - (y0*x2 + y2*x1 + y1*x0)))
        elif (xMin,xMinY) == (x0,y0) :
            toplamAlan = yamukAlan - 0.5 * (abs((x0*y2 + x2*y3 + x3*y0) - (y0*x2 + y2*x3 + y3*x0)))
        elif xMin <= x0 <= xMax and abs(y2 - (m * x2 - m * xMin + xMinY)) < abs(y0 - (m * x0 - m * xMin + xMinY)):
            toplamAlan = yamukAlan - 0.5 * (abs((x0*y3 + x3*y1 + x1*y0) - (y0*x3 + y3*x1 + y1*x0)))
        else :
            toplamAlan = yamukAlan - 0.5 * (abs((x3*y2 + x2*y1 + x1*y3) - (y3*x2 + y2*x1 + y1*x3)))
#case 4
elif int(abs(checkedPoints[0][1]) > abs(m * checkedPoints[0][0] - m * xMin + xMinY)) ^ int(abs(checkedPoints[1][1]) > abs(m * checkedPoints[1][0] - m * xMin + xMinY)) :
    if  xMin <= x0 <= xMax and abs(y0) < abs(m * x0 - m * xMin + xMinY) :
        toplamAlan = yamukAlan - 0.5 * (abs((x0*y1 + x1*y3 + x3*y0) - (y0*x1 + y1*x3 + y3*x0)))
    elif xMin <= x0 <= xMax and abs(y0) > abs(m * x0 - m * xMin + xMinY) :
        toplamAlan = yamukAlan - 0.5 * (abs((x3*y2 + x2*y1 + x1*y3) - (y3*x2 + y2*x1 + y1*x3)))
    elif (xMin,xMinY) == (x0,y0) :
        if y0 <= 0 and y1 <= 0 and y2 <= 0:
            toplamAlan = yamukAlan - 0.5 * (abs((x1*y2 + x2*y0 + x0*y1) - (y1*x2 + y2*x0 + y0*x1)))
        elif y0 >= 0 and y1 >= 0 and y2 >= 0:
            toplamAlan = yamukAlan - 0.5 * (abs((x0*y2 + x2*y3 + x3*y0) - (y0*x2 + y2*x3 + y3*x0)))
    elif (xMax,xMaxY) == (x0,y0) :
        if y0 <= 0 and y1 <= 0 and y2 <= 0:
            toplamAlan = yamukAlan - 0.5 * (abs((x0*y2 + x2*y3 + x3*y0) - (y0*x2 + y2*x3 + y3*x0)))
        elif y0 >= 0 and y1 >= 0 and y2 >= 0:
            toplamAlan = yamukAlan - 0.5 * (abs((x0*y2 + x2*y1 + x1*y0) - (y0*x2 + y2*x1 + y1*x0)))

print("{:0.2f}".format(toplamAlan))





