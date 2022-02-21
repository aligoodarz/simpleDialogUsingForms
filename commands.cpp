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
