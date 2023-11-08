//11127129�i�a�� 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//���|�����c
//�r�� 
struct Stack {
  	char data;
 	struct Stack* next;
};

//�Ʀr 
struct Stack2 {
   	int data;
   	struct Stack2* next;
};

//�r�� 
struct Token {
   	char data[10];
   	struct Token* next;
};

//��Ƶ��c 
class StackC{
private:
	
	Token* headt=NULL;  //Token��C���Y 
	Stack* heads=NULL;  //char���|�̤W��
	Stack2* heads2=NULL;//int���|�̤W��
public:
	
	//���o�M�]�w private���e 
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
	
	//�N���e�[�Jchar���|�̤W�� 
	Stack* push(Stack* top, char data) {
    	Stack* newNode = new Stack;
    	newNode->data = data;
    	newNode->next = top;
		top = newNode;
		return top;
	}
	
	//��Xchar���|���������e
	char pop(Stack** top) {
   	 	if (*top == NULL) {
        	return '\0'; // ���|�S�F��^�ǪŦr�� 
    	}
    	Stack* temp = *top;
    	*top = temp->next;
    	char data = temp->data;
    	delete temp;     //�M���w���X���e�����c 
    	return data;     //�^�Ǩ��X�����e 
	}
	
	//�[�Jint���|�̤W�� 
	void push2(Stack2** top, int data) {
    	Stack2* newNode = new Stack2;
    	newNode->data = data;
    	newNode->next = *top;
    	*top = newNode;
	}

	//�u�Xint���|���������e
	int pop2(Stack2** top) {
    	if (*top == NULL) {
    	    return 0; // ���|����
    	}
    	Stack2* temp = *top;
    	*top = temp->next;
    	int data = temp->data;
    	delete temp; //�R���w�u�X����� 
    	return data; //�^�Ǩ��X�����e 
	}
	
	//����O���� 
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

//�ˬd���ǥ|�h�B��O�_�X�k�Aerror�Ω��x�s���~�r���άA�� 
int Check( char* expression, char &error,StackC heap) {
	
    Stack* op = heap.GetSh();  //�soperator����C���Y 
	
	//�B�z��ƪ���r���
    for (int i = 0; expression[i] != '\0'; i++) {
        char temp = expression[i]; //�Ȧs��i�Ӧr�� 

        if (temp == '('&&expression[i + 1] != ')') {
            op=heap.push(op, temp); //�N(��J��C 
        } 
		else if (temp == ')') {
			//���X��C�Ĥ@��( 
            char topChar = heap.pop(&op);
            if (topChar != '(') {
            	//�S�����o( 
            	error=')';
                return 2; // �A��������
            }
            //���N����Ů���L
            while(expression[i + 1]==' '){
            	i++;
			}
            if(isdigit(expression[i + 1])){
            	error='1';
            	return 3; //)�ᤣ�ઽ���O�Ʀr 
			}
        } 
        else if (temp == '('&&expression[i + 1] == ')') {
        	error='2';
            return 3;//�A�������ӥH()�X�{ 
        }
        else if(temp == ' '){
        	//�O�Ů���L
        	while(expression[i]==' '){
            	i++;
			}
			i--;
		}
		else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
            if (i == 0 || expression[i - 1] == '(' || expression[i - 1] == '+' || expression[i - 1] == '-' || expression[i - 1] == '*' || expression[i - 1] == '/') {
                error='2';
				return 3; // �B��ūe�������ӬO���A���Ψ�L�B���
            }
            
            //���N����Ů���L 
            while(expression[i + 1]==' '){
            	i++;
			}
            if (expression[i + 1] == '\0' || expression[i + 1] == '+' || expression[i + 1] == '-' || expression[i + 1] == '*' || expression[i + 1] == '/') {
                error='3';
				return 3; // �B��ū᭱�����ӬO��L�B���
            }
            if (expression[i + 1] == ')'){
            	//���X��C�Ĥ@��(
            	char topChar = heap.pop(&op);
            	if (topChar != '(') {
            		//�S�����o( 
            		error=')';
                	return 2; // �A��������
            	}
            	error='2';
            	return 3;// �B��ū᭱�����ӬO�k�A��
			}
        } 
		else if (isdigit(temp)) {
            // �ˬd�O�_�O�h��ƪ��Ʀr
            int j = i + 1;
            while (isdigit(expression[j])) {
                j++;
            }
            i = j - 1;
        } 
		else {
			error=temp;
            return 1; // ���O�X�k�r��
        }
    }

    // �ˬd�O�_�����ǰt���A��
    while (op != NULL) {
        char topChar = heap.pop(&op);
        if (topChar == '(') {
        	error='(';
            return 2; // �٦����A�����ǰt
        }
    }

    return 0; // �B�⦡�X�k
}

//����B��l���u�����ǡA�^�ǼƦr�V�j�V�u�� 
int DoFirst( char ch ) {
    if (ch == '+' || ch == '-') {
        return 1;// +-���u�� 
    } 
	else if (ch == '*' || ch == '/') {
        return 2;// */�u�� 
    }
    return 0; // ��L�r�� 
}

