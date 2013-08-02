#ifndef LAB07_H
#define LAB07_H

#include <vector>
#include <string>
#include <iostream>

class person
{
public:
	person()//Class constructor
	{
		/*var1*/ = 0;
		/*var2*/ = 0.0;
		/*var3*/ = "0";
	}

	~person()//Class destructor
	{   /*Usually has this form. May cause errors.*/
		delete /*var1*/;
		delete /*var2*/;
		delete /*var3*/;
	}

private:
	/*Struct or sub-class object goes here*/
	typedef	person* them;
	vector<them>

};

#endif // LAB07_H
