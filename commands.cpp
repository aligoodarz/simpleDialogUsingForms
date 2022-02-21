#include "commands.h"

AddCommand::AddCommand(QGraphicsItem * item, QGraphicsScene * scene) : mItem (item) , mScene(scene)
{

}

void AddCommand::undo()
{
    if (mItem){
        mScene->removeItem(mItem);
    }
}

void AddCommand::redo()
{
    if (mItem){
        mScene->addItem(mItem);
    }
}

RemoveCommand::RemoveCommand(QGraphicsItem *item, QGraphicsScene *scene):
    mItem(item), mScene(scene)
{

}

void RemoveCommand::undo()
{
    if (mItem)
        mScene->addItem(mItem);
}

void RemoveCommand::redo()
{
    if (mItem)
        mScene->removeItem(mItem);
}
