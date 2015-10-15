#include "SDFGenerator.h"

SDFGenerator::SDFGenerator(uint Nodes, uint Edges)
:
numNodes(Nodes),
numEdges(Edges),
actualEdges(0)
{

}

SDFGenerator::~SDFGenerator()
{

}

////////////////// MISC METHODS ///////////////////////

std::vector<Edge*>* SDFGenerator::getEdgeList()
{

    return &edges;
}



//////////////////////////////////////////////////////

/******************** The SDF BUILDER *************************/
/*************************************************************/
/* Builds the Graph */
void SDFGenerator::buildGraph() throw()
{
    bool debug = false;
    try
    {
        // Setting the 1st Node
        Node *n = findNode(randomType, &Node::NodeDataBase, NULL);
        addNodestoGraph(*n);
        setFirst(n);



        std::cout << "Building Graph" << std::endl;

        buildAllConnected();

        int netEdges = numEdges - getActualEdgeCount();


        while(netEdges)
        {
            Node* n1 = findNode(randomType, &nodes, NULL);
            Node* n2 = findNode(compatitbleType, &nodes, n1);

           // std::cout << "Node found : " << n1->getLabel() << "   " << n2->getLabel() << std::endl;

            makeEdge(n1, n2);
            netEdges--;
        }



         if(debug)
        {


            std::cout << "Node List " << std::endl;

            std::vector<Node*> *vec = &nodes;

            for(auto it : *vec)
            {
                std::cout << it->getLabel() << " : " ;
            }

        }


        // Set the last Node
        Node* last = nodes.back();
        setLast(last);

        removeDuplicates();
        std::cout << "Duplicates Removed" << std::endl;

    }
    catch(std::exception ex)
    {
        std::cout << ex.what() << std::endl;
    }

    if(debug)
    {
        std::cout << "1st Node " << firstNode->getLabel() << std::endl << "last Node " << lastNode->getLabel();
    }
    return;
}

/* Builds a minimum SDF with all the nodes connected */
void SDFGenerator::buildAllConnected() throw()
{
    try
    {
        for(uint i = 0; i < numNodes - 1 ; i++)
        {
            Node* n1 = nodes.at(i);

            if(bool debug = false)
            {
                std::cout << "Finding Compatitble " << std::endl;
            }
            Node* n2 = findNode(compatitbleType, &Node::NodeDataBase, n1);

            addNodestoGraph(*n2);


            if(bool debug =  false)
            {
                std::cout << "Building Edge  " << std::endl;
            }
            makeEdge(n1, n2);
               if(bool debug =  false)
            {
                std::cout << "Edge Built  " << std::endl;
            }
        }
        // Removes Duplicate Nodes in List
       // std::vector<Node*>::iterator it = std::unique (nodes.begin(), nodes.end());
       // nodes.resize(std::distance(nodes.begin(), it));
            removeDuplicateNode();
    }
    catch(...)
    {
        throw;
    }
    return;
}


/* Builds an Edge between the two Nodes */
void SDFGenerator::makeEdge(Node* n1, Node* n2) throw(std::logic_error)
{
    try
    {

        std::stringstream label, head, tail;
        label << "ch" << edges.size() + 1;
        head << n1->getOutputType();
        tail << n2->getInputType();
        Edge e(label.str(), head.str(), tail.str(), n1, n2);
        addEdgestoGraph(e);
        n1->modifyOutDegree(Node::increase);
        n2->modifyInDegree(Node::increase);
    }
    catch(...)
    {
        throw std::logic_error("Edge Not Possible with the Nodes");
    }
    return;
}


/*Add Nodes to the Graph */
void SDFGenerator::addNodestoGraph(Node& n) throw(std::logic_error)
{
    try
    {
        nodes.push_back(new Node(n));
    }
    catch(...)
    {
        throw std::logic_error("Not able to add Node");
    }
    return;
}

/*Add Edges to the Graph */
void SDFGenerator::addEdgestoGraph(Edge& e) throw(std::logic_error)
{

    try
    {
        edges.push_back(new Edge(e));
        actualEdges = edges.size();
    }
    catch(...)
    {
        throw std::logic_error("Not able to add Edge");
    }
    return;
}

