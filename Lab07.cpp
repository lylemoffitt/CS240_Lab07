#include "Lab07.h"

using namespace std;

void god::readIn(string fileName)
{
	string num;
	int num2;
    size_t tempNum;
	ifstream fileIn(fileName);
	if(fileIn.bad())
	{
		cout << "Corrupt file" << endl;
		return;
	}
	string item;
	yoPtr contact;
	getline(fileIn, num);
	stringstream convert(num);     //should convert string to int...
    int = stoi(num, tempNum, 10);//Is this the right one? it has more paramters  look at line uhh 33   hah cool...
	//don't think we need this v
    if (!(convert >> num2))//i'll look it up. it has the string, size_t and the base that you want back in, so base 10
		num2 = 0;
    num2 = *tempNum;
	network = num2;
	for(int i=0;i<network;i++)
	{
		if(fileIn.bad())
			break;
		yofile person; //Possibly going to cause errors. Check to see if we need "new".
		getline(fileIn, item);
		person.name = item; //nameIt replaced with assignment
		contact = &person;
		members.push_back(contact);
	}
	for(int i=0; i<network; i++)
		fillInfo(fileIn);

}

void god::fillInfo(ifstream file)
{
	string item;
	char type;
	string num;
	int num2;
	yoPtr contact;
	getline(file, item, ",");
	getline(file, num);
	stringstream convert(num);//should convert string to int....
	if (!(convert >> num2))
		num2 = 0;

	contact = getLink(item);
	contact->friendCount = num;
	for(int i=0; i< num; i++)
	{
		if(file.bad())
			break;
		getline(file, item, ",");
		getline(file, type);
		if(type == 'F')
			contact->friendz.push_back(getLink(item));
		else if(type == 'K')
			contact->kin.push_back(getLink(item));
		else if(type == 'C')
			contact->coworkers.push_back(getLink(item));
		else
			cout << "Invalid Type" << endl;
	}
}

god::yoPtr god::getLink(string theName)
{
	for(int i=0; i<network; i++)
	{
		if(theName == members[i]->name)
			return (yoPtr)members[i];
	}
	cout << "Invalid Friendyofile Name" << endl;
	return nullptr;
}

god::pokedex god::getCat(char type, string pName)
{
	yoPtr contact = getLink(pName);
	//pokedex = typedef std::vector<fptr>
	//finding the size of the inquired list for the member passed in
	pokedex fptrTemp;
	if(type == 'A')//put this in overloaded getCat?
	{
		char cat[3] = "FCK";
		for(int j=0; j<3 ; j++)
		{
			pokedex recTemp = getCat(cat[j], pName);
			fptrTemp.insert(fptrTemp.end(), recTemp.begin(), recTemp.end());
		}
		return fptrTemp;
	}
	int num;
	if(type == 'F')
		num = contact->friendz.size();
	else if(type == 'K')
		num = contact->kin.size();
	else if(type == 'C')
		num = contact->coworkers.size();
	else
		cout << "Invalid Category" << endl;
	//creates a vector of the contacts of the specified member
	for(int i=0; i< num; i++)
	{
		if(type == 'F')
			fptrTemp.push_back( contact->friendz[i] );
		else if(type == 'K')
			fptrTemp.push_back( contact->kin[i] );
		else if(type == 'C')
			fptrTemp.push_back( contact->coworkers[i] );
		else
			cout << "Invalid Category" << endl;
	}
	return fptrTemp;
}

void god::viewCat(char category, string pName)
{
	pokedex profile = getCat(category,pName);
	for( int i=0,j=profile.size(); i<j; i++ )
	{
		cout << profile[i].name << endl;
	}
}

void god::viewAll(std::string pName)
{
	char cat[3] = "FCK";
	for(int j=0; j<3 ; j++)
	{
		viewCat(cat[j],pName);
	}
}

god::pokedex god::getRelations(string relat, string pName)
/*Recursive function with multiple possible call options.
 *Options:	A = ALL
 *			F = friendz
 *			C = coworkers
 *			K = kin
 *The letters specify the relationship path to follow.
 *Examples: *//*
 * "FK", "Bob" will show the friends of the kin of Bob
 * "A" ,"Bob" will show all the people bob knows
 * "AA" , "Bob" will show all the above and everyone they know.
 */

{
	char R = (char)relat[ relat.length() ]; //Store the last char
	pokedex dexTemp= getCat(R, pName);// Get the corresponding pointer
	if (relat.length() <= 1){
		//catch the recursion call and return when only one letter is left
		return dexTemp;
	}
	relat.erase(relat.length());//
	for( int i=0, j=dexTemp.size(); i<j; i++ )
	{
		//Fetch all the links from the person's group
		pokedex recTemp = getRelations(relat, dexTemp[i].name);
		dexTemp.insert(dexTemp.end(), recTemp.begin(), recTemp.end());
		//Append the recieved vector's data to the once currently in use
}
}



