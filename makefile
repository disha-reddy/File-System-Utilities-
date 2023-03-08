all: myls mysearch mystat mytail

myls: myls-Disha.c
	gcc -Wall myls-Disha.c

mysearch: mysearch-Disha.c
	gcc -Wall mysearch-Disha.c

mystat: mystat-Disha.c
	gcc -Wall mystat-Disha.c

mytail: mytail-Disha.c
	gcc -Wall mytail-Disha.c