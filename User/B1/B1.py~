import json

with open('ip.json') as my_file:
	data = json.load(my_file)


matrix=[-1]*8

matrix[0]=data["start"]


cnt=0

def Place(r,c):
	for i in range(r):
		if(matrix[i]==c):
			return 0
		elif(abs(matrix[i]-c)==abs(i-r)):
			return 0
	return 1

def printfunc():
	global cnt
	cnt=cnt+1
	print cnt
	for i in range(8):
		for j in range(8):
			if(matrix[i]==j):
				print (i,j)


def Queen(row):
	for column in range(8):
		if(Place(row,column)):
			matrix[row]=column
			if(row==7):
				printfunc()
			else:
				Queen(row+1)
				
						

Queen(0)

