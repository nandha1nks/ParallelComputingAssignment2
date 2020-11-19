I have set no. of threads to 2^no. of digits in the matrix size
I have observed the running time is less in multiples of 4, (searching for reasons, dont know is that fully correct)
After some certain number the increase in num of threads doesn't give significant increase or drop, so I thought take the least number
The time kept changing, causing the analysis to be difficult and may be inacurate. 

In the plots, points are not marked. Couldn't find a good software to do that. So, I listing the points here.

S.No 	|Mat. Size 	|Running Time of All Iterations	| No. of Iterations	| Running time of 1 Iterations  |
1		|	10		|				1				|		219			|			0.0045				|
2		|	20		|				7				|		694			|			0.01				|
3		|	30		|				10				|		595			|			0.016				|
4		|	50		|				22				|		705			|			0.03				|
5		|	75		|				70				|		1174		|			0.06				|
6		|	100		|				97				|		1067		|			0.09				|
7		|	200		|				384				|		1266		|			0.3					|
8		|	300		|				677				|		1010		|			0.67				|
9		|	500		|				2651			|		1083		|			2.4					|
10		|	750		|				6506			|		1242		|			5.2					|
11		|	1000	|				8676			|		1153		|			7.5					|
12		|	2000	|				41305			|		1246		|			33					|	