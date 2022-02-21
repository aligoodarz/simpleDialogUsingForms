#ifndef COMMANDS_H
#define COMMANDS_H

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

#endif // COMMANDS_H
