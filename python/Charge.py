#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Charge.py
#  Write by ZengXin 2018/05/07 10:50:47
#  To solve static electricity problem.

import xlrd                               #Open excel file's library
import xlwt                               #Write excel file's library
import math                               #The math compute library
import numpy as np                        #Array's library
import matplotlib.pyplot as plt           #The plot graph library
import csv                                #The csv library

pi = 3.141593                             #The Circumference rate
g = 9.806650                              #The Gravitational acceleration
#cf = 0.44                                 #The Drag coefficient
g_row = 1.20                              #The detisity of air

class charge():
	def __init__(self, filename):
		self.filename = filename
		self.row = 1410.0                      #The dentisity of particle 1410.0kg/m3
		self.ra = 0.00079                      #The radius of particle is 0.79mm
		self.V = 4 / 3 * pi * (self.ra ** 3)   #The volume of particle
		self.m = self.row * self.V             #The mass of particle
		self.time = 1.0 / 4000.0               #The run time
		self.X_S = np.zeros((1000), dtype = np.float64)   #X's distance
		self.Y_S = np.zeros((1000), dtype = np.float64)   #Y's distance
		self.X_V = np.zeros((1000), dtype = np.float64)   #X's velocity
		self.Y_V = np.zeros((1000), dtype = np.float64)   #Y's velocity
		self.V = np.zeros((1000), dtype = np.float64)     #velocity
		self.X_a = np.zeros((1000), dtype = np.float64)   #X's acceleration
		self.Y_a = np.zeros((1000), dtype = np.float64)   #Y's acceleration
		
		self.q = np.zeros((1000), dtype = np.float64)     #Charge quantity
		self.g = np.zeros((1000), dtype = np.float64)     #Gravity
		self.cf = np.zeros((1000), dtype = np.float64)    #The cf
		self.Re = np.zeros((1000), dtype = np.float64)    #The Re

	
	def OpenFile(self):
		data = xlrd.open_workbook(self.filename)
		table = data.sheets()[0]
		nrows = table.nrows 
		ncols = table.ncols
		num = -1
		for i in range(0, nrows):
			rowValues= table.row_values(i)
			k = 0
			num = num + 1
			for item in rowValues:
				if k == 0:
					self.X_S[num] = float(item) * 0.01 / 67   #0.01/129m
				elif k == 1:
					self.Y_S[num] = float(item) * 0.01 / 67
				k = k + 1
		
		#angtan = input("Please input the tan value:")
		theta = math.atan(-0.01132)#float(angtan)，0.00856082222
		for i in range(0, num + 1):
			self.X_S[i] = self.X_S[i] * math.cos(theta) - self.Y_S[i] * math.sin(theta)
			self.Y_S[i] = self.Y_S[i] * math.cos(theta) + self.X_S[i] * math.sin(theta)
		
		for i in range(0, num - 2):
			self.X_S[i] = (self.X_S[i] + self.X_S[i + 1] + self.X_S[i + 2] +
			 self.X_S[i + 3]) / 4
			self.Y_S[i] = (self.Y_S[i] + self.Y_S[i + 1] + self.Y_S[i + 2] +
			 self.Y_S[i + 3]) / 4
		self.X_S[num - 2] = (self.X_S[num - 2] + self.X_S[num - 1] + self.X_S[num - 0]) / 3
		self.Y_S[num - 2] = (self.Y_S[num - 2] + self.Y_S[num - 1] + self.Y_S[num - 0]) / 3
		
		self.X_S[num - 1] = (self.X_S[num - 1] + self.X_S[num - 0]) / 2
		self.Y_S[num - 1] = (self.Y_S[num - 1] + self.Y_S[num - 0]) / 2
		
		return num                         #Return the number of spot
			
	def Compute(self, num):
		for i in range(0, num - 1):
			#self.X_V[i] = - ((self.X_S[i + 1] - self.X_S[i]) / self.time +
			 #(self.X_S[i + 2] - self.X_S[i +1]) / self.time + ) / 2
			#self.Y_V[i] = - ((self.Y_S[i + 1] - self.Y_S[i]) / self.time +
			 #(self.Y_S[i + 2] - self.Y_S[i +1]) / self.time) / 2
			self.X_V[i] =  (self.X_S[i + 2] - self.X_S[i]) / self.time / 2
			self.Y_V[i] =  (self.Y_S[i + 2] - self.Y_S[i]) / self.time / 2
			 
		self.X_V[num - 1] =  self.X_V[num - 2]
		self.Y_V[num - 1] =  self.Y_V[num - 2]
		
		for i in range(0, num + 1):
			self.V[i] = math.sqrt(self.X_V[i] ** 2 + self.Y_V[i] ** 2)
		
		for i in range(0, num):
			self.X_a[i] = (self.X_V[i + 1] - self.X_V[i]) / self.time
			self.Y_a[i] = (self.Y_V[i + 1] - self.Y_V[i]) / self.time
	
	def cd_sphere(self):
		for i in range(0, num + 1):
			self.Re[i] = 2 * self.ra *self.V[i] / (14.8 * 10 ** (-6))
			if self.Re[i] <= 0.0:
				self.cf[i] = 0.0
			elif self.Re[i] > 8.0e6:
				self.cf[i] = 0.2
			elif self.Re[i] > 0.0 and self.Re[i] <= 0.5:
				self.cf[i] = 24.0 / self.Re[i]
			elif self.Re[i] > 0.5 and self.Re[i] <= 100.0:
				p = np.array([4.22, -14.05, 34.87, 0.658])
				self.cf[i] = np.polyval(p, 1.0 / self.Re[i])
			elif  self.Re[i] > 100.0 and  self.Re[i] <= 1.0e4:
				p = np.array([-30.41, 43.72, -17.08, 2.41])
				self.cf[i] = np.polyval(p, 1.0 / np.log10(self.Re[i]))
			elif self.Re[i] > 1.0e4 and self.Re[i] <= 3.35e5:
				p = np.array([-0.1584, 2.031, -8.472, 11.932])
				self.cf[i] = np.polyval(p, np.log10(self.Re[i]))
			elif self.Re[i] > 3.35e5 and self.Re[i] <= 5.0e5:
				x1 = np.log10(self.Re[i] / 4.5e5)
				self.cf[i] = 91.08 * x1 ** 4 + 0.0764
			else:
				p = np.array([-0.06338, 1.1905, -7.332, 14.93])
				self.cf[i] = np.polyval(p, np.log10(self.Re[i]))
			
	
	def Charge(self):
		print("Please input the Y data is down or up, if down please input 1, if up please input 2")
		state = input()		
		for i in range(0, num):
			F_x = self.m * self.X_a[i]
			F_y = self.m * self.Y_a[i]
			self.q[i] = (F_x - 0.5 * self.cf[i] * g_row * pi * (self.ra ** 2) * self.X_V[i] * self.X_V[i]) / 35000 * 0.15
			if int(state) == 1:
				self.g[i] = (F_y + 0.5 * self.cf[i] * g_row * pi * (self.ra ** 2)
				 * self.Y_V[i] * self.Y_V[i]) / self.m
			else:
				self.g[i] = (F_y - 0.5 * self.cf[i] * g_row * pi * (self.ra ** 2) 
				* self.Y_V[i] * self.Y_V[i]) / self.m
	
	def Fit(self, k):
		X = np.zeros((k), dtype = np.float64)
		Y = np.zeros((k), dtype = np.float64)
		print("Please input x or y, if fit x input 1, fit y input 2")
		fit_value = input()
		for i in range(0, k):
			X[i] = self.X_S[i]
			Y[i] = self.Y_S[i]
		if int(fit_value) == 1:
			z = np.polyfit(Y, X, 1)
			p = np.poly1d(z)
			for i in range(0, k):
				self.X_S[i] = p(self.Y_S[i])
		else:
			z = np.polyfit(X, Y, 2)
			p = np.poly1d(z)
			for i in range(0, k):
				self.Y_S[i] = p(self.X_S[i])
		#y = p(Y)
		
		#plot = plt.plot(X, Y, 'r',label='polyfit values')
		#plt.show()
		
		
	def SaveData(self, k):
		result = "resultnew" + self.filename
		print("The result is save as %s" % (result))
		book = xlwt.Workbook(encoding = 'utf-8', style_compression=0)
		sheet = book.add_sheet('test', cell_overwrite_ok=True)
		sheet.write(0, 0, 'x')
		sheet.write(0, 1, 'y')
		sheet.write(0, 2, 'x_v')
		sheet.write(0, 3, 'y_v')
		sheet.write(0, 4, 'v')
		sheet.write(0, 5, 'x_a')
		sheet.write(0, 6, 'y_a')
		sheet.write(0, 7, 'charge')
		sheet.write(0, 8, 'gravity')
		sheet.write(0, 9, 'Re')
		sheet.write(0, 10, 'cf')
		
		
		for i in range(0, k - 5):
			sheet.write(i + 1, 0, obj.X_S[i])
			sheet.write(i + 1, 1, obj.Y_S[i])
			sheet.write(i + 1, 2, obj.X_V[i])
			sheet.write(i + 1, 3, obj.Y_V[i])
			sheet.write(i + 1, 4, obj.V[i])
			sheet.write(i + 1, 5, obj.X_a[i])
			sheet.write(i + 1, 6, obj.Y_a[i])
			sheet.write(i + 1, 7, obj.q[i])
			sheet.write(i + 1, 8, obj.g[i])
			sheet.write(i + 1, 9, obj.Re[i])
			sheet.write(i + 1, 10, obj.cf[i])
			
		book.save(result)
	
	def SaveCharge(self, k):
		f = open("charge.txt", "w")
		for i in range(0, k - 5):
			print("%.8e" % (obj.q[i]))
			f.write(str(obj.q[i]))
			f.write("\n")

#Open filename = txt
f = open('filename.txt')
filename = f.read()
#filename = "Vaccum15KV1449071_2centroid.xls"
obj = charge(filename)
num = obj.OpenFile()
obj.Fit(num + 1)
obj.Compute(num)
obj.cd_sphere()
obj.Charge()
obj.SaveData(num)

"""
print("The number of data plots is: \t%d" % (num + 1))
print("The partice's mass is: \t%.6e kg" % (obj.m))
print("The displacement: ")
for i in range(0, num + 1):
	print("%.12lf\t%.12lf" % (obj.X_S[i], obj.Y_S[i]))

print("The velocity: ")
print("x\ty\tz")
for i in range(0, num):
	print("%.8lf\t%.8lf\t%.8lf" % (obj.X_V[i], obj.Y_V[i], obj.V[i]))

print("The acceleration: ")
for i in range(0, num - 1):
	print("%.8lf\t%.8lf" % (obj.X_a[i], obj.Y_a[i]))
	
print("The charge: ")
"""
