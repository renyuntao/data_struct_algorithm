#!/usr/bin/env python

def fibonacciSearch(arr,n,x):
	"""
	Fibonacci Search
	if x in arr[],then return the index of x;
	otherwise,return -1
	"""
	fib2 = 0
	fib1 = 1
	fibm = 1

	while fibm < n:
		fib2 = fib1
		fib1 = fibm
		fibm = fib2 + fib1

	# Initial `offset`
	offset = -1

	while fibm > 1:
		i = min(offset+fib2,n-1)

		if arr[i] < x:
			fibm = fib1
			fib1 = fib2
			fib2 = fibm - fib1
			offset = i
		elif arr[i] > x:
			fibm = fib2
			fib1 = fib1 - fib2
			fib2 = fibm - fib1
		else:
			return i

	# `offset+1` is always the first element of the range
	if fib1 and arr[offset+1] == x:
		return offset+1
	
	return -1

if __name__ == '__main__':
	arr = [10,22,35,40,45,50,80,82,85,90,100]
	length = len(arr)
	x = 85
	print('Found at index:',fibonacciSearch(arr,length,x))