/* Delete Edge from the Graph */
void SDFGenerator::deleteEdge(Edge *e) throw()
{
    try
    {
        if(int pos = findEdgefromList(e, &edges))
        {
            edges.erase(edges.begin() + pos - 1);
        }
        else
            throw std::logic_error ("Delete Edge: Edge Not Found");

    }
    catch(...)
    {
        throw;
    }
    return;
}
/* Compare Edges for equality */
bool SDFGenerator::edgeUnique(Edge* e1, Edge* e2)
{
    std::pair<Node*, Node*> edge1pair = e1->getSourceAndDest();
    std::pair<Node*, Node*> edge2pair = e2->getSourceAndDest();

    if((edge1pair.first->getLabel() == edge2pair.first->getLabel())
    && (edge1pair.second->getLabel() == edge2pair.second->getLabel()) )
    {
        return false;
    }
    return true;

}
/* Compare Nodes for equality */
bool SDFGenerator::nodeUnique(Node* n1, Node* n2)
{

    if((n1->getLabel() == n2->getLabel()) && (n1->getInputType() == n2->getInputType())
    &&(n1->getOutputType() == n2->getOutputType()))
    {
        return false;
    }
    return true;
}


/* Removes Duplicate Nodes*/

void SDFGenerator::removeDuplicateNode() throw(std::logic_error)
{
    bool debug = false;
    try
    {
        if(nodes.size() <= 1)
            return;
        if(debug)
            printNodesInGraph(PrintOp::Console, NULL);
        for(std::vector<Node*>::iterator it = nodes.begin(); it!= nodes.end(); it++)
        {
            for(std::vector<Node*>::iterator j = it + 1; j!= nodes.end(); j++)
            {
                if(nodeUnique((*it), *j))
                {
                    continue;
                }
                else
                {
                    nodes.erase(j);
                    j--;
                }
            }
        }
    }
    catch(...)
    {}

}

/* Removes Duplicate Edges from Graph */
void SDFGenerator::removeDuplicates() throw(std::logic_error)
{
    bool debug = false;

    try
    {


        if(edges.size() <= 1)
            return;

        if(debug)
                printEdgesInGraph(PrintOp::Console, NULL);

        for( std::vector<Edge*>::iterator it = edges.begin(); it!= edges.end() ; it++)
        {
            for(std::vector<Edge*>::iterator j = it+1; j != edges.end(); j++)
            {
                if(edgeUnique((*it), (*j)))
                {
                    if(debug)
                    {
                        std::cout << (*it)->getLabel() << " and "
                        << (*j)->getLabel() << " are distinct " << std::endl;
                    }
                    continue;
                }
                else
                   {
                        if(debug)
                        {
                            std::cout << (*it)->getLabel() << " and "
                            << (*j)->getLabel() << " NOT distinct " << std::endl;

                            std::cout << "Deleting " << (*j)->getLabel() << std::endl;
                        }

                        edges.erase(j);
                        j--;
                   }
            }
        }

    }
    catch(...)
    {
        throw std::logic_error("Remove Duplicate : Not able to access Edge List");
    }

}


/*
void SDFGenerator::setStartandEnd() throw()
{   // Find random 1st and last node
    try
    {
        Node *n1 = findNode(randomType, &Node::NodeDataBase, NULL);
        Node *n2 = findNode(randomType, &Node::NodeDataBase, NULL);

        setFirst(n1);
        setLast(n2);

        addNodestoGraph(*n1);
        addNodestoGraph(*n2);

    }
    catch(...)
    {
        throw std::logic_error("Unable to set 1st and last node");
    }


    return;
}
*/

/***************** To find the NODES/ACTORS and Channels/Edges****************************/
/*********************************************************************/

/* Find the Node and return a reference */
Node* SDFGenerator::findNode(findNodeType NodeType,  std::vector<Node*>* Node_List, Node * n = NULL) throw()
{

    try
    {
        if(NodeType == SDFGenerator::compatitbleType)
        {
            return findCompatitbleNode(n, Node_List);
        }
        else
        {
            return findRandomNode(Node_List);
        }

    }
    catch(...)  // Should be made specific later
    {
        throw;
    }


}

/* Find the Node and return a reference - compatible type */
Node* SDFGenerator::findCompatitbleNode(Node* n, std::vector<Node*>* Node_list) throw(std::out_of_range)
{
    uint output_type = n->getOutputType();
    int index = Node::getInputMatch(output_type);
    int i = 0;
   // Node_list = &Node::IpTypeSortedNodes[index];

    uint max_size = Node_list->size();

    bool debug = false;
    if(debug)
    {
        std::cout << "Finding Compatitble Node" << std::endl;
    }

  //  std:: cout << " WAITING HERE" << std::endl;
    try
    {
        do
        {

            i  = rand() % max_size;
      //    AnalysisSDF::PrintRounds(); // Just to check the probablility - works avg - 5 tries
        } while(Node_list->at(i)->getInputType() != output_type);
        // Keep looping till a compatitble Node is found (probablility = 1/4)
    }
    catch(...)
    {
        throw std::out_of_range("Compatitble : Node not found");
    }

    return Node_list->at(i);
}

