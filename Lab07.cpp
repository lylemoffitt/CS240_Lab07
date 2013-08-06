#include "Lab07.h"

using namespace std;

god::god()
{
    network = 0;
	members.reserve(10);
	yofile();
}


void god::readIn(string fileName)
{
	string num;
	int num2;
	size_t *tempNum=0;

	fstream fileIn;
	fileIn.open(fileName.c_str(),fstream::in);
	
	if(fileIn.fail())
	{
		cout << "Corrupt file" << endl;
		return;
	}
	string item;
	//yoPtr contact = nullptr;
	getline(fileIn, num);
	//stringstream convert(num);
	num2 = stoi(num, tempNum, 10);
	
	//should convert string to int....
	//if (!(convert >> num2))
		//num2 = 0;

	network = num2;
	yofile tempArr[100];
	for(int i=0;i<network;i++)
	{
		if(fileIn.eof())
			break;
		getline(fileIn, item);
		yofile person; //Possibly going to cause errors. Check to see if we need "new".
		person.name = item;
		//person.nameIt(item);
		//yoPtr contact = &person;
		tempArr[i] = person;
		members.push_back(&tempArr[i]);
		
	}
	for(int i=0; i<network; i++)
		fillInfo(fileIn);
	/*
	cout << "alice\n";
	viewCat('F', "Alice");
	viewCat('K', "Alice");
	viewCat('C', "Alice");
	cout << "\nbob\n";
	viewCat('F', "Bob");
	viewCat('K', "Bob");
	viewCat('C', "Bob");
	cout << "\nDanielle\n";
	viewCat('F', "Danielle");
	viewCat('K', "Danielle");
	viewCat('C', "Danielle");
	cout << "\nfred\n";
	viewCat('F', "Fred");
	viewCat('K', "Fred");
	viewCat('C', "Fred");
	cout << "\nelsie\n";
	viewCat('F', "Elsie");
	viewCat('K', "Elsie");
	viewCat('C', "Elsie");
	cout << "\ncarl\n";
	viewCat('F', "Carl");
	viewCat('K', "Carl");
	viewCat('C', "Carl");
	
	cout << "a, b, d, c, f, e";
	viewAll("Alice");
	viewAll("Bob");
	viewAll("Danielle");
	viewAll("Carl");
	viewAll("Fred");
	viewAll("Elsie");
	
	int i =3;
	i = chkCommon("Alice", "Bob");
	cout << i << endl;
	i = chkCommon("Alice", "Danielle");
	cout << i << endl;
	i = chkCommon("Alice", "Fred");
	cout << i << endl;
	i = chkCommon("Alice", "Elsie");
	cout << i << endl;
	i = chkCommon("Alice", "Carl");
	cout << i << endl;
	i = chkCommon("Danielle", "Bob");
	cout << i << endl;
	i = chkCommon("Fred", "Bob");
	cout << i << endl;
	i = chkCommon("Carl", "Bob");
	cout << i << endl;
	i = chkCommon("Elsie", "Bob");
	cout << i << endl;
	i = chkCommon("Danielle", "Carl");
	cout << i << endl;
	i = chkCommon("Danielle", "Fred");
	cout << i << endl;
	i = chkCommon("Danielle", "Elsie");
	cout << i << endl;
	i = chkCommon("Carl", "Elsie");
	cout << i << endl;
	i = chkCommon("Carl", "Fred");
	cout << i << endl;
	i = chkCommon("Fred", "Elsie");
	cout << i << endl;
	i = chkCommon("Jorge", "George");
	cout << i << endl;
	i = chkCommon("Jorge", "Alice");
	cout << i << endl;
	i = chkCommon("George", "Bob");
	cout << i << endl;
	

	nonMutual();
	*/
	cout << "Alice\n";
	suggestedFriends("Alice");
	cout << "\nBob\n";
	suggestedFriends("Bob");
	cout << "\nCarl\n";
	suggestedFriends("Carl");
	cout << "\nDanielle\n";
	suggestedFriends("Danielle");
	cout << "\nElsie\n";
	suggestedFriends("Elsie");
	cout << "\nFred\n";
	suggestedFriends("Fred");
	cout << "\nJorge\n";
	suggestedFriends("Jorge");
	cout << "\nGeorge\n";
	suggestedFriends("George");


}

