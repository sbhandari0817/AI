Name: Santosh Bhandari
ID:1001387116

Language used: C++
Omega Copatible:Yes

Structure: 
	The code is composed of 5 function and 1 main part
	acompare is there to compare the fringe and give boolean value
	readHvalue is there to read heuristic file if provided by user
	findHvalue return the heuristic value of the node
	ReadFile reads the input file and store in array of struct called cities. 
	GenerateNode is used to expand and generate the node until the goal is reached the node are sorted and store in fringes
	according to the total cost to reach there from the start state for uninformed search and 
	heuristic value is added for the informed search
	printOutput is used to recursively print the output in desired format if goal is reached
	main function is used to call all this function as required and while loop is used inside 
		main function to loop until goal is reached or deadend is reached if there is no path then 
		output it printed from the main part of the program. 

To run code:
	in omega:
	g++ main.cpp -o find_route
	find_route input.txt StartPoint EndPoint (HeuristicFileIFPResent)
		Note: Startpoint and Endpoint are case sensetive need to enter same 
				as in file 
Tested cases:
	g++ main.cpp -o find_route
	find_route input1.txt Bremen Kassel
	find_route input1.txt Munich Dortmund
	find_route input1.txt Manchester London
	find_route input1.txt London Kassel
	find_route input1.txt Bremen Kassel h_kassel.txt
	find_route input1.txt Munich Kassel h_kassel.txt