#include <iostream>
#include <vector>

using namespace std;


struct cordinate2
{
	int x;
	int y;
	int z;
};

bool tell(int i){
	if(i== 1)	return true;
	return false;
}

int main(){
	// vector<int> v;
	// v.push_back(5);
	// v.push_back(6);
	// cout<<v[0];
	// cout<<v[1];
	cordinate2 temp[5];
	pair<int, int> temp;
	temp[0] = cordinate2 (1, 2, 3);
	// cout<<temp[0].z;
	// if(tell(21))	cout<<"rajan";
	return 0;
}