def rotate(a,b,c):
    """
    эта функция определяет, с какой стороны от вектора AB находится точка C (положительное возвращаемое значение
    соответствует левой стороне, отрицательное — правой).
    """
    return (b[0]-a[0])*(c[1]-b[1])-(b[1]-a[1])*(c[0]-b[0])

def jarvismarch(points):
      n = len(points)      
      P = list(range(0,n))
      #Знайти стартову точку, що належить до мінімальної опуклої оболонки, й оголосити її поточною(ліва нижня).
      for i in range(1,n):
          if ((a[P[i]][0] < a[P[0]][0]) or 
             ((a[P[i]][0] == a[P[0]][0]) and (a[P[i]][1] < a[P[0]][1]))): 
                 P[i], P[0] = P[0], P[i]  

      H = [P[0]]
      # Якщо всі дані точки розташовано на одній прямій, вивести список з двох крайніх точок і припинити виконання алгоритму.
      line=True;   
      dj=abs(a[0][0]-a[1][0])+abs(a[0][1]-a[1][1])
      j=1
      for i in range(2,n):
          line=line and (rotate(a[P[0]],a[P[1]],a[P[i]])==0)
          di=abs(a[P[0]][0]-a[P[i]][0])+abs(a[P[0]][1]-a[P[i]][1])#шукаємо крайню справа точку
          if dj<di:
            j=i
            dj=di
          if (not line): break
      if (line):
          H.append(P[j])
          return H  

      #Шукати найправішу точку (з даних) щодо поточної точки й робити її поточною доти, 
      #поки поточною знову виявиться стартова вершина. 
      #Точку, яку вже зарахували до оболонки, надалі можна не враховувати.
      del P[0]
      P.append(H[0])
      while True:  
          right = 0
          for i in range(1,len(P)):
            if rotate(points[H[-1]],points[P[right]],points[P[i]])<0:
              right = i
          if P[right]==H[0]: 
            break
          else:
            H.append(P[right])
            del P[right]
      return H


if __name__ == '__main__':
    a = [[0,0],[0,10],[5,5],[10,0],[15,5],[13,5]]
    print(jarvismarch(a))
