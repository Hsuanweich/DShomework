//11127129�i�a�� 11127136�^��� 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cstring>

#define MAX_LENGTH 100
static char num[MAX_LENGTH];//�s�ϥΪ̿�J���ɮ׸��X
static bool success = false;   //�����O�_���\�}���ɮ� 
static bool find = false;      //�����O�_���P�W��� 

//��Ƶ��c 
struct Data{
	char id[10];         
	char name[100];		
	char type1[50];		 
	char type2[50];
	char total[50];
	char hp[5];
	char attack[5];
	char defense[5];  		 
};

struct Datatree{
	char hp[5];
	int index;
};

//��`�I 
class TreeNode {
public:
    Datatree data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Datatree data) : data(data), left(NULL), right(NULL) {}
	
};
 
//��ʾ� 
class BinaryTree {
private:
    TreeNode* root;
    std::vector<TreeNode*> tree;

    // �̲��~�ͼƴ��J���
    TreeNode* insert(TreeNode* node, Data value,int index) {
        if (node == NULL) {
        	Datatree in;
        	strcpy(in.hp,value.hp);
        	in.index=index;
            return new TreeNode(in);
        }
		
		
		if (atoi(value.hp) < atoi(node->data.hp)) {
	        node->left = insert(node->left, value,index);
	    } else if (atoi(value.hp) >= atoi(node->data.hp)) {
	        node->right = insert(node->right, value,index);
		}
		
        

        return node;
    }

    // �e�ǹM����ƦL�X 
    void preorderTraversal(TreeNode* temp) const {
        if (temp != NULL) {
        	/*
            printf("%s\t%s\t%s\t%s\t%s %s\t%s %s\t%s\t%s\t%s\t%s\t%s\n", temp->data.id, temp->data.name, temp->data.code, temp->data.department,temp->data.sessioncode,
		   temp->data.session,temp->data.degreecode, temp->data.degree, temp->data.student, temp->data.teacher, temp->data.graduate, temp->data.city, temp->data.category);
            */
			preorderTraversal(temp->left);
            preorderTraversal(temp->right);
        }
    }
    
    
    //�p�����D�� 
    int Height(TreeNode* node) const {
        if (node == NULL) {
            return 0;
        }

        int leftHeight = Height(node->left);
        int rightHeight = Height(node->right);

        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight); //���k���̤j+1 
    }

    // �R����ʾ���
    void destroyTree(TreeNode* node) {
    	
        if (node != NULL) {
        	if (node->left != NULL) {
		        destroyTree(node->left);
		    }
			if (node->right != NULL) {
		        destroyTree(node->right);
		    }
            
            delete node;
            
        }
        
        return;
    }
    
public:
	bool containsDigits(char *str) {
	    bool x=true;
		while (*str) {
		    if (!isdigit(*str)) {
		       x=false ;// �]�t�D�Ʀr
		    }
		    str++;
		}
		return x; // ���]�t�Ʀr
	}
    BinaryTree() : root(NULL) {}

    // ���J���(��� ) 
    void insert(Data value,int index) {
        root = insert(root, value, index);
	}

    // �e�ǹM�����
    void preorderTraversal() const {
        preorderTraversal(root);
    }
    
    //���}�D�ư� 
    int getHeight() const {
        return Height(root);
    }

    // �R����ʾ���
    void destroyTree() {
        destroyTree(root);
        root = NULL;
    }
    
    //���}����l�𤤳̤p���`�I(�̥� 
    int findMin() {
    	TreeNode* node=root;
        while (node->left != NULL) {
            node = node->left;
        }
        return node->data.index;
    }
    
    int findMax() {
    	TreeNode* node=root;
        while (node->right != NULL) {
            node = node->right;
        }
        return node->data.index;
    }
	
};
bool containsDigits(char *str) {
    bool x=true;
	while (*str) {
	    if (!isdigit(*str)) {
	       x=false ;// �]�t�D�Ʀr
	    }
	    str++;
	}
	return x; // ���]�t�Ʀr
}
//�ˬd�r��O�_���r�� 
int isAllAlpha(char *str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0; // ���O�^��r��
        }
        str++;
    }
    return 1; // �O�^��r��
}
//�ˬd�r��O�_���Ʀr 
bool isAllDigits(char *str) {
    	bool x=true;
	    while (*str) {
	        if (!isdigit(*str)) {
	            x=false ;// �]�t�D�Ʀr
	        }
	        str++;
	    }
	    return x; 
}

//Ū���ɮפ������ 
std::vector<Data> Read(std::vector<Data> datain,FILE *file){
	char line[1024]; 
	//�e1�椣���n 
	fgets(line, sizeof(line), file);
	Data temp;
	char chtemp[10];
	
	int i=0;
	
	
	while ( fscanf(file, "%s%*[\t]%[^\t]%*[\t]%s%*[\t]%s%*[\t]%s%*[\t]%s%*[\t]%s%*[\t]%s", &temp.id, &temp.name, &temp.type1, &temp.type2, 
		   &temp.total,&temp.hp, &temp.attack,&temp.defense)!= EOF) {
		/*
	    sscanf(line, "%[^\t]", temp.id);
	    sscanf(line, "%*s\t%[^\t]", temp.name);
	    sscanf(line, "%*s%*s\t%[^\t]", temp.type1);
	    sscanf(line, "%*s%*s%*s\t%[^\t]", temp.type2);
	    sscanf(line, "%*s%*s%*s%*s\t%[^\t]", temp.total);
	    sscanf(line, "%*s%*s%*s%*s%*s\t%[^\t]", temp.hp);
	    sscanf(line, "%*s%*s%*s%*s%*s%*s\t%[^\t]", temp.attack);
		sscanf(line, "%*s%*s%*s%*s%*s%*s%*s\t%[^\t]", temp.defense); 
		*/
		
		fgets(line, sizeof(line), file);
		
		if(containsDigits(temp.type2)){
			strcpy(temp.defense,temp.attack);
			strcpy(temp.attack,temp.hp);
			strcpy(temp.hp,temp.total);
		}
		
		datain.push_back(temp);
    }
    

    return datain;
}

