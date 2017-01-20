#include "Pathfinder.h"

Pathfinder::Astar::Astar()
{

}

Pathfinder::Astar::~Astar()
{

}

bool Pathfinder::Astar::CompareFunction(Node& node1, Node& node2)
{
	return node1.GetF() < node2.GetF();
}

void Pathfinder::Astar::AddToOpen(std::unique_ptr<Pathfinder::Node>& node, std::vector<std::unique_ptr<Pathfinder::Node>>& open)
{
	for (std::vector<std::unique_ptr<Pathfinder::Node>>::iterator it = open.begin(); it != open.end(); ++it)
	{
		if (node->GetF() <= it->get()->GetF())
		{
			open.insert(it, std::move(node));
			break;
		}
	}
}
//
//void Pathfinder::Astar::AddToClosed(Node& node)
//{
//
//}

//bool Pathfinder::Astar::FindInOpen(Node& node)
//{
//
//}

std::unique_ptr<Pathfinder::Node>& Pathfinder::Astar::FindNodeInList(uint32_t xCoord, uint32_t yCoord, std::vector<std::unique_ptr<Pathfinder::Node>>& searchVector)
{
	std::vector<std::unique_ptr<Pathfinder::Node>>::iterator it = std::find_if // Using lambda expression
	(
		searchVector.begin(), searchVector.end(),
		[](uint32_t xCoord, uint32_t yCoord, std::unique_ptr<Pathfinder::Node>& node) { 
			return std::tie(xCoord, yCoord) == node->GetPosition(); 
	}
	);
	if (it == searchVector.end())
	{
#ifdef DEBUG
		std::cout << "Not found in closed!";
#endif
		return std::unique_ptr<Pathfinder::Node>::unique_ptr(); // Return empty unique_ptr
	}
	return *it;
}

bool Pathfinder::Astar::IsBetterPath(Node& node, Node& currentNode)
{
	uint32_t oldCost = node.GetG();
	std::unique_ptr<Pathfinder::Node>& oldParent = node.GetParent();
	node.ChangeParent(currentNode);
	if (oldCost < node.GetG())
	{
#ifdef DEBUG
		std::cout << "Returning old parent!";
#endif
		node.ChangeParent(*oldParent); // Return old parent
		return true;
	}	
	return false;
}

//bool Pathfinder::Astar::NodeComparison(std::unique_ptr<Pathfinder::Node>& node, std::tuple<uint32_t, uint32_t> position)
//{
//	if (node->GetPosition() == position)
//		return true;
//	else
//		return false;
//}

uint16_t Pathfinder::Astar::InputMapLocation(uint32_t xCoord, uint32_t yCoord, const int nMapHeight)
{
	return (yCoord - 1) * nMapHeight + (xCoord - 1);
}

uint8_t Pathfinder::Astar::NumOfClosed()
{
	return closed.size();
}

int Pathfinder::Astar::FindPath 
(
	const int nStartX, const int nStartY,
	const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize
) 
{
	std::unique_ptr<Pathfinder::Node> startingNode (new Pathfinder::Node(nStartX, nStartY));
	std::unique_ptr<Pathfinder::Node> finishNode (new Pathfinder::Node(nStartX, nStartY));

	open.push_back(std::move(startingNode));

	while (true) // Set exit condition condition
	{
		std::unique_ptr<Pathfinder::Node>& newCurrent = std::move(open.front()); // Lowest F score in the sorted open list

		closed.push_back(newCurrent); // New node becomes current and is moved to closed list
		uint32_t xCoord, yCoord;

		std::tie(xCoord, yCoord) = newCurrent->GetPosition();
		
		// Add 4 surrounding nodes to open list, unless closed/non-walkable
		// pMap[i] = 1 - walkable, pMap[i] = 0 - non-walkable

		// If not walkable or on the closed list, ignore
		if (pMap[InputMapLocation(xCoord, yCoord - 1,nMapHeight)] != 0 && FindNodeInList(xCoord, yCoord - 1, closed))
		{
			// If not already in open list
			std::unique_ptr<Pathfinder::Node>& openNode = FindNodeInList(xCoord, yCoord - 1, open);
			if (!openNode) 
			{
				std::unique_ptr<Pathfinder::Node> newNode(new Pathfinder::Node(xCoord, yCoord - 1, *finishNode, newCurrent, closed.size()));
				Pathfinder::Astar::AddToOpen(newNode, open);
			}
			else
			{
				// If on already on the open list, check for better path through current node
				if (IsBetterPath(*openNode))
				{
					openNode->ChangeParent(*newCurrent);
				}
			}
		}

		if (pMap[InputMapLocation(xCoord, yCoord + 1, nMapHeight)] != 0 && (FindNodeInList(xCoord, yCoord + 1, closed) != nullptr))
		{
			std::unique_ptr<Pathfinder::Node> newNode(new Pathfinder::Node(xCoord, yCoord + 1, *finishNode, newCurrent, closed.size()));

		}

		if (pMap[InputMapLocation(xCoord - 1, yCoord, nMapHeight)] != 0 && FindNodeInList(xCoord - 1, yCoord, closed))
		{
			std::unique_ptr<Pathfinder::Node> newNode(new Pathfinder::Node(xCoord - 1, yCoord, *finishNode, newCurrent, closed.size()));

		}

		if (pMap[InputMapLocation(xCoord + 1, yCoord, nMapHeight)] != 0 && FindNodeInList(xCoord + 1, yCoord, closed))
		{
			std::unique_ptr<Pathfinder::Node> newNode(new Pathfinder::Node(xCoord + 1, yCoord, *finishNode, newCurrent, closed.size()));

		}

	}

}