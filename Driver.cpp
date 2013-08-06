#include "Lab07.h"
using namespace std;

int main(int argc, char **argv)
{
    god god;
	
	long sec1, sec2;
	long sstart, send;
	timeval start, end;
	timeval searchS, searchE;
	string s1;
	if(argc<=1)
	{
		return 0;
	}
	else
	{
		s1=argv[1];
	}
	gettimeofday(&start, NULL);
	cout<<"Building search structure"<<endl;
	cout<<"parsing: "<<s1<<endl;
	god.readIn(s1);
	gettimeofday(&end, NULL);
	sec1= end.tv_sec - start.tv_sec;
	sec2 = end.tv_usec - start.tv_usec;
	sec1= sec1*1000000;
	cout<<"time: "<< (sec1+sec2)<< " miliseconds"<<endl;

	//I didn't know where the menu choice was supposed to go
	// Here seemed like a logical choice
	int choice =0 ;
	string name1,name2;
	do {
		if (choice == 0)
		{
			cout << "\nPlease select a #'d option:" << endl;
			cout << "1) View Contacts" << endl ;
			cout << "2) Suggest Friends" << endl ;
			cout << "3) Determine if connected" << endl ;
			cout << "4) Show non-mutual connections" << endl ;
			cout << "5) Exit\n" << endl ;
			cin >> choice;
		}else if (choice != 5)
		{
			sec1= end.tv_sec - start.tv_sec;
			sec2 = end.tv_usec - start.tv_usec;
			sec1= sec1*1000000;
			cout<<"time: "<< (sec1+sec2)<< " miliseconds"<<endl;
			choice =0;
		}
		switch( choice )
		{
			case 1:
				cout << "\nEnter your name: ";
				cin >> name1;
				god.viewAll(name1);
				break;
			case 2:
				cout << "\nEnter your name: ";
				cin >> name1;
				god.suggestedFriends(name1);
				break;
			case 3:
				cout << "\nEnter your name: ";
				cin >> name1;
				cout << "\nEnter their name: ";
				cin >> name2;
				gettimeofday(&end, NULL);
				if( god.chkCommon(name1,name2) )
				{
					cout << "\nYou are connected!" << endl;
				}else
				{
					cout << "\nYou are not connected :(" << endl;
				}
				break;
			case 4:
				gettimeofday(&end, NULL);
				god.nonMutual();
				break;
			case 5:
				cout << "Goodbye" << endl;
				break;
			default:
				choice =0;
				break;
		}
	} while (choice < 5);

	// End menu

	
	return 0;
}
