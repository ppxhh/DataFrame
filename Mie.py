#2018/06/14 15:21:48
#Write by Zengxing
#To get Mie theory's result
#Input m = n - k * i
#n: Refractive index; k: Absorption index
#x: Scale parameter
#Thank you for using the code.\

import numpy as np
import math
from Complex import *
import  xml.dom.minidom  #Data use .xml
from xml.dom import Node

PI = 3.141593
m = 10 #input("Please input the number of wavenumber")
Lambda = np.zeros((m), dtype=np.float64)
n_ref = np.zeros((m), dtype=np.float64)
k_ref = np.zeros((m), dtype=np.float64)
d_p = np.zeros((m), dtype=np.float64)
x = np.zeros((m), dtype=np.float64)

dom = xml.dom.minidom.parse('abc.xml')
Data = dom.documentElement
Lam_str = Data.getElementsByTagName('Lambda')
Lam = Lam_str[0]
print(Lam.firstChild.data)
Lam_str = Data.getElementsByTagName('Lambda')
Lam = Lam_str[0]
print(Lam.firstChild.data)
Lam_str = Data.getElementsByTagName('Lambda')
Lam = Lam_str[0]
print(Lam.firstChild.data)

for i in range(0, m):
	x[i] = PI * d_p / Lambda[i]
	



"""
#The library
import numpy as np
import math
import matplotlib.pyplot as plt 

#The Particle class
class Particle():
	def __init__(self, d, Ro, n, k):
		self.d  = d                     #The diameter
		self.Ro = Ro                    #The density
		self.n  = n                     #Complex refractive index
		self.k  = k                     #Absorption index
		#self.an = np.zeros((1000), dtype = np.float64)   #an
		#self.bn = np.zeros((1000), dtype = np.float64)   #bn
		self.Be = np.zeros((1000), dtype = np.float64)   #Be
		self.Be_ = np.zeros((1000), dtype = np.float64)  #Be
		self.Ha = np.zeros((1000), dtype = np.float64)   #Ha
		self.Ha_ = np.zeros((1000), dtype = np.float64)  #Ha
		
	def Bess_n(self, z, n):
		Be_0 = math.cos(z)
		self.Be[0] = math.sin(z)
		self.Be_[0] = - n / z * self.Be[0] + Be_0
		self.Be[1] = (2 * n - 1) / z * self.Be[0] + Be_0
		self.Be_[1] = - n / z * self.Be[1] + self.Be[0]
		for i in range(2, n + 1):
			self.Be[i] = (2 * n - 1) / z * self.Be[i - 1] + self.Be[i - 2]
			self.Be_[i] = -n / z * self.Be[i] + self.Be[i - 1]
			
	def Hank(self, z, n):
		Ha_0 = math.cos(z) - math.sin(z) * j
		self.Ha[0] = math.sin(z) + math.cos(z) * j
		self.Ha_[0] = - n / z * self.Ha[0] + Ha_0
		self.Ha[1] = (2 * n - 1) / z * self.Ha[0] + Ha_0
		self.Ha_[1] = -n / z * self.Ha[1] + self.Ha[0]
		for i in range(2, n + 1):
			self.Ha[i] = (2 * n - 1) / z * self.Ha[i - 1] + self.Ha[i - 2]
			self.Ha_[i] = - n / z * self.Ha[i] + self.Ha[i - 1]
		
	def a_b(self, N):                #The input is m and x
		an = 0
		
print(math.e)
"""
