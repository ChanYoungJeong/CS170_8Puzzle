#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <functional>

//using gridi = std::vector<int> ;

typedef struct Node {
	
	std::vector<int> Current_State;
	int m_size = 9;
	int Cmp_Cost;
	int depth;
	struct Node* prev;
	struct Node* next;
	Node() : m_size(9), depth(0), Cmp_Cost(0), next(NULL), prev(NULL) { };
	Node(int Current_Depth, const std::vector<int>& arr);
	
	void swap_index(int Empty_Tile_Index, int Adjacent_Index);
	int find_empty_tile();


}NODE;


struct HashFn
{
	size_t operator()(const std::vector<int>& g) const
	{
		// Primes
		const int p = 7919;

		size_t res = 0;
		for (size_t i = 0; i < g.size(); ++i)
		{
				res ^= (static_cast<int>(pow(p, i))) * g[i];
		}

		return res;
	}
};


struct cmp {
	bool operator()(NODE* a, NODE* b) {
		return a->Cmp_Cost > b->Cmp_Cost;
	}
};

class State
{
private:
	int depth;
	std::map<int, std::vector<int> > NeighbourMap;
	std::vector<int> goal_vector = { 1,2,3,4,5,6,7,8,0 };
	

public:
	NODE* head;

	std::priority_queue<NODE*, std::vector<NODE*>, cmp> open_list;

	std::unordered_set<std::vector<int> , HashFn> close_list;
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
	void Uniform_Search();
	void Print_Node(NODE* node);
	bool Find_Goal_Node(NODE* node);
	bool Find_Repeated_Node(NODE* node);
	void Print_All_State(NODE* node);
	bool isSolvable(NODE* node);

	std::vector<int> Find_Adjacent_Tile(int Empty_Tile);
	
	//For Astar-Misplace_Tile Algorithm
	int Misplace_Tile_Calculator(const std::vector<int> current_state);
	void Astar_Misplace_Search();

	//For Euclidean Distance heuristic.
	int Euclidean_Distance(const std::vector<int> current_state);
	int Compare_Tile_Position(int Tile_Value, int Tile_Index);
	void Astar_Euclidean_Distance_Search();
};
