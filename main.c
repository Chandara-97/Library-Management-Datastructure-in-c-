//Add a new book to the library. A book may contain the following info:
//- ISBN (10 digits)
//- Title
//- Author(s) (max 3 authors)
//- Year of publication
//- Number of copies
//- Modify a book (using its ISBN)
//- Delete a book (using its ISBN)
//- List all books in the library
//- Sort the books by their ISBN or by their titles
//- Search for a book by its title using hashing
//- List all books published later than a given date and by a given author
//- Save all data to file
//- Load data from file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 1000
typedef struct{
	long long ISBN;
	int Pub_Year;
	int Number_Copy;
	char Title[50];
	char Author1[50];
	char Author2[50];
	char Author3[50];
}Book;

typedef struct{
    Book data;
    struct Node *next;
} NODE;

typedef struct{
    NODE *head;
    int n;
} List;

List *create_list() {
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->n = 0;
    return list;
}




// =========================================add book==============================================
void insert_front (List *list,Book add) {

    NODE *tmp = (NODE*)malloc(sizeof(NODE));
	tmp->data.ISBN=add.ISBN;
	strcpy(tmp->data.Title,add.Title);
	strcpy(tmp->data.Author1,add.Author1);
	strcpy(tmp->data.Author2,add.Author2);
	strcpy(tmp->data.Author3,add.Author3);
	tmp->data.Pub_Year=add.Pub_Year;
	tmp->data.Number_Copy=add.Number_Copy;
	tmp->next = list->head;
	list->head = tmp;
    list->n++;
}
void add(List *list){
    int n;
    printf("Insert the amount of Book:");
    scanf("%d",&n);
    int i;
    Book add;
    for(i=0;i<n;i++){
        printf("ISBN:"); scanf("%lld",&add.ISBN);
        printf("Title:");fflush(stdin);gets(add.Title);
        printf("Author1:");fflush(stdin);gets(add.Author1);
        printf("Author2:");fflush(stdin);gets(add.Author2);
        printf("Author3:");fflush(stdin);gets(add.Author3);
        printf("Publish Year:"); scanf("%d",&add.Pub_Year);
        printf("Number of Copy:"); scanf("%d",&add.Number_Copy);
        printf("===============================================================\n\n");
        insert_front(list,add);
    }
}

//==================================list all book===============================
void list_all_book(List *list){
    NODE *tmp = (NODE*)malloc(sizeof(NODE)*M);
    int i=1;
    tmp = list->head;
    char ISBN[10],Title[10],Author1[10],Author2[10],Author3[10],Pub_Year[15],Number_Copy[15],No[10];
	strcpy(ISBN,"ISBN");
	strcpy(Title,"Title");
	strcpy(Author1,"Author1");
	strcpy(Author2,"Author2");
	strcpy(Author3,"Author3");
	strcpy(Pub_Year,"Publish_Year");
	strcpy(Number_Copy,"Number_Copy");
	strcpy(No,"No");
	//printf("%s\t%s\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t%s\n",No,ISBN,Title,Author1,Author2,Author3,Pub_Year,Number_Copy);
    while(tmp != NULL){
      printf("No:%d\n",i);i++;
  printf("ISBN:%lld\n",tmp->data.ISBN);
  printf("Title:%s\n",tmp->data.Title);
  printf("Author1:%s\n",tmp->data.Author1);
  printf("Author2:%s\n",tmp->data.Author2);
  printf("Author3:%s\n",tmp->data.Author3);
  printf("Publish Year:%d\n",tmp->data.Pub_Year);
  printf("Number of Copy:%d\n",tmp->data.Number_Copy);
  printf("===============================================================\n\n");

        tmp = tmp->next;
    }
}
//=====================================up information book================================
void modify(List *list){
    int found=0;
    long long Up_isbn;
    printf("Put ISBN BOOK That You Want To Modify:\n");scanf("%lld",&Up_isbn);
    Book modify;
    NODE *tmp = list->head;
    while (tmp != NULL) {
        if(tmp->data.ISBN==Up_isbn){
        printf("Title:");fflush(stdin);gets(modify.Title);
        printf("Author1:");fflush(stdin);gets(modify.Author1);
        printf("Author2:");fflush(stdin);gets(modify.Author2);
        printf("Author3:");fflush(stdin);gets(modify.Author3);
        printf("Publish Year:"); scanf("%d",&modify.Pub_Year);
        printf("Number of Copy:"); scanf("%d",&modify.Number_Copy);

    	strcpy(tmp->data.Title,modify.Title);
    	strcpy(tmp->data.Author1,modify.Author1);
    	strcpy(tmp->data.Author2,modify.Author2);
    	strcpy(tmp->data.Author3,modify.Author3);
    	tmp->data.Pub_Year=modify.Pub_Year;
    	tmp->data.Number_Copy=modify.Number_Copy;
        found=1;
        }
        tmp=tmp->next;
    }
    if(found==0){
        printf("Product not found\n");
    }
    printf("\n\n");
}
//=====================================delete a book=========================================
void remove_front (List *list) {
    NODE *tmp = list->head;
    list->head = tmp->next;
    free(tmp);
    list->n--;
}
void search_pos(long long *isbn,int *find,List *list){
    NODE *tmp;
    tmp=list->head;
    int j=0;
    while(tmp!=NULL){
        *find=*find+1;
        if(tmp->data.ISBN==isbn){
            return;
        }
        tmp=tmp->next;
    }
    *find=0;
    return 0;
}

