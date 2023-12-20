//11127129張軒偉 11127136彭晨維 
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
static char num[MAX_LENGTH];//存使用者輸入的檔案號碼
static bool success = false;   //紀錄是否成功開啟檔案 
static bool find = false;      //紀錄是否找到同名資料 

//資料結構 
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

//樹節點 
class TreeNode {
public:
    Datatree data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Datatree data) : data(data), left(NULL), right(NULL) {}
	
};
 
//整棵樹 
class BinaryTree {
private:
    TreeNode* root;
    std::vector<TreeNode*> tree;

    // 依畢業生數插入函數
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

    // 前序遍歷函數印出 
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
    
    
    //私有的求樹高 
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
    
public:
	bool containsDigits(char *str) {
	    bool x=true;
		while (*str) {
		    if (!isdigit(*str)) {
		       x=false ;// 包含非數字
		    }
		    str++;
		}
		return x; // 不包含數字
	}
    BinaryTree() : root(NULL) {}

    // 插入函數(兩種 ) 
    void insert(Data value,int index) {
        root = insert(root, value, index);
	}

    // 前序遍歷函數
    void preorderTraversal() const {
        preorderTraversal(root);
    }
    
    //公開求數高 
    int getHeight() const {
        return Height(root);
    }

    // 刪除整棵樹函數
    void destroyTree() {
        destroyTree(root);
        root = NULL;
    }
    
    //公開的找子樹中最小的節點(最左 
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
	       x=false ;// 包含非數字
	    }
	    str++;
	}
	return x; // 不包含數字
}
//檢查字串是否為字母 
int isAllAlpha(char *str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0; // 不是英文字母
        }
        str++;
    }
    return 1; // 是英文字母
}
//檢查字串是否為數字 
bool isAllDigits(char *str) {
    	bool x=true;
	    while (*str) {
	        if (!isdigit(*str)) {
	            x=false ;// 包含非數字
	        }
	        str++;
	    }
	    return x; 
}

//讀取檔案中的資料 
std::vector<Data> Read(std::vector<Data> datain,FILE *file){
	char line[1024]; 
	//前1行不重要 
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
void One(BinaryTree &hptree,std::vector<Data> &datain){           
	char trash;             //存不需要的換行
	int width = 2; 
	int width3 = 3; 
	//讀入檔案號碼 
	printf("Input a file number[0: quit]:");
	scanf("%s",&num);
	
	std::string com=num;
	std::string x="0";
	if(com.compare(x) == 0){
		return ;
	}

	datain=Set(datain);
	
	if(success){
		//有成功讀到檔案 
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
//任務二 
//找比輸入大的畢業生人數 
void Two(BinaryTree &graduate){ 
	char search[100];
	int x;
	
	if(success){
		//有讀到檔案 
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
//找同輸入的學校 
void Three(BinaryTree &name){ 
	char search[100];
	
	if(success){
		//有讀到檔案 
		printf("Input a school name:");
		scanf("%s",&search);
		
		name.Searchschool(search);
	
	}
	
}

*/
int main() {
	BinaryTree hptree;
	std::vector<Data> datain;
	char trash;      //存不需要的換行
	int dowhat=-1;//存取指令
	   
	//不停地詢問要執行的動作直到輸入0退出 
	while(dowhat!=0){
		//印出介面並讀取指令 
		printf("***** Pokemon Tree and Heap *****\n");
    	printf("* 0. QUIT                       *\n");
    	printf("* 1. Read a file to build BST   *\n");
    	printf("* 2. Transform it into Max Heap *\n");
    	printf("*********************************\n");
    	printf("Input a choice(0, 1, 2):");
		scanf("%d",&dowhat);
		
	
	    //若非合法指令則輸出錯誤訊息，合法則執行相應動作 
		if(dowhat!=0&&dowhat!=1&&dowhat!=2){
			printf("Command does not exist!\n");
			//讀取前面指令訊息多餘的換行 
			printf("\n");
		}
		else if(dowhat==1){
			//解構 
			datain.clear();
			hptree.destroyTree();
			printf("\n");
			//指令為1則呼叫One()執行後續程序 
			One(hptree,datain);
		}
		else if(dowhat==2){
			if(success){
				//指令為2則呼叫執行後續程序 
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
				//指令為3則呼叫One()執行後續程序 
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

