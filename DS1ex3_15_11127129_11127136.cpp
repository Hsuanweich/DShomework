//11127129�i�a�� 11127136�^��� 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <ctime>


struct Datain{
	int oid;
	int arrival;
	int duration;
	int timeout;
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

std::vector<Datain> Set(std::vector<Datain> datain,char num[100]){ 
	char fname[200]="input";//�s����ɮת��W�r
	
	//�걵�ɦW 
	strcat(fname,num);
	strcat(fname,".txt");
	
	//�}�Ҭ������ 
	FILE *file;
	file = fopen(fname, "rb"); // �H��Ū�Ҧ����}���
	if (file == NULL) {
		//�䤣�즹���h��X���~�T�� 
    	printf("\ninput%s.txt does not exist!\n",num);
	}
	else{
		//���h�I�smaze.SetMaze()�~�����g�c�]�w 
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

void One(){
	char num[100] ;         //�s�ϥΪ̿�J���ɮ׸��X 
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
	datain=Set(datain,num);
	clock_t end_time = clock();
	// �p�����ɶ��]�H�@�����^
	read_time=((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;
	
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
			//Two();
		}
	}
	

}

