//11127129張軒偉 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//堆疊的結構
//字元 
struct Stack {
  	char data;
 	struct Stack* next;
};

//數字 
struct Stack2 {
   	int data;
   	struct Stack2* next;
};

//字串 
struct Token {
   	char data[10];
   	struct Token* next;
};

//資料結構 
class StackC{
private:
	
	Token* headt=NULL;  //Token串列的頭 
	Stack* heads=NULL;  //char堆疊最上方
	Stack2* heads2=NULL;//int堆疊最上方
public:
	
	//取得和設定 private內容 
	Token* GetTh(){
		return headt;
	}
	void SetTh(Token *head){
		headt=head;
	}
	
	Stack* GetSh(){
		return heads;
	}
	void SetSh(Stack* top){
		heads=top;
	}
	
	Stack2* GetS2h(){
		return heads2;
	}
	void SetS2h(Stack2* top){
		heads2=top;
	}
	
	//將內容加入char堆疊最上方 
	Stack* push(Stack* top, char data) {
    	Stack* newNode = new Stack;
    	newNode->data = data;
    	newNode->next = top;
		top = newNode;
		return top;
	}
	
	//丟出char堆疊頂部的內容
	char pop(Stack** top) {
   	 	if (*top == NULL) {
        	return '\0'; // 堆疊沒東西回傳空字元 
    	}
    	Stack* temp = *top;
    	*top = temp->next;
    	char data = temp->data;
    	delete temp;     //清除已取出內容的結構 
    	return data;     //回傳取出的內容 
	}
	
	//加入int堆疊最上方 
	void push2(Stack2** top, int data) {
    	Stack2* newNode = new Stack2;
    	newNode->data = data;
    	newNode->next = *top;
    	*top = newNode;
	}

	//彈出int堆疊頂部的內容
	int pop2(Stack2** top) {
    	if (*top == NULL) {
    	    return 0; // 堆疊為空
    	}
    	Stack2* temp = *top;
    	*top = temp->next;
    	int data = temp->data;
    	delete temp; //刪除已彈出的資料 
    	return data; //回傳取出的內容 
	}
	
	//釋放記憶體 
	void free(){
		Token* temp1=NULL;   
		Stack* temp2=NULL;  
		Stack2* temp3=NULL;
		
		if(headt!=NULL){
			temp1=headt;
			while(headt->next!=NULL){
				headt=headt->next;
				delete temp1;
				temp1=headt;
			}
			delete temp1;
		}
		
		if(heads!=NULL){
			temp2=heads;
			while(heads->next!=NULL){
				heads=heads->next;
				delete temp2;
				temp2=heads;
			}
			delete temp2;
		}
		
		if(heads2!=NULL){
			temp3=heads2;
			while(heads2->next!=NULL){
				heads2=heads2->next;
				delete temp3;
				temp3=heads2;
			}
			delete temp3;
		}
		
	}
};

//檢查中序四則運算是否合法，error用於儲存錯誤字元或括號 
int Check( char* expression, char &error,StackC heap) {
	
    Stack* op = heap.GetSh();  //存operator的串列的頭 
	
	//處理資料直到字串尾
    for (int i = 0; expression[i] != '\0'; i++) {
        char temp = expression[i]; //暫存第i個字元 

        if (temp == '('&&expression[i + 1] != ')') {
            op=heap.push(op, temp); //將(堆入串列 
        } 
		else if (temp == ')') {
			//取出串列第一個( 
            char topChar = heap.pop(&op);
            if (topChar != '(') {
            	//沒有取得( 
            	error=')';
                return 2; // 括號不成對
            }
            //先將後續空格跳過
            while(expression[i + 1]==' '){
            	i++;
			}
            if(isdigit(expression[i + 1])){
            	error='1';
            	return 3; //)後不能直接是數字 
			}
        } 
        else if (temp == '('&&expression[i + 1] == ')') {
        	error='2';
            return 3;//括號不應該以()出現 
        }
        else if(temp == ' '){
        	//是空格跳過
        	while(expression[i]==' '){
            	i++;
			}
			i--;
		}
		else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
            if (i == 0 || expression[i - 1] == '(' || expression[i - 1] == '+' || expression[i - 1] == '-' || expression[i - 1] == '*' || expression[i - 1] == '/') {
                error='2';
				return 3; // 運算符前面不應該是左括號或其他運算符
            }
            
            //先將後續空格跳過 
            while(expression[i + 1]==' '){
            	i++;
			}
            if (expression[i + 1] == '\0' || expression[i + 1] == '+' || expression[i + 1] == '-' || expression[i + 1] == '*' || expression[i + 1] == '/') {
                error='3';
				return 3; // 運算符後面不應該是其他運算符
            }
            if (expression[i + 1] == ')'){
            	//取出串列第一個(
            	char topChar = heap.pop(&op);
            	if (topChar != '(') {
            		//沒有取得( 
            		error=')';
                	return 2; // 括號不成對
            	}
            	error='2';
            	return 3;// 運算符後面不應該是右括號
			}
        } 
		else if (isdigit(temp)) {
            // 檢查是否是多位數的數字
            int j = i + 1;
            while (isdigit(expression[j])) {
                j++;
            }
            i = j - 1;
        } 
		else {
			error=temp;
            return 1; // 不是合法字符
        }
    }

    // 檢查是否有未匹配的括號
    while (op != NULL) {
        char topChar = heap.pop(&op);
        if (topChar == '(') {
        	error='(';
            return 2; // 還有左括號未匹配
        }
    }

    return 0; // 運算式合法
}

