//11127129�i�a�� 11127136�^��� 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <ctime>

#define MAX_LENGTH 100
#define MAX_QUEUE 3
static char num[MAX_LENGTH];//�s�ϥΪ̿�J���ɮ׸��X
static bool sucess = true;   //�����O�_���\�}���ɮ� 

struct Datain{
	int oid;
	int arrival;
	int duration;
	int timeout;
};

struct CompletedTask {
    int id;
    int completionTime;
    int delayTime;
};

struct CanceledTask {
    int id;
    int cancelTime;
    int delayTime;
};

class Queue {
private:
    class Job {
    public:
        int jobNumber;
        int entryTime;
        int processingTime;
        int deadline;

        Job(int number, int entry, int processing, int due) 
            : jobNumber(number), entryTime(entry), processingTime(processing), deadline(due) {}
    };

    class Node {
    public:
        Job* data;
        Node* next;

        Node(Job* job) : data(job), next(NULL) {}
    };

    Node* front;
    Node* rear;

public:
    Queue() : front(NULL), rear(NULL) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() {
        return front == NULL;
    }

    void enqueue(int number, int entry, int processing, int due) {
        Job* newJob = new Job(number, entry, processing, due);
        Node* newNode = new Node(newJob);

        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            Node* temp = front;
            Job* job = temp->data;

            front = front->next;
            delete temp;

            if (front == NULL) {
                rear = NULL;
            }

        } else {
            //throw out_of_range("dequeue from an empty queue");
        }
    }

    int size() {
        int count = 0;
        Node* current = front;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        return count;
    }

    Datain getFront() {
        if (!isEmpty()) {
        	Datain temp;
        	temp.oid=front->data->jobNumber;
        	temp.arrival=front->data->entryTime;
        	temp.duration=front->data->processingTime;
        	temp.timeout=front->data->deadline;
            return temp;
        } else {
            //throw out_of_range("getFront from an empty queue");
        }
    }
    
};


std::vector<Datain> Read(std::vector<Datain> datain,FILE *file){
	char line[1024]; 
	fgets(line, sizeof(line), file);
	Datain temp;
	
	int i=0;
    
    while (fscanf(file, "%d\t%d\t%d\t%d", &temp.oid, &temp.arrival, &temp.duration, &temp.timeout) != EOF) {
		datain.push_back(temp);
    }
    
    

    return datain;
}

std::vector<Datain> Set(std::vector<Datain> datain){ 
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
    	sucess=false;
	}
	else{ 
		sucess=true;
		datain=Read(datain,file);
		//�]�w����������� 
		fclose(file);
	}
	
	return datain; //�N�]�w�n���^�� 
}

std::vector<Datain> Set2(std::vector<Datain> datain){ 
    char fname[200]="sorted";//�s����ɮת��W�r
	
	
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
    	sucess=false;
	}
	else{ 
	    sucess=true;
		datain=Read(datain,file);
		//�]�w����������� 
		fclose(file);
	}
	
	return datain; //�N�]�w�n���^�� 
}
std::vector<Datain> Sorted(std::vector<Datain> datain){
	int n = datain.size();
	
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            Datain temp = datain[i];
            int j;
            for (j = i; j >= gap && (datain[j - gap].arrival > temp.arrival || (datain[j - gap].arrival == temp.arrival && datain[j - gap].oid > temp.oid)); j -= gap) {
				datain[j] = datain[j - gap];
            }
			datain[j] = temp;
            
        }
    }
    
    return datain;
}

