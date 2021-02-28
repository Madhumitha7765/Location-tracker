#include<iostream>
#include<string.h>
#include<math.h>
#include<stdlib.h>
using namespace std;


typedef struct LNode
{
    struct LNode *next;
    int xC;
    int yC;
    char pName[20];
}LNode;


 LNode  *head=NULL;


typedef struct Node
{
    struct Node *left;
    int xcoord;
    int ycoord;
    char c;
    char pType[20];
    char place[20];
    struct Node *right;
}Node;


LNode* createLNode(int x,int y,char p[])
{
    LNode   *temp = new LNode;
    temp->xC=x;
    temp->yC=y;
    strcpy(temp->pName,p);
    temp->next=NULL;
    return temp;
}

Node* createNode(int c1,int c2,char pl[],char tp[])
{
    Node *temp=new Node;
    temp->left=NULL;
    temp->right=NULL;
    temp->xcoord=c1;
    temp->ycoord=c2;
    temp->c='x';
    int i=0;
    while(pl[i]!='\0')
    {
        temp->place[i]=pl[i];
        i++;
    }
    temp->place[i]='\0';
    strcpy(temp->pType,tp);
    return temp;
}


Node* insertNode(Node *root,int c1,int c2,char pl[],char tp[])
{
    static int h=0;
    h++;
    if(root==NULL)
    {
        return createNode(c1,c2,pl,tp);
    }
    else if(root!=NULL)
    {

        if(root->c=='x')
        {
            if(root->xcoord>c1)
            {

                root->left=insertNode(root->left,c1,c2,pl,tp);
            }
            else if(root->xcoord<=c1)
            {

                root->right=insertNode(root->right,c1,c2,pl,tp);
            }
        }

        else if(root->c=='y')
        {
            if(root->ycoord>c2)
            {

                root->left=insertNode(root->left,c1,c2,pl,tp);
            }
            else if(root->ycoord<=c2)
            {

                root->right=insertNode(root->right,c1,c2,pl,tp);
            }
        }
    }

    return root;
}


Node* search(int c1,int c2,struct Node **q,int action)
{
    int g;
    struct Node *qp=NULL;
    int flag=0;
    while((*q)!=NULL)
    {
        if((*q)->c=='x')
        {
                    if((*q)->xcoord>c1)
                    {
                        qp=(*q);
                        (*q)=(*q)->left;
                    }
                    else if((*q)->xcoord<c1)
                    {
                        qp=(*q);
                        (*q)=(*q)->right;
                    }
                    if((*q)==NULL)
                    {
                        break;
                    }
                    else if((*q)->xcoord==c1 && (*q)->ycoord==c2)
                    {
                        flag=1;
                        break;
                    }

                }
                else if((*q)->c=='y')
                {
                    if((*q)->ycoord>c2)
                    {
                        qp=(*q);
                        (*q)=(*q)->left;
                    }
                    else if((*q)->ycoord<c2)
                    {
                        qp=(*q);
                        (*q)=(*q)->right;
                    }
                    if((*q)==NULL)
                    {
                        break;
                    }
                    else if((*q)->xcoord==c1 && (*q)->ycoord==c2)
                    {
                        flag=1;
                        break;
                    }

                }
            }
            if(action==0)
                return qp;
            else if(action==1)
            {
                if(flag==1)
                    cout<<"\n \tCAB FOUND";
                else if(flag==0)
                    cout<<"\n \tCAB NOT FOUND"<<endl;
                return NULL;
            }
            else if(action==3)
            {

                cout<<"\n\t"<<(*q)->place<<endl;
            }
}

void traverse(struct Node *p)
{
    if(p!=NULL)
    {
        traverse(p->left);
        cout<<"\n\tX COORDINATE : "<<p->xcoord<<"\n\tY COORDINATE :  "<<p->ycoord<<"\n\tTYPE OF PLACE : "<<p->pType<<"\n\tNAME OF PLACE : "<<p->place<<" \n";
        traverse(p->right);
    }
    else cout<<endl;
}


float findDistance(struct LNode *p)
{
    int x1=head->xC;
    int y1=head->yC;
    int x2=p->xC;
    int y2=p->yC;
    int a=(x2-x1)*(x2-x1);
    int b=(y2-y1)*(y2-y1);
    float d=pow((a+b),0.5);
    return d;
}

