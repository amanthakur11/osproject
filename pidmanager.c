#include<stdio.h>
#include<pthread.h>
#include<time.h>
#define MIN_PID 300
#define MAX_PID 5000

pthread_mutex_t mutex;
int allocate_map();
int allocate_pid();
void release_pid();
int n;

struct process{
	int pid,allocated;
}pidm[MAX_PID-MIN_PID];

void* processfunc(void *a) {
	int pid=allocate_pid();
	printf("New process created : %d\n",pid);
	int _time=(rand())%(n)+10;
	sleep(_time);
	release_pid(pid);
	printf("Process destroyed : %d\n",pid);
}
int allocate_map(){
	int i=MIN_PID;
	while(i<=MAX_PID){
			pidm[i-MIN_PID].pid=i;
		pidm[i-MIN_PID].allocated=0;
		i++;
	}
	if(i==MAX_PID+1){
	return 1;
    }
    return -1;
}


void createprocess() {
	int l=0;
	printf("enter the no of process you want to enter: ");
	scanf("%d",&n);
	pthread_t Pid[n];
	int p=pthread_mutex_init(&mutex,NULL);
	
	while(l<n) {
		pthread_create(&Pid[l],NULL,&processfunc,NULL);
		sleep(1);
		l++;
	}
	
	l=0;
	while(l<n) {
		pthread_join(Pid[l],NULL);
		l++;
	}	
}

int main() {
	int a=allocate_map();
	 if(a!=-1){
		srand(time(0));
		createprocess();
	}
	else{
		printf("something went wrong please restart.");
	}
	return 0;
}
