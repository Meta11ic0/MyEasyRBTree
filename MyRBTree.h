#ifndef _MYRBTREE_H_
#define _MYRBTREE_H_
#include "MyRBTreeNode.h"

class MyRBTree
{
public:
    MyRBTree():Root(nullptr),NodeNums(0)
    {
        printf("Default constructor, initializing Nil\n");
        Nil = new MyRBTreeNode();
        Nil->LChild=Nil;
        Nil->RChild=Nil;
        Nil->SetColor(Black);
    };
    bool IsNil(MyRBTreeNode* Node);
    MyRBTreeNode* LeftRotation(MyRBTreeNode* Node);
    MyRBTreeNode* RightRotation(MyRBTreeNode* Node);
    MyRBTreeNode* InsertNode(int i);
    void FixAfterInsertion(MyRBTreeNode* Node);
    MyRBTreeNode* FindNode(int i);
    MyRBTreeNode* FindMinimumNode(MyRBTreeNode* Node);
    void TransPlanet(MyRBTreeNode* X, MyRBTreeNode* Y);
    MyRBTreeNode* DeleteNode(int i);
    void FixAfterDeletion(MyRBTreeNode* Node);
    void DeleteTree(MyRBTreeNode* Node);
    ~MyRBTree(){DeleteTree(Root);delete Nil;};
private:
    MyRBTreeNode* Root;
    MyRBTreeNode* Nil;
    int NodeNums;
};

bool MyRBTree::IsNil(MyRBTreeNode* Node)
{
    if(Node->LChild == Node)
        return true;
    return false;
}

MyRBTreeNode* MyRBTree::LeftRotation(MyRBTreeNode* Node)
{
    if(Node == nullptr)
    {
        printf("LeftRotation On nullptr\n");
        return Node;
    }

    printf("LeftRotation On %d\n", Node->GetNodeValue());

    MyRBTreeNode* OldParent = Node->Parent;
    MyRBTreeNode* OldRNode = Node->RChild;
    MyRBTreeNode* NewRNode = OldRNode->LChild;

    Node->Parent = OldRNode;
    OldRNode->LChild = Node;

    NewRNode->Parent = Node;
    Node->RChild = NewRNode;

    OldRNode->Parent = OldParent; 
    if(Node == Root)
    {
        Root = OldRNode;
    }
    else if(OldParent->LChild== Node)
    {
        OldParent->LChild = OldRNode;
    }
    else
    {
        OldParent->RChild = OldRNode;
    }

    return Node;
}

MyRBTreeNode* MyRBTree::RightRotation(MyRBTreeNode* Node)
{
    if(Node == nullptr)
    {
        printf("RightRotation On nullptr\n");
        return Node;
    }

    printf("RightRotation On %d\n", Node->GetNodeValue());

    MyRBTreeNode* OldParent = Node->Parent;
    MyRBTreeNode* OldLNode = Node->LChild;
    MyRBTreeNode* NewLNode = OldLNode->RChild;

    Node->Parent = OldLNode;
    OldLNode->RChild = Node;

    NewLNode->Parent = Node;
    Node->LChild = NewLNode;
    
    OldLNode->Parent = OldParent; 
    if(Node == Root)
    {
        Root = OldLNode;
    }
    else if(OldParent->LChild == Node)
    {
        OldParent->LChild = OldLNode;
    }
    else
    {
        OldParent->RChild = OldLNode;
    }
      
    return Node;
}

MyRBTreeNode* MyRBTree::InsertNode(int i)
{
    MyRBTreeNode* TempParent = Nil;
    MyRBTreeNode* Temp = Root;
    if(Root == nullptr)
    {
        Root = new MyRBTreeNode(i);
        Root->Parent = Nil;
        Root->LChild = Nil;
        Root->RChild = Nil;
        printf("Insert Root : %d\n", i);
        ++NodeNums;
        return Root;
    }
    int TempValue = Temp->GetNodeValue();

    while(!IsNil(Temp))
    {
        TempParent = Temp;
        TempValue = Temp->GetNodeValue();
        if(i > TempValue)
            Temp = TempParent->RChild;
        else if(i < TempValue)
            Temp = TempParent->LChild;
        else
        {
            printf("Value :%d already exists\n",i);
        }
    }

    Temp = new MyRBTreeNode(i);
    Temp->LChild = Nil;
    Temp->RChild = Nil;
    Temp->Parent = TempParent;
    Temp->SetColor(Red);

    if(IsNil(TempParent))
        Root = Temp;
    else if(i < TempValue)
    {
        printf("%d is inserted to %d's Lchild\n", i, TempValue);
        TempParent->LChild = Temp;
    }
    else
    {
        printf("%d is inserted to %d's Rchild\n", i, TempValue);
        TempParent->RChild = Temp;
    }
    ++NodeNums;
    FixAfterInsertion(Temp);

    return Temp;
}