void delete_Book(List *list){
    int find=0;
    long long del_isbn;
    NODE *p;
    NODE *tmp;
    p=list->head;
    int i;
    printf("Input the ISBN to delete:");scanf("%lld",&del_isbn);
    search_pos(del_isbn,&find,list);
    if(find==0){
        printf("Product cannot find\n");
    }
    else{
        find--;
        if (find == 0) {
            remove_front(list);
        } else {
            NODE *tmp;
            NODE *tmp2 = list->head;
            for (int i = 0; i < find - 1; i++) {
                tmp2 = tmp2->next;
            }
            tmp = tmp2->next;
            tmp2->next = tmp->next;
            free(tmp);
            list->n--;
        }
        printf("Done\n");
    }
}
//==============================================sorted================================
typedef struct{
    Book data;
    struct node *left,*right;
}node;
node *new_node(Book sort){
    node *head;
    head=(node*)malloc(sizeof(node));
    head->data.ISBN=sort.ISBN;
    strcpy(head->data.Title,sort.Title);
    strcpy(head->data.Author1,sort.Author1);
    strcpy(head->data.Author2,sort.Author2);
    strcpy(head->data.Author3,sort.Author3);
    head->data.Pub_Year=sort.Pub_Year;
    head->data.Number_Copy=sort.Number_Copy;
    head->left=NULL;
    head->right=NULL;

    return head;
}
node *insert(node *head,Book sort){
    if(head==NULL){
        return new_node(sort);
    }
    else if(head->data.ISBN>sort.ISBN){
        head->left=insert(head->left,sort);
    }
    else if(head->data.ISBN<sort.ISBN){
        head->right=insert(head->right,sort);
    }

    return head;
}

node *insert_name(node *head,Book sort){
    if(head==NULL){
        return new_node(sort);
    }
    else if(strcmp(head->data.Title,sort.Title)>0){
        head->left=insert(head->left,sort);
    }
    else if(strcmp(head->data.Title,sort.Title)<0){
        head->right=insert(head->right,sort);
    }

    return head;
}


void inorder ( node *sr ){
    if ( sr != NULL )
    {
        inorder ( sr -> left ) ;
		printf("ISBN:%lld\n",sr->data.ISBN);
		printf("Title:%s\n",sr->data.Title);
		printf("Author1:%s\n",sr->data.Author1);
		printf("Author2:%s\n",sr->data.Author2);
		printf("Author3:%s\n",sr->data.Author3);
		printf("Publish Year:%d\n",sr->data.Pub_Year);
		printf("Number of Copy:%d\n",sr->data.Number_Copy);
		printf("===============================================================\n\n");
        inorder ( sr -> right ) ;
    }
}

void sort(List *list){
    FILE *fptr;
    int i=1;
    node *head=NULL;
    int opt;
    NODE *tmp = list->head;

    printf("Sort by:\n");
    printf("1.Code\n");
    printf("2.Name\n");
    printf("Choose one(Number):");
    scanf("%d",&opt);

    switch(opt)
    {
    case 1:
        {
            while (tmp != NULL) {
                head=insert(head,tmp->data);
                tmp = tmp->next;
            }
            break;
        }
    case 2:
        {
            while (tmp != NULL) {
                head=insert_name(head,tmp->data);
                tmp = tmp->next;
            }
            break;
        }
    }
    inorder(head);
}