void traverseLL(struct Node *r, float range)
{
    float d;
    struct Node *rd=r;
    struct LNode *l=head;
        char pl[20];
        while(l!=NULL)
        {
            d=findDistance(l);
            if(d<=range)
            {
                search(l->xC,l->yC,&r,3);
                r=rd;
            }

            l=l->next;
        }
        cout<<"\n\n\n";
}

LNode* addNode(int x, int y, char tp[])
{
    struct LNode *p=new LNode;
    if(head==NULL)
    {
        p=createLNode(x,y,tp);
        head=p;
    }
    else
    {
        struct LNode *p=head;
        while(p->next!=NULL)
        {
            p=p->next;
        }
        p->next=createLNode(x,y,tp);
    }
}

void rangeSearch(struct Node *p,float range,char rangePlace[])
{
     if(p!=NULL)
    {
        rangeSearch(p->left,range,rangePlace);
        if(strcmp(p->pType,rangePlace)==0)
            addNode(p->xcoord,p->ycoord,rangePlace);
        rangeSearch(p->right,range,rangePlace);
    }

}

int findNodes(Node*p,int level,char t[])
{
    static int flag =0;
    int left=0,right=0;
    if(p==NULL)
    {
        return 0;
    }
    if(level==1)
    {
        if(strcmp(p->pType,t)==0)
        {
                struct LNode   *q=new LNode;
                q=createLNode(p->xcoord,p->ycoord,p->place);
                if(head==NULL)
                {
                    head=q;
                    return 1;

                }
                else
                {
                    struct LNode *prev=head;
                    while(prev->next!=NULL)
                        prev=prev->next;
                    prev->next=q;
                    return 1;
                }
        }
        else
            return 1;
    }
    left=findNodes(p->left,level-1,t);
    right=findNodes(p->right,level-1,t);
    return left||right;

}


void nearestPlace(Node *p,char t[])
{

    int level=1;
    while(findNodes(p,level,t))
    {
        level++;
    }
    struct LNode *trav = head;
    while(trav!=NULL)
    {
        trav=trav->next;
    }
    struct LNode*trav2 = head->next ;
    struct LNode*min = head;
    int rootX=p->xcoord;
    int rootY=p->ycoord;
    int minDist = sqrt(pow((head->xC-rootX),2) + pow((head->yC-rootY),2));
    int tempDist;
    while(trav2!=NULL)
    {
       tempDist = sqrt(pow((trav2->xC-rootX),2) + pow((trav2->yC-rootY),2));
       if(tempDist < minDist)
       {
           minDist = tempDist;
           min=trav2;
       }
       trav2=trav2->next;
    }

    cout<<"\n \tThe nearest "<< t << " is"<<" "<< min->pName<<"\n";


}


