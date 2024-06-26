#include <stdio.h>
#include <stdlib.h>
int main()
{
	int arr[]={1,2,3,5,6,8,11,12,15,16,19};
	int X=0;
	int x;
	int lct=arr[0];
	int i=0;
	int l=4,L=10;
	while(i<11){
		int ta=arr[i];
		x=X-(ta-lct);
		X=x+l;
		if (x>=0 && x<=L){
			printf("Packet %d is a conforming packet\n",i+1);
			lct=arr[i];
		}
		else{
			printf("Packet %d is non-conforming packet\n",i+1);
			X=x+(ta-lct);
			lct=arr[i-1];
		}
		i++;
	}
	return 0;
}