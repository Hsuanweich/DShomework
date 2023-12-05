//11127129�i�a�� 11127136�^��� 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <stack>
#include <vector>
#include <string>

#define MAX_LENGTH 100
static char num[MAX_LENGTH];//�s�ϥΪ̿�J���ɮ׸��X
static bool success = false;   //�����O�_���\�}���ɮ� 

struct Data{
	char id[10];         //
	char name[50];		
	char code[50];		 //
	char department[50];
	char sessioncode[5];
	char session[5];
	char degreecode[5];
	char degree[5];  	
	int student;
	int teacher;
	int graduate;
	int citycode;		 //
	char city[50];		 //
	char categorycode[5];//
	char category[5];	 //
};

class TreeNode {
public:
    Data data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Data data) : data(data), left(NULL), right(NULL) {}
	
};
 
class BinaryTree {
private:
    TreeNode* root;
    std::vector<TreeNode*> tree;

    // �̲��~�ͼƴ��J���
    TreeNode* insertg(TreeNode* node, Data value) {
        if (node == NULL) {
            return new TreeNode(value);
        }

        if (value.graduate < node->data.graduate) {
            node->left = insertg(node->left, value);
        } else if (value.graduate >= node->data.graduate) {
            node->right = insertg(node->right, value);
        }

        return node;
    }
    // �̦W�ٴ��J���
    TreeNode* insertn(TreeNode* node, Data value) {
        if (node == NULL) {
            return new TreeNode(value);
        }
        
        std::string temp=value.name;
        std::string com=node->data.name;
        

        if (temp.compare(com) < 0) {
            node->left = insertn(node->left, value);
        } else if (temp.compare(com) >= 0) {
            node->right = insertn(node->right, value);
        }

        return node;
    }

    // �e�ǹM�����
    void preorderTraversal(TreeNode* temp) const {
        if (temp != NULL) {
        	
            printf("%s\t%s\t%s\t%s\t%s %s\t%s %s\t%d\t%d\t%d\t%s\t%s\n", temp->data.id, temp->data.name, temp->data.code, temp->data.department,temp->data.sessioncode,
		   temp->data.session,temp->data.degreecode, temp->data.degree, temp->data.student, temp->data.teacher, temp->data.graduate, temp->data.city, temp->data.category);
            
			preorderTraversal(temp->left);
            preorderTraversal(temp->right);
        }
    }
    
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
    
    std::vector<Data> BiggerThanValue(TreeNode* node, int value,std::vector<Data> &list) const {
        if (node != NULL) {
            if (node->data.graduate >= value) {
                // ��e�`�I�Ψ�k�l�𬰭Կ�
                list.push_back(node->data);
                BiggerThanValue(node->left, value,list);
                BiggerThanValue(node->right, value,list);
            } else {
                // ���ܥk�l��
                BiggerThanValue(node->right, value,list);
            }
        }
        return list;
    }
    
    void Searchschool(TreeNode* node, char search[50],std::vector<Data> &list) {
        if (node != NULL) {
        	std::string com=node->data.name;
        	std::string x=search;
            if (x.compare(com) == 0) {
                // ��쵥����w�Ȫ��`�I
                list.push_back(node->data);
                Searchschool(node->right, search,list);
                
            } else if (x.compare(com) > 0) {
                // ���ܥk�l��
                Searchschool(node->right, search,list);
            } else {
                // ���ܥ��l��
                Searchschool(node->left, search,list);
            }
        }
    }

public:
    BinaryTree() : root(NULL) {}

    // ���J���
    void insertg(Data value) {
        root = insertg(root, value);
    }
    
    void insertn(Data value) {
        root = insertn(root, value);
    }

    // �e�ǹM�����
    void preorderTraversal() const {
        preorderTraversal(root);
    }
    
    int getHeight() const {
        return Height(root);
    }

    // �R����ʾ���
    void destroyTree() {
        destroyTree(root);
        root = NULL;
    }

    void BiggerThanValue(int value)  {
    	
    	std::vector<Data> list;
		list=BiggerThanValue(root,value,list);
		int i = 0;
		printf("Search results:\n");
		while(i<list.size()){
			
			
			Data temp=list[i];
			
			printf("[%d]\t%s\t%s\t%s %s\t%s %s\t%d\t%d\t%d\n",i+1 , temp.name, temp.department,temp.sessioncode,
		        temp.session, temp.degreecode,temp.degree, temp.student, temp.teacher, temp.graduate);
		    i++;
		}
		printf("\n");
		list.clear();
	}
	
