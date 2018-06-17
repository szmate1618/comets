#include "FatLeaf.hpp"

class PlaceHolder
{
	int whatever;
};

int main()
{
	FatLeaf<double, PlaceHolder> fl(0);
	return 0;
}
