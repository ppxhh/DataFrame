#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sympy
import numpy as np

t = np.zeros((1000), dtype = np.float32)
d = np.zeros((1000), dtype = np.float32)
h = np.zeros((1000), dtype = np.float32)

#Open file
import xlrd
f = open('filename.txt')
filename = f.read()
data = xlrd.open_workbook(filename)
table = data.sheets()[0]
nrows = table.nrows 
ncols = table.ncols

rowValues= table.row_values(1)
ll = 0
for item in rowValues:
	if ll == 2:
		a = float(item)
	elif ll == 3:
		b = float(item)
	else:
		c = float(item)
	ll = ll + 1

print("a, b, c: %.12lf %.12lf %.12lf" % (a, b, c))

p = -1
for i in range(3, nrows):
	rowValues= table.row_values(i)
	k = 0
	p = p + 1
	for item in rowValues:
		if k == 0:
			t[p] = float(item)
		elif k == 1:
			d[p] = float(item)
		k = k + 1
		
print("The d with time:")
for i in range(0, p + 1):
	print("%.12lf %.12lf" % (t[i], d[i]))

print("The result h is: ")
for i in range(0, p + 1):
	x = sympy.Symbol('x')
	hh = sympy.solve(a * x ** 3 + b * x ** 2 + c * x + d[i], x)
	h[i] = hh[0]
	print("%.12lf" % h[i])

print("The result is save in result.txt!")
f1 = open('result.txt', 'w')
for i in range(0, p + 1):
	f1.write(str(h[i]))
	f1.write("\n")