//比較運算子的優先順序，回傳數字越大越優先 
int DoFirst( char ch ) {
    if (ch == '+' || ch == '-') {
        return 1;// +-不優先 
    } 
	else if (ch == '*' || ch == '/') {
        return 2;// */優先 
    }
    return 0; // 其他字元 
}

//轉換中序式為後序式
Token *Postfix( char* infix,StackC heap ) {
    struct Stack* op = heap.GetSh();  //存operator的串列的頭
    Token *head=new Token;           //存所有Token的串列的頭 
    heap.SetTh(head);                //設定 Token的串列的頭 
    
    Token *cur = heap.GetTh();        //存目前的Token
    Token *pre = NULL;        //存前一個的Token

    //處理資料直到字串尾 
    for (int i = 0; infix[i] != '\0'; i++) {
        char temp = infix[i]; //暫存第i個字元 

        if (temp == '(') {
            op=heap.push(op,temp); //將(堆入串列 
        } 
		else if (temp == ')') {
			//若是括號不成對 
			
            while (op != NULL && op->data != '(') {
            	cur->data[0]=heap.pop(&op);
            	cur->data[1]='\0';
            	cur->next=new Token;
            	pre=cur;
                cur=cur->next;
            }
            
            heap.pop(&op); //取出operator串列第一個字元 
        } 
        else if(temp == ' '){
			//是空格不做事 
		}
		else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
            while (op != NULL && op->data != '(' && DoFirst(temp) <= DoFirst(op->data)) {
            	//比較運算優先順序
				//優先級高的先加入 
                cur->data[0] = heap.pop(&op);
                cur->data[1]='\0';
                cur->next=new Token;
                pre=cur;
                cur=cur->next;
            }
            op=heap.push(op, temp);//將運算子堆入operator串列
        } 
		else if (isdigit(temp)) {
			//多位數字儲存，中間有空白跳過 
			int x=1;
			cur->data[0]=temp;
            while (isdigit(infix[i + 1])||infix[i + 1]==' ') {
                i++;
                if(infix[i]!=' '){
                	cur->data[x]=infix[i];
                	x++;
				}
                
            }
            cur->data[x]='\0';
            cur->next=new Token;
            pre=cur;
            cur=cur->next;
        }
    }

    while (op != NULL) {
    	//將剩下的運算子依序加入 
        cur->data[0] = heap.pop(&op);
        cur->data[1]='\0';
        cur->next=new Token;
        pre=cur;
        cur=cur->next;
    }

    delete cur;
    pre->next=NULL; //將串列尾設為NULL 
    return heap.GetTh();

}

