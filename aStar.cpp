#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "allegroconfig.hpp"
#include "enemy.hpp"
#include "wall.hpp"
#include "config.hpp"

using namespace std;

short map[XSIZE][YSIZE];
short closedNodesMap[XSIZE][YSIZE]; // map of closed (tried out) nodes
short openNodesMap[XSIZE][YSIZE]; // map of open (not yet tried) nodes
short directionMap[XSIZE][YSIZE];
short xDirections[DIRECTIONS]= {1, 0, -1, 0};
short yDirections[DIRECTIONS]= {0, 1, 0, -1};

class Node
{
    short xPosition;
    short yPosition;  // current position
    short level;  // total distance already travelled to reach the Node
    short priority;  // priority = level + remaining distance estimate smaller: higher priority

public:
    Node(short _xPosition, short _yPostion, short _level, short _priority)
    {
        xPosition = _xPosition;
        yPosition = _yPostion;
        level = _level;
        priority = _priority;
    }

    short getX() const
    {
        return xPosition;
    }

    short getY() const
    {
        return yPosition;
    }

    short getLevel() const
    {
        return level;
    }

    short getPriority() const
    {
        return priority;
    }

    void updatePriority(const short & _xDestination, const short & _yDestination)
    {
        priority = level + estimate(_xDestination, _yDestination) * 10; //A*
    }

    // Estimation function for the remaining distance to the goal
    const short & estimate(const short & _xDestination, const short & _yDestination) const
    {
        static short xDistance, yDistance, distance;
        xDistance = _xDestination - xPosition;
        yDistance = _yDestination - yPosition;

        distance = static_cast<short>( sqrt( xDistance * xDistance + yDistance * yDistance));

        return(distance);
    }
};

bool operator<(const Node & aNode, const Node & bNode) // Determine priority (in the priority queue)
{
    return aNode.getPriority() > bNode.getPriority();
}

// A-star algorithm -> return string of direction digits
string pathFind( const short & xStart, const short & yStart, const short & xFinish, const short & yFinish )
{
    static priority_queue<Node> priorityQueue[2]; // list of open (not yet tried) nodes
    static short priorityQueueIndex; // priorityQueue index
    static Node* node0;
    static Node* childNode;
    short j=0;
    short x, y, xChange, yChange;
    char charDirection;
    priorityQueueIndex=0;

    for(y=0; y < YSIZE; y++)// reset the Node maps
    {
        for(x=0; x < XSIZE; x++)
        {
            closedNodesMap[x][y] = 0;
            openNodesMap[x][y] = 0;
        }
    }

    node0 = new Node(xStart, yStart, 0, 0); // create start Node and push into list of open nodes
    node0 -> updatePriority(xFinish, yFinish);
    priorityQueue[priorityQueueIndex].push(*node0);
    openNodesMap[x][y] = node0 -> getPriority(); // mark it on open nodes map
    delete node0; //clear memory

    while(!priorityQueue[priorityQueueIndex].empty()) // A* search
    {
        // get the current Node with the highest priority from the list of open nodes
        node0 = new Node( priorityQueue[priorityQueueIndex].top().getX(), priorityQueue[priorityQueueIndex].top().getY(), priorityQueue[priorityQueueIndex].top().getLevel(), priorityQueue[priorityQueueIndex].top().getPriority());

        x = node0 -> getX();
        y = node0 -> getY();

        priorityQueue[priorityQueueIndex].pop(); // remove the Node from the open list
        openNodesMap[x][y]=0;
        closedNodesMap[x][y]=1; // mark it on the closed nodes map

        if(x==xFinish && y==yFinish) // quit searching when goal state is reached
        {
            // generate path from finish to start by following directions
            string path = ""; //empty path
            while(!(x == xStart && y == yStart))
            {
                j = directionMap[x][y];
                charDirection = '0' + (j + DIRECTIONS/2)%DIRECTIONS;
                path = charDirection + path;
                x += xDirections[j];
                y += yDirections[j];
            }

            delete node0; // clear memory
            while(!priorityQueue[priorityQueueIndex].empty())
                priorityQueue[priorityQueueIndex].pop(); // empty the leftover nodes

            return path;
        }

        for(short i=0; i<DIRECTIONS; i++) // generate moves (child nodes) in all possible directions
        {
            xChange = x + xDirections[i];
            yChange = y + yDirections[i];

            if(!(xChange < 0 || xChange > XSIZE-1 || yChange < 0 || yChange > YSIZE-1 || map[xChange][yChange] == 1 || closedNodesMap[xChange][yChange] == 1))
            {
                childNode = new Node( xChange, yChange, node0 -> getLevel(), node0 -> getPriority()); // generate a child Node
                childNode -> updatePriority(xFinish, yFinish);

                if(openNodesMap[xChange][yChange] == 0) // if it is not in the open list then add into that
                {
                    openNodesMap[xChange][yChange] = childNode -> getPriority();
                    priorityQueue[priorityQueueIndex].push(*childNode);
                    delete childNode; //clear memory
                    directionMap[xChange][yChange] = (i + DIRECTIONS/2)%DIRECTIONS; // mark its parent Node direction
                }
                else if(openNodesMap[xChange][yChange] > childNode -> getPriority())
                {
                    openNodesMap[xChange][yChange] = childNode -> getPriority();
                    directionMap[xChange][yChange]=(i + DIRECTIONS/2)%DIRECTIONS; // update the parent direction info

                    // replace the Node by emptying one priorityQueue to the other one except the Node to be replaced will be ignored and the new Node will be pushed in instead
                    while(!(priorityQueue[priorityQueueIndex].top().getX() == xChange && priorityQueue[priorityQueueIndex].top().getY() == yChange))
                    {
                        priorityQueue[1-priorityQueueIndex].push(priorityQueue[priorityQueueIndex].top());
                        priorityQueue[priorityQueueIndex].pop();
                    }
                    priorityQueue[priorityQueueIndex].pop(); // remove wanted Node

                    if(priorityQueue[priorityQueueIndex].size() > priorityQueue[1-priorityQueueIndex].size())  // empty the larger size priorityQueue to the smaller one
                        priorityQueueIndex = 1 - priorityQueueIndex;

                    while(!priorityQueue[priorityQueueIndex].empty())
                    {
                        priorityQueue[1 - priorityQueueIndex].push(priorityQueue[priorityQueueIndex].top());
                        priorityQueue[priorityQueueIndex].pop();
                    }
                    priorityQueueIndex = 1 - priorityQueueIndex;
                    priorityQueue[priorityQueueIndex].push(*childNode); // add the better Node instead
                    delete childNode; // only 2nd item added
                }
                else delete childNode; // clear memory
            }
        }
        delete node0; // clear memory
    }

    return ""; // no route found
}

