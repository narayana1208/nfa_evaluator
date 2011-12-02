#ifndef NFA_H
#define NFA_H

#include <QHash>
#include <QSet>
#include <QString>
#include <QPair>
#include "traversal.h"

class Nfa
{
public:
    static Nfa* createNfa(QSet<QString>* Q, QString q0, QSet<QString>* sigma, QHash<QPair<QString, QString>, QSet<QString>*>* delta, QSet<QString>* f);

    // TODO: Figure out how to make private.
    Nfa(QSet<QString>* Q, QString q0, QSet<QString>* sigma, QHash<QPair<QString, QString>, QSet<QString>*>* delta, QSet<QString>* f);

    // TODO: Make private again.
    bool isValidString(QString string, bool isParallel);
    QSet<QString>* runNfa(QString string);
    QSet<QString>* runNfaP(QString string);

    QList<Traversal*>* step(Traversal* trav, QString* str);

    /*
     * Prints a string that python can read in as its own native data structures
     * (Used for testing)
     */
    QString toPyString();

private:
    // Private member variables.
    QSet<QString>* Q;
    QString q0;
    QSet<QString>* sigma;
    QHash<QPair<QString, QString>, QSet<QString>*>* delta;
    QSet<QString>* f;

    QSet<QString>* traverse(Traversal* traversal, QString* str);

    // Private methods.
    Nfa();
    void debugPrintDelta();
    void debugPrintSet(QSet<QString>* set);

    // Verbose output
    bool verbose;
};

#endif // NFA_H
