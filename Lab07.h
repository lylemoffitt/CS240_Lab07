#include <ios>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
class god { private:
	struct yofile
	{
		int friendCount; //Number of friends this person has
		std::string name; //Their name
		std::vector<yofile*> kin; //The
		std::vector<yofile*> coworkers;
		std::vector<yofile*> friendz;
		std::vector<yofile*> allContacts;
		yofile() // Not sure if we need this, but i added to be safe.
		{
			friendCount = 0;
			name = "";
			/*
			kin.clear();
			coworkers.clear();
			friendz.clear();
			allContacts.clear();
			*/
		}
	};
	//god's data is holy ... ('cuz of all the zeros)
	int network;
	std::vector<yofile*> members; public:
	typedef yofile* yoPtr;
	typedef std::vector<yofile*> yolodex; //it's better than a rolodex
	typedef yolodex* pokedex;
	god();
	//yofile(std::string name);
	bool check(std::string pName);
	void fillInfo(std::ifstream& file); //fills in one person's info from the text
	void readIn(std::string fileName); //reads in file to god vector and creates member objects
	//bool chkCommon(yoPtr one, yoPtr two); //used for checking existance of non mutual friends & for if graph connections
	bool chkCommon(std::string one, std::string two);
	yoPtr getLink(std::string theName); //compares string with vector of pointers to members of the network and returns its address
	yolodex getCat(char category, std::string pName);
	void viewCat(char category, std::string pName);//return a list of references to all the people who have the given relationship to person
	void viewAll(std::string pName);
	void nonMutual();
	void suggestedFriends(std::string pName);
};