void Onecpu(std::vector<Datain>& tasks,std::vector<CompletedTask>& completedTasks,std::vector<CanceledTask>& canceledTasks) {
    Queue taskQueue;
	Datain temp;         
    int currentTime = 0;
    Datain currentTask ;
    bool have=false;
    
	
    while (!taskQueue.isEmpty() || !tasks.empty()) {
    	
    	if(taskQueue.isEmpty()&&tasks.front().arrival==currentTime){
    		currentTask=tasks.front();
    		tasks.erase(tasks.begin());
    		have=true;
		}
		else if(taskQueue.isEmpty()){
			// �p�G��C���šA�ɶ��e�i
            currentTime++;
		}
		else{
			// �p�G��C�����šA�B�z��C��������
			currentTask=taskQueue.getFront();
            taskQueue.dequeue();
            have=true;
		}
		
		/*
		if(have) {
			printf("%d  %d\n",currentTask.oid,currentTime);
		}
		*/
		
        if (currentTime > currentTask.timeout&&have) {
            canceledTasks.push_back({currentTask.oid, currentTime, currentTime - currentTask.arrival});
            have=false;
        } 
		else if(have) {
			
            // �������
            if (currentTime+currentTask.duration > currentTask.timeout) {
                canceledTasks.push_back({currentTask.oid, currentTask.timeout, currentTask.timeout-currentTask.arrival});
                currentTime = currentTask.timeout;
                have=false;
            }
            else{
            		
                completedTasks.push_back({currentTask.oid, currentTime+currentTask.duration, currentTime - currentTask.arrival});
                currentTime += currentTask.duration;
                have=false;
			}
    	}
        
        // �N��F�ɶ��ŦX��e�ɶ������ȥ[�J��C
        while (!tasks.empty() && tasks.front().arrival < currentTime) {
            if (taskQueue.size() < MAX_QUEUE) {
            	temp=tasks.front();
            	taskQueue.enqueue(temp.oid, temp.arrival, temp.duration, temp.timeout);
			}
            else if(taskQueue.size() <= MAX_QUEUE&&tasks.front().arrival==currentTime){
            	temp=tasks.front();
            	taskQueue.enqueue(temp.oid, temp.arrival, temp.duration, temp.timeout);	
            } 
			else if(tasks.front().arrival<currentTime){
            	canceledTasks.push_back({tasks.front().oid, tasks.front().arrival, 0});
            }
            
			
            tasks.erase(tasks.begin());
        }

        
    }
    
    /*
    while (!taskQueue.isEmpty() || !tasks.empty() || (currentTime < executingTask.timeout && !executingTask.oid == -1)) {
        // �N��F�ɶ��ŦX��e�ɶ������ȥ[�J��C
        while (!tasks.empty() && tasks.front().arrival <= currentTime) {
            if (taskQueue.size() < 3) {
                temp=tasks.front();
            	taskQueue.enqueue(temp.oid, temp.arrival, temp.duration, temp.timeout);
            } else {
                canceledTasks.push_back({executingTask.oid, currentTime, 0});
            }
            tasks.erase(tasks.begin());
        }

        // �p�G��C�����šA�B�z��C��������
        if (!taskQueue.isEmpty()) {
            Datain currentTask = taskQueue.getFront();
            taskQueue.dequeue();

            // �ˬd�O�_�O��
            if (currentTime > currentTask.timeout) {
                canceledTasks.push_back({currentTask.oid, currentTime, currentTime - currentTask.arrival});
            } else {
                // �������
                executingTask = currentTask;
                currentTime += currentTask.duration;

                // �ˬd�S���p�G�s�u�@�i�J�ɨ�P�w����u�@�����ɨ�۵�
                while (!taskQueue.isEmpty() && taskQueue.getFront().arrival == currentTime) {
                    // �N�������u�@��J�M��
                    completedTasks.push_back({executingTask.oid, currentTime, currentTime - executingTask.arrival});

                    // ��s���b���檺�u�@�P��C
                    executingTask = taskQueue.getFront();
                    taskQueue.dequeue();
                    currentTime += executingTask.duration;
                }

                // �N�������u�@��J�M��
                completedTasks.push_back({executingTask.oid, currentTime, currentTime - executingTask.arrival});
            }
        } else {
            // �p�G��C���šA�ɶ��e�i
            currentTime++;
        }
    }
    */
}