/* Find the Node and return a reference - random type */
Node* SDFGenerator::findRandomNode(std::vector<Node*>* Node_list) throw(std::out_of_range)
{
    uint max_size = Node_list->size();
    int n = rand() % max_size;

    try
    {
        return Node_list->at(n);
    }
    catch(...)
    {
        throw std::out_of_range("Random : Node not found");
    }

}


/* Find the edge in the list */
int SDFGenerator::findEdgefromList(Edge* e, std::vector<Edge*>* Edge_list) throw(std::out_of_range)
{
    int edgePos = 0;
    bool debug = false;
   try{
        for(std::vector<Edge*>::iterator it = Edge_list->begin(); it != Edge_list->end(); it++)
        {
            if(debug)
            {
                std::cout << "Edge - " << e->getLabel() << " -- " << (*it)->getLabel() << std::endl;

            }
            if(e->getLabel() == (*it)->getLabel())
            {
                return edgePos;
            }

            edgePos++;
        }
    }
   catch(...)
   {
        throw std::out_of_range("Edge not found");
   }
    return -1;

}


/******************* Printer Functions ******************/
/********************************************************/

/* Prints the Nodes in graph */
void SDFGenerator::printNodesInGraph(PrintOp::PrintZone printType ,std::ofstream * obj) throw (std::out_of_range)
{
    bool debug = false;
    std::cout << " Printing Graph " << std::endl;
    try
    {
        if(debug)
        {
            std::cout << "=====================================" << std::endl;
            std::cout << " The nodes in Graph are " << std::endl;
        }

        for(std::vector<Node*>::iterator it = nodes.begin(); it!=nodes.end(); it++)
        {
            (*it)->printNode(printType, obj);
        }
    }
    catch(...)
    {
        throw std::out_of_range("Nodes not in Range : inaccessible ");
    }

    return;
}

/*Prints the Edges in graph */
void SDFGenerator::printEdgesInGraph(PrintOp::PrintZone printType, std::ofstream *obj) throw (std::out_of_range)
{
 bool debug = false;

    try
    {
        if(debug)
        {
            std::cout << "=====================================" << std::endl;
            std::cout << " The Edges in Graph are " << std::endl;
        }

        for(std::vector<Edge*>::iterator it = edges.begin(); it!=edges.end(); it++)
        {
            (*it)->printEdge(printType, obj);
        }
    }
    catch(...)
    {
        throw std::out_of_range("Nodes not in Range : inaccessible ");
    }

    return;

}

/*Prints the entire graph in dot format */
void SDFGenerator::printTheGraphinDot(PrintOp::PrintZone pType, std::ofstream *obj) throw(std::out_of_range)
{
    std::stringstream ss;
    ss << "digraph g { \nsize\"" << numNodes << "," << actualEdges << "\";\n" << std::endl;

    if(pType == PrintOp::Console)
    {
        std::cout << ss.str();
    }
    else
    {
        *obj << ss.str();
        AnalysisSDF::dottyFontFix(obj);
    }
    ss.str("");
    ss << std::endl << " } " << std::endl;
    try
    {
        printNodesInGraph(pType, obj);
        printEdgesInGraph(pType, obj);
    }
    catch(...)
    {
        throw std::out_of_range("Unable to Print the SDF");
    }


    if(pType == PrintOp::Console)
    {
        std::cout << ss.str();
    }
    else
    {
        *obj << ss.str();
    }

    return;
}

 /** Get and Set Functions **/
uint SDFGenerator::getNodesMaxNum()
{
    return numNodes;
}

uint SDFGenerator::getEdgesMaxNum()
{
    return numEdges;
}

Node* SDFGenerator::getstart()
{
    return firstNode;
}
Node* SDFGenerator::getEnd()
{
    return lastNode;
}


void SDFGenerator::setFirst(Node* n)
{
    firstNode = n;
 //   firstNode->setInDegreeMax(1);

}

void SDFGenerator::setLast(Node* n)
{
    lastNode = n;
}

uint SDFGenerator::getActualEdgeCount()
{
    return (actualEdges = edges.size());

}

std::vector<Node*>* SDFGenerator::getNodeList()
{
     return &nodes;
}

bool SDFGenerator::isFirst(Node* n) throw(std::logic_error)
{
    try
    {
        if(firstNode->getLabel() == n->getLabel())
        {
            return true;
        }
        return false;
    }
    catch(...)
    {
        throw std::logic_error("first Node not set");
    }
}

bool SDFGenerator::isLast(Node* n) throw(std::logic_error)
{

    try
    {
        if(lastNode->getLabel() == n->getLabel())
        {
            return true;
        }
        return false;
    }
    catch(...)
    {
        throw std::logic_error("last Node not set");
    }
}


