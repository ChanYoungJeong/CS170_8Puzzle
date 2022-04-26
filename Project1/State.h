#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>


typedef struct Node {
	
	std::vector<int> Current_State;
	int m_size;
	int Current_Depth;
	struct Node* prev;
	struct Node* next;
	Node() : m_size(9), Current_Depth(0), next(NULL) { };
	Node(int size, const std::vector<int>& arr);
	
	void swap_index(int Empty_Tile_Index, int Adjacent_Index);
	int find_empty_tile();

}NODE;



class State
{
private:
	int depth;
	std::map<int, std::vector<int> > NeighbourMap;
	std::vector<int> goal_vector = { 1,2,3,4,5,6,7,8,0 };
	

public:
	NODE* head;
	std::vector<NODE*> open_list;
	std::vector<NODE*> close_list;
	bool status;
	State() : status(false), depth(0), head(NULL) 
	{
		Create_NeighbourMap(); 
	}
	~State()
	{
		NODE* deleteNode;
		while (head->next != NULL)
		{
			deleteNode = head;
			head = head->next;
			delete deleteNode;
		}
	}

	void Create_NeighbourMap();
	void Get_Initial_Node(NODE* node);
	void Create_Node();
	void Print_Node(NODE* node);
	bool Find_Goal_Node(NODE* node);
	void Find_Adjacent_Tile(int Empty_Tile);
	bool Find_Repeated_Node(NODE* node);
	void Print_All_State(NODE* node);

	bool isSolvable(NODE& node);
};
