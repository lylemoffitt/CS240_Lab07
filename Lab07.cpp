#include "lab07.h"

using namespace std;

void master::readIn(string fileName)
{
	ifstream fileIn(fileName);
	if(fileIn.bad())
	{
		cout << "Corrupt file" << endl;
		return;
	}
	string item;
	facePtr contact;
	getline(fileIn, network);
	for(int i=0;i<network;i++)
	{
		if(fileIn.bad())
			break;
		face person = new face();
		getline(fileIn, item);
		person.name = item;
		contact = &person;
		members.push_back(contact);
	}
	for(int i=0; i<network; i++)
		fillInfo(fileIn);

}

void face::fillInfo(iftsream& file)
{
	string item;
	char type;
	int num;
	facePtr contact;
	getline(file, item, ",");
	getline(file, num);

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

facePtr master::getLink(string theName)
{
	for(int i=0; i<network; i++)
	{
		if(theName == members[i]->name)
			return (facePtr)members[i];
	}
	cout << "Invalid FriendFace Name" << endl;
	return nullptr;
}

vectFace master::getCat(char category, std::string personName)
{
	facePtr contact = getLink(personName);
	char type = category;
	vectFace fptrTemp;
	int num;
	if(type == 'F')
		num = contact->friendz.size();
	else if(type == 'K')
		num = contact->kin.size();
	else if(type == 'C')
		num = contact->coworkers.size();
	else
		cout << "Invalid Category" << endl;
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

void master::vewCat(char category, std::string personName)
{
	facePtr contact = getLink(personName);
	char type = category;
	vectFace iterator it;
	for(it= fptrTemp.begin(); it!=fptrTemp.end(); it++)
	{
		cout << (*it)->name << endl;
	}
}

