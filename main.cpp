/*
    Santosh Bhandari
    1001387116
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

//Global variables.

std::string startCity;         //store the start point of search
std::string destination;       //store the destination
std::string routeFile;         //file where the map is stored
std::string heuristicFile;     //File that is needed to do inform search.
bool isInformedSearch = false; //Track if the program is informed or not
bool isGoalReached = false;    //Track if the goal is reached or not

//Defining struct for city
//Which store path to two node and
//Cost to reach that node.
struct City
{
    std::string startNode;
    std::string endNode;
    float cost;
};
City *cities;      //Array of City to store all data from file
int noOfcites = 0; //Count the no of data in the file

//Defining Fringe that
//store node name cost and
//parent index to that fringe.
struct Fringe
{
    std::string place;
    float ncost;
    float tcost;
    float Hvalue;
    float totalcost;
    int ParentIndex;
};
Fringe *fringes;          //Array of fringe to take node and expand
int noOfFringe = 0;       //Total no of fringe in array
int positionOnFringe = 0; //Position from where data is taken to expand.

//Struct of Heuristic file with name of each node and value correspond to
//that node
struct HVal
{
    std::string city;
    float value;
};
HVal *hval;   //Array of Heuristic file to store all data
int NoOfHval; //Total no heuristic data in file.

//Keep track of nodes that are expanded and generated
int nodeExpanded = 0;
int nodeGenerated = 0;

//Function to sorting Fringe.
bool acompare(Fringe lhs, Fringe rhs)
{
    return lhs.totalcost < rhs.totalcost;
}

//This is the function to read value from
//Heuristic file and store in the array of stuct.
void readHvalue()
{
    int count = 0;      //Count no of path in the file
    std::string line;   //to read file by line
    std::ifstream FILE; //to read file provided by user

    FILE.open(heuristicFile.c_str()); //converting c++ type to c type
    if (!FILE.is_open())
    {
        std::cerr << "File Could not be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }
    while (std::getline(FILE, line))
    {
        if (line.compare("END OF INPUT") == 0)
        {
            break;
        }
        count++;
    }
    hval = new HVal[count];
    FILE.close();

    count = 0;
    FILE.open(heuristicFile.c_str()); //converting c++ type to c type
    if (!FILE.is_open())
    {
        std::cerr << "File Could not be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }
    while (std::getline(FILE, line))
    {
        if (line.compare("END OF INPUT") == 0)
        {
            break;
        }
        HVal temp;
        std::istringstream iss(line);
        iss >> temp.city >> temp.value;
        iss.ignore();

        //Adding values
        hval[count].city = temp.city;
        hval[count].value = temp.value;
        count++;
    }
    FILE.close();
    NoOfHval = count;
}

//This is function that take city name and return then heuristic value
//for that node.
float findHvalue(std::string cityName)
{
    if (isInformedSearch == false)
    {
        return 0;
    }
    else
    {
        int i;
        for (i = 0; i < NoOfHval; i++)
        {
            if (hval[i].city.compare(cityName) == 0)
            {
                return hval[i].value;
            }
        }
        return 0;
    }
}

//This is function to read data from
//input file and store in the vector of
//cities.
//This is function to read data from
//input file and store in the vector of
//cities.
void ReadFile()
{
    int count = 0; //Count no of path in the file

    std::string line;   //to read file by line
    std::ifstream FILE; //to read file provided by user

    FILE.open(routeFile.c_str()); //converting c++ type to c type
    if (!FILE.is_open())
    {
        std::cerr << "File Could not be opened!" << routeFile << std::endl;
        exit(EXIT_FAILURE);
    }
    while (std::getline(FILE, line))
    {
        if (line.compare("END OF INPUT") == 0)
        {
            break;
        }
        count++;
    }
    cities = new City[count * 2];
    fringes = new Fringe[2 * count];
    count = 0;
    FILE.close();
    FILE.open(routeFile.c_str()); //converting c++ type to c type
    if (!FILE.is_open())
    {
        std::cerr << "File Could not be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }
    while (std::getline(FILE, line))
    {
        if (line.compare("END OF INPUT") == 0)
        {
            break;
        }
        City temp;
        std::istringstream iss(line);
        iss >> temp.startNode >> temp.endNode >> temp.cost;
        iss.ignore();

        //Making two struct for each line
        //so that It will be easier to search path
        cities[count].startNode = temp.startNode;
        cities[count].endNode = temp.endNode;
        cities[count].cost = temp.cost;
        count++;
        cities[count].startNode = temp.endNode;
        cities[count].endNode = temp.startNode;
        cities[count].cost = temp.cost;
        count++;
    }
    FILE.close();
    noOfcites = count;
}

//This is the step where the program verify
//if the node is expanded or not
//if not expanded than it expand node and
//gives the new nodes.
void GenerateNode()
{
    for (int j = 0; j < positionOnFringe; j++)
    {
        if (fringes[positionOnFringe].place.compare(fringes[j].place) == 0)
        {
            nodeExpanded++;
            return;
        }
    }
    Fringe temp;
    for (int i = 0; i < noOfcites; i++)
    {
        bool isPresent = false;
        if ((cities[i].startNode).compare(fringes[positionOnFringe].place) == 0)
        {
            fringes[noOfFringe].place = cities[i].endNode;
            fringes[noOfFringe].ncost = cities[i].cost;
            fringes[noOfFringe].tcost = (cities[i].cost + fringes[positionOnFringe].tcost);
            fringes[noOfFringe].Hvalue = findHvalue(fringes[noOfFringe].place);
            fringes[noOfFringe].ParentIndex = positionOnFringe;
            fringes[noOfFringe].totalcost = (fringes[noOfFringe].Hvalue + fringes[noOfFringe].tcost);
            noOfFringe++;
            nodeGenerated++;
        }
    }
    nodeExpanded++;
    std::sort(fringes, fringes + noOfFringe, acompare); //Sorting according to toal cost in Fringe.
}

//Print the output of the program
//It is recursive function to print
//All the path and the total distance.
void printOutput(int position)
{
    if (fringes[position].ParentIndex != -1)
    {
        printOutput(fringes[position].ParentIndex);
        std::cout << fringes[fringes[position].ParentIndex].place
                  << " to " << fringes[position].place
                  << ", " << fringes[position].ncost
                  << " km" << std::endl;
    }
    else
    {
    }
    return;
}

int main(int argc, char *argv[])
{
    routeFile = argv[1];
    startCity = argv[2];
    destination = argv[3];
    if (argc > 4)
    {
        isInformedSearch = true;
        heuristicFile = argv[4];
    }
    ReadFile();
    if (isInformedSearch)
    {
        readHvalue();
    }
    while (!isGoalReached)
    {
        if (noOfFringe == 0)
        {
            fringes[positionOnFringe].place = startCity;
            fringes[positionOnFringe].ncost = 0;
            fringes[positionOnFringe].tcost = 0;
            fringes[positionOnFringe].Hvalue = findHvalue(startCity);
            fringes[positionOnFringe].totalcost = findHvalue(startCity);
            fringes[positionOnFringe].ParentIndex = -1;
            noOfFringe++;
            nodeGenerated++;
        }
        if ((fringes[positionOnFringe].place).compare(destination) == 0)
        {
            nodeExpanded++;
            std::cout << "nodes expanded " << nodeExpanded << std::endl;
            std::cout << "nodes generated " << nodeGenerated << std::endl;
            std::cout << std::fixed;
            std::cout << "distance: ";
            std::cout << std::setprecision(1) << fringes[positionOnFringe].tcost << " km" << std::endl;
            std::cout << "route: " << std::endl;
            printOutput(positionOnFringe);
            isGoalReached = true;
        }
        else if (positionOnFringe == noOfFringe)
        {
            std::cout << "nodes expanded " << nodeExpanded << std::endl;
            std::cout << "nodes generated " << nodeGenerated << std::endl;
            std::cout << "distance infinity " << std::endl;
            std::cout << "route: \n none" << std::endl;
            isGoalReached = true;
        }
        else
        {
            GenerateNode();
            positionOnFringe++;
        }
    }
    return 0;
}
