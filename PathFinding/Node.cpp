#include "Node.h"

Pathfinder::Node::Node
(
	uint32_t x = 0, uint32_t y = 0
) : xPosition(x), yPosition(y), parent(nullptr)
{

}

Pathfinder::Node::Node
(
	uint32_t x, uint32_t y, 
	Node& dst, std::unique_ptr<Node> const &par, 
	size_t closedNum
) : xPosition(x), yPosition(y), parent(std::move(par))
{
	G = closedNum * nonDiagonalCost + 10; // Initial G cost, using the fact that no diagonal movement is allowed
	H = CostToNode(dst);
	F = G + H;
}

Pathfinder::Node::~Node()
{

}

std::unique_ptr<Pathfinder::Node>& Pathfinder::Node::GetParent()
{
	return this->parent;
}

void Pathfinder::Node::UpdateF()
{
	this->F = this->G + this->H;
}

void Pathfinder::Node::UpdateG()
{

}

uint32_t Pathfinder::Node::CostToNode(Node& node)
{
	uint32_t xDest, yDest, cost;

	std::tie(xDest, yDest) = node.GetPosition();
	uint32_t xIterator = this->xPosition;
	uint32_t yIterator = this->yPosition;
	cost = 0;

	while (xIterator != xDest)
	{
		cost += nonDiagonalCost;
		if (xIterator > xDest)
		{
			xIterator--;
		}
		else {
			xIterator++;
		}
	}
	while (yIterator != yDest)
	{
		cost += nonDiagonalCost;
		if (yIterator > yDest)
		{
			yIterator--;
		}
		else {
			yIterator++;
		}
	}

	return cost;
}
