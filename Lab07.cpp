#include "Lab07.h"

using namespace std;
//constructor
god::god()
{
	network = 0;
	members.reserve(10);
	yofile();
}

//checks to see if the member entered is in the network
bool god::check(string pName)
{
	for(int i=0;i<members.size();i++)
	{
		if(pName.compare(members[i]->name) == 0)
			return true;
	}
	return false;
}

//begins building the object for creating FriendFace
//reads in the network size and all of the names afterwards
void god::readIn(string fileName)
{
	string num;
	int num2;
	size_t *tempNum=0;



	ifstream fileIn(fileName);
	if(fileIn.bad())//checks to see if file is corrupt
	{
		cout << "Corrupt file" << endl;
		return;
	}
	string item;
	getline(fileIn, num);
	num2 = stoi(num, tempNum, 10);

	network = num2; //sets the class int variable to the size of the network
	for(int i=0;i<network;i++)
	{
		if(fileIn.eof())
			break;
		getline(fileIn, item);
		yofile *person= new yofile; //allocates a new struct on the heap for each member
		(*person).name = item;//sets the name of the struct for each member
		yoPtr contact = new yofile; //creats a pointer->struct on the heap
		contact = person; //sets the pointer to the struct
		members.push_back(contact); //pushes the pointer into the member vector

	}
	//after all of the structs and the member vector has been made, we send it to
	//fillInfo to construct one member's connections
	//repeatedly goes in to construct each member's contacts and pointers
	for(int i=0; i<network; i++)
		fillInfo(fileIn);
}

//after readin, fills in the information and connects the links to from
//the member's contacts to their respective structs
void god::fillInfo(ifstream& file)
{
	string item, type;
	string num;
	int num2;
	yoPtr contact;
	getline(file, item,',');//reads in the name and their number of friends
	getline(file, num);
	size_t *tempNum=0;
	num2 = stoi(num, tempNum, 10); //converts it to an int

	contact = getLink(item);
	contact->friendCount = num2;
	for(int i=0; i< num2; i++)
	{
		if(file.bad())
			break;
		getline(file, item, ','); //gets contacts their type of relationship to the memeber
		getline(file, type);
		if(type.at(0) == ' ')//gets rid of the space
			type.erase(0,1);
		//depending in the type of relationship, the member is pushed into their respective vector
		//as well as a master vector, all contacts
		if(type == "F")
		{
			contact->friendz.push_back(getLink(item));
			contact->allContacts.push_back(getLink(item));
		}
		else if(type == "K")
		{
			contact->kin.push_back(getLink(item));
			contact->allContacts.push_back(getLink(item));
		}
		else if(type == "C")
		{
			contact->coworkers.push_back(getLink(item));
			contact->allContacts.push_back(getLink(item));
		}
		else
			cout << "Invalid Type" << endl;
	}
}

//takes in a memeber name and searches through the memnber (master) vector for them
//returns it's pointer
god::yoPtr god::getLink(string theName)
{
	for(int i=0; i<network; i++)
	{
		if(theName == members[i]->name)
			return members[i];
	}
	cout << "Invalid Friendyofile Name" << endl;
	return nullptr;
}

//takes in a char and a string for the type of contact and member name, repectively
//returns the vector carrying the pointer to these contacts
god::yolodex god::getCat(char category, string pName)
{
	yoPtr contact = getLink(pName);
	char type = category;
	//pokedex = typedef std::vector<fptr>
	//finding the size of the inquired list for the member passed in
	//pokedex fptrTemp;
	yolodex vecTemp;
	int num;
	if(type == 'F') //checks to see which of contact vctors needed
		num = contact->friendz.size();
	else if(type == 'K')
		num = contact->kin.size();
	else if(type == 'C')
		num = contact->coworkers.size();
	else
		cout << "Invalid Category" << endl;
	//creates a vector of the contacts of the specified member
	for(int i=0; i< num; i++)//then creates a temp vector that
	{//carries all of the contacts asked for and returns it
		if(type == 'F')
			vecTemp.push_back( contact->friendz[i] );
		else if(type == 'K')
			vecTemp.push_back( contact->kin[i] );
		else if(type == 'C')
			vecTemp.push_back( contact->coworkers[i] );
		else
			cout << "Invalid Category" << endl;
	}
	//fptrTemp = vecTemp;
	return vecTemp;
}

//takes in a category and the member name
//uses getcat to get the F, K, C vector and prints out their contacts under that category
void god::viewCat(char category, string pName)
{
	yolodex profile = getCat(category,pName);
	for( int i=0,j=profile.size(); i<j; i++ )
	{
		cout << profile[i]->name << endl;
	}
}

//calls viewcat to view all of the conatcts of a member
void god::viewAll(std::string pName)
{
	char cat[] = "FCK";
	for(int j=0; j<3 ; j++)
	{
		viewCat(cat[j],pName);
	}
}