int main()
{
    int pass,m;
    long long contact;
    static int h=0;
    struct Node *root=NULL;
    struct Node *p;
    char cpl[20],ctp[20];
    char pl[20];
    char tp[20];
    int c1,c2,choose1=0,choose=0;
    struct Node *q=root,*qp=NULL;
    char p1[20],p2;
    struct Node *n,*froot2;
    float range;
    char rangePlace[20];
    cout<<"//////////////////// CAB TRACKER AND BOOKING USING KD TREES IMPLEMENTATION  \\\\\\\\\\\\\\\\\\\\ ";
    cout<<"\n";
    cout<<"\n";
    do{
        cout<<"\n\n\n\t * Enter your designation * \n";
        cout<<"\n\t1.CUSTOMER \n\t2.ADMIN\n\t3.EXIT\n";
        cout<<"\n\tChoice : ";
        cin>>m;
        switch(m)
        {
                case 1 :
                                        cout<<"\n\t\t\t\t  <<<  WELCOME TO CAB TRACKER AND BOOKING  >>>\n";
                                        do
                                            {
                                            cout<<"\n\t * Enter the action you wish to perform * \n\n\t1.Explore nearest place around you\n";
                                            cout<<"\t2.Finding places where CAB is available in a given range\n\t3.Book a CAB\n\t4.View all CAB details\n\t5.Exit to Mainmenu\n";
                                            cout<<"\n\tChoice : ";
                                            cin>>choose1;
                                            switch(choose1)
                                            {

                                                case 1:

                                                        cout<<"\n \tEnter the type of place you want to explore:";
                                                        cin>>p1;
                                                        nearestPlace(root,p1);
                                                        head=NULL;
                                                        break;

                                                case 2:
                                                        froot2=root;
                                                        n=root;
                                                        cout<<"\n \tEnter the type place to search : ";
                                                        cin>>rangePlace;
                                                        cout<<"\n \tEnter the range to search (in metres) : ";
                                                        cin>>range;
                                                        cout<<"\n \tCabs are available in the following places :  \n";
                                                        rangeSearch(n,range,rangePlace);
                                                        traverseLL(froot2,range);
                                                        head=NULL;
                                                        break;


                                                case 3:
                                                        cout<<"\n \tEnter your current location : ";
                                                        cin>>cpl;
                                                        cout<<"\n \tEnter your target location : ";
                                                        cin>>ctp;
                                                        cout<<"\n \tEnter your contact number : ";
                                                        cin>>contact;
                                                        cout<<"\n\n\t\t\t CAB BOOKED SUCCESSFULLY.ARRIVING SOON!\n\n";
                                                        break;

                                                case 4 :
                                                         traverse(root);
                                                         break;
                                                case 5:
                                                            cout<<"\n\n";
                                                            choose1=0;
                                                            break;

                                                default:
                                                        cout<<" \t\t\tPlease enter a correct option";

                                            }
                                        }while(choose1!=0);

                    break;


        case 2 :
                                cout<<"\n\tEnter the Admin passcode : ";
                                cin>>pass;
                                if(pass==1234)
                                {
                                        do
                                        {
                                            cout<<"\n\n\n\t * Enter the action you wish to perform * \n\n\t1.Insert a CAB\n\t2.Search for a CAB\n\t3.View all CAB DETAILS\n\t4.Exit to Mainmenu\n";
                                            cout<<"\n \tChoice : ";
                                            cin>>choose;
                                            switch(choose)
                                            {
                                                case 1:
                                                        h++;
                                                        cout<<"\n \tEnter x coordinate : ";
                                                        cin>>c1;
                                                        cout<<"\n \tEnter y coordinate : ";
                                                        cin>>c2;
                                                        cout<<"\n \tEnter the type of place cab should be deployed : ( Mall,Restaurant,Hospital etc)"<<" ";
                                                        cin>>tp;
                                                        cout<<"\n \tEnter the name of the place : ";
                                                        cin>>pl;
                                                        root=insertNode(root,c1,c2,pl,tp);

                                                        if(h>1)
                                                        {
                                                            qp=search(c1,c2,&q,0);
                                                            if(qp!=NULL)
                                                            {
                                                                if(qp->c=='x')
                                                                    q->c='y';
                                                                else if(qp->c=='y')
                                                                    q->c='x';
                                                            }
                                                        }
                                                        break;

                                                case 2:
                                                        if(root==NULL)
                                                        {
                                                           cout<<"\n \t\t\tNO CAB HAS BEEN INSERTED. PLEASE CONTINUE AFTER DEPLOYING A CAB\n";
                                                        }
                                                        else
                                                        {
                                                            struct Node *f,*froot=root,*froot3=root;
                                                            int cx,cy;
                                                            cout<<"\n \tEnter the coordinates to search: \n";
                                                            cout<<"\n \tX coordinate : ";
                                                            cin>>cx;
                                                            cout<<"\n \tY coordinate : ";
                                                            cin>>cy;
                                                            f=search(cx,cy,&froot,1);
                                                            cout<<endl;
                                                        }
                                                        break;

                                                case 3:
                                                        traverse(root);
                                                        break;

                                                case 4:
                                                        cout<<"\n\n";
                                                        choose=0;
                                                        break;

                                                default:
                                                        cout<<"\t\tPlease enter a correct option";

                                            }
                                        }while(choose!=0);
                                }
                                else
                                {
                                    cout<<"\n \t\t\t Wrong password ## ACCESS DENIED ##\n";
                                }

                                break;

            case 3 :
                               cout<<"\n\n\t\t\tTHANK YOU FOR VIEWING OUR PACKAGE!\n\n";
                               exit(0);

            default :

                                 cout<<"\n\t\tPlease enter a correct option";

        }
    }while(m!=0);
}
