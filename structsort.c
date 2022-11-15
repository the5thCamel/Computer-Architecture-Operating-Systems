#include <stdio.h>
#include <stdlib.h>
#define swap(a, b, t) (t = a, a = b, b = t)
struct aircraftDes
{
	int version;
	char nickname[15];
	char type[5];
} ;

int main()
{
	
	int i;
	//allocating size for the array of structures
	//instead just declare an array of 11 structures and remember to use a pointer to structures
	struct aircraftDes aircraftArr[11];
	struct aircraftDes *p;
	p = aircraftArr;
	printf("Please enter 10 aircraft below (ex: F 14 Tomcat or SU 27 Flanker): \n");
	//here I will be taking user input for the 10 structs
	for(i = 0; i < 10; i++)
	{
		printf("Enter an aircraft type (ex: b or f or jas): ");
		scanf("%s", p->type);
		printf("Enter aircraft version number (ex: 14 or 35): ");
		scanf("%d", &p->version);
		printf("Enter aircraft nickname or nato designation (ex: tomcat or flanker): ");
		scanf("%s", p->nickname);
		++p;
		
		
	}
	//here I will perform the insertion sort operation
	int l = 0;
	for(int j = 0; j < 10; ++j)
	{
		while(aircraftArr[l].version > aircraftArr[l + 1].version && l >= 0)
		{
			swap(aircraftArr[l], aircraftArr[l + 1], aircraftArr[10]);
			l--;
		}
		l = j;
		++p;
	}
	
	printf("Here is your list of aircraft sorted by their version number:\n");
	p = aircraftArr;
	for(int k = 0; k < 10; k++)
	{
		printf("%s-%d %s \n", p->type, p->version, p->nickname);
		++p;
	}
	
	
	return 0;
}