//�ഫ���Ǧ�����Ǧ�
Token *Postfix( char* infix,StackC heap ) {
    struct Stack* op = heap.GetSh();  //�soperator����C���Y
    Token *head=new Token;           //�s�Ҧ�Token����C���Y 
    heap.SetTh(head);                //�]�w Token����C���Y 
    
    Token *cur = heap.GetTh();        //�s�ثe��Token
    Token *pre = NULL;        //�s�e�@�Ӫ�Token

    //�B�z��ƪ���r��� 
    for (int i = 0; infix[i] != '\0'; i++) {
        char temp = infix[i]; //�Ȧs��i�Ӧr�� 

        if (temp == '(') {
            op=heap.push(op,temp); //�N(��J��C 
        } 
		else if (temp == ')') {
			//�Y�O�A�������� 
			
            while (op != NULL && op->data != '(') {
            	cur->data[0]=heap.pop(&op);
            	cur->data[1]='\0';
            	cur->next=new Token;
            	pre=cur;
                cur=cur->next;
            }
            
            heap.pop(&op); //���Xoperator��C�Ĥ@�Ӧr�� 
        } 
        else if(temp == ' '){
			//�O�Ů椣���� 
		}
		else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
            while (op != NULL && op->data != '(' && DoFirst(temp) <= DoFirst(op->data)) {
            	//����B���u������
				//�u���Ű������[�J 
                cur->data[0] = heap.pop(&op);
                cur->data[1]='\0';
                cur->next=new Token;
                pre=cur;
                cur=cur->next;
            }
            op=heap.push(op, temp);//�N�B��l��Joperator��C
        } 
		else if (isdigit(temp)) {
			//�h��Ʀr�x�s�A�������ťո��L 
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
    	//�N�ѤU���B��l�̧ǥ[�J 
        cur->data[0] = heap.pop(&op);
        cur->data[1]='\0';
        cur->next=new Token;
        pre=cur;
        cur=cur->next;
    }

    delete cur;
    pre->next=NULL; //�N��C���]��NULL 
    return heap.GetTh();

}

int Count(Token *postfix,char &error,StackC heap) {
    Stack2* op = heap.GetS2h(); //���o���|��top 

    Token* cur = postfix;
    while (cur != NULL) {
        if (isdigit(cur->data[0])) {
        	heap.push2(&op, atoi(cur->data)); // �ഫ�r�Ŭ�int�æs�J���| 
            
        } 
		else if (cur->data[0] != ' ') { // �����Ů�
            // �J��B���
            int operand2 = heap.pop2(&op);
            int operand1 = heap.pop2(&op);
            int result = 0.0;
            
            // �ھڹB��Ű���B��
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
                	//���Ƭ�0�S��B�z 
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

//Ū����{�����촫�� 
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
    char input[1000]; //�s��Ū�J���B�⦡ 
    char error;
    char error0='\0';
    //Ū�J��{�� 
	printf("Input an infix expression:");
	Read(input);
	
    if (Check(input,error,heap)==0) {
    	//�禡�����X�k 
    	printf("It is a legitimate infix expression.\n");
    	
        Token *postfix=NULL;              //�s��Ǧ��쵲���Y 
        postfix=Postfix(input,heap);  //�I�s�禡���o��Ǧ� 
        int result=Count(postfix,error0,heap);
        //��X��Ǧ��åH�A���j �A���K����O���� 
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
		//���~�T��1 
        printf("Error 1: %c is not a legitimate character.\n",error);
    }
    else if(Check(input,error,heap)==2){
    	//���~�T��2-(
    	if(error=='('){
    		printf("Error 2: there is one extra open parenthesis.\n");
		}
		//���~�T��2-)
        else if(error==')'){
        	printf("Error 2: there is one extra close parenthesis.\n");
		}
    }
    else if(Check(input,error,heap)==3){
    	//���~�T��3-1
    	if(error=='1'){
    		printf("Error 3: there is one extra operand.\n");
		}
		//���~�T��3-2
		else if(error=='2'){
			printf("Error 3: it is not infix in the parentheses.\n");
	 	}
	 	//���~�T��3-3
	 	else if(error=='3'){
	 		printf("Error 3: there is one extra operator.\n");
	 	}
        
    }
    
    heap.free(); // ����heap�Ҧ����|�M��C���O���� 

}

int main() {
	char trash;      //�s���ݭn������
	char dowhat='\0';//�s�����O
	
	//�����a�߰ݭn���檺�ʧ@�����J0�h�X 
	while(dowhat!='0'){
		//�L�X������Ū�����O 
		printf("* Arithmetic Expression Evaluator *\n");
    	printf("* 0. QUIT                         *\n");
    	printf("* 1. Infix2postfix Transformation *\n");
    	printf("***********************************\n");
    	printf("Input a command(0, 1):");
		scanf("%c",&dowhat);
		//Ū���O�e������M�ťժ���X�{�r�� 
		while(dowhat=='\n'||dowhat==' '){
	    	scanf("%c",&dowhat);
		}
		//Ū���O�ᴫ��e���D���n�r��
		scanf("%c",&trash);
		while(dowhat!='\n'&&trash!='\n'){
			scanf("%c",&trash);	
		}
		printf("\n");
		
	    //�Y�D�X�k���O�h��X���~�T���A�X�k�h��������ʧ@ 
		if(dowhat!='0'&&dowhat!='1'){
			printf("Command does not exist!\n");
			printf("\n");
		}
		else if(dowhat=='1'){
			//���O��1�h�I�sOne()�������{�� 
			One();
			printf("\n");
		}
	}
	

}
