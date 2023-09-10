#ifndef _MYRBTREENODE_H_
#define _MYRBTREENODE_H_

enum class MyRBTreeNodeColor
{
    Red, 
    Black
};
#define Red MyRBTreeNodeColor::Red
#define Black MyRBTreeNodeColor::Black

class MyRBTreeNode
{
public:
    MyRBTreeNode() : Value(0), Parent(nullptr), LChild(nullptr), RChild(nullptr), Color(Black){};
    MyRBTreeNode(int a, MyRBTreeNodeColor c = Black) : Value(a), Parent(nullptr), LChild(nullptr), RChild(nullptr), Color(c){}; 
    bool operator ==(MyRBTreeNode *Rnode);
    bool operator !=(MyRBTreeNode *Rnode);
    int GetNodeValue();
    MyRBTreeNodeColor GetNodeColor();
    const char* GetNodeColorInChar();
    void SetColor(MyRBTreeNodeColor c);
public:
    MyRBTreeNode* LChild;
    MyRBTreeNode* RChild;
    MyRBTreeNode* Parent;
private:
    int Value;
    MyRBTreeNodeColor Color;

};

bool MyRBTreeNode::operator == (MyRBTreeNode *Rnode)
{
    if(this->GetNodeValue() == Rnode->GetNodeValue())
        return true;
    else
        return false;
}

bool MyRBTreeNode::operator != (MyRBTreeNode *Rnode)
{
    if(this == Rnode)
        return false;
    else
        return true;
}

int MyRBTreeNode::GetNodeValue()
{
    return this->Value;
}

MyRBTreeNodeColor MyRBTreeNode::GetNodeColor()
{
    return this->Color;
}

const char* MyRBTreeNode::GetNodeColorInChar()
{
    const char* str;
    if(this->Color == Black)
        str = "Black";
    else
        str = "Red";
    return str;
}

void MyRBTreeNode::SetColor(MyRBTreeNodeColor c)
{
    this->Color = c;
}

#endif