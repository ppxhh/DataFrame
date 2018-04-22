import csv
import numpy as np
import math

def deduce(ff, pp, ss):  
	G = 1
	Ps = 1
	Pa = 1
	Pb = 1
	Ts = 1
	Tb = 1
	rows = 1
	rowb = 1
	rowc = 1
	p1 = 1
	
	result = G / ((ff + pp + ss) * Ps / Pa * math.sqrt(rows * Pb * Ts 
	/ rowb / Ps / Tb) - (p1 * G / Pa / rowc))
	
	return result

a = np.zeros((100), dtype=np.float32)
b = np.zeros((100), dtype=np.float32)
c = np.zeros((100), dtype=np.float32)
d = np.zeros((100), dtype=np.float32)
e = np.zeros((100), dtype=np.float32)
f = np.zeros((100), dtype=np.float32)

print("Please input the ID: ")
ID = input()
name = "data+" + str(ID) + ".csv"

print(name)

fp = open(name,'r') 
rdcsv = csv.reader(fp,dialect='excel')
i=0

print("The value: ")
for row in rdcsv:
	i = i + 1
	if i > 1:		
		a[i-2] = row[1]
		b[i-2] = row[2]
		c[i-2] = row[3]
		d[i-2] = row[4]
		e[i-2] = row[5]
		f[i-2] = row[6]
		print (a[i-2],b[i-2],c[i-2],d[i-2],e[i-2],f[i-2])
			
print(i-1)

sum_a = sum(a)
average_a = sum_a / (i-1)
sum_b = sum(b)
average_b = sum_b / (i-1)
sum_c = sum(c)
average_c = sum_c / (i-1)
sum_d = sum(d)
average_d = sum_d / (i-1)
sum_e = sum(e)
average_e = sum_e / (i-1)
sum_f = sum(f)
average_f = sum_f / (i-1)

print("The average values: ")
print("P1/Bar\t     P2/Bar\tM/KG\t    F1/m3/h\tF2/m3/h\t    F3/m3/h")
print("%lf   %lf   %lf   %lf   %lf   %lf\n" % (average_a,  average_b,  average_c,  average_d,  average_e,  average_f))

result = deduce(average_a, average_b, average_c)
print("The result = %lf" % (result))

filename = 'output.txt' 
with open(filename, 'w') as file_object:
	file_object.write("P1/Bar\t     P2/Bar\tM/KG\t    F1/m3/h\tF2/m3/h\t    F3/m3/h\n")
	file_object.write("%lf   %lf   %lf   %lf   %lf   %lf\n" % (average_a,  average_b,  average_c,  average_d,  average_e,  average_f))
	file_object.write("The result = %lf" % (result)) 

fp.close()
