import numpy as np  #一个用python实现的科学计算包

def f1(x, y):
	return (-1)*x*x*y*y #函数式 

def f2(x):
	return 3/(1+x*x*x) #精确解

def Ac(a, b, h):  #精确解函数
	x = np.zeros((100), dtype=np.float32)
	ac = np.zeros((100), dtype=np.float32)
	x[0] = a
	i = 0
	print("Print the accurate result: \n")
	while i < (b-a)/h+1:
		x[i]=x[0]+i*h
		ac[i]=f2(x[i])
		
		print("result[%d" % (i) + "] = %f" % (ac[i]) + "\n")
		i += 1
		
def RK4(a, b, h, c): #RK4方法函数

	i = 0
	x = np.zeros((100), dtype=np.float32)
	y = np.zeros((100), dtype=np.float32)
	y[0] = c
	x[0] = a
	print("Print the Runge-Kutta's result:\n")
	while i < (b-a)/h+1:
		x[i] = x[0]+i*h
		k1 = f1(x[i],y[i])
		k2 = f1((x[i]+h/2),(y[i]+h*k1/2))
		k3 = f1((x[i]+h/2),(y[i]+h*k2/2))
		k4 = f1((x[i]+h),(y[i]+h*k3))
		
		y[i+1] = y[i]+h*(k1+k2*2+k3*2+k4)/6
		error = abs(y[i] - f2(x[i]))
		print("y[%d" % (i) + "] = %f" % (y[i]) + "\t" + "error: %f\t" % (error) + "\n")
		i += 1
		
def AB4(a, b, c): #AB4方法函数
	x = np.zeros((100), dtype=np.float32)
	y = np.zeros((100), dtype=np.float32)
	y1 = np.zeros((100), dtype=np.float32)
	y[0] = c
	x[0] = a
	i = 0
	print("Print the AB4s's result:\n")
	while i <= (b-a)/h+1:
		x[i] = x[0]+i*h
		k1 = f1(x[i],y[i])
		k2 = f1((x[i]+h/2),(y[i]+h*k1/2))
		k3 = f1((x[i]+h/2),(y[i]+h*k2/2))
		k4 = f1((x[i]+h),(y[i]+h*k3))
		y[i+1] = y[i]+h*(k1+k2*2+k3*2+k4)/6
		i += 1
	j = 3
	y1[0] = y[0]
	y1[1] = y[1]
	y1[2] = y[2]
	y1[3] = y[3]
	while (j <(b - a)/h + 1):
		y1[j+1] = y1[j]+(55*f1(x[j],y1[j])-59*f1(x[j-1],y1[j-1])+37*
		f1(x[j-2],y1[j-2])-9*f1(x[j-3],y1[j-3]))*h/24
		error = abs(y[j] - f2(x[j]))
		print("y1[%d" % (j) + "] = %f" % (y1[j]) + "\t" + "error: %f\t" % (error) + "\n")
		j += 1
		
def AB4_AM4(a,b,h,c): #AB4-AM4方法函数
	x = np.zeros((100), dtype=np.float32)
	y = np.zeros((100), dtype=np.float32)
	y1 = np.zeros((100), dtype=np.float32)
	y11 = np.zeros((100), dtype=np.float32)
	y[0] = c
	x[0] = a
	i = 0
	print("Print the AB4_AM4's result:\n")
	while i <= (b-a)/h+1:
		x[i] = x[0]+i*h
		k1 = f1(x[i],y[i])
		k2 = f1((x[i]+h/2),(y[i]+h*k1/2))
		k3 = f1((x[i]+h/2),(y[i]+h*k2/2))
		k4 = f1((x[i]+h),(y[i]+h*k3))
		y[i+1] = y[i]+h*(k1+k2*2+k3*2+k4)/6
		i += 1
	j = 3
	y1[0] = y[0]
	y1[1] = y[1]
	y1[2] = y[2]
	y1[3] = y[3]
	while (j <(b - a)/h + 1):
		y1[j+1] = y1[j]+(55*f1(x[j],y1[j])-59*f1(x[j-1],y1[j-1])+37*f1(x[j-2],y1[j-2])- 9*f1(x[j-3],y1[j-3]))*h/24
		y11[j+1] = y1[j]+(9*f1(x[j+1],y1[j+1])+19*f1(x[j],y1[j])-5*f1(x[j-1],y1[j-1])+ f1(x[j-2],y1[j-2]))*h/24
		y1[j+1] = y11[j+1]
		error = abs(y1[j] - f2(x[j]))
		print("y1[%d" % (j) + "] = %f" % (y1[j]) + "\t" + "error: %f\t" % (error) + "\n")
		j += 1
				
def AB4_AM4_new(a,b,h,c): #AB4-AM4改进方法函数
	x = np.zeros((100), dtype=np.float32)
	y = np.zeros((100), dtype=np.float32)
	y1 = np.zeros((100), dtype=np.float32)
	y2 = np.zeros((100), dtype=np.float32)
	y3 = np.zeros((100), dtype=np.float32)
	y[0] = c
	x[0] = a
	i = 0
	print("Print the AB4_AM4_new's result:\n")
	while i <= (b-a)/h+1:
		x[i] = x[0]+i*h
		k1 = f1(x[i],y[i])
		k2 = f1((x[i]+h/2),(y[i]+h*k1/2))
		k3 = f1((x[i]+h/2),(y[i]+h*k2/2))
		k4 = f1((x[i]+h),(y[i]+h*k3))
		y[i+1] = y[i]+h*(k1+k2*2+k3*2+k4)/6
		i += 1
	j = 3
	y1[0] = y[0]
	y1[1] = y[1]
	y1[2] = y[2]
	y1[3] = y[3]
	while (j <(b - a)/h + 1):
		y1[j+1] = y1[j]+(55*f1(x[j],y1[j])-59*f1(x[j-1],y1[j-1])+37*f1(x[j-2],y1[j-2])- 9*f1(x[j-3],y1[j-3]))*h/24
		y2[j+1] = y1[j]+(9*f1(x[j+1],y1[j+1])+19*f1(x[j],y1[j])-5*f1(x[j-1],y1[j-1])+ f1(x[j-2],y1[j-2]))*h/24
		y3[j+1] = y1[j+1]*251/270+y2[j+1]*19/270
		y1[j+1] = y3[j+1]
		error = abs(y1[j] - f2(x[j]))
		print("y1[%d" % (j) + "] = %f" % (y1[j]) + "\t" + "error: %f\t" % (error) + "\n")
		j += 1
				
print("Please input the up and down Section, step langth and initlise value:\n")
a = 0 #The down value
b = 1.5 #The up value
h = 0.1 #The step length
c = 3  #The y(0)

Ac(a, b, h)
RK4(a,b,h,c)
AB4(a,b,c)
AB4_AM4(a,b,h,c)
AB4_AM4_new(a,b,h,c)
