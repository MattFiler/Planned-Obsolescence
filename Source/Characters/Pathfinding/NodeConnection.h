//
// Created by tobyj on 22/01/2019.
//

#ifndef PLANNEDOBSOLESCENCE_NODECONNECTION_H
#define PLANNEDOBSOLESCENCE_NODECONNECTION_H

struct PathNode;

/**
 **   Represents the connection between 2 nodes. Holds relevant information
 *    for path-finding
 */
struct NodeConnection
{
  PathNode* node = nullptr;
  bool open = true;
  float score = -1;
};

#endif // PLANNEDOBSOLESCENCE_NODECONNECTION_H