//checks to see if two people are connected
//returns true if hey are and false if they aren't
bool god::chkCommon(string one, string two)
{
	yoPtr memberPtr = getLink(one);
	int i=0, j=0;
	for(i=0; i<memberPtr->allContacts.size(); i++)
	{//checks to see if 'two' matches any of the friends contained in one's contacts
		if(two == memberPtr->allContacts[i]->name)
			return true;
	}
	for(i=0; i<memberPtr->allContacts.size();i++)
	{//if not then recursesusing one of 'one's friends in their contacts
	//and checks to see if 'two' matches any of their contacts and so on
		j = chkCommon(memberPtr->allContacts[i]->name, two);
		if(j==1)
			return true;
	}
	return false;
}

//checks to see who in the network are nonmutual connections
void god::nonMutual()
{
	int flag=0;
	//yoPtr temp = nullptr;
    for(int i = 0; i < network; i++)//creates a loop to check all of the members in the network
    {
        for(int j=0; j <members[i]->friendCount; j++)//then for each member, checks all of their contacts
        {
            yoPtr match = getLink(members[i]->allContacts[j]->name); //we get the link to the member in persepctive
			if(match->friendCount==0)//we check to see if they have any friends and if they don't
				flag = 1; //then set the flag to show nonmutual
		for(int k=0; k <match->friendCount; k++) //then search the member's friend's friends to see if the member is their friend
                {
			if( members[i]->name != match->allContacts[k]->name)//if the member is not equal to member's friend's contact
			{
				flag=1;
			}
			else
                	{
				flag=0;
				break;
			}
                }
		if(flag == 1)//then if the flag is set print out the match
		{
			cout<<members[i]->name<<" and "<<match->name<<endl;
			flag = 0;
		}
        }
    }
}

            

void god::suggestedFriends(string pName)
// Takes in a string and searches for all relations in order.
// Priority is dictated by proceedural order.
// 

{
	yoPtr memPtr = getLink(pName);
	vector<string> sugFrList;
	int i,j;
	// Friends of friends
	for(i=0; i<memPtr->friendz.size();i++)
		for(j=0; j<memPtr->friendz[i]->friendz.size();j++)
			sugFrList.push_back(memPtr->friendz[i]->friendz[j]->name);
    // Friends of family
	for(i=0; i<memPtr->kin.size();i++)
		for(j=0; j<memPtr->kin[i]->friendz.size();j++)
			sugFrList.push_back(memPtr->kin[i]->friendz[j]->name);
    // Family of Friends
	for(i=0; i<memPtr->friendz.size();i++)
		for(j=0; j<memPtr->friendz[i]->kin.size();j++)
			sugFrList.push_back(memPtr->friendz[i]->kin[j]->name);
    // Family of family
	for(i=0; i<memPtr->kin.size();i++)
		for(j=0; j<memPtr->kin[i]->kin.size();j++)
			sugFrList.push_back(memPtr->kin[i]->kin[j]->name);
    // Coworkers of coworkers
	for(i=0; i<memPtr->coworkers.size();i++)
		for(j=0; j<memPtr->coworkers[i]->coworkers.size();j++)
			sugFrList.push_back(memPtr->coworkers[i]->coworkers[j]->name);
    // Friends of coworkers
	for(i=0; i<memPtr->coworkers.size();i++)
		for(j=0; j<memPtr->coworkers[i]->friendz.size();j++)
			sugFrList.push_back(memPtr->coworkers[i]->friendz[j]->name);
	// Coworkers of friends
	for(i=0; i<memPtr->friendz.size();i++)
		for(j=0; j<memPtr->friendz[i]->coworkers.size();j++)
			sugFrList.push_back(memPtr->friendz[i]->coworkers[j]->name);
    // Coworkers of family
	for(i=0; i<memPtr->kin.size();i++)
		for(j=0; j<memPtr->kin[i]->coworkers.size();j++)
			sugFrList.push_back(memPtr->kin[i]->coworkers[j]->name);
    // Family of coworkers
	for(i=0; i<memPtr->coworkers.size();i++)
		for(j=0; j<memPtr->coworkers[i]->kin.size();j++)
			sugFrList.push_back(memPtr->coworkers[i]->kin[j]->name);
			
	vector<string> matches; // Create temp storage vectors for matches
	int k, flag=0;
    // Copy each name only once into the 'matches' vector
	for (i=0; i < sugFrList.size(); i++  )
	{
		for(j=0;j<matches.size();j++)
		{
			if(sugFrList[i].compare(matches[j]) == 0)
				break;
		}
		if(j >= matches.size())
			matches.push_back(sugFrList[i]);
	}
	// Print out all people who are not matched (i.e. known)
	for(i=0;i<matches.size();i++)
	{
		for(j=0;j<memPtr->allContacts.size(); j++)
		{
			if(matches[i].compare(memPtr->allContacts[j]->name) ==0)
			{
				flag = 0;
				break;
			}
			else
			{
				flag =1;
			}
		}
		if((pName.compare(matches[i]) != 0) && flag ==1)
			cout << matches[i] << endl;			
	}   
	sugFrList.clear();// Empty out the list for the next function call
	
}