void god::fillInfo(ifstream& file)
{
	string item, type;
	string num;
	int num2;
	yoPtr contact;
	getline(file, item,',');
	getline(file, num);
	size_t *tempNum=0;
	num2 = stoi(num, tempNum, 10);

	contact = getLink(item);
	contact->friendCount = num2;
	for(int i=0; i< num2; i++)
	{
		if(file.bad())
			break;
		getline(file, item, ',');
		getline(file, type);
		if(type.at(0) == ' ')
			type.erase(0,1);
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

god::yolodex god::getCat(char category, string pName)
{
	yoPtr contact = getLink(pName);
	char type = category;
	//pokedex = typedef std::vector<fptr>
	//finding the size of the inquired list for the member passed in
	//pokedex fptrTemp;
	yolodex vecTemp;
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
			vecTemp.push_back( contact->friendz[i] );
		else if(type == 'K')
			vecTemp.push_back( contact->kin[i] );
		else if(type == 'C')
			vecTemp.push_back( contact->coworkers[i] );
		else
			cout << "Invalid Category" << endl;
	}
	//*fptrTemp = vecTemp;
	return vecTemp;
}

void god::viewCat(char category, string pName)
{
	yolodex profile = getCat(category,pName);
	for( int i=0,j=profile.size(); i<j; i++ )
	{
		cout << profile[i]->name << endl;
	}
}

void god::viewAll(std::string pName)
{
	char cat[] = "FCK";
	for(int j=0; j<3 ; j++)
	{
		viewCat(cat[j],pName);
	}
}

god::yolodex god::getRelations(string relat, string pName)
/* "FK", "Bob" will show the friends of the kin of bob
 * "A" ,"Bob" will show all the people bob knows
 * "AA" , "Bob" will show all the above and everyone they know.
 */

{
	char rel;
	yolodex fptrTemp;
	if (relat.length() <= 1){
		rel = relat[0];//get the last char in string
		fptrTemp = getCat(rel, pName);
		return fptrTemp;
	}
	fptrTemp = getCat(relat.at(1), pName);
}

bool god::chkCommon(string one, string two)
{
	yoPtr memberPtr = getLink(one);
	int i=0, j=0;
	for(i=0; i<memberPtr->allContacts.size(); i++)
	{
		if(two == memberPtr->allContacts[i]->name)
			return true;
	}
	for(i=0; i<memberPtr->allContacts.size();i++)
	{
		j = chkCommon(memberPtr->allContacts[i]->name, two);
		if(j==1)
			return true;
	}
	return false;
	
	//memberPtr = memberPtr->

}

void god::nonMutual()
{
	int flag=0;
	//yoPtr temp = nullptr;
    for(int i = 0; i < network; i++)
    {
        for(int j=0; j <members[i]->friendCount; j++)
        {
            yoPtr match = getLink(members[i]->allContacts[j]->name);
			if(match->friendCount==0)
				flag =1;
			for(int k=0; k <match->friendCount; k++)
                {
                  //  if(members[i]->allContacts[j]->name == match->name && members[i]->name == match->allContacts[k]->name)
					if( members[i]->name != match->allContacts[k]->name)
					{
						flag=1;
					}
                    else
                    {
						flag=0;
						break;
					}
                } 
			if(flag == 1)
			{
				cout<<members[i]->name<<" and "<<match->name<<endl;
				flag = 0;
			}
        }
    }
}


void god::suggestedFriends(string pName)
{
	yoPtr memPtr = getLink(pName);
	vector<string> sugFrList;
	int i,j;
	for(i=0; i<memPtr->friendz.size();i++)
		for(j=0; j<memPtr->friendz[i]->friendz.size();j++)
			sugFrList.push_back(memPtr->friendz[i]->friendz[j]->name);

	for(i=0; i<memPtr->kin.size();i++)
		for(j=0; j<memPtr->kin[i]->friendz.size();j++)
			sugFrList.push_back(memPtr->kin[i]->friendz[j]->name);

	for(i=0; i<memPtr->friendz.size();i++)
		for(j=0; j<memPtr->friendz[i]->kin.size();j++)
			sugFrList.push_back(memPtr->friendz[i]->kin[j]->name);

	for(i=0; i<memPtr->kin.size();i++)
		for(j=0; j<memPtr->kin[i]->kin.size();j++)
			sugFrList.push_back(memPtr->kin[i]->kin[j]->name);

	for(i=0; i<memPtr->coworkers.size();i++)
		for(j=0; j<memPtr->coworkers[i]->coworkers.size();j++)
			sugFrList.push_back(memPtr->coworkers[i]->coworkers[j]->name);

	for(i=0; i<memPtr->coworkers.size();i++)
		for(j=0; j<memPtr->coworkers[i]->friendz.size();j++)
			sugFrList.push_back(memPtr->coworkers[i]->friendz[j]->name);
	
	for(i=0; i<memPtr->friendz.size();i++)
		for(j=0; j<memPtr->friendz[i]->coworkers.size();j++)
			sugFrList.push_back(memPtr->friendz[i]->coworkers[j]->name);

	for(i=0; i<memPtr->kin.size();i++)
		for(j=0; j<memPtr->kin[i]->coworkers.size();j++)
			sugFrList.push_back(memPtr->kin[i]->coworkers[j]->name);

	for(i=0; i<memPtr->coworkers.size();i++)
		for(j=0; j<memPtr->coworkers[i]->kin.size();j++)
			sugFrList.push_back(memPtr->coworkers[i]->kin[j]->name);

	vector<string> matches;
	vector<string> disOne;
	int k, flag=0;
	i=0;

	
	while (i < sugFrList.size())
		{
			for(j=0;j<matches.size();j++)
			{
				if(sugFrList[i].compare(matches[j]) == 0)
					break;
			}
			if(j >= matches.size())
				matches.push_back(sugFrList[i]);
			i++;
		}
	
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

	sugFrList.clear();
	
}
