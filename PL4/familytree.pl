/* 	Karin Dion and Benjamin Malz 

	Program: 	dion_malz.pl

	Purpose:	to search a family tree to answer simple queries
				about family relationships 
	Input:		the following queries can be submitted by the user:
					mother(X,Y).                auntoruncle(X,Y).
					father(X,Y).                cousin(X,Y).
					parent(X,Y).                greatgrandmother(X,Y).
					sibling(X,Y).               greatgrandfather(X,Y).
					grandfather(X,Y).           spouse(X,Y).
					grandmother(X,Y).           nieceornephew(X,Y).
					grandparent(X,Y).	
				X and Y can be replaced by the name of a person or simply
				left as a X or Y	
	Output:		if the query is true, a PROLOG response of "yes" will be 
				printed in the terminal - if the query is false, or if there
				is not enough information in the database to answer the 
				query, a PROLOG response of "no" will be printed in the 
				terminal - if there are multiple answers to a query, the 
				user will input a ";" to see the next answer(s)
*/


mother(michael,marie).
mother(mark,gail).
mother(sonja,christl).
mother(marie,elise).
mother(kim,gail).
mother(elke,christl).
mother(larry,beatrice).
mother(bruce,gail).
mother(max,elise).
mother(berta,elise).
mother(nicole,addie).
mother(reinhard,irmgard).
mother(hans,elise).
mother(meleita,addie).
mother(lisa,regina).
mother(norman,beatrice).
mother(joey,addie).
mother(trina,regina).
mother(george,beatrice).
mother(hanni,elise).
mother(mj,christine).
mother(christl,elise).
mother(edith,hanni).
mother(john,jennifer).
mother(luke,jen).
mother(adam,jen).
mother(bettina,christl).
father(luke,michael).
father(adam,michael).
father(bettina,heinz).
father(christl,bernhard).
father(edith,erwin).
father(john,bruce).
father(george,gerard).
father(hanni,bernhard).
father(mj,mark).
father(norman,gerard).
father(joey,norman).
father(trina,reinhard).
father(hans,bernhard).
father(meleita,norman).
father(lisa,reinhard).
father(berta,bernhard).
father(nicole,norman).
father(reinhard,max).
father(larry,gerard).
father(bruce,george).
father(max,bernhard).
father(marie,bernhard).
father(kim,george).
father(elke,heinz).
father(michael,larry).
father(mark,george).
father(sonja,heinz).

parent(X,Y):- 
	father(X,Y);
	mother(X,Y).

sibling(X,Y):-
	parent(X,A),
	parent(Y,A),
	X \= Y.

grandfather(X,Y):-
	parent(X,A),
	father(A,Y).

grandmother(X,Y):-
	parent(X,A),
	mother(A,Y).

grandparent(X,Y):-
	grandfather(X,Y);
	grandmother(X,Y).

auntoruncle(X,Y):-
	parent(X,A),
	sibling(A,Y),
	X \= Y.

auntoruncle(X,Y):-
	/* not blood related */
	parent(X,A),
	sibling(A,B),
	spouse(B,Y),
	X \= Y.

cousin(X,Y):-
	parent(X,A),
	sibling(A,B),
	parent(Y,B),
	X \= Y.

greatgrandmother(X,Y):-
	parent(X,A),
	parent(A,B),
	mother(B,Y).

greatgrandfather(X,Y):-
	parent(X,A),
	parent(A,B),
	father(B,Y).

nieceornephew(X,Y):-
	sibling(A,Y),
	parent(X,A),
	X \= Y.

nieceornephew(X,Y):-
	/* not blood related */
	spouse(Y,A),
	sibling(A,B),
	parent(X,B),
	X \= Y.

spouse(X,Y):-
	parent(A,X),
	parent(A,Y),
	X \= Y.
