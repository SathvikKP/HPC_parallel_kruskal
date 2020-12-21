#include <iostream>
#include <fstream>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	char* inputfile = argv[1];
	int x,y,w;
	std::fstream file(inputfile,std::ios_base::out);
	
	int V=atoi(argv[2]),E=atoi(argv[2]);
	file<<V<<" "<<E<<"\n";
	for (int i=0;i<E;i++)
	{
		x = i%E;
		y = (i+1)%E;
		w = V-i;
		file<<x<<" "<<y<<" "<<w<<"\n";
	}
	return 0;
}
