#include "State.h"

//Node Functions
Node::Node(int Current_Depth, const std::vector<int>& arr)
	: depth(Current_Depth), Cmp_Cost(0)
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
	head->depth = node->depth;
	open_list.push(head);
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

	node->next = NULL;
	int depth = 1;
	while (node != head)
	{
		node->prev->next = node;
		node = node->prev;
	}

	while (node != NULL)
	{
		std::cout << "DPETH : " << node->Cmp_Cost - node->depth << std::endl;
		Print_Node(node);
		depth++;
		node = node->next;
	}

}

void State::Uniform_Search() {

	int Empty_Tile = 0;
	int temp_depth = 0;
	int list_size = open_list.size();


	for (int j = 0; j < list_size; j++) {
		//temp->Current_State = open_list.front()->Current_State;
		NODE* temp = new NODE(open_list.top()->depth, open_list.top()->Current_State);
		temp_depth = temp->depth + 1;
		Empty_Tile = temp->find_empty_tile();

		//std::cout << NeighbourMap.at(Empty_Tile).size() << std::endl;

		for (int i = 0; i < NeighbourMap.at(Empty_Tile).size(); i++)
		{
			NODE* Next_Node = new NODE(temp_depth, temp->Current_State);
			Next_Node->swap_index(Empty_Tile, NeighbourMap.at(Empty_Tile)[i]);
			Next_Node->prev = open_list.top();
			Next_Node->Cmp_Cost = temp_depth;
			if (!Find_Repeated_Node(Next_Node))
			{
				if (Find_Goal_Node(Next_Node))
				{
					std::cout << "Find Goal" << std::endl;
					Print_All_State(Next_Node);
					status = true;
					return;
				}
				else {
					open_list.push(Next_Node);
				}
			}
			else {
				delete Next_Node;
			}

		}
		close_list.insert(open_list.top()->Current_State);
		open_list.pop();

		
	}
}

bool State::Find_Repeated_Node(NODE* node)
{
	auto iter = close_list.find(node->Current_State);
	if (iter != close_list.end())
	{
		return true;
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

std::vector<int> State::Find_Adjacent_Tile(int Empty_Tile)
{
	auto iter =	NeighbourMap.find(Empty_Tile);
	static std::vector<int> s;
	if (iter != NeighbourMap.end())
	{
		s = iter->second;
	}
	return s;
}

bool State::isSolvable(NODE* node) {

	int counter = 0;
	for(int i = 0; i < node->Current_State.size()-1; i++)
		for (int j = i + 1; j < node->Current_State.size(); j++)
		{
			if (node->Current_State[j] && node->Current_State[i] && node->Current_State[i] > node->Current_State[j])
			{
				counter++;
			}
		}
	return(counter % 2 == 0);
}


int State::Misplace_Tile_Calculator(const std::vector<int> current_state)
{
	int Misplace_Tile = 0;

	for (int i = 0; i < current_state.size(); i++)
	{
		if (current_state[i] != goal_vector[i])
		{
			Misplace_Tile++;
		}
	}

	return Misplace_Tile;
}


void State::Astar_Misplace_Search() {

	int Empty_Tile;
	int temp_depth;
	int misplace_tile;
	int adjacet_tile;
	int list_size = open_list.size();


	for (int j = 0; j < list_size; j++) {

		NODE* temp = new NODE(open_list.top()->depth, open_list.top()->Current_State); //copy the top Node in Open_list
		temp_depth = temp-> depth + 1;
		Empty_Tile = temp->find_empty_tile();
		std::vector<int> temp_arr;
		temp_arr = Find_Adjacent_Tile(Empty_Tile);

		for (int i = 0; i < temp_arr.size(); i++) //Get Adjcaent Tile of EmptyTile
		{
			NODE* Next_Node = new NODE(temp_depth, temp->Current_State);
			Next_Node->swap_index(Empty_Tile, temp_arr[i]);
			Next_Node->prev = open_list.top();
			
			misplace_tile = Misplace_Tile_Calculator(Next_Node->Current_State);
			Next_Node->Cmp_Cost = misplace_tile + temp_depth;


			if (!Find_Repeated_Node(Next_Node))
			{
				if (Find_Goal_Node(Next_Node))
				{
					std::cout << "Find Goal" << std::endl;
					Print_All_State(Next_Node);
					status = true;
					return;
				}
				else {
					open_list.push(Next_Node);
				}
			}
			else {
				delete Next_Node;
			}

		}
		close_list.insert(open_list.top()->Current_State);
		open_list.pop();


	}
}


int State::Euclidean_Distance(const std::vector<int> current_state)
{
	int counter = 0;
	for (int i = 0; i < current_state.size(); i++)
	{
		counter += Compare_Tile_Position(current_state[i], i);
	}
	return counter;
}

int State::Compare_Tile_Position(int Tile_Value, int Tile_Index) 
{
	int result = 0;
	int divide = 0;
	int remainder = 0;
	divide = Tile_Index / 3;
	remainder = Tile_Index % 3;
	result = divide + remainder;
	int Actual_Index = 0;

	for (int i = 0; goal_vector.size(); i++)
	{
		if (Tile_Value == goal_vector[i])
		{
			divide = i / 3;
			remainder = i % 3;
			Actual_Index = divide + remainder;
			break;
		}
	}
	
	return abs(Actual_Index - result);
}

void State::Astar_Euclidean_Distance_Search() {

	int Empty_Tile;
	int temp_depth;
	int misplace_tile;
	int adjacet_tile;
	int list_size = open_list.size();


	for (int j = 0; j < list_size; j++) {

		NODE* temp = new NODE(open_list.top()->depth, open_list.top()->Current_State); //copy the top Node in Open_list
		temp_depth = temp->depth + 1;
		Empty_Tile = temp->find_empty_tile();
		std::vector<int> temp_arr;
		temp_arr = Find_Adjacent_Tile(Empty_Tile);

		for (int i = 0; i < temp_arr.size(); i++) //Get Adjcaent Tile of EmptyTile
		{
			NODE* Next_Node = new NODE(temp_depth, temp->Current_State);
			Next_Node->swap_index(Empty_Tile, temp_arr[i]);
			Next_Node->prev = open_list.top();

			misplace_tile = Euclidean_Distance(Next_Node->Current_State);
			Next_Node->Cmp_Cost = misplace_tile + temp_depth;


			if (!Find_Repeated_Node(Next_Node))
			{
				if (Find_Goal_Node(Next_Node))
				{
					std::cout << "Find Goal" << std::endl;
					Print_All_State(Next_Node);
					status = true;
					return;
				}
				else {
					open_list.push(Next_Node);
				}
			}
			else {
				delete Next_Node;
			}

		}
		close_list.insert(open_list.top()->Current_State);
		open_list.pop();


	}
}