void MyRBTree::FixAfterInsertion(MyRBTreeNode* Node)
{
    printf("Begin to fix tree after Insertion\n");
    while(Node->Parent->GetNodeColor() == Red)
    {
        printf("Node : %d is %s\n", Node->GetNodeValue(), Node->GetNodeColorInChar());
        printf("Parent : %d is %s\n", Node->Parent->GetNodeValue(), Node->Parent->GetNodeColorInChar());
        printf("Grandparent : %d is %s\n", Node->Parent->Parent->GetNodeValue(), Node->Parent->Parent->GetNodeColorInChar());
        if(Node->Parent == Node->Parent->Parent->LChild)
        {
            printf("Parent : %d is lchild\n", Node->Parent->GetNodeValue());
            MyRBTreeNode* Uncle = Node->Parent->Parent->RChild;
            printf("Uncle : %d is %s\n", Uncle->GetNodeValue(), Uncle->GetNodeColorInChar());
            if(Uncle->GetNodeColor() == Red)
            {
                printf("Make the little tree based on Grandparent balanced first by changing color\n");
                printf("Set Parent : %d and Uncle : %d to Black, Set Grandparent %d to Red\n", Node->Parent->GetNodeValue(), Node->Parent->Parent->GetNodeValue());
                printf("Then make Node become Grandparent and start another around\n");
                Node->Parent->SetColor(Black);
                Uncle->SetColor(Black);
                Node->Parent->Parent->SetColor(Red);
                Node = Node->Parent->Parent;
            }
            else
            {
                printf("Make the little tree on Grandparent balanced first by changing color and rotation\n");
                if(Node == Node->Parent->RChild)
                {
                    printf("Node is not a straight line with his Parent and Grandparent, so do the rotation\n");
                    LeftRotation(Node->Parent);
                    Node = Node->LChild;
                    printf("Make Node always points to the end of the straight line\n");
                    printf("Node : %d is %s\n", Node->GetNodeValue(), Node->GetNodeColorInChar());
                    printf("Parent : %d is %s\n", Node->Parent->GetNodeValue(), Node->Parent->GetNodeColorInChar());
                    printf("Grandparent : %d is %s\n", Node->Parent->Parent->GetNodeValue(), Node->Parent->Parent->GetNodeColorInChar());
                }
                printf("Make Parent to Black and Grandparent to Red\n");
                Node->Parent->SetColor(Black);
                Node->Parent->Parent->SetColor(Red);
                RightRotation(Node->Parent->Parent);
            }
        }
        else
        {
            printf("Parent is rchild\n");
            MyRBTreeNode* Uncle = Node->Parent->Parent->LChild;
            printf("Uncle : %d is %s\n", Uncle->GetNodeValue(), Uncle->GetNodeColorInChar());
            if(Uncle->GetNodeColor() == Red)
            {
                printf("Make the little tree based on Grandparent balanced first by changing color\n");
                printf("Set Parent : %d and Uncle : %d to Black, Set Grandparent %d to Red\n", Node->Parent->GetNodeValue(), Node->Parent->Parent->GetNodeValue());
                printf("Then make Node become Grandparent and start another around\n");
                Node->Parent->SetColor(Black);
                Uncle->SetColor(Black);
                Node->Parent->Parent->SetColor(Red);
                Node = Node->Parent->Parent;
            }
            else
            {
                printf("Make the little tree balance first by changing color and rotation\n");
                if(Node == Node->Parent->LChild)
                {
                    printf("Node is not a straight line with his Parent and Grandparent, so do the rotation\n");
                    RightRotation(Node->Parent);
                    Node = Node->RChild;
                    printf("Make Node always points to the end of the straight line\n");
                    printf("Node : %d is %s\n", Node->GetNodeValue(), Node->GetNodeColorInChar());
                    printf("Parent : %d is %s\n", Node->Parent->GetNodeValue(), Node->Parent->GetNodeColorInChar());
                    printf("Grandparent : %d is %s\n", Node->Parent->Parent->GetNodeValue(), Node->Parent->Parent->GetNodeColorInChar());                
                }
                printf("Make Parent to Black and Grandparent to Red\n");
                Node->Parent->SetColor(Black);
                Node->Parent->Parent->SetColor(Red);
                LeftRotation(Node->Parent->Parent);
            }
        }
    }
    printf("Parent : %d is %s, do not need to change anymore.\n", Node->Parent->GetNodeValue(), Node->Parent->GetNodeColorInChar());
    printf("Incase Root was turned to Red, set Root to Black\n");
    Root->SetColor(Black);
}

