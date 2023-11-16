//11127129張軒偉 11127136彭晨維 
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
	char fname[200]="input";//存整個檔案的名字
	
	//串接檔名 
	strcat(fname,num);
	strcat(fname,".txt");
	
	//開啟相應文件 
	FILE *file;
	file = fopen(fname, "rb"); // 以唯讀模式打開文件
	if (file == NULL) {
		//找不到此文件則輸出錯誤訊息 
    	printf("\ninput%s.txt does not exist!\n",num);
	}
	else{
		//找到則呼叫maze.SetMaze()繼續執行迷宮設定 
		datain=Read(datain,file);
		//設定完成關閉文件 
		fclose(file);
	}
	
	return datain; //將設定好的回傳 
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
	char num[100] ;         //存使用者輸入的檔案號碼 
	char fname[200]="sorted";//存整個檔案的名字 
	char trash;             //存不需要的換行
	FILE *sortedf;
	std::vector<Datain> datain;
	double read_time;
	double sort_time;
	double write_time;
	
	
	
	//讀入檔案號碼 
	printf("Input a file number:");
	scanf("%s",&num);
	//讀取前面讀取檔案號碼訊息多餘的換行
	scanf("%c",&trash);
	printf("\n");
	
	clock_t start_time = clock();
	datain=Set(datain,num);
	clock_t end_time = clock();
	// 計算執行時間（以毫秒為單位）
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
	char trash;      //存不需要的換行
	char dowhat='\0';//存取指令
	
	//不停地詢問要執行的動作直到輸入0退出 
	while(dowhat!='0'){
		//印出介面並讀取指令 
		printf("**** Simulate FIFO Queues by SQF *****\n");
    	printf("* 0. Quit                            *\n");
    	printf("* 1. Sort a file                     *\n");
    	printf("* 2. Simulate one FIFO queue         *\n");
    	printf("**************************************\n");
    	printf("Input a command(0, 1, 2):");
		scanf("%c",&dowhat);
		printf("\n");
	
	    //若非合法指令則輸出錯誤訊息，合法則執行相應動作 
		if(dowhat!='0'&&dowhat!='1'&&dowhat!='2'){
			printf("Command does not exist!\n");
			//讀取前面指令訊息多餘的換行 
			if(dowhat!='\n'){
				scanf("%c",&trash);	
			}
			
			printf("\n");
		}
		else if(dowhat=='1'){
			//指令為1則呼叫One()執行後續程序 
			One();
		}
		else if(dowhat=='2'){
			//指令為1則呼叫One()執行後續程序 
			//Two();
		}
	}
	

}

