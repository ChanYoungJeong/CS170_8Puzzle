#include "State.h"

//Node Functions
Node::Node(int size, const std::vector<int>& arr) 
	: m_size(size) 
{
		Current_State = arr;

}

void Node::swap_index(int Empty_Tile_Index, int Adjacent_Index)
{
	int temp = Current_State[Empty_Tile_Index];
	Current_State[Empty_Tile_Index] = Current_State[Adjacent_Index];
	Current_State[Adjacent_Index] = temp;
}

int Node::find_empty_tile() {
	for (int i = 0; i < m_size + 1; i++)
	{
		if (Current_State[i] == 0)
		{
			return i;
		}
	}
}


//State Functions
void State::Get_Initial_Node(NODE* node) {
	head = node;
	head->Current_Depth = depth;
	open_list.push_back(head);
}

void State::Print_Node(NODE* node) {
	for (int i = 0; i < 3; i++) {
		//std::cout << node->Current_State[i] << std::endl;
		for (int j = 0; j < 3; j++)
		{
			std::cout << node->Current_State[j + (3 * i)];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool State::Find_Goal_Node(NODE* node)
{
		if (node->Current_State == goal_vector)
		{
			return true;
		}

	return false;
}

void State::Print_All_State(NODE* node) {

	while (node != head)
	{
		node->prev->next = node;
		node = node->prev;
	}

	while (node != NULL)
	{
		Print_Node(node);
		node = node->next;
	}

}

void State::Create_Node() {

	int Empty_Tile;
	NODE* temp = new NODE();
	depth++;
	
	for (int j = 0; j < open_list.size(); j++) {
		temp->Current_State = open_list.front()->Current_State;
		Empty_Tile = open_list.front()->find_empty_tile();

		//std::cout << NeighbourMap.at(Empty_Tile).size() << std::endl;

		for (int i = 0; i < NeighbourMap.at(Empty_Tile).size(); i++)
		{
			NODE* Next_Node = new NODE();
			Next_Node->Current_State = temp->Current_State;
			Next_Node->swap_index(Empty_Tile, NeighbourMap.at(Empty_Tile)[i]);
			Next_Node->Current_Depth = depth;
			Next_Node->prev = open_list.front();


			if (!Find_Repeated_Node(Next_Node))
			{
				if (Find_Goal_Node(Next_Node))
				{
					std::cout << "Find Goal" << std::endl;
					Print_All_State(Next_Node);
					status = true;
					break;
				}
				else {
					open_list.push_back(Next_Node);
				}
			}

		}
		close_list.push_back(open_list.front());
		open_list.erase(open_list.begin());
	}
}

bool State::Find_Repeated_Node(NODE* node)
{
	for (int i = 0; i < close_list.size(); i++)
	{
			if (node->Current_State == close_list[i]->Current_State)
			{
				return true;
			}
	}
	return false;
}

void State::Create_NeighbourMap()
{
	NeighbourMap.insert(std::make_pair(0, std::vector<int>{1, 3}));
	NeighbourMap.insert(std::make_pair(1, std::vector<int>{0, 2, 4}));
	NeighbourMap.insert(std::make_pair(2, std::vector<int>{1, 5}));
	NeighbourMap.insert(std::make_pair(3, std::vector<int>{4, 0, 6}));
	NeighbourMap.insert(std::make_pair(4, std::vector<int>{3, 5, 1, 7}));
	NeighbourMap.insert(std::make_pair(5, std::vector<int>{4, 2, 8}));
	NeighbourMap.insert(std::make_pair(6, std::vector<int>{7, 3}));
	NeighbourMap.insert(std::make_pair(7, std::vector<int>{6, 8, 4}));
	NeighbourMap.insert(std::make_pair(8, std::vector<int>{7, 5}));
}

bool State::isSolvable(NODE& node) {

	int counter = 0;
	for(int i = 0; i < node.Current_State.size()-1; i++)
		for (int j = i + 1; j < node.Current_State.size(); j++)
		{
			if (node.Current_State[j] && node.Current_State[i] && node.Current_State[i] > node.Current_State[j])
			{
				counter++;
			}
		}
	return(counter % 2 == 0);
}