MyRBTreeNode* MyRBTree::FindNode(int i)
{
    if(Root == nullptr)
    {
        printf("This Tree is empty!\n");
        return nullptr;
    }
    MyRBTreeNode* Temp = Root;
    int TempValue = Temp->GetNodeValue();
    while(!IsNil(Temp))
    {
        TempValue = Temp->GetNodeValue();
        if(i > TempValue)
            Temp = Temp->RChild;
        else if(i < TempValue)
            Temp = Temp->LChild;
        else
            break;
    }

    if(IsNil(Temp))
    {
        printf("This Node (%d) is not inside the Tree!\n",i);
        return nullptr;
    }
    return Temp;
}

MyRBTreeNode* MyRBTree::FindMinimumNode(MyRBTreeNode* Node)
{
    while(!IsNil(Node->LChild))
        Node = Node->LChild;
    return Node;
}

void MyRBTree::TransPlanet(MyRBTreeNode* X, MyRBTreeNode* Y)
{
    printf("TransPlanet Node Y : %d (%s) to Node X : %d (%s)'s position, but do nothing changes to their own childs\n", Y->GetNodeValue(), Y->GetNodeColorInChar(), X->GetNodeValue(), X->GetNodeColorInChar());
    if(X == Root)
        Root = Y;
    else if( X == X->Parent->LChild)
        X->Parent->LChild = Y;
    else
        X->Parent->RChild = Y;
    Y->Parent = X->Parent;
}

MyRBTreeNode* MyRBTree::DeleteNode(int i)
{
    
    MyRBTreeNode* Z = FindNode(i);
    if(!Z)
    {
        printf("Node : %d is not in this tree\n", i);
        return nullptr;
    }
    printf("The Node which we going to delete we call it Node Z: %d (%s)\n", Z->GetNodeValue(), Z->GetNodeColorInChar());
    MyRBTreeNode* Y = Z;
    MyRBTreeNode* X = Z;
    MyRBTreeNodeColor YOriginColor = Y->GetNodeColor();
    /*
    Z is the node we want to delete at first, but we chose to make a node Y 
    move into Z's position to replace Z with Z's color. Then we know that Y
    is real node that we r going to delete, and we use X to replace Y just like 
    Y replace Z.
    */
    if(IsNil(Z->LChild))
    {
        printf("Node's Lchild is Nil, then we call Z's Rchild Node X\n");
        X = Z->RChild;
        TransPlanet(Z, Z->RChild);
    }
    else if(IsNil(Z->RChild))
    {
        printf("Node's Rchild is Nil, then we call Z's Lchild Node X\n");
        X = Z->LChild;
        TransPlanet(Z, Z->LChild);       
    }
    else
    {
        Y = FindMinimumNode(Z->RChild);
        YOriginColor = Y->GetNodeColor();
        printf("Find the successor of Node Z, call it Node Y\n");
        printf("Node Y: %d is %s\n", Y->GetNodeValue(), Y->GetNodeColorInChar());

        X = Y->RChild;
        printf("Call Y's Rchild Node X, no matter it is Nil or not\n");
        TransPlanet(Y, Y->RChild);
        printf("Make X go to Y's postion \n");

        Y->RChild = Z->RChild;
        Y->RChild->Parent = Y;
        TransPlanet(Z, Y);
        Y->LChild = Z->LChild;
        Y->LChild->Parent = Y;
        Y->SetColor(Z->GetNodeColor());
        printf("Make Y go to Z's postion with Z's color\n");
    }
    //delete Root
    if(Root == Z)
    {
        printf("Z is Root\n");
        if(Z == Y)
        {
            printf("Make Root point to X\n");
            Root = X;
        }
        else
        {
            printf("Make Root point to Y\n");
            Root = Y;
        }
    }
    delete Z;
    printf("Delete the Node Z\n");
    --NodeNums;
    if(YOriginColor == Black)
    {
        printf("The color of node we already removed from its original poision is black,\nwe need to fix this tree from the subtree based on X\n");
        FixAfterDeletion(X);
    }
    return Y;
}