int Count(Token *postfix,char &error,StackC heap) {
    Stack2* op = heap.GetS2h(); //取得堆疊的top 

    Token* cur = postfix;
    while (cur != NULL) {
        if (isdigit(cur->data[0])) {
        	heap.push2(&op, atoi(cur->data)); // 轉換字符為int並存入堆疊 
            
        } 
		else if (cur->data[0] != ' ') { // 忽略空格
            // 遇到運算符
            int operand2 = heap.pop2(&op);
            int operand1 = heap.pop2(&op);
            int result = 0.0;
            
            // 根據運算符執行運算
            switch (cur->data[0]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                	//除數為0特殊處理 
                	if(operand2==0){
                		error='0';
                		return heap.pop2(&op);
					}
                    result = operand1 / operand2;
                    break;
            }
			
            heap.push2(&op, result);
        }
        cur = cur->next;
    }
    
    return heap.pop2(&op); 
}

//讀取方程式直到換行 
void Read(char *input) {
		char ch;
		int i=0;
		scanf("%c", &ch);
		while(ch!='\n'){
			input[i]=ch;
			i++;
			scanf("%c", &ch);
		}
		input[i]='\0';
}

void One() {
	StackC heap;
    char input[1000]; //存取讀入的運算式 
    char error;
    char error0='\0';
    //讀入方程式 
	printf("Input an infix expression:");
	Read(input);
	
    if (Check(input,error,heap)==0) {
    	//函式完全合法 
    	printf("It is a legitimate infix expression.\n");
    	
        Token *postfix=NULL;              //存後序式鏈結的頭 
        postfix=Postfix(input,heap);  //呼叫函式取得後序式 
        int result=Count(postfix,error0,heap);
        //輸出後序式並以，分隔 ，順便釋放記憶體 
        printf("Postfix expression: ");
        Token * cur=postfix;   
        Token * pre=NULL;
        printf("%s",cur->data);
        pre=cur;
        cur=cur->next;
        delete pre;
        while(cur!=NULL){
        	printf(", ");
        	printf("%s",cur->data);
        	pre=cur;
        	cur=cur->next;
        	delete pre;
		}
		printf("\n");
		if(error0=='0'){
			printf("### Error: Divided by ZERO! ###\n");
			printf("### It cannot be successfully evaluated! ###\n");
		}
		else{
			printf("Answer: %d\n",result);
		}
		
    } 
	else if(Check(input,error,heap)==1){
		//錯誤訊息1 
        printf("Error 1: %c is not a legitimate character.\n",error);
    }
    else if(Check(input,error,heap)==2){
    	//錯誤訊息2-(
    	if(error=='('){
    		printf("Error 2: there is one extra open parenthesis.\n");
		}
		//錯誤訊息2-)
        else if(error==')'){
        	printf("Error 2: there is one extra close parenthesis.\n");
		}
    }
    else if(Check(input,error,heap)==3){
    	//錯誤訊息3-1
    	if(error=='1'){
    		printf("Error 3: there is one extra operand.\n");
		}
		//錯誤訊息3-2
		else if(error=='2'){
			printf("Error 3: it is not infix in the parentheses.\n");
	 	}
	 	//錯誤訊息3-3
	 	else if(error=='3'){
	 		printf("Error 3: there is one extra operator.\n");
	 	}
        
    }
    
    heap.free(); // 釋放heap所有堆疊和串列的記憶體 

}

int main() {
	char trash;      //存不需要的換行
	char dowhat='\0';//存取指令
	
	//不停地詢問要執行的動作直到輸入0退出 
	while(dowhat!='0'){
		//印出介面並讀取指令 
		printf("* Arithmetic Expression Evaluator *\n");
    	printf("* 0. QUIT                         *\n");
    	printf("* 1. Infix2postfix Transformation *\n");
    	printf("***********************************\n");
    	printf("Input a command(0, 1):");
		scanf("%c",&dowhat);
		//讀指令前的換行和空白直到出現字元 
		while(dowhat=='\n'||dowhat==' '){
	    	scanf("%c",&dowhat);
		}
		//讀指令後換行前的非必要字元
		scanf("%c",&trash);
		while(dowhat!='\n'&&trash!='\n'){
			scanf("%c",&trash);	
		}
		printf("\n");
		
	    //若非合法指令則輸出錯誤訊息，合法則執行相應動作 
		if(dowhat!='0'&&dowhat!='1'){
			printf("Command does not exist!\n");
			printf("\n");
		}
		else if(dowhat=='1'){
			//指令為1則呼叫One()執行後續程序 
			One();
			printf("\n");
		}
	}
	

}
