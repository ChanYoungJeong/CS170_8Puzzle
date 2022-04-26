#include "State.h"

using namespace std;
int main()
{


	vector<int> Init_VeryEasy = { 1,2,3,4,5,6,7,0,8 };
	vector<int> Init_Easy = { 1,2,0,4,5,3,7,8,6 };
	vector<int> Init_doable = { 0,1,2,4,5,3,7,8,6 };
	vector<int> Init_OhBoy = { 8,7,1,6,0,2,5,4,3 };
	vector<int> Init_Impossible = { 1,2,3,4,5,6,8,7,0 };

	NODE Initial_Node(0, Init_OhBoy);
	State* list = new State();
	list->Get_Initial_Node(&Initial_Node);

	if (list->isSolvable(Initial_Node)){
		do
		{
			list->Create_Node();
		} while (list->status == false);
	}
	else {
		cout << "It's not solvabale" << endl;
	}

	cout << list->open_list.size() << endl;
	cout << list->close_list.size() << endl;
	/*
	for (int i = 0; i < list->open_list.size(); i++)
	{
		list->Print_Node(list->open_list[i]);
	}
	*/
}