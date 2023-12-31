#include<stdio.h>
#include<stdlib.h>
#include <string.h>

// The following is a employee in the organisation, it has the pointer to two more employees a subordinate_1 and a subordinate_2
struct Employee {
    int emp_id; // emp_ids will be unique
    char* emp_name;
    int emp_salary;
    struct Employee* subordinate_1;
    struct Employee* subordinate_2;
};

// The following function creates a employee and returns its pointer
struct Employee* create_employee(int id, char* name, int salary) {
    struct Employee* ptr = (struct Employee*) malloc(sizeof(struct Employee));
    ptr->emp_id = id;
    ptr->emp_salary = salary;
    ptr->emp_name = strdup(name);
    // strdup() creates a copy of the string or char pointer and stores it in the new char pointer of the employee
    ptr->subordinate_1 = NULL;
    ptr->subordinate_2 = NULL;
    return ptr;
}

// The following code creates a organisation from scanning the input file
struct Employee* create_company() {
    int id, salary;
    char name[100];
    scanf("%d", &id);
    if(id == -1) return NULL; // -1 is used when there is a NULL pointer ie when no value is present

    scanf("%s %d", name, &salary);
    struct Employee* par = create_employee(id, name, salary);

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
    printf("%d %s %d ", ceo->emp_id, ceo->emp_name, ceo->emp_salary);
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
// CEO is a global pointer that points to the CEO of the company

// The below function returns the employee id of the first common boss

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

int get_first_common_boss(int emp_id1,int emp_id2){
    struct Employee* lcb = lowestCommonBoss(CEO , emp_id1 , emp_id2);
    return lcb->emp_id;
}

//Print the employees with the same last name sperated by a space in the order of their level
void samelevel(struct Employee* node , int level,int l, char* name){
    if(node == NULL){
        return;
    }
    if(level == l){
        if(strcmp(node->emp_name ,name) == 0){
            printf("%d " , node->emp_id);
        }
    }
    else{
        samelevel(node->subordinate_1 , level+1 , l , name);
        samelevel(node->subordinate_2 , level+1 , l , name);
    }
}
void EmployeesAtSameLevel(int level , char* name) {
    samelevel(CEO , 0 , level , name);
    return;
}
int maxDepth(struct Employee* node){
    if (node == NULL){
        return 0;
    }
    int subodi1d = maxDepth(node->subordinate_1);
    int subodi2d = maxDepth(node->subordinate_2);
    if ( subodi1d > subodi2d){
        return subodi1d + 1;
    }
    else{
        return subodi2d + 1;
    }
}

void same_last_names(int emp_id){
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
    findnode(CEO , emp_id);
    int depth = maxDepth(CEO);
    int i = 0;
    while(i<= depth){
        EmployeesAtSameLevel(i , nd->emp_name);
        i++;
    }
    return;
}

// Print the bosses of the given employee in the order from CEO to immediate boss

void get_all_bosses(int emp_id){
    if(CEO->emp_id == emp_id){
        printf("%d" , -1);
        return;
    }
    struct Employee* lcb = CEO;
    while(lcb->emp_id != emp_id){
        printf("%d " , lcb->emp_id);
        if(lcb->subordinate_1!= NULL){
            if(lcb->subordinate_1 == lowestCommonBoss(CEO , emp_id , lcb->subordinate_1->emp_id)){
                lcb = lcb->subordinate_1;
            }
            else{
                lcb = lcb->subordinate_2;
            }
        }
        else{
            lcb = lcb->subordinate_2;
        }
    }
    return;
}

// Return the average salary of the team with the given employee as head
double get_average_salary(int emp_id){
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
    double salary = 0;
    void netsalary(struct Employee* node){
        if(node == NULL){
            return;
        }
        salary += node->emp_salary;
        netsalary(node->subordinate_1);
        netsalary(node->subordinate_2);
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
    netsalary(nd2);
    teamsize(nd2);
    double avg = salary/size;
    return avg;
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

    char operation_type[100];

    while(T--) {
        scanf("%s", operation_type);

        if(strcmp(operation_type, "get_first_common_boss") == 0) {
            int x,y;
            scanf("%d %d", &x, &y);
            int ans = get_first_common_boss(x,y);
            printf("%d\n", ans);
        } 
        else if(strcmp(operation_type, "same_last_names") == 0) {
            int x;
            scanf("%d", &x);
            same_last_names(x);
            printf("\n");
        } 
        else if(strcmp(operation_type, "get_all_bosses") == 0) {
            int x;
            scanf("%d", &x);
            get_all_bosses(x);
            printf("\n");
        } 
        else if(strcmp(operation_type, "get_average_salary") == 0) {
            int x;
            scanf("%d", &x);
            double ans = get_average_salary(x);
            printf("%.2f\n", ans);
        } 

    }

    return 0;
}
