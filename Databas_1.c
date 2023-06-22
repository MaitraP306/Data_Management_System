#include<stdio.h>
#include<stdlib.h>
#include <string.h>

// The following is a employee in the organisation, it has the pointer to two more employees a subordinate_1 and a subordinate_2
struct Employee {
    int emp_id; // emp_ids will be unique
    struct Employee* subordinate_1;
    struct Employee* subordinate_2;
};

// The following function creates a employee and returns its pointer
struct Employee* create_employee(int x) {
    struct Employee* ptr = (struct Employee*) malloc(sizeof(struct Employee));
    ptr->emp_id = x;
    ptr->subordinate_1 = NULL;
    ptr->subordinate_2 = NULL;
    return ptr;
}

// The following code creates a organisation from scanning the input file
struct Employee* create_company() {
    int x;
    scanf("%d", &x);

    if(x == -1) return NULL; // -1 is used when there is a NULL pointer ie when no value is present
    struct Employee* par = create_employee(x);

    par->subordinate_1 = create_company();
    par->subordinate_2 = create_company();

    return par;
}

// The following function
void print_company_helper(struct Employee* ceo) {
    // take input
    if(!ceo) {
        printf("%d ", -1);
        return;
    }
    printf("%d ", ceo->emp_id);
    print_company_helper(ceo->subordinate_1);
    print_company_helper(ceo->subordinate_2);
    return;
}

void print_company(struct Employee* ceo) {
    print_company_helper(ceo);
    printf("\n");
    return;
}

// --------------------------------------------------- YOU CAN EDIT BELOW THIS LINE -----------------------------------

struct Employee* CEO = NULL;
struct Employee* Node = NULL;
struct Employee* Node2 = NULL;
// CEO is a global pointer that points to the CEO of the company


/*  In this function you have to print all the employees at a given level, Note that ceo is at level 0
In any of the functions which involve printing you need not print -1 for NULL pointers */
void samelevel(struct Employee* node , int level,int l){
    if(node == NULL){
        return;
    }
    if(level == l){
        printf("%d " , node->emp_id);
    }
    else{
        samelevel(node->subordinate_1 , level+1 , l);
        samelevel(node->subordinate_2 , level+1 , l);
    }
}
void EmployeesAtSameLevel(int level) {
    samelevel(CEO , 0 , level);
    return;
}
int Boss(int emp_id) {
    struct Employee* parent = NULL;
    void findparent(struct Employee* node , int emp){
        if(node->subordinate_1==NULL && node->subordinate_2==NULL){
            return;
        }
        if(node->subordinate_1==NULL){
            if(node->subordinate_2->emp_id == emp){
                parent = node;
            }
            findparent(node->subordinate_2 , emp);
            return;
        }
        if(node->subordinate_2==NULL){
            if(node->subordinate_1->emp_id == emp){
                parent = node;
            }
            findparent(node->subordinate_1 , emp);
            return;
        }
        if(node->subordinate_1->emp_id == emp || node->subordinate_2->emp_id == emp){
            parent = node;
        }
        findparent(node->subordinate_1 , emp);
        findparent(node->subordinate_2 , emp);
        return;
    }
    if(CEO->emp_id == emp_id){
        return -1;
    }
    findparent(CEO , emp_id);
    return parent->emp_id ;
}

// You have to print the employees as you search the organization look for the examples in the pdf and the input.txt and output.txt for details
// Note: You do not have to print -1 for NULL pointers

void get_employees() {
    struct Employee* Node1 = NULL;
    if(Node == NULL && Node2== NULL){
        if(CEO == NULL){return;}
        Node = CEO;
        printf("%d " , Node->emp_id);
        Node1 = Node;
        Node2 = Node;
        Node = Node->subordinate_1;
        get_employees();
        Node = Node1;
        Node = Node->subordinate_2;
        get_employees();
        return;
    }
    else{
        if(Node == NULL){
            return;
        }
        else{
            printf("%d " , Node->emp_id);
            Node2 = Node;
            Node1 = Node;
            Node = Node->subordinate_1;
            get_employees();
            Node = Node1;
            Node = Node->subordinate_2;
            get_employees();
        }
    }
}

/* In the following function you have to print the immediate team of a employee - it includes their boss and their subordinates*/



void ImmediateTeam(int emp_id) {
    struct Employee* nd = NULL;
    void findnode(struct Employee* node,int emp_id){
        if(node == NULL){
            return ;
        }
        if(node->emp_id == emp_id){
            nd = node;
        }
        findnode(node->subordinate_1 , emp_id);
        findnode(node->subordinate_2 , emp_id);
    }
    int k = Boss(emp_id);
    findnode(CEO , emp_id);
    if(nd->subordinate_1 == NULL && nd->subordinate_2 == NULL && k ==-1){
        return;
    }
    if(nd->subordinate_1 == NULL && nd->subordinate_2 == NULL)
    {printf("%d" , k);
        return;
    }
    if(nd->subordinate_2 == NULL && k==-1)
    {printf("%d" ,nd->subordinate_1->emp_id );
        return;
    }
    if(nd->subordinate_1 == NULL && k==-1)
    {printf("%d" ,nd->subordinate_2->emp_id );
        return;
    }
    if(nd->subordinate_1 == NULL )
    {printf("%d %d" ,k , nd->subordinate_2->emp_id );
        return;
    }
    if(nd->subordinate_2 == NULL )
    {printf("%d %d" ,k , nd->subordinate_1->emp_id );
        return;
    }
    if(k==-1)
    {printf("%d %d" ,nd->subordinate_1->emp_id  ,nd->subordinate_2->emp_id );
        return;
    }
    printf("%d %d %d" , Boss(emp_id) , nd->subordinate_1->emp_id , nd->subordinate_2->emp_id);

}

