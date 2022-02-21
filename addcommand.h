#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsItem>
#include <QGraphicsScene>

class AddCommand : public QUndoCommand
{
public:
    AddCommand(QGraphicsItem * item, QGraphicsScene * scene);
    void undo() override;
    void redo() override;

private:
    QGraphicsItem * mItem;
    QGraphicsScene * mScene;


};

#endif // ADDCOMMAND_H
