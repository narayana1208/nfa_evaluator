#include <QtCore/QCoreApplication>
#include <QHash>
#include <QSet>
#include <QTime>
#include "stdio.h"

#include "nfa.h"
#include "node.h"

void debugPrintSet(QSet<Node>* set)
{
    QSetIterator<Node> i(*set);

    printf("[ ");
    while(i.hasNext())
    {
        Node node = i.next(); // Not doing it this way caused a weird const error.
        printf("%s ", node.getName().toStdString().c_str());
    }
    printf("]\n");
}

int main()
{
    // QCoreApplication a(argc, argv);
    // return a.exec();

    // Nfa* nfa = new Nfa();
    Node* s1 = new Node("s1");
    Node* s2 = new Node("s2");
    Node* s3 = new Node("s3");
    Node* s4 = new Node("s4");
    Node* s5 = new Node("s4");
    Node* s6 = new Node("s6");
    s1->addRelation(*s3, "1");
    s1->addRelation(*s4, "@");
    s1->addRelation(*s6, "2");
    s6->addRelation(*s2, "0");
    s6->addRelation(*s2, "1");
    s4->addRelation(*s2, "3");
    s3->addRelation(*s2, "4");
    s3->addRelation(*s4, "@");
    s2->addRelation(*s1, "4");
    s2->addRelation(*s5, "1");
    s5->addRelation(*s1, "2");
    s5->addRelation(*s3, "2");
    s3->addRelation(*s5, "2");

    if (VERBOSE)
    {
        s1->debugPrint();
        s3->debugPrint();
        s4->debugPrint();
        s6->debugPrint();
        s2->debugPrint();

        // Raw state tests...

        printf("Raw states of s1: ");
        debugPrintSet(s1->rawStates(FORWARDS));

        printf("Backwards raw states of s4: ");
        debugPrintSet(s4->rawStates(BACKWARDS));

        // Traversal tests...

        printf("Forward traversal set of node s5 on 2: ");
        debugPrintSet(s5->traverseOn("2", FORWARDS));

        printf("Backward traversal set of node s5 on 2: ");
        debugPrintSet(s5->traverseOn("2", BACKWARDS));

        printf("Forward traversal set of node s5 on 6: ");
        debugPrintSet(s5->traverseOn("6", FORWARDS));
    }
}