//======================================search title========================================
typedef struct{
    Book data;
    struct node *next;
}hashing;

hashing *arr[M];
int h(char *s){
    int slength=strlen(s);
    int i,sum=0;
    for(i=0;i<slength;i++){
        sum+=(int)s[i];
    }
    return sum%M;
}

void insert_Book(Book data){
    hashing *newnode=(hashing*)malloc(sizeof(hashing));
    int key;
    newnode->data.ISBN=data.ISBN;
    strcpy(newnode->data.Title,data.Title);
    strcpy(newnode->data.Author1,data.Author1);
    strcpy(newnode->data.Author2,data.Author2);
    strcpy(newnode->data.Author3,data.Author3);
    newnode->data.Pub_Year=data.Pub_Year;
    newnode->data.Number_Copy=data.Number_Copy;
    newnode->next=NULL;

    key=h(data.Title);

    if(arr[key]==NULL){
        arr[key]=newnode;
    }
    else{
        hashing *temp=arr[key];
        while(temp->next){
            temp=temp->next;
        }
        temp->next=newnode;
    }
}

void search(char *n){
    int key;
    key=h(n);
    hashing *temp;
    temp=arr[key];

    while(temp){
        if(strcmp(temp->data.Title,n)==0){
            printf("ISBN:%lld\n",temp->data.ISBN);
            printf("Title:%s\n",temp->data.Title);
            printf("Author1:%s\n",temp->data.Author1);
            printf("Author2:%s\n",temp->data.Author2);
            printf("Author3:%s\n",temp->data.Author3);
            printf("Publish Year:%d\n",temp->data.Pub_Year);
            printf("Number of Copy:%d\n",temp->data.Number_Copy);
        }
        temp=temp->next;
    }
}

void search_Book(List *list){
    FILE *fptr;
    int i=1;
    char search_Title[50];
    NODE *tmp = list->head;
    while (tmp != NULL) {
        insert_Book(tmp->data);
        tmp = tmp->next;
    }
    printf("Insert Book Title to search:");fflush(stdin);gets(search_Title);
    search(search_Title);
}
//==================================List_Condition=======================================
void list_condition(List *list){
    int pub_year;
    char author1[50],author2[50],author3[50];
    printf("Input The Publish Year:");scanf("%d",&pub_year);
    printf("Input Author1:");fflush(stdin);gets(author1);
    NODE *tmp = list->head;
    while(tmp!=NULL){
            int fit=strcmp(author1,tmp->data.Author1)+strcmp(author1,tmp->data.Author2)+strcmp(author1,tmp->data.Author3);
        if((0 <tmp->data.Pub_Year-pub_year)&(fit)){

        }
        else{
            printf("ISBN:%lld\n",tmp->data.ISBN);
            printf("Title:%s\n",tmp->data.Title);
            printf("Author1:%s\n",tmp->data.Author1);
            printf("Author2:%s\n",tmp->data.Author2);
            printf("Author3:%s\n",tmp->data.Author3);
            printf("Publish Year:%d\n",tmp->data.Pub_Year);
            printf("Number of Copy:%d\n",tmp->data.Number_Copy);
            printf("=========================================================\n\n");
        }


        tmp=tmp->next;
        }
    }

