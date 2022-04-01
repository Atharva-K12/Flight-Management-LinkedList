/*  Name- Atharva Kathale 
    Enrollment no. - BT19CSE051
    Batch 2
*/

#define NAME_SIZE 30
#define MAX_SIZE 4
#define MIN_SIZE 2
#define MAX_TREE_SIZE 20
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
typedef enum {VVIP,VIP,public} class;
typedef enum {Delay,OnTime,Cancelled,Promoted} status;
typedef enum {false,true} bool;
typedef struct flight
{
    char name[NAME_SIZE];
    class flight_class;
    status flight_status;
    int capacity,id,arrival_time,departure_time,stay_time,delay;
    long int key;
} flight;
typedef struct TreeNode
{
    flight data[MAX_SIZE+1];
    struct TreeNode *ptr[MAX_SIZE+1];
    int size;
} TreeNode;
TreeNode *root = NULL;
void dataInit(flight *ptr)
{
    ptr->stay_time=ptr->departure_time-ptr->arrival_time;
    ptr->delay=0;
    ptr->key=ptr->id*10000+ptr->arrival_time;
}
flight newRecord(char name[],int id,int capacity,int arrival_time,int departure_time,class flight_class,status flight_status)
{
    flight flight_record;
    flight_record.arrival_time=arrival_time;
    flight_record.capacity=capacity;
    flight_record.id=id;
    flight_record.departure_time=departure_time;
    flight_record.flight_class=flight_class;
    flight_record.flight_status=flight_status;
    strcpy(flight_record.name,name);
    dataInit(&flight_record);
    return flight_record;
}
TreeNode* newNode(flight flight_record,TreeNode *child)
{
    TreeNode* node=(TreeNode*)malloc(sizeof(TreeNode));
    node->data[1]=flight_record;
    node->size=1;
    node->ptr[0] =root;
    node->ptr[1]=child;
    return node;
}
void insertNode(flight flight_record,int pos,TreeNode* node,TreeNode* child)
{
    int i;
    for(i=node->size;i>pos;i--)
    {
        node->data[i+1]=node->data[i];
        node->ptr[i+1]=node->ptr[i];
    }
    node->data[i+1]=flight_record;
    node->ptr[i+1]=child;
    node->size++;
}
void splitNode(flight flight_record,flight *p_record,int pos,TreeNode *node,TreeNode *child,TreeNode **new_node)
{
    int median,i;
    if(pos>MIN_SIZE)
        median=MIN_SIZE+1;
    else
        median=MIN_SIZE;
    *new_node=(TreeNode*)malloc(sizeof(TreeNode));
    i=median+1;
    while(i<=MAX_SIZE)
    {
        (*new_node)->data[i-median]=node->data[i];
        (*new_node)->ptr[i-median]=node->ptr[i];
        i++;
    }
    node->size=median;
    (*new_node)->size=MAX_SIZE-median;
    if(pos<=-MIN_SIZE)
        insertNode(flight_record,pos,node,child);
    else
        insertNode(flight_record,pos-median,*new_node,child);
    *p_record=node->data[node->size];
    (*new_node)->ptr[0]=node->ptr[node->size];
    node->size--;
}
bool setValuebyKey(flight flight_record,flight *p_record,TreeNode*node,TreeNode**child)
{
    int pos;
    if(!node)
    {
        *p_record=flight_record;
        *child=NULL;
        return true;
    }
    if(flight_record.key<node->data[1].key)
        pos=0;
    else
    {
        for(pos=node->size;flight_record.key<node->data[pos].key&&pos>1;pos--);
        if(flight_record.key==node->data[pos].key)
        {
            node->data[pos]=flight_record;
            return false;
        }
    }
    if(setValuebyKey(flight_record,p_record,node->ptr[pos],child))
    {
        if(node->size<MAX_SIZE)
            insertNode(*p_record,pos,node,*child);
        else
        {
            splitNode(*p_record,&flight_record,pos,node,*child,child);
            return true;
        }
    }
    return false;
}
bool setValuebyArrival(flight flight_record,flight *p_record,TreeNode*node,TreeNode**child)
{
    int pos;
    if(!node)
    {
        *p_record=flight_record;
        *child=NULL;
        return true;
    }
    if(flight_record.arrival_time<=node->data[1].arrival_time)
        pos=0;
    else
    {
        for(pos=node->size;flight_record.arrival_time<=node->data[pos].arrival_time&&pos>1;pos--);
    }
    if(setValuebyArrival(flight_record,p_record,node->ptr[pos],child))
    {
        if(node->size<MAX_SIZE)
            insertNode(*p_record,pos,node,*child);
        else
        {
            splitNode(*p_record,&flight_record,pos,node,*child,child);
            return true;
        }
    }
    return false;
}
bool setValuebyDeparture(flight flight_record,flight *p_record,TreeNode*node,TreeNode**child)
{
    int pos;
    if(!node)
    {
        *p_record=flight_record;
        *child=NULL;
        return true;
    }
    if(flight_record.departure_time<=node->data[1].departure_time)
        pos=0;
    else
    {
        for(pos=node->size;flight_record.departure_time<=node->data[pos].departure_time&&pos>1;pos--);
    }
    if(setValuebyDeparture(flight_record,p_record,node->ptr[pos],child))
    {
        if(node->size<MAX_SIZE)
            insertNode(*p_record,pos,node,*child);
        else
        {
            splitNode(*p_record,&flight_record,pos,node,*child,child);
            return true;
        }
    }
    return false;
}
bool setValuebyStay(flight flight_record,flight *p_record,TreeNode*node,TreeNode**child)
{
    int pos;
    if(!node)
    {
        *p_record=flight_record;
        *child=NULL;
        return true;
    }
    if(flight_record.stay_time<=node->data[1].stay_time)
        pos=0;
    else
    {
        for(pos=node->size;flight_record.stay_time<=node->data[pos].stay_time&&pos>1;pos--);
    }
    if(setValuebyStay(flight_record,p_record,node->ptr[pos],child))
    {
        if(node->size<MAX_SIZE)
            insertNode(*p_record,pos,node,*child);
        else
        {
            splitNode(*p_record,&flight_record,pos,node,*child,child);
            return true;
        }
    }
    return false;
}
bool setValuebyStayrev(flight flight_record,flight *p_record,TreeNode*node,TreeNode**child)
{
    int pos;
    if(!node)
    {
        *p_record=flight_record;
        *child=NULL;
        return true;
    }
    if(flight_record.stay_time>=node->data[1].stay_time)
        pos=0;
    else
    {
        for(pos=node->size;flight_record.stay_time>=node->data[pos].stay_time&&pos>1;pos--);
    }
    if(setValuebyStayrev(flight_record,p_record,node->ptr[pos],child))
    {
        if(node->size<MAX_SIZE)
            insertNode(*p_record,pos,node,*child);
        else
        {
            splitNode(*p_record,&flight_record,pos,node,*child,child);
            return true;
        }
    }
    return false;
}
bool insert(TreeNode *node,char name[],int id,int capacity,int arrival_time,int departure_time,class flight_class,status flight_status)
{
    flight i,flight_record=newRecord(name,id,capacity,arrival_time,departure_time,flight_class,flight_status);
    bool flag;
    TreeNode *child;
    flag=setValuebyKey(flight_record,&i,node,&child);
    if(flag)
    {
        node=newNode(i,child);
    }
    return flag;
}
void insertbyArrival(TreeNode *node,flight flight_record)
{
    flight i;
    bool flag;
    TreeNode *child;
    flag=setValuebyArrival(flight_record,&i,node,&child);
    if(flag)
    {
        node=newNode(i,child);
    }
}
void insertbyDeparture(TreeNode *node,flight flight_record)
{
    flight i;
    bool flag;
    TreeNode *child;
    flag=setValuebyDeparture(flight_record,&i,node,&child);
    if(flag)
    {
        node=newNode(i,child);
    }
}
void insertbyStay(TreeNode *node,flight flight_record)
{
    flight i;
    bool flag;
    TreeNode *child;
    flag=setValuebyStay(flight_record,&i,node,&child);
    if(flag)
    {
        node=newNode(i,child);
    }
}
void print(TreeNode *node)
{
    int i;
    char *class_arr[]={"VVIP","VIP","Public"};
    char *status_arr[]={"Delay","OnTime","Cancelled","Promoted"};
    if(node)
    {
        for(i=0;i<node->size;i++)
        {
            print(node->ptr[i]);
            printf("Name: %s\nID: %d\nClass: %s\nCapacity: %d\nArrival Time: %d\nDeparture Time:%d\n",node->data[i+1].name,node->data[i+1].id,class_arr[node->data[i+1].flight_class],node->data[i+1].capacity,node->data[i+1].arrival_time,node->data[i+1].departure_time);
	        printf("Stay Time: %d\nStatus: %s\nDelay: %d\n",node->data[i+1].stay_time,status_arr[node->data[i+1].flight_status],node->data[i+1].delay);
        }
        print(node->ptr[i]);
    }
}
void printflight(flight f)
{
    char *class_arr[]={"VVIP","VIP","Public"};
    char *status_arr[]={"Delay","OnTime","Cancelled","Promoted"};
    printf("Name: %s\nID: %d\nClass: %s\nCapacity: %d\nArrival Time: %d\nDeparture Time:%d\n",f.name,f.id,class_arr[f.flight_class],f.capacity,f.arrival_time,f.departure_time);
    printf("Stay Time: %d\nStatus: %s\nDelay: %d\n",f.stay_time,status_arr[f.flight_status],f.delay);
}
flight* search(flight flight_record,int *pos,TreeNode *node)
{
    if(node!=NULL)
    {
        if(flight_record.key<node->data[1].key)
            *pos=0;
        else
        {
            for(*pos=node->size;(flight_record.key < node->data[*pos].key && *pos>1);(*pos)--);
            if(flight_record.key==node->data[*pos].key)
            {
                printf("Flight found\n");
                return &node->data[*pos];
            }
        }
        search(flight_record,pos,node->ptr[*pos]);
    }
    return NULL;
}
void copy(TreeNode *node,int pos)
{
    TreeNode *temp;
    temp=node->ptr[0];
    while(temp->ptr[0]!=NULL)
        temp=temp->ptr[0];
    node->data[pos]=temp->data[1];
}
void remVal(TreeNode *node,int pos)
{
    int i;
    for(i=pos+1;i<=node->size;i++)
    {
        node->data[i-1]=node->data[i];
        node->ptr[i-1]=node->ptr[i];
    }
    node->size--;
}
void rightShift(TreeNode* node,int pos)
{
    TreeNode*x=node->ptr[pos];
    int i=x->size;
    while(i>0)
    {
        x->data[i+1]=x->data[i];
        x->ptr[i+1]=x->ptr[i];
        i++;
    }
    x->data[1]=node->data[pos];
    x->ptr[1]=node=x->ptr[0];
    x->size++;
    x = node->ptr[pos-1];
    node->data[pos]=x->data[x->size];
    node->ptr[pos]=x->ptr[x->size];
    x->size--;   
}
void leftShift(TreeNode* node,int pos)
{
    int i=1;
    TreeNode *x=node->ptr[pos-1];
    x->size++;
    x->data[x->size]=node->data[pos];
    x->ptr[x->size]=node->ptr[pos]->ptr[0];
    x=node->ptr[pos];
    node->data[pos]=x->data[1];
    x->ptr[0]=x->ptr[1];
    x->size--;
    while(i<=x->size)
    {
        x->data[i]=x->data[i+1];
        x->ptr[i]=x->ptr[i+1];
        i++;
    }
}
void mergeNodes(TreeNode*node ,int pos)
{
    int i=1;
    TreeNode *node1=node->ptr[pos],*node2=node->ptr[pos-1];
    node2->size++;
    node2->data[node2->size]=node->data[pos];
    node2->ptr[node2->size]=node->ptr[0];
    while(i<=node1->size)
    {
        node2->size++;
        node2->data[node2->size]=node1->data[i];
        node2->ptr[node2->size]=node->ptr[i];
        i++;
    }
    i=pos;
    while(i<node->size)
    {
        node->data[i]=node->data[i+1];
        node->ptr[i]=node->ptr[i+1];
        i++;
    }
    node->size--;
    free(node1);
}
void adjustNode(TreeNode *node,int pos)
{
    if(!pos)
    {
        if(node->ptr[1]->size>MIN_SIZE)
        {
            leftShift(node,1);
        }
        else
        {
            mergeNodes(node,1);
        }
    }
    else
    {
        if(node->size!=pos)
        {
            if(node->ptr[pos-1]->size >MIN_SIZE)
            {
                rightShift(node,pos);
            }
            else
            {
                if(node->ptr[pos+1]->size>MIN_SIZE)
                {
                    leftShift(node,pos+1);
                }
                else
                {
                    mergeNodes(node,pos);
                }
            }
        }
        else
        {
            if(node->ptr[pos-1]->size>MIN_SIZE)
                rightShift(node,pos);
            else
                leftShift(node,pos);
        }
    }
}
bool delVal(flight flight_record,TreeNode*node)
{
    int pos;
    bool flag=false;
    if(node)
    {
        if(flight_record.key<node->data[1].key)
        {
            pos=0;
            flag=false;
        }
        else
        {
            pos=node->size;
            while(flight_record.key<node->data[pos].key&&pos>1)
                pos--;
            if(flight_record.key == node->data[pos].key)
                flag=true;
            else
                flag=false;
        }
        if(flag)
        {
            if(node->ptr[pos-1])
            {
                copy(node,pos);
                flag=delVal(node->data[pos],node->ptr[pos]);
                if(flag==false)
                    printf("Deletion failed!\n");
            }
            else
                remVal(node,pos);
        }
        else
            flag=delVal(flight_record,node->ptr[pos]);
        if(node->ptr[pos])
            if(node->ptr[pos]->size <MIN_SIZE)
                adjustNode(node,pos);
    }
    return flag;
}
void delete(flight flight_record,TreeNode *node)
{
    TreeNode*temp;
    if(delVal(flight_record,node))
    {
        printf("Record not found!\n");
        return;
    }
    else
    {
        if(node->size==0)
        {
            temp=node;
            node=node->ptr[0];
            free(temp);
        }
    }
    root=node;
}
int getNumFlights(TreeNode *node)
{
    int i,count=0;
    if(node)
    {
        for(i=0;i<node->size;i++)
        {
            count+=getNumFlights(node->ptr[i]);
            count++;
        }
        count+=getNumFlights(node->ptr[i]);
        count++;
    }
    return count;
}
bool isEmpty(TreeNode *node)
{
    return getNumFlights(node)==0;
}
bool isFull(TreeNode*node)
{
    return getNumFlights(node)==MAX_TREE_SIZE;
}
TreeNode* getSortedonDepartureTime(TreeNode *node)
{
    TreeNode *DepartureTree=NULL;
    int i;
    if(node)
    {
        for(i=0;i<node->size;i++)
        {
           DepartureTree=getSortedonDepartureTime(node->ptr[i]);
           insertbyDeparture(DepartureTree,node->data[i+1]);
        }
        DepartureTree=getSortedonDepartureTime(node->ptr[i]);
    }
    return DepartureTree;
}
TreeNode* getSortedonStayTime(TreeNode *node)
{
    TreeNode *StayTree=NULL;
    int i;
    if(node)
    {
        for(i=0;i<node->size;i++)
        {
           StayTree=getSortedonStayTime(node->ptr[i]);
           insertbyStay(StayTree,node->data[i+1]);
        }
        StayTree=getSortedonStayTime(node->ptr[i]);
    }
    return StayTree;
}
TreeNode* getSortedonArrivalTime(TreeNode *node)
{
    TreeNode *ArrivalTree=NULL;
    int i;
    if(node)
    {
        for(i=0;i<node->size;i++)
        {
           ArrivalTree=getSortedonArrivalTime(node->ptr[i]);
           insertbyArrival(ArrivalTree,node->data[i+1]);
        }
        ArrivalTree=getSortedonArrivalTime(node->ptr[i]);
    }
    return ArrivalTree;
}
void getLongestStay(TreeNode* node,int ref)
{
    int i;
    if(node)
    {
        for(i=0;i<node->size;i++)
        {
            getLongestStay(node->ptr[i],ref);
            if(node->data[i+1].stay_time==ref)
            {
                printflight(node->data[i+1]);
            }
        }
        getLongestStay(node->ptr[i],ref);
    }
}
int traverseforlargesttime(TreeNode* node)
{
    int i,largest=0;
    if(node)
    {
        for(i=0;i<node->size;i++)
        {
            largest=traverseforlargesttime(node->ptr[i]);
            if(largest<=node->data[i+1].stay_time)
                largest=node->data[i+1].stay_time;
        }
        if(largest<=traverseforlargesttime(node->ptr[i]))
            largest=traverseforlargesttime(node->ptr[i]);
    }
    return largest;
}
void getFlightswithLongestStay(TreeNode*node)
{
    TreeNode* temptree=getSortedonStayTime(node);
    int ref=traverseforlargesttime(temptree);
    getLongestStay(temptree,ref);
}
void UpdateFlightStatus(TreeNode*node,TreeNode*replacement)
{
    int i,temp;
    flight * flight_record;
    if(replacement)
    {
        for(i=0;i<replacement->size;i++)
        {
            UpdateFlightStatus(node,replacement->ptr[i]);
            flight_record=search(replacement->data[i+1],&temp,node);
            if(flight_record)
                switch (replacement->data[i+1].flight_status)
                {
                case 0:
                    flight_record->arrival_time+=replacement->data[i+1].delay;
                    flight_record->departure_time+=replacement->data[i+1].delay;
                case 1:
                    break;
                case 2:
                    delete(*flight_record,node);
                    break;
                case 3:
                    flight_record->flight_class=replacement->data[i+1].flight_class;
                default:
                    break;
                }
        }
        UpdateFlightStatus(node,replacement->ptr[i]);
    }
}
void threelistUpdate(TreeNode *rootnode,TreeNode*VVIPTree,TreeNode*VIPTree,TreeNode*PublicTree)
{
    int i;
    if(rootnode)
    {
        for(i=0;i<rootnode->size;i++)
        {
            threelistUpdate(rootnode->ptr[i],VVIPTree,VIPTree,PublicTree);
            switch(rootnode->data[i+1].flight_class)
            {
                case 0: {
                    bool f = insert(VVIPTree, rootnode->data[i + 1].name, rootnode->data[i + 1].id,
                                    rootnode->data[i + 1].capacity, rootnode->data[i + 1].arrival_time,
                                    rootnode->data[i + 1].departure_time, rootnode->data[i + 1].flight_class,
                                    rootnode->data[i + 1].flight_status);
                    break;
                }
                case 1: {
                    bool f = insert(VIPTree, rootnode->data[i + 1].name, rootnode->data[i + 1].id,
                                    rootnode->data[i + 1].capacity, rootnode->data[i + 1].arrival_time,
                                    rootnode->data[i + 1].departure_time, rootnode->data[i + 1].flight_class,
                                    rootnode->data[i + 1].flight_status);
                    break;
                }
                case 2: {
                    bool f = insert(PublicTree, rootnode->data[i + 1].name, rootnode->data[i + 1].id,
                                    rootnode->data[i + 1].capacity, rootnode->data[i + 1].arrival_time,
                                    rootnode->data[i + 1].departure_time, rootnode->data[i + 1].flight_class,
                                    rootnode->data[i + 1].flight_status);
                    break;
                }
            }
        }
    }
}
void SearchFlights(TreeNode *node,int start,int end)
{
    int i;
    if(node)
    {
        for(i=0;i<node->size;i++)
        {
            SearchFlights(node->ptr[i],start,end);
            if(node->data[i+1].arrival_time>=start&&node->data[i+1].departure_time<=end)
            {
                printflight(node->data[i+1]);
            }
        }
        SearchFlights(node->ptr[i],start,end);
    }
}
int main()
{
    int i,insert_flag;
    TreeNode *root=(TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *VVIPTree=(TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *VIPTree=(TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *PublicTree=(TreeNode*)malloc(sizeof(TreeNode));

    
    root=NULL;
    VVIPTree=NULL;
    PublicTree=NULL;
    VIPTree=NULL;
    int response,flag=0;
    while(flag==0)
    {
        printf("\nEnter the Operation number to perform\n");
        printf("1. Insert/Update a record(s)\n");
        printf("2. Delete a record\n");
        printf("3. Get the Number of Flights\n");
        printf("4. Check if Flight List is Empty\n");
        printf("5. Check if Flight List is Full\n");
        printf("6. Get the Flight(s) with longest stay time\n");
        printf("7. Sort the Flight list on Arrival Time\n");
        printf("8. Sort the Flight list on Departure Time\n");
        printf("9. Sort the Flight list on Stay Time\n");
        printf("10. Update Flight Status\n");
        printf("11. Search Flight based on Start and End time\n");
        printf("12. Print List\n");
        printf("0. Exit\n");
        scanf("%d",&response);
        //system("cls");
        switch(response)
        {
            case 1:
            {
                int i,n;
                printf("Enter Number of Records: ");
                scanf("%d",&n);
                for(i=0;i<n;i++)
                {
                    bool insert_flag;
                    int id,capacity,arrival_time,departure_time;
                    char name[NAME_SIZE];
                    class flight_class;
                    status flight_status;
                    printf("Enter the Record:\nName: ");
                    scanf("%s",name);
                    printf("Enter Class:\n\t0)VVIP\n\t1)VIP\n\t2)Public\n");
                    scanf("%d",&flight_class);
                    printf("Enter ID: ");
                    scanf("%d",&id);
                    printf("Enter Capacity: ");
                    scanf("%d",&capacity);
                    printf("Enter Arrival Time: ");
                    scanf("%d",&arrival_time);
                    printf("Enter Departure Time: ");
                    scanf("%d",&departure_time);
                    printf("Enter Status:\n\t0)Delay\n\t1)On Time\n\t2)Cancelled\n\t3)Promoted\n");
                    scanf("%d",&flight_status);
                    insert_flag=insert(root,name,id,capacity,arrival_time,departure_time,flight_class,flight_status);
                }
                threelistUpdate(root,VVIPTree,VIPTree,PublicTree);
                if (insert_flag==true)
                    {
                        printf("Inserted!\n");
                    }
                    else
                    {
                        printf("Error, couldn't insert record\n");
                    }
                break;
            }
            case 2:
            {
                int id,arrivaltime;
                printf("Enter id: ");
                scanf("%d",&id);
                printf("Enter ArrivalTime: ");
                scanf("%d",&arrivaltime);
                flight flight_record;
                flight_record.arrival_time=arrivaltime;
                flight_record.id=id;
                dataInit(&flight_record);
                delete(flight_record,root);
                threelistUpdate(root,VVIPTree,VIPTree,PublicTree);
                break;
            }
            case 3:
            {
                printf("%d\n",getNumFlights(root));
                break;
            }
            case 4:
            {
                if (isEmpty(root))
                    printf("Empty\n");
                else
                    printf("Not Empty\n");
                break;
            }
            case 5:
            {
                if (isFull(root))
                    printf("Full\n");
                else
                    printf("Not Full\n");
                break;
            }
            case 6:
            {
                getFlightswithLongestStay(root);
                break;
            }
            case 7:
            {
                TreeNode * arrivaltree = getSortedonArrivalTime(root);
                print(arrivaltree);
                break;
            }
            case 8:
            {
                TreeNode * departuretree = getSortedonDepartureTime(root);
                print(departuretree);
                break;
            }
            case 9:
            {
                TreeNode * staytree = getSortedonStayTime(root);
                print(staytree);
                break;
            }
            case 10:
            {
                int i,n;
                printf("Enter Number of changes: ");
                scanf("%d",&n);
                TreeNode *root2=(TreeNode*)malloc(sizeof(TreeNode));
                root2=NULL;
                for(i=0;i<n;i++)
                {
                    bool insert_flag;
                    int id,capacity,arrival_time,departure_time;
                    char name[NAME_SIZE];
                    class flight_class;
                    status flight_status;
                    printf("Enter the Record:\nName: ");
                    scanf("%s",name);
                    printf("Enter Class:\n\t0)VVIP\n\t1)VIP\n\t2)Public\n");
                    scanf("%d",&flight_class);
                    printf("Enter ID: ");
                    scanf("%d",&id);
                    printf("Enter Capacity: ");
                    scanf("%d",&capacity);
                    printf("Enter Arrival Time: ");
                    scanf("%d",&arrival_time);
                    printf("Enter Departure Time: ");
                    scanf("%d",&departure_time);
                    printf("Enter Status:\n\t0)Delay\n\t1)On Time\n\t2)Cancelled\n\t3)Promoted\n");
                    scanf("%d",&flight_status);
                    insert_flag =insert(root2,name,id,capacity,arrival_time,departure_time,flight_class,flight_status);
                }
                UpdateFlightStatus(root,root2);
                printf("Updated!\n");
                threelistUpdate(root,VVIPTree,VIPTree,PublicTree);
                break;
            }
            case 11:
            {
                int start,end;
                printf("Enter Start time and end time: ");
                scanf("%d%d",&start,&end);
                SearchFlights(root,start,end);
                break;
            }
            case 12:
            {
                printf("Enter the Number corresponding to list you want to print:\n");
                printf("1. Complete List\n");
                printf("2. List with VVIP Flights\n");
                printf("3. List with VIP Flights\n");
                printf("4. List with Public Flights\n");
                printf("5. All of them\n");
                int response2;
                scanf("%d",&response2);
                switch(response2)
                {
                    case 1:
                        print(root);
                        break;
                    case 2:
                        print(VVIPTree);
                        break;
                    case 3:
                        print(VIPTree);
                        break;
                    case 4:
                        print(PublicTree);
                        break;
                    case 5:
                        print(root);
                        print(VVIPTree);
                        print(VIPTree);
                        print(PublicTree);
                        break;
                    default:
                        break;
                }   
            }
            case 0:
            default:
                flag=1;
                break;
        }
    }
}

