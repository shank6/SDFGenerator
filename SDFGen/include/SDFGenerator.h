#ifndef SDFGENERATOR_H
#define SDFGENERATOR_H

#include "Node.h"
#include "Edge.h"

#include <exception>
#include <stdexcept>
#include <algorithm>
#include "AnalysisSDF.h"

class SDFGenerator
{
    public:

        enum findNodeType { compatitbleType , randomType  };


        SDFGenerator(uint Node_num, uint Edge_num);
        virtual ~SDFGenerator();
        /** Node/Actor - Channel/Edge Finders **/
        /* Find a node from the pool of Nodes from the list */
        /* Find Node type is to check compatatiblity with the previous Node, or select random Node*/
        Node* findNode(findNodeType NType ,std::vector<Node*>* Node_list,  Node* n ) throw();
        Node* findCompatitbleNode(Node* n, std::vector<Node*>* Node_list) throw(std::out_of_range);
        Node* findRandomNode(std::vector<Node*>* Node_list) throw(std::out_of_range);
        int findEdgefromList(Edge* e ,std::vector<Edge*>* Edge_list) throw(std::out_of_range);

        /** SDF Builder**/
        /*Build the Graph */
        void buildGraph() throw();
        /* Builds a minimum SDF with all the nodes connected */
        void buildAllConnected() throw();
        /*Add Nodes to the Graph */
        void addNodestoGraph(Node& n) throw(std::logic_error);
        /*Add Edges to the Graph */
        void addEdgestoGraph(Edge& e) throw(std::logic_error);
        /* Builds an Edge of Compatitble Type */
        void makeEdge(Node* n1, Node *n2) throw(std::logic_error);
        /* Delete Edge from the Graph */
        void deleteEdge(Edge* e) throw();
        void removeDuplicateNode() throw(std::logic_error);
        /* Removes Duplicated from the list */
        void removeDuplicates() throw(std::logic_error);


      //   /* Assign Start and End of SDF */
     //   void setStartandEnd() throw();



        /** Printer Functions **/
        /* Prints the Nodes in graph */
        void printNodesInGraph(PrintOp::PrintZone pType,std::ofstream *obj) throw (std::out_of_range);
        /*Print the Edges in graph */
        void printEdgesInGraph(PrintOp::PrintZone pType, std::ofstream *obj) throw (std::out_of_range);
        /*Prints the entire graph in dot format */
        void printTheGraphinDot(PrintOp::PrintZone pType, std::ofstream *obj) throw(std::out_of_range);


        /** Get and Set Functions **/
        uint getNodesMaxNum();
        uint getEdgesMaxNum();

        Node* getstart();
        Node* getEnd();
        void setFirst(Node* n);
        void setLast(Node* n);

        uint getActualEdgeCount();

        /* Checks whether 1st node */
        bool isFirst(Node* n) throw(std::logic_error);
        /* Checks whether last node */
        bool isLast(Node* n)throw(std::logic_error);

        /* gets the reference to the Node List */
        std::vector<Node*>* getNodeList();

        //MISC METHODS - LATER DELETE
        std::vector<Edge*>* getEdgeList() ;

    protected:
    private:

    uint numNodes;
    uint numEdges;
    uint actualEdges;

    Node* firstNode;
    Node* lastNode;
    std::vector<Node*> nodes;
    std::vector<Edge*> edges;

    /* Predicate for unique- */
    bool edgeUnique(Edge*, Edge*);
    bool nodeUnique(Node*, Node*);

    // Misc Variables
    findNodeType Ntype;



};

#endif // SDFGENERATOR_H
