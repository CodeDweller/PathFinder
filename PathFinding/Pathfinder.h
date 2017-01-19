// A* implementation, no diagonal movement 
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>
#include <list>
#include "Node.h"

#define DEBUG 1

namespace Pathfinder
{
	class Astar
	{
	private:
		std::vector<std::unique_ptr<Pathfinder::Node>> open; // Sorted list of open nodes
		std::vector<std::unique_ptr<Pathfinder::Node>> closed; // List of closed nodes
		//std::vector<Pathfinder::Node> forbidden; // List of forbidden nodes
		/////////////////////////////////////////////////////////////////////////////////////
		bool CompareFunction(Node& node1, Node& node2); // Std::sort compare function
		void AddToOpen(std::unique_ptr<Pathfinder::Node>& node, std::vector<std::unique_ptr<Pathfinder::Node>>& open);
		//void AddToClosed(Node& node);
		//bool FindInOpen(Node& node);
		//bool FindInClosed(uint32_t xCoord, uint32_t yCoord);
		std::unique_ptr<Pathfinder::Node>& FindNodeInList(uint32_t xCoord, uint32_t yCoord, std::vector<std::unique_ptr<Pathfinder::Node>>& searchVector);
		bool IsBetterPath(Node& node);
		//bool NodeComparison(std::unique_ptr<Pathfinder::Node>& node, std::tuple<uint32_t, uint32_t> position); // Find_if compare function
		uint8_t NumOfClosed();
		uint16_t InputMapLocation(uint32_t xCoord, uint32_t yCoord, const int nMapHeight);
	public:
		Astar();
		~Astar();
		int FindPath // Non-static
		(
			const int nStartX, const int nStartY,
			const int nTargetX, const int nTargetY,
			const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
			int* pOutBuffer, const int nOutBufferSize
		);
	};
}