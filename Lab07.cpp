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
	for(int i=0; i< person.friendCount; i++)
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
			contact->coworker.push_back(getLink(item));
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