string FindPath(Enemy **enemy, Wall **wall, Player * player, short choice, bool onlyImmortal, bool isPlayer)
{
    for(short y = 0; y < YSIZE; y++)    // create empty map
    {
        for(short x = 0; x < XSIZE; x++)
            map[x][y] = 0;
    }

    for (short i=0; i < OBSTACLES ; i++) // set nodes with obstacles
    {
        if(wall[i] -> getVisible())
        {
            if(onlyImmortal)
            {
                if (!wall[i] -> getDestroyable())
                    map[wall[i] -> getX() / 50][wall[i] -> getY() / 50] = 1;
            }

            else
                map[wall[i] -> getX() / 50][wall[i] -> getY() / 50] = 1;
        }
    }

    for (short i=0; i < ENEMIES ; i++) // set nodes with enemies
    {
        if(!enemy[i] -> getDead())
        {
            short x = enemy[i] -> getX()/50;
            short y = enemy[i] -> getY()/50;
            if(enemy[i] -> getX() % 50 > 45)
                x++;
            if(enemy[i] -> getY() % 50 > 45)
                y++;
            map[x][y] = 1;
        }

    }
    if(isPlayer) // set Node with player
    {
        short x = player -> getX()/50;
        short y = player -> getY()/50;
        if(player-> getX() % 50 > 45)
            x++;
        if(player -> getY() % 50 > 45)
            y++;
        map[x][y] = 1;
    }

    short xStart = enemy[choice] -> getX()/50;
    short yStart = enemy[choice] -> getY()/50;

    if(enemy[choice] -> getX() % 50 > 45)
        xStart++;
    if(enemy[choice] -> getY() % 50 > 45)
        yStart++;

    short xFinish = enemy[choice] -> getDestinationX()/50;
    short yFinish = enemy[choice] -> getDestinationY()/50;

    if(enemy[choice] -> getDestinationX() % 50 > 45)
        xFinish++;
    if(enemy[choice] -> getDestinationY() % 50 > 45)
        yFinish++;

    string route=pathFind(xStart, yStart, xFinish, yFinish);
    if(route == "")
        return "5"; //empty route

    return route;
}

/*
0 - right
1 - down
2 - left
3 - up
*/