void MyRBTree::FixAfterDeletion(MyRBTreeNode* Node)
{
    printf("Begin to fix tree after Deletion\n");
    while(Node != Root && Node->GetNodeColor() == Black)
    {
        if(Node == Node->Parent->LChild)
        {
            MyRBTreeNode *Brother = Node->Parent->RChild;
            printf("Node : %d is Lchild, it has double-black\n", Node->GetNodeValue(), Node->GetNodeColorInChar());
            printf("Brother : %d (%s) \n", Brother->GetNodeValue(), Brother->GetNodeColorInChar());
            if(Brother->GetNodeColor() == Red)
            {
                printf("Parent is balck,so we will swtich the color between Parent and Brother, then do rotation to insure the color of brothernode is black\n");
                Brother->SetColor(Black);
                Node->Parent->SetColor(Red);
                LeftRotation(Node->Parent);
                Brother = Node->Parent->RChild;
                printf("new Brother : %d (%s) \n", Brother->GetNodeValue(), Brother->GetNodeColorInChar());
            }

            if(Brother->LChild->GetNodeColor() == Black && Brother->RChild->GetNodeColor() == Black)
            {
                printf("The color of Brother's two childs is black, so we push one black color up,\nmake Node and Brother both lose one black, then Parent becomes the new Node and start a new round\n");
                Brother->SetColor(Red);
                Node = Node->Parent;
            }
            else 
            {
                
                if(Brother->RChild->GetNodeColor() == Black)
                {
                    printf("Color of Brother's Lchild is red\n");
                    printf("Color of Brother's Rchild is black\n");
                    printf("Switch color between Brother and Brother's Lchild, then do rotation on Brother to insure the color of brothernode is black and the color of brothernode's rchild is red\n");
                    Brother->SetColor(Red);
                    Brother->LChild->SetColor(Black);
                    RightRotation(Brother);
                    Brother = Node->Parent->RChild;
                    printf("new Brother : %d (%s) \n", Brother->GetNodeValue(), Brother->GetNodeColorInChar());
                }
                printf("Now the color of Brother is balck, the color of Brother's Rchild is red,\nso we make Brother put on Parent's color,\n make Brother's Rchild and Parent go to black, then we do Leftrotation on Parent\nBalance regain!!\n ");
                Brother->SetColor(Node->Parent->GetNodeColor());
                Node->Parent->SetColor(Black);
                Brother->RChild->SetColor(Black);
                LeftRotation(Node->Parent);
                Node = Root;
            }
        }
        else
        {
            MyRBTreeNode *Brother = Node->Parent->LChild;
            printf("Node : %d is Rchild, it has double-black\n", Node->GetNodeValue(), Node->GetNodeColorInChar());
            printf("Brother : %d (%s) \n", Brother->GetNodeValue(), Brother->GetNodeColorInChar());
            if(Brother->GetNodeColor() == Red)
            {
                printf("Parent is balck,so we will swtich the color between Parent and Brother, then do rotation to insure the color of brothernode is black\n");
                Brother->SetColor(Black);
                Node->Parent->SetColor(Red);
                RightRotation(Node->Parent);
                Brother = Node->Parent->LChild;
                printf("new Brother : %d (%s) \n", Brother->GetNodeValue(), Brother->GetNodeColorInChar());
            }

            if(Brother->LChild->GetNodeColor() == Black && Brother->RChild->GetNodeColor() == Black)
            {
                printf("The color of Brother's two childs is black, so we push one black color up,\nmake Node and Brother both lose one black, then Parent becomes the new Node and start a new round\n");
                Brother->SetColor(Red);
                Node = Node->Parent;
            }
            else 
            {
                if(Brother->LChild->GetNodeColor() == Black)
                {
                    printf("Color of Brother's Rchild is red\n");
                    printf("Color of Brother's Lchild is black\n");
                    printf("Switch color between Brother and Brother's Rchild, then do rotation on Brother to insure the color of brothernode is black and the color of brothernode's lchild is red\n");
                    Brother->SetColor(Red);
                    Brother->RChild->SetColor(Black);
                    LeftRotation(Brother); 
                    Brother = Node->Parent->LChild;
                    printf("new Brother : %d (%s) \n", Brother->GetNodeValue(), Brother->GetNodeColorInChar());
                }
                printf("Now the color of Brother is balck, the color of Brother's Rchild is red,\nso we make Brother put on Parent's color,\n make Brother's Lchild and Parent go to black, then we do rotation on Parent\nBalance regain!!\n ");
                Brother->SetColor(Node->Parent->GetNodeColor());
                Node->Parent->SetColor(Black);
                Brother->LChild->SetColor(Black);
                RightRotation(Node->Parent);
                Node = Root;
            }            
        }
    }
    printf("Incase Root was turned to Red, set Root to Black\n");
    Node->SetColor(Black);
}

void MyRBTree::DeleteTree(MyRBTreeNode* Node)
{
    if(IsNil(Node))
        return;
    DeleteTree(Node->LChild);
    DeleteTree(Node->RChild);
    delete Node;
}

#endif