//�}��input�ɮסA���\�h�I�sŪ�� 
std::vector<Data> Set(std::vector<Data> datain){ 
    char fname[200]="input";//�s����ɮת��W�r
	
	
	//�걵�ɦW 
	strcat(fname,num);
	strcat(fname,".txt");
	//�}�Ҭ������ 
	FILE *file;
	file = fopen(fname, "rb"); // �H��Ū�Ҧ����}���
	if (file == NULL) {
		//�䤣�즹���h��X���~�T�� 
    	printf("### input%s.txt does not exist! ###\n",num);
    	printf("\n");
    	success=false;
	}
	else{ 
		success=true;
		datain=Read(datain,file);
		//�]�w����������� 
		fclose(file);
	}
	
	return datain; //�N�]�w�n���^�� 
}

//���Ȥ@ 
void One(BinaryTree &hptree,std::vector<Data> &datain){           
	char trash;             //�s���ݭn������
	int width = 2; 
	int width3 = 3; 
	//Ū�J�ɮ׸��X 
	printf("Input a file number[0: quit]:");
	scanf("%s",&num);
	
	std::string com=num;
	std::string x="0";
	if(com.compare(x) == 0){
		return ;
	}

	datain=Set(datain);
	
	if(success){
		//�����\Ū���ɮ� 
		int i = 0;
		printf("\t#\tName     \t\t\tType 1\t\tHP\tAttack\tDefense\n",i+1 , datain[i].id, datain[i].name,datain[i].type1,
			        datain[i].total, datain[i].hp,datain[i].attack);
		while(i<datain.size()){
			
			
			printf("[%*d]\t%s\t%-32s%-16s%s\t%s\t%s\n",width,i+1 , datain[i].id, datain[i].name,datain[i].type1,
			       datain[i].hp, datain[i].attack,datain[i].defense);    
			
			
			hptree.insert(datain[i],i);
			i++;
		}
	    
		//graduate.preorderTraversal();
	
	     
		printf("HP tree height = %d\n",hptree.getHeight());
		printf("Leftmost node:\n");
		printf("        #       Name                            Type 1          HP      Attack  Defense\n");
		i=hptree.findMin();
		printf("[%*d]\t%s\t%-32s%-16s%s\t%s\t%s\n",width3,i+1 , datain[i].id, datain[i].name,datain[i].type1,
			       datain[i].hp, datain[i].attack,datain[i].defense); 
			printf("Rightmost node:\n");
		printf("        #       Name                            Type 1          HP      Attack  Defense\n");
		i=hptree.findMax();
		printf("[%*d]\t%s\t%-32s%-16s%s\t%s\t%s\n",width3,i+1 , datain[i].id, datain[i].name,datain[i].type1,
			       datain[i].hp, datain[i].attack,datain[i].defense); 
		printf("\n");
		
	}
}
/*
//���ȤG 
//����J�j�����~�ͤH�� 
void Two(BinaryTree &graduate){ 
	char search[100];
	int x;
	
	if(success){
		//��Ū���ɮ� 
		printf("Input the number of graduates:");
		scanf("%s",&search);
		
		if(isAllDigits(search)){
			x=atoi(search);
			graduate.BiggerThanValue(x);
		}
		else{
			printf("### the input string %s is not a decimal number! ###\n",search);
			printf("There is no match!\n");
			printf("\n");
		}
		
	
		
		
	}
	
}
//��P��J���Ǯ� 
void Three(BinaryTree &name){ 
	char search[100];
	
	if(success){
		//��Ū���ɮ� 
		printf("Input a school name:");
		scanf("%s",&search);
		
		name.Searchschool(search);
	
	}
	
}

*/
int main() {
	BinaryTree hptree;
	std::vector<Data> datain;
	char trash;      //�s���ݭn������
	int dowhat=-1;//�s�����O
	   
	//�����a�߰ݭn���檺�ʧ@�����J0�h�X 
	while(dowhat!=0){
		//�L�X������Ū�����O 
		printf("***** Pokemon Tree and Heap *****\n");
    	printf("* 0. QUIT                       *\n");
    	printf("* 1. Read a file to build BST   *\n");
    	printf("* 2. Transform it into Max Heap *\n");
    	printf("*********************************\n");
    	printf("Input a choice(0, 1, 2):");
		scanf("%d",&dowhat);
		
	
	    //�Y�D�X�k���O�h��X���~�T���A�X�k�h��������ʧ@ 
		if(dowhat!=0&&dowhat!=1&&dowhat!=2){
			printf("Command does not exist!\n");
			//Ū���e�����O�T���h�l������ 
			printf("\n");
		}
		else if(dowhat==1){
			//�Ѻc 
			datain.clear();
			hptree.destroyTree();
			printf("\n");
			//���O��1�h�I�sOne()�������{�� 
			One(hptree,datain);
		}
		else if(dowhat==2){
			if(success){
				//���O��2�h�I�s�������{�� 
				//Two(graduate);
			}
			else{
				printf("Please choose command 1 first!\n");
				printf("\n");	
			}
			
		}
		/*
		else if(dowhat==3){
			if(success){
				//���O��3�h�I�sOne()�������{�� 
				Three(name);
			}
			else{
				printf("Please choose command 1 first!\n");
				printf("\n");
			}
			
		}
		*/
	}
	
	hptree.destroyTree();
	
	

}

