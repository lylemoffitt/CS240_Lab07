#include "Lab07.h"

using namespace std;

void god::readIn(string fileName)
{
	string num;
	int num2;

	ifstream fileIn(fileName);
	if(fileIn.bad())
	{
		cout << "Corrupt file" << endl;
		return;
	}
	string item;
	yoPtr contact;
	getline(fileIn, num);
	stringstream convert(num);
	//should convert string to int....
	if (!(convert >> num2))
		num2 = 0;

	network = num2;
	for(int i=0;i<network;i++)
	{
		if(fileIn.bad())
			break;
		yofile person; //Possibly going to cause errors. Check to see if we need "new".
		getline(fileIn, item);
		person.nameIt(item);
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

god::pokedex god::getCat(char category, string pName)
{
	yoPtr contact = getLink(pName);
	char type = category;
	//pokedex = typedef std::vector<fptr>
	//finding the size of the inquired list for the member passed in
	pokedex fptrTemp;
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
	for( int i=0,j=profile->size(); i<j; i++ )
	{
		cout << profile->at(i).name << endl;
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
/* "FK", "Bob" will show the friends of the kin of bob
 * "A" ,"Bob" will show all the people bob knows
 * "AA" , "Bob" will show all the above and everyone they know.
 */
{
	pokedex fptrTemp;
	if (relat.length() <= 1){
		char rel = relat[0];//get the last char in string
		fptrTemp = getCat(rel, pName);
		return fptrTemp;
	}
	fptrTemp = getCat(relat, pName);
}



