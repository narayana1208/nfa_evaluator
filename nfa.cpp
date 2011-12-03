#include "nfa.h"
#include "stdio.h"
#include <QHashIterator>

Nfa::Nfa()
{
    /*Q = new QSet<QString>();
    q0 = "";
    sigma = new QSet<QString>();
    delta = new QHash<QPair<QString, QString>, QSet<QString>*>();
    reverseDelta =  new QHash<QPair<QString, QString>, QSet<QString>*>();
    f = new QSet<QString>();*/
}

/*void Nfa::addTransition(QString source, QString destination, QString path)
{

}*/

/*void Nfa::debugPrintDelta()
{
    QHashIterator<QPair<QString, QString>, QSet<QString>*> i(*delta);
    QPair<QString, QString> pair;
    while (i.hasNext())
    {
        i.next();
        pair = i.key();
        printf("key< %s %s >, pair", pair.first.toStdString().c_str(), pair.second.toStdString().c_str());
        QSet<QString>* value = i.value();
        debugPrintSet(value);
        printf("\n");
    }
}

void Nfa::debugPrintSet(QSet<QString>* set)
{
    QSetIterator<QString> j(*set);
    printf("{ ");
    while (j.hasNext())
    {
        printf("%s ", j.next().toStdString().c_str());
    }
    printf("}");
}

bool Nfa::isValidString(QString string, bool isParallel)
{
    // Save the set from running runNfa into a variable so that it can
    // be properly deleted.
    QSet<QString>* finalStates;
    if (isParallel)
    {
        if (VERBOSE)
        {
            printf("Traversing NFA in parallel.\n");
        }
        finalStates = runNfaP(string);
    }
    else
    {
        if (VERBOSE)
        {
            printf("Traversing NFA sequentially.\n");
        }
        finalStates = runNfa(string);
    }
    bool intersects = finalStates->intersect(*f).count() > 0;
    delete finalStates; // Remove memory allocated for finalStates.
    return intersects;
}

QSet<QString>* Nfa::runNfa(QString string)
{
  Traversal* trav = new Traversal(0, &q0);
  QSet<Traversal*>* travs = setupInitials(trav);
  return traverse(travs, &string);
}

QSet<Traversal*>* Nfa::setupInitials(Traversal* trav)
{
  QSet<Traversal*>* travs = new QSet<Traversal*>();
  QPair<QString, QString> pair;
  pair.first = *(trav->state());
  pair.second = "@";

  return travs->unite(*delta->value(pair));
}

QSet<QString>* Nfa::traverse(QSet<Traversal*>* qSet, QString* str)
{
    // Special Case: Check to see if epsilon jump exists between initial state and another state
    QPair<QString, QString> pair;
    pair.first = *(trav->state());
    pair.second = QString("@");

    // If there's an epsilon jump to any other states, jump
    if (delta->contains(pair))
    {
        qSet->unite(*delta->value(pair));
    }

    // Represents all the states that you WILL be in, during the next iteration
    QSet<QString>* newSet = new QSet<QString>();;
    for (int i = 0; i < str->size(); i++)
    {
        // Empty the new states (current states are kept in qSet)
        newSet->clear();
        QSetIterator<QString> j(*qSet);
        while(j.hasNext())
        {
            // Create a pair of State and transition
            pair.first = j.next();
            pair.second = (*str)[i];
            // If the State-Transition pair has any matches, add them to the new set
            if (delta->contains(pair))
            {
                newSet->unite(*delta->value(pair));
            }

            // Check for epsilon jumps, add them to the new set
            pair.second = QString("@");
            if (delta->contains(pair))
            {
                newSet->unite(*delta->value(pair));
            }
            
            // newSet becomes current set (qSet) for the next iteration
            qSet->clear();
            qSet->unite(*newSet); // Done this way for memory management.

            // If all the transitions leave the NFA, no matches, you're done
            if (qSet->count() == 0)
            {
                return qSet;
            }
        }
    }

    // Congrats! There were matches!
    delete newSet;
    return qSet;

}*/

/*QSet<QString>* Nfa::runNfaP(QString string)
{
    // debugPrintDelta();
    QSet<QString>* qSet = new QSet<QString>();
    qSet->insert(q0);

    QPair<QString, QString> pair;
    pair.first = q0;
    pair.second = QString("@");
    // printf("key< %s %s >\n", pair.first.toStdString().c_str(), pair.second.toStdString().c_str());

    if (delta->contains(pair))
    {
        qSet->unite(*delta->value(pair));
        //debugPrintSet(qSet);
        //printf("\n");
    }

    QSet<QString>* newSet = new QSet<QString>();;
    #pragma omp parallel for
    for (int i = 0; i < string.length(); i++)
    {
        newSet->clear();
        QSetIterator<QString> j(*qSet);
        while(j.hasNext())
        {
            pair.first = j.next();
            pair.second = string[i];
            if (delta->contains(pair))
            {
                newSet->unite(*delta->value(pair));
            }

            pair.second = QString("@");
            if (delta->contains(pair))
            {
                newSet->unite(*delta->value(pair));
            }

            qSet->clear();
            qSet->unite(*newSet); // Done this way for memory management.

            //if (qSet->count() == 0)
            //{
            //    return qSet;
            //}
        }
    }

    //debugPrintSet(qSet);
    //printf("\n");
    return qSet;
}*/
