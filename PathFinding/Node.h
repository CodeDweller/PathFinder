// Node class
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <tuple>

#define nonDiagonalCost 10
#define diagonalCost 14

namespace Pathfinder
{
	class Node
	{
	private:
		uint32_t xPosition;
		uint32_t yPosition;
		//bool walkable;
		uint32_t G; // Movement cost from starting point A to a given square on the grid
		uint32_t H; // Heuristic
		uint32_t F; // F = G + H
		std::unique_ptr<Node> parent; // Pointer to the parent
		/////////////////////////////////////////////////////////////////////////////////////
		void UpdateG();
		void UpdateF();
		uint32_t CostToNode(Node& src);
	public:
		/////////////////////////////////////////////////////////////////////////////////////
		// Constructors/Destructor
		/////////////////////////////////////////////////////////////////////////////////////
		Node(uint32_t x = 0, uint32_t y = 0); // Start/Destination nodes only
		Node
		(
			uint32_t x, uint32_t y, 
			Node& dst, std::unique_ptr<Node> const &par,
			size_t closedNum // closedNum - number of elements in the closed list
		);
		~Node();
		/////////////////////////////////////////////////////////////////////////////////////
		// Getters/Setters
		/////////////////////////////////////////////////////////////////////////////////////
		uint32_t GetG();
		uint32_t GetH();
		uint32_t GetF();
		std::tuple<std::uint32_t, std::uint32_t> GetPosition();
		bool GetWalkable();
		std::unique_ptr<Node>& GetParent();

		void ChangeParent(Node& newparent);
		
		



	};

}

