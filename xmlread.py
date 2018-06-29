#coding=utf-8
import  xml.dom.minidom
from xml.dom import Node

dom = xml.dom.minidom.parse('abc.xml')


root = dom.documentElement
for child in root.childNodes:
	if child.nodeType == Node.ELEMENT_NODE:
		dictAttr = {}
		for key in child.attributes.keys():
			attr = child.attributes[key] 
			dictAttr[attr.name] = attr.value
			print(attr.value)

bb = root.getElementsByTagName('Lambda')
b = bb[0]
print(b.firstChild.data)
bb = root.getElementsByTagName('Refractive_index')
b1 = bb[0]
print(b1.firstChild.data)