void One(){          
	char fname[200]="sorted";//�s����ɮת��W�r 
	char trash;             //�s���ݭn������
	FILE *sortedf;
	std::vector<Datain> datain;
	double read_time;
	double sort_time;
	double write_time;
	
	
	
	//Ū�J�ɮ׸��X 
	printf("Input a file number:");
	scanf("%s",&num);
	//Ū���e��Ū���ɮ׸��X�T���h�l������
	scanf("%c",&trash);
	printf("\n");
	
	clock_t start_time = clock();
	datain=Set(datain);
	clock_t end_time = clock();
	// �p�����ɶ��]�H�@�����^
	read_time=((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;
	
	if(sucess){
		int size=datain.size();
		int i=0;
	
		printf("\tOID\tArrival\tDuration\tTimeOut\n");
		while(i<size){
			printf("(%d)\t%d\t%d\t%d\t%d\n",i+1,datain[i].oid,datain[i].arrival,datain[i].duration,datain[i].timeout);
			i++;
		}
		printf("\n");
	
		clock_t start_time2 = clock();
		datain=Sorted(datain);
		clock_t end_time2 = clock();
		sort_time=((double)(end_time2 - start_time2) / CLOCKS_PER_SEC) * 1000.0;
	
		strcat(fname,num);
		strcat(fname,".txt");
		sortedf=fopen(fname, "w");
	
		clock_t start_time3 = clock();
		i=0;
		fprintf(sortedf,"OID\tArrival\tDuration\tTimeOut\n");
		while(i<size){
			fprintf(sortedf,"%d\t%d\t%d\t%d\n",datain[i].oid,datain[i].arrival,datain[i].duration,datain[i].timeout);
			i++;
		}
		clock_t end_time3 = clock();
		write_time=((double)(end_time3 - start_time3) / CLOCKS_PER_SEC) * 1000.0;
	
		printf("Reading data:%d clocks (%f ms).\n",(int)read_time,read_time);
		printf("Sorting data:%d clocks (%f ms).\n",(int)sort_time,sort_time);
		printf("Writing data:%d clocks (%f ms).\n",(int)write_time,write_time);
		printf("\n");
	
		printf("See %s\n",fname);
		printf("\n");
	
		datain.clear();
		fclose(sortedf);
	}
}

void Two(){ 
    Queue taskQueue;   
	char fname[200]="output";//�s����ɮת��W�r 
	char trash;             //�s���ݭn������
	FILE *outputf;
	std::vector<Datain> datain;
	std::vector<CompletedTask> completedTasks;
	std::vector<CanceledTask> canceledTasks;
	double td;
	double ad;
	double rate;

	if(num[0]=='\0'){
		//Ū�J�ɮ׸��X 
		printf("Input a file number:");
		scanf("%s",&num);
		printf("\n");
	}
	//Ū���e��Ū���ɮ׸��X�T���h�l������
	scanf("%c",&trash);

	datain=Set2(datain);
	
	if(sucess){
		Onecpu(datain,completedTasks,canceledTasks);
                  
		strcat(fname,num);
		strcat(fname,".txt");
		outputf=fopen(fname, "w");
	
		int totaltask=canceledTasks.size()+completedTasks.size();
		rate=completedTasks.size()/(double)totaltask*100;
	
		int i = 0;
		int size = canceledTasks.size();
		fprintf(outputf,"\t[Abort Jobs]\n");
		fprintf(outputf,"\tOID\tAbort\tDelay\n");
		while(i<size){
			td=td+canceledTasks[i].delayTime;
			fprintf(outputf,"[%d]\t%d\t%d\t%d\n",i+1,canceledTasks[i].id,canceledTasks[i].cancelTime,canceledTasks[i].delayTime);
			i++;
		}
	
		i = 0;
		size = completedTasks.size();
		fprintf(outputf,"\t[Jobs Done]\n");
		fprintf(outputf,"\tOID\tDeparture\tDelay\n");
		while(i<size){
			td=td+completedTasks[i].delayTime;
			fprintf(outputf,"[%d]\t%d\t%d\t%d\n",i+1,completedTasks[i].id,completedTasks[i].completionTime,completedTasks[i].delayTime);
			i++;
		}
	
		ad=td/(double)totaltask;
	
		fprintf(outputf,"[Average Delay]\t%.2f ms\n",(double)ad);
		fprintf(outputf,"[Success Rate]\t%.2f %%\n",(double)rate);
	
		printf("The simulation is running...\n");
		printf("See %s\n",fname);
		printf("\n");
	
		datain.clear();
		fclose(outputf);
	}
	
}

int main() {
	char trash;      //�s���ݭn������
	char dowhat='\0';//�s�����O   
	//�����a�߰ݭn���檺�ʧ@�����J0�h�X 
	while(dowhat!='0'){
		//�L�X������Ū�����O 
		printf("**** Simulate FIFO Queues by SQF *****\n");
    	printf("* 0. Quit                            *\n");
    	printf("* 1. Sort a file                     *\n");
    	printf("* 2. Simulate one FIFO queue         *\n");
    	printf("**************************************\n");
    	printf("Input a command(0, 1, 2):");
		scanf("%c",&dowhat);
		printf("\n");
	
	    //�Y�D�X�k���O�h��X���~�T���A�X�k�h��������ʧ@ 
		if(dowhat!='0'&&dowhat!='1'&&dowhat!='2'){
			printf("Command does not exist!\n");
			//Ū���e�����O�T���h�l������ 
			if(dowhat!='\n'){
				scanf("%c",&trash);	
			}
			
			printf("\n");
		}
		else if(dowhat=='1'){
			//���O��1�h�I�sOne()�������{�� 
			One();
		}
		else if(dowhat=='2'){
			//���O��1�h�I�sOne()�������{�� 
			Two();
		}
	}
	

}

