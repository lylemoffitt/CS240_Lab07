#include "Lab07.h"
using namespace std;

int main(int argc, char **argv)
{
	God god;
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
    
    
    
    
    return 0;
}
