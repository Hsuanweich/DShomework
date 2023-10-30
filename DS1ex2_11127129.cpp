#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//���|�����c
struct Stack {
    char data;
    struct Stack* next;
};

struct Stack2 {
    double data;
    struct Stack2* next;
};

struct Token {
    char data[10];
    struct Token* next;
};

//�N���e�[�J���|�̤W�� 
Stack* push(Stack* top, char data) {
    Stack* newNode = new Stack;
    newNode->data = data;
    newNode->next = top;
	top = newNode;
	return top;
}

//��X���|���������e
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

//�ˬd���ǥ|�h�B��O�_�X�k�Aerror�Ω��x�s���~�r���άA�� 
int Check( char* expression, char &error) {
    struct Stack* op = NULL;  //�soperator����C���Y 

	//�B�z��ƪ���r���
    for (int i = 0; expression[i] != '\0'; i++) {
        char temp = expression[i]; //�Ȧs��i�Ӧr�� 

        if (temp == '('&&expression[i + 1] != ')') {
            op=push(op, temp); //�N(��J��C 
        } 
		else if (temp == ')') {
			//���X��C�Ĥ@��( 
            char topChar = pop(&op);
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
            	char topChar = pop(&op);
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
        char topChar = pop(&op);
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
Token *Postfix( char* infix, Token *head) {
    struct Stack* op = NULL;  //�soperator����C���Y
    head=new Token;           //�s�Ҧ�Token����C���Y 
    Token *cur = head;        //�s�ثe��Token
    Token *pre = NULL;        //�s�e�@�Ӫ�Token

    //�B�z��ƪ���r��� 
    for (int i = 0; infix[i] != '\0'; i++) {
        char temp = infix[i]; //�Ȧs��i�Ӧr�� 

        if (temp == '(') {
            op=push(op,temp); //�N(��J��C 
        } 
		else if (temp == ')') {
			//�Y�O�A�������� 
			
            while (op != NULL && op->data != '(') {
            	cur->data[0]=pop(&op);
            	cur->data[1]='\0';
            	cur->next=new Token;
            	pre=cur;
                cur=cur->next;
            }
            
            pop(&op); //���Xoperator��C�Ĥ@�Ӧr�� 
        } 
        else if(temp == ' '){
			//�O�Ů椣���� 
		}
		else if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
            while (op != NULL && op->data != '(' && DoFirst(temp) <= DoFirst(op->data)) {
            	//����B���u������
				//�u���Ű������[�J 
                cur->data[0] = pop(&op);
                cur->data[1]='\0';
                cur->next=new Token;
                pre=cur;
                cur=cur->next;
            }
            op=push(op, temp);//�N�B��l��Joperator��C
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
        cur->data[0] = pop(&op);
        cur->data[1]='\0';
        cur->next=new Token;
        pre=cur;
        cur=cur->next;
    }

    delete cur;
    pre->next=NULL; //�N��C���]��NULL 
    return head;

}

//�[�J�B�I��
void push2(Stack2** top, double data) {
    Stack2* newNode = new Stack2;
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

//�u�X���|�������B�I��
double pop2(Stack2** top) {
    if (*top == NULL) {
        return 0; // ���|����
    }
    Stack2* temp = *top;
    *top = temp->next;
    double data = temp->data;
    delete temp;
    return data;
}

double Count(Token *postfix,char &error) {
    Stack2* op = NULL;

    Token* cur = postfix;
    while (cur != NULL) {
        if (isdigit(cur->data[0])) {
        	push2(&op, atof(cur->data)); // �ഫ�r�Ŭ�float
            
        } 
		else if (cur->data[0] != ' ') { // �����Ů�
            // �J��B���
            double operand2 = pop2(&op);
            double operand1 = pop2(&op);
            double result = 0.0;
            
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
                	if(operand2==0){
                		printf("error\n");
                		error='0';
                		return pop2(&op);
					}
                    result = operand1 / operand2;
                    break;
            }
			
            push2(&op, result);
        }
        cur = cur->next;
    }
    
    return pop2(&op); 
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
	
    char input[1000]; //�s��Ū�J���B�⦡ 
    char error;
    char error0;
    //Ū�J��{�� 
	printf("Input an infix expression:");
	Read(input);
	
    if (Check(input,error)==0) {
    	//�禡�����X�k 
    	printf("It is a legitimate infix expression.\n");
    	
        Token *postfix=NULL;              //�s��Ǧ��쵲���Y 
        postfix=Postfix(input, postfix);  //�I�s�禡���o��Ǧ� 
        double result=Count(postfix,error0);
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
		printf("%f\n",result);
    } 
	else if(Check(input,error)==1){
		//���~�T��1 
        printf("Error 1: %c is not a legitimate character.\n",error);
    }
    else if(Check(input,error)==2){
    	//���~�T��2-(
    	if(error=='('){
    		printf("Error 2: there is one extra open parenthesis.\n");
		}
		//���~�T��2-)
        else if(error==')'){
        	printf("Error 2: there is one extra close parenthesis.\n");
		}
    }
    else if(Check(input,error)==3){
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
