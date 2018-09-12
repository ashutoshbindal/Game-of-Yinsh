#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

struct cordinate2
{
	int x;
	int y;
	int z;	
};

struct cordinate1
{
	int hex;
	int point;
};

int main(){
	//hex2car
	map<pair<int, int>, cordinate2> hex2cart;
	pair<int, int> temp1;
	cordinate2 temp2;

	//hex0
	temp1 = {0, 0};
	temp2 = {6, 6, 6};
	hex2cart[temp1] = temp2;

	//hex1
	vector<int> x = {6, 7, 7, 6, 5, 5};
	vector<int> y = {7, 6, 5, 5, 6, 7};
	vector<int> z = {7, 7, 6, 5, 5, 6};
	for(int i= 0; i< 6; i++){
		temp1 = {1, i};
		temp2 = {x[i]-1, y[i]-1, z[i]-1};
		hex2cart[temp1] = temp2;
	}

	//hex2
	vector<int>().swap(x);
	vector<int>().swap(y);
	vector<int>().swap(z);
	x = {6, 7, 8, 8, 8, 7, 6, 5, 4, 4, 4, 5};
	y = {8, 7, 6, 5, 4, 4, 4, 5, 6, 7, 8, 8};
	z = {8, 8, 8, 7, 6, 5, 4, 4, 4, 5, 6, 7};
	for(int i= 0; i< 12; i++){
		temp1 = {2, i};
		temp2 = {x[i]-1, y[i]-1, z[i]-1};
		hex2cart[temp1] = temp2;
	}

	//hex3
	vector<int>().swap(x);
	vector<int>().swap(y);
	vector<int>().swap(z);
	x = {6,7,8,9,9,9,9,8,7,6,5,4,3,3,3,3,4,5};
	y = {9,8,7,6,5,4,3,3,3,3,4,5,6,7,8,9,9,9};
	z = {9,9,9,9,8,7,6,5,4,3,3,3,3,4,5,6,7,8};
	for(int i= 0; i< 18; i++){
		temp1 = {3, i};
		temp2 = {x[i]-1, y[i]-1, z[i]-1};
		hex2cart[temp1] = temp2;
	}

	//hex4
	vector<int>().swap(x);
	vector<int>().swap(y);
	vector<int>().swap(z);
	x = {6,7,8,9,10,10,10,10,10,9,8,7,6,5,4,3,2,2,2,2,2,3,4,5};
	y = {10,9,8,7,6,5,4,3,2,2,2,2,2,3,4,5,6,7,8,9,10,10,10,10};
	z = {10,10,10,10,10,9,8,7,6,5,4,3,2,2,2,2,2,3,4,5,6,7,8,9};
	for(int i= 0; i< 12; i++){
		temp1 = {4, i};
		temp2 = {x[i]-1, y[i]-1, z[i]-1};
		hex2cart[temp1] = temp2;
	}

	//hex5
	vector<int>().swap(x);
	vector<int>().swap(y);
	vector<int>().swap(z);
	x = {6,7,8,9,10,11,11,11,11,11,11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,2,3,4,5};
	y = {11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,2,3,4,5,6,7,8,9,10,11,11,11,11,11};
	z = {11,11,11,11,11,11,10,9,8,7,6,5,4,3,2,1,1,1,1,1,1,2,3,4,5,6,7,8,9,10};
	for(int i= 0; i< 12; i++){
		temp1 = {5, i};
		temp2 = {x[i]-1, y[i]-1, z[i]-1};
		hex2cart[temp1] = temp2;
	}


	vector<int>().swap(x);
	vector<int>().swap(y);
	vector<int>().swap(z);


	//cart2hex

	//hex0
	pair<int, int> cart2hex[11][11][11];
	temp1 = {0, 0};
	temp2 = hex2cart[temp1];
	cart2hex[temp2.x][temp2.y][temp2.z] = {0, 0};

	for(int h = 1; h< 6; h++){
		for(int p= 0; p< 6*h; p++){
			temp1 = {h, p};
			temp2 = hex2cart[temp1];
			cart2hex[temp2.x][temp2.y][temp2.z] = {h, p};
		}
	}

	return 0;
}