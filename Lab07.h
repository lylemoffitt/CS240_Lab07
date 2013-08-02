#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <sstream>

class face
{
	public:
		typedef face* fptr;
		face();
		face(std::string name);
		void fillInfo(std::ifstream& file); //fills in one person's info from the text

	private:
		std::string name;
		int friendCount;
		std::vector<fptr> kin;
		std::vector<fptr> coworker;
		std::vector<fptr> friendz;

};

class master: face
{
	public:
		typedef fptr facePtr;
		master();
		void readIn(std::string fileName); //reads in file to master vector and creates member objects
		bool chkCommon(facePtr one, facePtr two); //used for checking existance of non mutual friends & for if graph connections
		facePtr getLink(std::string theName); //compares string with vector of pointers to members of the network and returns its address

	private:
		int network;
		std::vector<facePtr> members;
};






