#include "State.h"
#include <chrono>
enum Test_Case
{
	Init_VeryEasy = 1,
	Init_Easy,
	Init_doable,
	Init_OhBoy,
	Init_Impossible
};

enum Algorithm_Type
{
	Unifor_Search = 1,
	Astar_Misplace,
	Astar_Euclidean
};

using namespace std;
int main()
{
	int choose_case;
	int choose_algorithm;
	

	vector<int> Initial_State;

	cout << "Select Test Case you want" << endl;
	cout << "1.Very Easy\n2.Easy\n3.doable\n4.OhBoy\n5.Impossible" << endl;
	cin >> choose_case;



	switch ((Test_Case)choose_case) {
	case Init_VeryEasy :
		Initial_State = { 1,2,3,4,5,6,7,0,8 };
		break;

	case Init_Easy:
		Initial_State = { 1,2,0,4,5,3,7,8,6 };
		break;

	case Init_doable:
		Initial_State = { 0,1,2,4,5,3,7,8,6 };
		break;

	case Init_OhBoy:
		Initial_State = { 8,7,1,6,0,2,5,4,3 };
		break;

	case Init_Impossible:
		Initial_State = { 1,2,3,4,5,6,8,7,0 };
		break;
	}

	NODE* Initial_Node = new Node(0, Initial_State);

	State* list = new State();
	list->Get_Initial_Node(Initial_Node);

	cout << "Check Availability " << endl;
	if (!list->isSolvable(Initial_Node))
	{
		cout << "It's not solvabale" << endl;
		return 0;
	}
	else {
		cout << "It's solvable" << endl;
	}

	cout << "Select the algorithm you want to run the test case" << endl;
	cout << "1. Uniform Search \n2. Astar - Misplaced Search \n3. Astar - Eculidiean Distance Search" << endl;
	cin >> choose_algorithm;

	auto startTime = std::chrono::system_clock::now();
	switch ((Algorithm_Type)choose_algorithm) {
		case Unifor_Search:
			while (list->status == false)
			{
				list->Uniform_Search();
			}
			break;
	
		case Astar_Misplace:

			while (list->status == false)
			{
				list->Astar_Misplace_Search();
			}
			break;
		case Astar_Euclidean :

			while (list->status == false)
			{
				list->Astar_Euclidean_Distance_Search();
			}
			break;
	}

	

	auto endTime = std::chrono::system_clock::now();
	auto elapsedTime = std::chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
	cout << "Took " << elapsedTime.count() << " milliseconds to find a solution.\n";
	cout << "Maximum Queue Expanded : " << list->open_list.size() << endl;

	/*
	for (int i = 0; i < list->open_list.size(); i++)
	{
		list->Print_Node(list->open_list[i]);
	}
	*/
}