	void Searchschool(char search[50]) {
		std::vector<Data> list;
        Searchschool(root, search,list);
        printf("Search results:\n");
        int i=0;
		while(i<list.size()){
			
			
			Data temp=list[i];
			
			printf("[%d]\t%s\t%s\t%s %s\t%s %s\t%d\t%d\t%d\n",i+1 , temp.name, temp.department,temp.sessioncode,
		        temp.session, temp.degreecode,temp.degree, temp.student, temp.teacher, temp.graduate);
		    i++;
		}
		printf("\n");
		list.clear();
    }
};

//Ū���ɮפ������ 
std::vector<Data> Read(std::vector<Data> datain,FILE *file){
	char line[1024]; 
	//�e�T�椣���n 
	fgets(line, sizeof(line), file);
	fgets(line, sizeof(line), file);
	fgets(line, sizeof(line), file);
	Data temp;
	
	int i=0;
    
    while (fscanf(file, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%s\t%s\t%s", &temp.id, &temp.name, &temp.code, &temp.department, 
		   &temp.sessioncode,&temp.session, &temp.degreecode,&temp.degree, &temp.student, &temp.teacher, &temp.graduate, &temp.citycode,&temp.city,
		   &temp.categorycode, &temp.category) != EOF) {
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
void One(BinaryTree &graduate,BinaryTree &name){           
	char trash;             //�s���ݭn������
	std::vector<Data> datain;
	
	//Ū�J�ɮ׸��X 
	printf("Input a file number:");
	scanf("%s",&num);
	//Ū���e��Ū���ɮ׸��X�T���h�l������

	datain=Set(datain);
	
	if(success){
		//�����\Ū���ɮ� 
		int i = 0;
		
		while(i<datain.size()){
			graduate.insertg(datain[i]);
			i++;
		}
		
		//graduate.preorderTraversal();
	
		i=0;
		while(i<datain.size()){
			name.insertn(datain[i]);
			i++;
		}
	     
		printf("Tree height {School name} = %d\n",name.getHeight());
		printf("Tree height {Number of graduates} = %d\n",graduate.getHeight());
		printf("\n");
		
		
	}
	//�Ѻc 
	datain.clear();
}

//���ȤG 
void Two(BinaryTree &graduate){ 
	int x;
	
	if(success){
		//��Ū���ɮ� 
		printf("Input the number of graduates:");
		scanf("%d",&x);
		
		graduate.BiggerThanValue(x);
	
		
		
	}
	
}

void Three(BinaryTree &name){ 
	char search[50];
	
	if(success){
		//��Ū���ɮ� 
		printf("Input the number of graduates:");
		scanf("%s",&search);
		
		name.Searchschool(search);
	
	}
	
}

int main() {
	BinaryTree graduate;
	BinaryTree name;
	char trash;      //�s���ݭn������
	int dowhat=-1;//�s�����O
	   
	//�����a�߰ݭn���檺�ʧ@�����J0�h�X 
	while(dowhat!=0){
		//�L�X������Ū�����O 
		printf("*** University Graduate Information System ***\n");
    	printf("* 0. Quit                                    *\n");
    	printf("* 1. Create Two Binary Search Trees          *\n");
    	printf("* 2. Search by Number of Graduates           *\n");
    	printf("* 3. Search by School Name                   *\n");
    	printf("**********************************************\n");
    	printf("Input a command(0, 1-4):");
		scanf("%d",&dowhat);
		
	
	    //�Y�D�X�k���O�h��X���~�T���A�X�k�h��������ʧ@ 
		if(dowhat!=0&&dowhat!=1&&dowhat!=2&&dowhat!=3){
			printf("Command does not exist!\n");
			//Ū���e�����O�T���h�l������ 
			printf("\n");
		}
		else if(dowhat==1){
			graduate.destroyTree();
			name.destroyTree();
			printf("\n");
			//���O��1�h�I�sOne()�������{�� 
			One(graduate,name);
		}
		else if(dowhat==2){
			if(success){
				//���O��2�h�I�s�������{�� 
				Two(graduate);
			}
			else{
				printf("Please choose command 1 first!\n");
				printf("\n");	
			}
			
		}
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
	}
	
	graduate.destroyTree();
	name.destroyTree();
	
	

}

