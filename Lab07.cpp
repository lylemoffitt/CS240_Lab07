#include "Lab07.h"

using namespace std;

void god::readIn(string fileName)
{
    string num;
	int num2;
    size_t *tempNum;
    
	ifstream fileIn(fileName);
	if(fileIn.bad())
	{
		cout << "Corrupt file" << endl;
		return;
	}
	string item;
	//yoPtr contact = nullptr;
	getline(fileIn, num);
	//stringstream convert(num);     //should convert string to int...
    num2 = stoi(num, tempNum, 10);
	//don't think we need this v
    //if (!(convert >> num2))
	//	num2 = 0;
	network = num2;
	yofile tempArr[100];
    for(int i=0;i<network;i++)
	{
		if(fileIn.eof())
			break;
		yofile person; //Possibly going to cause errors. Check to see if we need "new".
		getline(fileIn, item);
		person.name = item; //nameIt replaced with assignment
		tempArr[i] = person;
		members.push_back(&tempArr[i]);
	}
	for(int i=0; i<network; i++)
		fillInfo(fileIn);

}

void god::fillInfo(ifstream file)
{
	string item, type;
	//char type;
	string num;
	int num2;
	yoPtr contact;
	getline(file, item, ",");
	getline(file, num);
	//stringstream convert(num);//should convert string to int....
	//if (!(convert >> num2))
	//	num2 = 0;

	contact = getLink(item);
	contact->friendCount = num;
	for(int i=0; i< num; i++)
	{
		if(file.bad())
			break;
		getline(file, item, ",");
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
///////////////////////////////READ///////////////////////////////////////////////////////////////
//////////////***nevermind after it leaves fillinfo and goes back to main, everything gets erased...
//////////////***but it fills out perfectlyish...except for the whole erasing part
//////////////***i think we should do vector of structs that have pointers inside them...
//////////////////////////////////////////////////////////////////////////////////////////////////
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

//god::pokedex god::getCat(char category, string pName)
god::yolodex god::getCat(char category, string pName)
{
	yoPtr contact = getLink(pName);
	char type = category;
	//pokedex = typedef std::vector<fptr>
	//finding the size of the inquired list for the member passed in
//	pokedex fptrTemp;
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
  //  fptrTemp = &vecTemp;
    //or *fptrTemp = vecTemp; //not sure which is better
	return vecTemp;
}

void god::viewCat(char category, string pName)
{
	yolodex profile = getCat(category,pName);
	for( int i=0,j=profile->size(); i<j; i++ )
	{
		cout << profile[i]->name << endl;
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

//bool chkCommon(yoPtr one, yoPtr two); 
//^ that's what we had before. I changed it to string instead
//seems better but I'm getting an error at the last line
//chkCommon(memberPtr->allContacts[i].name, two);
//the error is "god::yoPtr memberPtr \n Error: expression must have class type"
//also I think there's supposed to be a for loop around the recursive part 
//so it goes through all of the contacts
//then at the end be return false. 
bool god::chkCommon(yoPtr one, yoPtr two)
{
    yoPtr memberPtr = getLink(one);
	int i=0;
	for(i=0; i<memberPtr->allContacts.size(); i++)
	{
		if(two == memberPtr->allContacts[i]->name)
			return true;
	}
    for(i=0; i<allContacts.sze();i++)
	    chkCommon(memberPtr->allContacts[i].name, two);
    return false;//   ^
                //|-error-|
	
	//memberPtr = memberPtr->

}      
void god:: nonmutual()
{
    yoPtr temp = nullptr;
    for(int i = 0; i < network; i++)
    {
        for(int j=0; j <members[i]->friendCount; j++)
        {
            yoPtr match= getLink(temp->members[i]->allContacts[j]->name);
            for(int k=0; k <match->friendcount; k++)
                {
                    if(temp->members[i]->allContacts[j]->name==match->allContacts[k])
                    {
                        return NULL;
                    }
                    else
                    {
                    cout<<temp->members[i]->name<<"and"<<temp->members[i]->allContacts[j]->name<<endl;
                    }
                } 
        }
    }
}


void god::suggestedFriends(string pName)
{
    yoPtr memPtr = getLink(pName);
	yoPtr memFrPtr = memPtr->friendz[0];
	vector<string> sugFrList;
	for(int i=0; i<memPtr->friendz.size();i++)
		for(int j=0; j<memPtr->friendz[i]->friendz.size();j++)
			sugFrList.push_back(memPtr->friendz[i]->friendz[j]->name);

	for(int i=0; i<memPtr->kin.size();i++)
		for(int j=0; j<memPtr->kin[i]->friendz.size();j++)
			sugFrList.push_back(memPtr->kin[i]->friendz[j]->name);

	for(int i=0; i<memPtr->friendz.size();i++)
		for(int j=0; j<memPtr->friendz[i]->kin.size();j++)
			sugFrList.push_back(memPtr->friendz[i]->kin[j]->name);

	for(int i=0; i<memPtr->kin.size();i++)
		for(int j=0; j<memPtr->kin[i]->kin.size();j++)
			sugFrList.push_back(memPtr->kin[i]->kin[j]->name);

	for(int i=0; i<memPtr->coworkers.size();i++)
		for(int j=0; j<memPtr->coworkers[i]->coworkers.size();j++)
			sugFrList.push_back(memPtr->coworkers[i]->coworkers[j]->name);

	for(int i=0; i<memPtr->coworkers.size();i++)
		for(int j=0; j<memPtr->coworkers[i]->friendz.size();j++)
			sugFrList.push_back(memPtr->coworkers[i]->friendz[j]->name);
	
	for(int i=0; i<memPtr->friendz.size();i++)
		for(int j=0; j<memPtr->friendz[i]->coworkers.size();j++)
			sugFrList.push_back(memPtr->friendz[i]->coworkers[j]->name);

	for(int i=0; i<memPtr->kin.size();i++)
		for(int j=0; j<memPtr->kin[i]->coworkers.size();j++)
			sugFrList.push_back(memPtr->kin[i]->coworkers[j]->name);

	for(int i=0; i<memPtr->coworkers.size();i++)
		for(int j=0; j<memPtr->coworkers[i]->kin.size();j++)
			sugFrList.push_back(memPtr->coworkers[i]->kin[j]->name);

	vector<string> matches;
	int i=0,j=0;
	while (i < sugFrList.size())
		{
			for(j=0;j<matches.size();j++)
			{
				if(sugFrList[i].compare(sugFrList[j]) == 0)
					break;
			}
			if(j >= matches.size())
				matches.push_back(sugFrList[i]);
			i++;
		}
        
        
    for(i=0;i<matches.size();i++)
    		cout << matches[i] << endl;
		sugFrList.clear();
	/*
	char rel;
	yolodex fptrTemp;
	if (relat.length() <= 1){
		rel = relat[0];//get the last char in string
		fptrTemp = getCat(rel, pName);
		return fptrTemp;
	}
	fptrTemp = getCat(relat.at(1), pName);
	*/
}