void save_file(List *list){
    FILE *file;
    //Book copy;
    int n;
    int i;i=0;
    NODE *tmp = (NODE*)malloc(sizeof(NODE));
    tmp = list->head;

    char ISBN[10],Title[10],Author1[10],Author2[10],Author3[10],Pub_Year[15],Number_Copy[15],No[10];
	strcpy(ISBN,"ISBN");
	strcpy(Title,"Title");
	strcpy(Author1,"Author1");
	strcpy(Author2,"Author2");
	strcpy(Author3,"Author3");
	strcpy(Pub_Year,"Publish_Year");
	strcpy(Number_Copy,"Number_Copy");
	strcpy(No,"No");

    char name[100];
    printf("Input the name of file:"); scanf("%s",&name);
    file=fopen(name,"w");
        fprintf(file,"%s\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t%s\n",No,ISBN,Title,Author1,Author2,Author3,Pub_Year,Number_Copy);
        while(tmp) {
            fprintf(file,"%d\t%lld\t\t%s\t\t%s\t\t%s\t\t\t%s\t\t\t\t%d\t\t\t%d\n",i+1,tmp->data.ISBN,tmp->data.Title,tmp->data.Author1,tmp->data.Author2,tmp->data.Author3,tmp->data.Pub_Year,tmp->data.Number_Copy);
            //fwrite(&copy,sizeof (Book),1,file);
            tmp = tmp->next;
        }
         printf("Done\n");
    fclose(file);
}
//=====================load from file=======================================
void load(List *list){
    int n;
    int i;i=0;
    NODE *tmp = (NODE*)malloc(sizeof(NODE));
    tmp = list->head;
    FILE *file;

    char ISBN[10],Title[10],Author1[10],Author2[10],Author3[10],Pub_Year[15],Number_Copy[15],No[10];
    char ISBNstr[50],Titlestr[50],Author1str[50],Author2str[50],Author3str[50],Pub_Yearstr[50],Number_Copystr[50],Nostr[100];
	strcpy(ISBN,"ISBN");
	strcpy(Title,"Title");
	strcpy(Author1,"Author1");
	strcpy(Author2,"Author2");
	strcpy(Author3,"Author3");
	strcpy(Pub_Year,"Publish_Year");
	strcpy(Number_Copy,"Number_Copy");
	strcpy(No,"No");

    char name[100];
    printf("Input the name of file:"); scanf("%s",&name);
    file=fopen(name,"r");
    if(file == NULL){
        printf("Cannot read file\n");
        return;
    }
    fscanf(file, "%s %s %s %s %s %s %s %s\n",No,ISBN,Title,Author1,Author2,Author3,Pub_Year,Number_Copy);
    while(fscanf(file,"%s %s %s %s %s %s %s %s\n",Nostr,ISBNstr,Titlestr,Author1str,Author2str,Author3str,Pub_Yearstr,Number_Copystr)!=EOF) {

        //insert_front (List *list,Book add);
        NODE *tmp = (NODE*)malloc(sizeof(NODE));
        tmp->data.ISBN=atoi(ISBNstr);
        strcpy(tmp->data.Title,Titlestr);
        strcpy(tmp->data.Author1,Author1str);
        strcpy(tmp->data.Author2,Author2str);
        strcpy(tmp->data.Author3,Author3str);
        tmp->data.Pub_Year=atoi(Pub_Yearstr);
        tmp->data.Number_Copy=atoi(Number_Copystr);
        tmp->next = list->head;
        list->head = tmp;
        list->n++;
    }
    fclose(file);
}

//=================================================================================================================================================================
void display_manu(){
    List *list = create_list();
    int choice;
    printf("=================================================Library System=======================================================\n");
    do{
        system("cls");
        printf("================================================Welcome!==========================================================\n");
		printf("||         1.Add                                                                                                ||\n");
		printf("||         2.List                                                                                               ||\n");
		printf("||         3.Modify By ISBN                                                                                     ||\n");
		printf("||         4.Delete By ISBN                                                                                     ||\n");
		printf("||         5.Sort By ISBN or Title                                                                              ||\n");
		printf("||         6.Search Book by its title                                                                           ||\n");
		printf("||         7.List all books published later than a given date and by a given author                             ||\n");
		printf("||         8.Save File                                                                                          ||\n");
		printf("||         9.Load File                                                                                          ||\n");
		printf("==================================================================================================================\n");
		printf("Please choose one:");
		scanf("%d",&choice);
		switch(choice){
        case 1:
            {
                system("cls");
                add(list);
                break;
            }
        case 2:
            {
                system("cls");
                list_all_book(list);
                break;
            }
        case 3:
            {
                system("cls");
                printf("\n");
                modify(list);
                break;
            }
        case 4:
            {
                system("cls");
                delete_Book(list);
                break;
            }
        case 5:
            {
                system("cls");
                sort(list);
                break;

            }

        case 6:
            {
                system("cls");
                search_Book(list);
                break;
            }
        case 7:
            {
                system("cls");
                list_condition(list);
                break;
            }
        case 8:
            {
                save_file(list);
                break;
            }
        case 9:
            {
                load(list);
                break;
            }
        default:
            {
                printf("You input the invalid number.\n");
                break;
            }
		}
		printf("Please enter a key to continue\n");
    }
    while(getch()==13);

}
int main(){
    system("Color 60");
    display_manu();
}