// The following function returns the level of a employee with the given emp_id
int level(struct Employee* n,int emp_id , int l){
    if(n == NULL){
        return -1;
    }
    if(n->emp_id == emp_id){
        return l;
    }
    int sub1 = level(n->subordinate_1,emp_id , l+1);
    if(sub1 == -1){
        int sub2 = level(n->subordinate_2,emp_id , l+1);
        return sub2;
    }
    else{
        return sub1;
    }
}
int Level(int emp_id) {
    int l = 0;
    l = level(CEO , emp_id , 0);
    return l;
}

// The following function gives the distance between employees with emp_id1 and emp_id2
struct Employee* lowestCommonBoss(struct Employee* node , int emp1 , int emp2){
    if(node == NULL){
        return NULL;
    }
    if(node->emp_id == emp1 || node->emp_id == emp2 ){
        return node;
    }
    struct Employee* ans1 = lowestCommonBoss(node->subordinate_1 , emp1 , emp2);
    struct Employee* ans2 = lowestCommonBoss(node->subordinate_2 , emp1 , emp2);
    if(ans1 != NULL && ans2 != NULL){
        return node;
    }
    if(ans1!=NULL){
        return ans1;
    }
    return ans2;
}
int Distance(int emp_id1, int emp_id2) {
    struct Employee* lcb = lowestCommonBoss(CEO , emp_id1 , emp_id2);
    int a = Level(lcb->emp_id);
    int b = Level(emp_id1);
    int c = Level(emp_id2);
    return b+c-2*a;
}

/* The following function takes an emp_id this will belong to a employee in the organisation and your task is to return the emp_id of its boss
Note: If the boss does not exit return -1 */




/* The following function returns the diameter of a Organisation -
a diameter is the maximum distance between any two emp_ids in the organisation. You can use the distance function implemented above */
int max(int a , int b){
    if(a>b){
        return a;
    }
    return b;
}
int height(struct Employee* node){
    if(node== NULL){
        return 0;
    }
    int h1 = height(node->subordinate_1);
    int h2 = height(node->subordinate_2);
    return 1 + max(h1 , h2);
}
int diameter(struct Employee* node){
    if(node == NULL){
        return 0;
    }
    return max(height(node->subordinate_1)+height(node->subordinate_2) , max(diameter(node->subordinate_1) , diameter(node->subordinate_2)));
}
int Diameter() {
    if(CEO == NULL){
        return 0;
    }
    return diameter(CEO);
}

/* The following function takes an emp_id of a employee and returns the number of employees directly connected to it.
NULL pointers are not included */




int TeamSize(int emp_id) {
    int size = 0;
    void teamsize(struct Employee* node){
        if(node == NULL){
            return;
        }
        size += 1;
        teamsize(node->subordinate_1);
        teamsize(node->subordinate_2);
        return;
    }
    struct Employee* nd2 = NULL;
    void findnode2(struct Employee* node,int emp_id){
        if(node == NULL){
            return ;
        }
        if(node->emp_id == emp_id){
            nd2 = node;
        }
        findnode2(node->subordinate_1 , emp_id);
        findnode2(node->subordinate_2 , emp_id);
    }
    findnode2(CEO , emp_id);
    teamsize(nd2);
    return size;
}

// --------------------------------------------------- YOU CAN EDIT ABOVE THIS LINE -----------------------------------

/* The following driver code creates a organisation for you and based on the input file
it will call all the functions that are necessary, your job is to edit the functions
above the line. Their descriptions are in the pdf and in the comments in the code. */

int main(int argc, char const *argv[])
{
    CEO = create_company();
    print_company(CEO);

    int T;
    scanf("%d", &T);

    char operation_type[20];

    while(T--) {
        scanf("%s", operation_type);

        if(strcmp(operation_type, "level") == 0) {
            int x;
            scanf("%d", &x);
            int d = Level(x);
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "distance") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            int d = Distance(x, y);
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "employees_at_same_level") == 0) {
            int x;
            scanf("%d", &x);
            EmployeesAtSameLevel(x);
            printf("\n");
        }

        if(strcmp(operation_type, "get_employees") == 0) {
            get_employees();
            printf("\n");
        }

        if(strcmp(operation_type, "boss") == 0) {
            int x;
            scanf("%d", &x);
            int d = Boss(x);
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "diameter") == 0) {
            int d = Diameter();
            printf("%d\n", d);
        }

        if(strcmp(operation_type, "immediate_team") == 0) {
            int x;
            scanf("%d", &x);
            ImmediateTeam(x);
            printf("\n");
        }

        if(strcmp(operation_type, "team_size") == 0) {
            int x;
            scanf("%d", &x);
            int d = TeamSize(x);
            printf("%d\n", d);
        }
    }

    return 0;
}
