#include "State.h"
#include <chrono>

using namespace std;
int main()
{


	vector<int> Init_VeryEasy = { 1,2,3,4,5,6,7,0,8 };
	vector<int> Init_Easy = { 1,2,0,4,5,3,7,8,6 };
	vector<int> Test = { 1,2,3,0,5,6,4,7,8 };
	vector<int> Init_doable = { 0,1,2,4,5,3,7,8,6 };
	vector<int> Init_OhBoy = { 8,7,1,6,0,2,5,4,3 };
	vector<int> Init_Impossible = { 1,2,3,4,5,6,8,7,0 };

	NODE* Initial_Node = new Node(0, Test);
	State* list = new State();
	list->Get_Initial_Node(Initial_Node);

	auto startTime = std::chrono::system_clock::now();

	if (!list->isSolvable(Initial_Node)){
	
		cout << "It's not solvabale" << endl;
		return 0;
	}

	while (list->status == false)
	{
		list->Astar_Euclidean_Distance_Search();
		
	}



	auto endTime = std::chrono::system_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	std::cout << "Took " << elapsedTime.count() << " milliseconds to find a solution.\n";

	cout << list->open_list.size() << endl;
	cout << list->close_list.size() << endl;
	/*
	for (int i = 0; i < list->open_list.size(); i++)
	{
		list->Print_Node(list->open_list[i]);
	}
	*/
}