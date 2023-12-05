//11127129張軒偉 11127136彭晨維 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <stack>
#include <vector>
#include <string>

#define MAX_LENGTH 100
static char num[MAX_LENGTH];//存使用者輸入的檔案號碼
static bool success = false;   //紀錄是否成功開啟檔案 

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

    // 依畢業生數插入函數
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
    // 依名稱插入函數
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

    // 前序遍歷函數
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

        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight); //左右取最大+1 
    }

    // 刪除整棵樹函數
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
                // 當前節點及其右子樹為候選
                list.push_back(node->data);
                BiggerThanValue(node->left, value,list);
                BiggerThanValue(node->right, value,list);
            } else {
                // 移至右子樹
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
                // 找到等於指定值的節點
                list.push_back(node->data);
                Searchschool(node->right, search,list);
                
            } else if (x.compare(com) > 0) {
                // 移至右子樹
                Searchschool(node->right, search,list);
            } else {
                // 移至左子樹
                Searchschool(node->left, search,list);
            }
        }
    }

public:
    BinaryTree() : root(NULL) {}

    // 插入函數
    void insertg(Data value) {
        root = insertg(root, value);
    }
    
    void insertn(Data value) {
        root = insertn(root, value);
    }

    // 前序遍歷函數
    void preorderTraversal() const {
        preorderTraversal(root);
    }
    
    int getHeight() const {
        return Height(root);
    }

    // 刪除整棵樹函數
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

//讀取檔案中的資料 
std::vector<Data> Read(std::vector<Data> datain,FILE *file){
	char line[1024]; 
	//前三行不重要 
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

//開啟input檔案，成功則呼叫讀取 
std::vector<Data> Set(std::vector<Data> datain){ 
    char fname[200]="input";//存整個檔案的名字
	
	
	//串接檔名 
	strcat(fname,num);
	strcat(fname,".txt");
	//開啟相應文件 
	FILE *file;
	file = fopen(fname, "rb"); // 以唯讀模式打開文件
	if (file == NULL) {
		//找不到此文件則輸出錯誤訊息 
    	printf("### input%s.txt does not exist! ###\n",num);
    	printf("\n");
    	success=false;
	}
	else{ 
		success=true;
		datain=Read(datain,file);
		//設定完成關閉文件 
		fclose(file);
	}
	
	return datain; //將設定好的回傳 
}

//任務一 
void One(BinaryTree &graduate,BinaryTree &name){           
	char trash;             //存不需要的換行
	std::vector<Data> datain;
	
	//讀入檔案號碼 
	printf("Input a file number:");
	scanf("%s",&num);
	//讀取前面讀取檔案號碼訊息多餘的換行

	datain=Set(datain);
	
	if(success){
		//有成功讀到檔案 
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
	//解構 
	datain.clear();
}

//任務二 
void Two(BinaryTree &graduate){ 
	int x;
	
	if(success){
		//有讀到檔案 
		printf("Input the number of graduates:");
		scanf("%d",&x);
		
		graduate.BiggerThanValue(x);
	
		
		
	}
	
}

void Three(BinaryTree &name){ 
	char search[50];
	
	if(success){
		//有讀到檔案 
		printf("Input the number of graduates:");
		scanf("%s",&search);
		
		name.Searchschool(search);
	
	}
	
}

int main() {
	BinaryTree graduate;
	BinaryTree name;
	char trash;      //存不需要的換行
	int dowhat=-1;//存取指令
	   
	//不停地詢問要執行的動作直到輸入0退出 
	while(dowhat!=0){
		//印出介面並讀取指令 
		printf("*** University Graduate Information System ***\n");
    	printf("* 0. Quit                                    *\n");
    	printf("* 1. Create Two Binary Search Trees          *\n");
    	printf("* 2. Search by Number of Graduates           *\n");
    	printf("* 3. Search by School Name                   *\n");
    	printf("**********************************************\n");
    	printf("Input a command(0, 1-4):");
		scanf("%d",&dowhat);
		
	
	    //若非合法指令則輸出錯誤訊息，合法則執行相應動作 
		if(dowhat!=0&&dowhat!=1&&dowhat!=2&&dowhat!=3){
			printf("Command does not exist!\n");
			//讀取前面指令訊息多餘的換行 
			printf("\n");
		}
		else if(dowhat==1){
			graduate.destroyTree();
			name.destroyTree();
			printf("\n");
			//指令為1則呼叫One()執行後續程序 
			One(graduate,name);
		}
		else if(dowhat==2){
			if(success){
				//指令為2則呼叫執行後續程序 
				Two(graduate);
			}
			else{
				printf("Please choose command 1 first!\n");
				printf("\n");	
			}
			
		}
		else if(dowhat==3){
			if(success){
				//指令為3則呼叫One()執行後續程序 
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

