#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<time.h> 
#include<math.h>
using namespace std; 
#define BLOCK_SIZE 1024
#define MEM_SIZE 64
#define MAXSIZE 20
int bitmap[MEM_SIZE/8][8];
int page_count=0;//页表的长度 
int page_size=3;//固定的内存块数
int num_sum=0;//总页数
int num_miss=0;//缺页数

//置换空间的位示图 
int mapfree[MEM_SIZE/8][8];

int FIFO[3];
int LRU[3];
int swap_zone[MEM_SIZE];

//进程控制 
typedef struct PCB{
	char name[20];
	int start_address;
	int length;
	int state;  // 0---就绪，1--运行；2---阻塞 
	int *page_table;
	int *state_bit;
	int *swap_zone;
	struct PCB *next;
}PCB;
PCB *ready,*blocked,*running;
PCB *p1;
PCB *p;
int count_f=0;
int count_l=0;
typedef struct m_segment{
	int flag; //0----空闲，1-----忙碌
	int start;
	int length;
	struct m_segment *next; 
}m_segment;
m_segment *ms;

//typedef struct swap_zone{
//	int *page_table;
//	int *state_bit;
//	struct swap_zone *next;
//}swap_zone; 

//设备管理模块 
typedef struct Node{
	char name[10];
	char type[10];
	PCB *process;
	PCB *waitinglist;
	struct Node *parent;
	struct Node *next;
}Node; 
Node *CHCTs;
Node *COCTs;
Node *DCTs;


 
int enqueue(PCB *head, PCB *process);
void dispatch();
PCB *CreateNewProcess();
void BlockingProcess();
void WakeupProcess();
void TimeSliceOver();
void RevokeProcess();

void show();
void init_bitmap();
void show_bitmap();
void init_mapfree();
void show_mapfree();
void show_pageTable(PCB *p);
void address_translation(PCB *p);
void setbit_0(int num);


void FIFO_P();
void LRU_P();
void FIFO_Permutation_algorithm(PCB *p,int count_f);
void show_FIFO(PCB *p);
void LRU_Permutation_algorithm(PCB *p,int count_l);
void show_LRU(PCB *p);
void show_memoryF();
void show_memoryL();

Node *insert_node(Node *head,char *name,char *type,Node *parent); 
void init_device();
void show_relation_grap();
void add_device();
void delet_device();



//入队出队 
int enqueue(PCB *head, PCB *process){
	PCB *p=head;
	while(p->next!=NULL){
	    p=p->next;
	}
	p->next=process;
	process->next=NULL;
	return 1;
}
void dispatch(){
	PCB *rea,*run;
	rea=ready;
	run=running;
	if(run->next==NULL && rea->next!=NULL){
		run->next=rea->next;
		run->next->state=1;
		rea->next = rea->next->next;
		run->next->next = NULL;
	}
	if(rea->next==NULL){
		printf("没有可以调配的进程了\n");
	}
}

//创建新进程 
PCB * CreateNewProcess(){
	PCB * p;
	p = (PCB*)malloc(sizeof(PCB));
	p->next =NULL;
	printf("请输入新进程的名称：");
	scanf("%s",&p->name); 
	printf("请输入该进程的大小：");
	scanf("%d",&p->length);
	int block_count =0;
	p->state=0;
    m_segment *pre,*now;
    pre=ms;
    now=ms->next;
    while((now !=NULL) && (p->length > now->length)){
    	pre=now;
    	now=now->next;
	}
	if(now ==NULL){
		printf("内存空间不够分配，创建失败！！！"); 
	}else{
		p->start_address =now->start;
		
		if((now->length - p->length)<=2){
			p->length=now->length;
		}
		m_segment *temp;
		temp = (m_segment *)malloc(sizeof(m_segment));
		temp->flag = 0;
		temp->start = p->start_address + p->length;
		temp->length = now->length - p->length; 
		temp->next = NULL; 
 		pre->next = now->next; 
		if(temp->length>0){
			pre=ms;
			now=ms->next;
			while(now !=NULL && (now->length > temp->length)){
				pre=now;
				now=now->next;
			}
			pre->next = temp;
			temp->next = now;
		}
		
		//1.创建进程时，首先根据进程大小和页面大小算出一共占了几个内存卡 
		//2.然后创建一个空表即一个一维数组 
		block_count = (ceil)(p->length/(double)BLOCK_SIZE);
		page_count=block_count;
		p->page_table =(int *)malloc(sizeof(int)*block_count);
		p->state_bit=(int *)malloc(sizeof(int)*block_count);
		for(int i=0;i<page_count;i++){
	    	p->page_table[i]=-1;
		}
		for(int i=0;i<page_count;i++){
	    	p->state_bit[i]=0;
		}
		int count=0;
		for(int i=0;i<MEM_SIZE/8;i++){
			for(int j=0;j<8;j++){
					if(bitmap[i][j]==0){
						p->page_table[count]=8*i+j;
						bitmap[i][j]=1;
						count++;
					} 
					if(count==page_count){
					    break;
				     }
				}
				if(count==page_count){
					break;
			    }
	    } 
	     
		if(enqueue(ready,p)){
		  printf("进程%s创建完成！起始位置为:%d,长度为:%d,状态为:%d\n",p->name,p->start_address,p->length,p->state);
	    } 
		dispatch();
		return p;
	}
}

//阻塞进程
void BlockingProcess(){
	PCB *run,*blo;
	run=running->next;
	if(run !=NULL){
	  running->next=NULL;
	  run->state=2;
	  enqueue(blocked,run);	
	  	printf("进程%s阻塞成功！",run->name); 
	  dispatch();
	}else{
		printf("没有阻塞的进程");
	}
	
}

//唤醒进程
void WakeupProcess(){
	PCB *blo,*rea;
	blo = blocked->next;
	if(blo!=NULL){
		blocked->next=blo->next;
		enqueue(ready,blo); 
		printf("进程%s唤醒成功！",blo->name); 
		dispatch();		
	}else{
		printf("没有可唤醒的进程"); 
	}
	 
} 


//时间片到
void TimeSliceOver(){
	PCB *run,*rea;
	run=running->next;
	if(run!=NULL){
		running->next=NULL; 
		enqueue(ready,run);
			printf("进程%s时间片到了！",run->name); 
		dispatch(); 		
    }else{
    	printf("当前没有运行的进程");
	}
} 
 
 
//撤销进程
void RevokeProcess(){
	int target=0;
	PCB *run;
	run=running->next;
	if(run!=NULL)
	{
		m_segment *now,*pre,*temp1,*temp2;
		now=ms->next;
		pre=ms;
		while(now!=NULL)
		{
			if(now->start+now->length==run->start_address)//前面的有空闲 
			{
				now->length=now->length+run->length;
				temp1=(m_segment *)malloc(sizeof(m_segment));
				temp1->start=now->start;
				temp1->length=now->length;
				temp1->next=NULL; 
				pre->next=now->next;
				now=now->next;
				target=1;
			}                            
			if(target!=1 && run->start_address+run->length==now->start)//后面的有空闲 
			{
				now->start=run->start_address;
				now->length=now->length+run->length;
			    temp1=(m_segment *)malloc(sizeof(m_segment));
				temp1->start=now->start;
				temp1->length=now->length;
				temp1->next=NULL;
				pre->next=now->next;
				now=now->next;
				target=2;
			}
			if(target==1 || target==2)//前面或后面有空闲
				break;
			pre=now;
			now=now->next;
		}
		if(target==0)
		{
			temp2=(m_segment *)malloc(sizeof(m_segment));
			temp2->start=run->start_address;
			temp2->length=run->length;
			temp2->next=NULL;
		}
		if(target!=0)
		{
			now=ms->next;
			pre=ms;
			while(now!=NULL)
			{	
				if(target==1 && temp1->start+temp1->length==now->start)//前面有空闲后，后面也有空闲
				{
					now->start=now->start;
					now->length=now->length+temp1->length;
					temp2=(m_segment *)malloc(sizeof(m_segment));
					temp2->start=now->start;
					temp2->length=now->length;
					temp2->next = NULL;
					pre->next=now->next;
					now=now->next;  
					target=3;
				}
				if(target==2 && now->start+now->length==temp1->start)//后面有空闲后，前面也有空闲
				{
					now->length=now->length+temp1->length;
				    temp2=(m_segment *)malloc(sizeof(m_segment));
					temp2->start=now->start;
					temp2->length=now->length;
					temp2->next = NULL;
					pre->next=now->next;
					now=now->next;
					target=4;
	
				}
				if(target==3||target==4)
				break;
			    pre=now;
			    now=now->next;
			}
		}
		if(target==3||target==4||target==0)
		{
			now=ms->next;
			pre=ms;
			while(now!=NULL && temp2->length>now->length)
			{
				pre=now;
				now=now->next;
			}
			pre->next=temp2;
			temp2->next=now;
		}
		if(target==1||target==2)
		{
			now=ms->next;
			pre=ms;
			while(now!=NULL && temp1->length>now->length)
			{
				pre=now;
				now=now->next;
			}
			pre->next=temp1;
			temp1->next=now;
		}
		//进程终止时，根据页表的内容将位示图的位置1----0 
		for(int i=0;i<page_count;i++){
			setbit_0(run->page_table[i]);
		} 
		show_bitmap();
		running->next =NULL;	
		dispatch();
	}else{
		printf("没有可被终止的进程!");
	}

}



void show(){
	printf("\n");
	printf("************************************各个队列中的情况：***************************************************\n");
	PCB *p;
	printf("ready队列中进程的情况:\n");
	p=ready->next;
	while(p){
			printf("进程名称         进程起始位置        进程大小     进程结束位置     进程的状态 \n");
		printf("%s                   %d                  %d               %d            %d\n",p->name,p->start_address,p->length,p->start_address+p->length,p->state);
		p=p->next;
	}
	printf("running队列中进程的情况:\n");
	p=running->next;
	while(p){
			printf("进程名称         进程起始位置        进程大小     进程结束位置     进程的状态 \n");
		printf("%s                   %d                  %d               %d             %d\n",p->name,p->start_address,p->length,p->start_address+p->length,p->state);
		p=p->next;
	}
	printf("blocked队列中进程的情况:\n");
	p=blocked->next;
	while(p){
		printf("进程名称         进程起始位置        进程大小     进程结束位置     进程的状态 \n");
		printf("%s                   %d                  %d               %d            %d\n",p->name,p->start_address,p->length,p->start_address+p->length,p->state);
		p=p->next;
	}
	printf("************************************************************************************************************\n");
}
void show_blank(){
	printf("内存段空闲区段的情况:\n");
	printf("*******************************************************************************************************\n");
	m_segment *m = ms->next;
	while(m){
		printf("起始位置       空闲区大小     结束位置\n");
		printf("    %d           %d             %d\n",m->start,m->length,m->start+m->length);
		m=m->next;
	}
	printf("\n");
	printf("******************************************************************************************************\n");
}



void init_bitmap(){
	srand(time(0));
	for(int i=0;i<MEM_SIZE/8;i++){
		for(int j=0;j<8;j++){
			bitmap[i][j]=rand()%2;
		}
	}
}
void init_mapfree(){
	srand(time(NULL));
	for(int i=0;i<MEM_SIZE/8;i++){
		for(int j=0;j<8;j++){
			mapfree[i][j]=rand()%2;
		}
	}
}
void show_mapfree(){
	printf("-------------------------外存的位示图如下：-------------- ---------\n");
	for(int i=0;i<MEM_SIZE/8;i++){
	   for(int j=0;j<8;j++){
		 	printf("     %d ",mapfree[i][j]);
		}
		printf("\n");
	}
	printf("------------------------------------------------------------------\n");
}
void show_bitmap(){
	printf("-------------------------位示图如下：-----------------------------\n");
	for(int i=0;i<MEM_SIZE/8;i++){
	   for(int j=0;j<8;j++){
		 	printf("     %d ",bitmap[i][j]);
		}
		printf("\n");
	}
	printf("------------------------------------------------------------------\n");
}
void show_pageTable(PCB *p){
	printf("------该进程的页表如下：---------------------------------------------\n");
	printf("       页号  块号   状态位    外存的块号\n"); 
	for(int i=0;i<page_count;i++){
		printf("        %d  |  %2d      | %d         |2%d\n",i,p->page_table[i],p->state_bit[i],p->swap_zone[i]);		
	}
	printf("----------------------------------------------------------------------\n");
}


void setbit_0(int num){
	int row=0,col=0;
	row=num/8;
	col=num%8;
	bitmap[row][col]=0;
}


//地址转换 输入一个逻辑地址，转换为物理地址 
void address_translation(PCB *p){
	int address=0;
	int page_num=0;
	int distance=0 ;
	int address_after=0; 
	printf("请输入当前进程所要访问的逻辑地址（十进制）:");
	scanf("%d",&address);
	page_num = address/BLOCK_SIZE;
	distance = address%BLOCK_SIZE;
		//判断是否越界？ 
	if(page_num>page_count){
		printf("所给的逻辑地址已经越界!");
	}else{
		address_after=(p->page_table[page_num])*BLOCK_SIZE + distance;
	}
	printf("所对应的页号为%d，所对的页内偏移量为%d\n",page_num,distance);
	printf("所对应的物理地址为:%d\n",address_after);	
}

PCB *Create(){
	for(int i=0;i<page_size;i++){
		FIFO[i]=-1;
		LRU[i]=-1;
	}
	PCB *p = (PCB*)malloc(sizeof(PCB));
	p->next=NULL;  
	printf("请输入进程的名字:");
	scanf("%s",&p->name);
	printf("请输入进程的大小:");
	scanf("%d",&p->length);
	int block_count;
	block_count = (ceil)(p->length/(double)BLOCK_SIZE);
	page_count=block_count;
	p->page_table =(int *)malloc(sizeof(int)*block_count);
	p->state_bit=(int *)malloc(sizeof(int)*block_count);
	p->swap_zone =(int *)malloc(sizeof(int)*block_count);
	for(int i=0;i<page_count;i++){
    	p->page_table[i]=-1;
    	p->state_bit[i]=0;
    	p->swap_zone[i]=-1;
	}
	int count=0;
	for(int i=0;i<MEM_SIZE/8;i++){
		for(int j=0;j<8;j++){
				if(mapfree[i][j]==0){
					p->swap_zone[count]=8*i+j;
					mapfree[i][j]=1;
					count++;
				} 
				if(count==page_count-1){
					break;
				}
		}
		if(count==page_count-1){
			break;
		}
	} 
	return p;
}

//FIFO置换算法 
void FIFO_Permutation_algorithm(PCB *p,int count_f){ 
	int address;
	int address_after;
	printf("输入想要变换的逻辑地址：");
	scanf("%d",&address);
	int page_num = address/BLOCK_SIZE;
	num_sum++;
	//先判断是否在内存// 1---在内存，0----不在内存 
	if(p->state_bit[page_num]==1){  //在内存 
		address_after=p->page_table[page_num]*BLOCK_SIZE+address%BLOCK_SIZE;
		printf("该逻辑地址%d所对应的物理地址为：%d\n",address,address_after);
	}else{    //不在内存时，则缺页，要进行调度
		num_miss++; 
		int flag_x=-1;  //判断内存满还是没有满 
		for(int i=0;i<page_size;i++){
			if(FIFO[i]==-1){
				flag_x=i;
				break;
			}
		} 
		int flag=0;
		if(flag_x!=-1){  //内存还可以装的下，直接将页表中的所对应的块，装进内存即可
		
		//步骤：1.将所对应的块号装进内存所对应的的位置  FIFO[flagi]=page_num*i+j;
		//      2.将页表中的状态位设置为1； 
		 for(int i=0;i<MEM_SIZE/8;i++){
		 	for(int j=0;j<8;j++){
		 		if(bitmap[i][j]==0 && count_f<page_size){
		 			bitmap[i][j]=1;
		 			count_f++;
		 			p->page_table[page_num]=8*i+j;
		 			p->state_bit[page_num]=1;
		 			FIFO[flag_x]=page_num;
		 			flag=1;
		 			break;
				 }
			 }
			 if(flag==1){
			 	break;
			 }
		 }	
		 address_after=p->page_table[page_num]*BLOCK_SIZE+address%BLOCK_SIZE;
		 printf("该逻辑地址%d所对应的物理地址为：%d\n",address,address_after);
		}else{   //内存已经装不下了 
		//从外存中进行置换 
		//步骤：1.在FIFO选择一个时间最长的， 这里就是数组下标为0的
		//	    2.将FIFO删除，并且将数组从后到前一个一个前移
		//      3.将页号所对应的块号填到最新的FIFO[2]
		//      4.修改状态位：FIFO[0]-----0;FIFO[2}-------1;
		//      5.将FIFO[0]的页重新填到表中 
		int temp=FIFO[0];
		for(int i=0;i<page_size-1;i++){
			FIFO[i]=FIFO[i+1];	
		} 		
		FIFO[page_size-1]=page_num;
		p->state_bit[temp]=0;
		p->state_bit[page_num]=1;
		p->page_table[page_num]=p->page_table[temp];
		p->page_table[temp]=-1;
		address_after=p->page_table[page_num]*BLOCK_SIZE+address%BLOCK_SIZE;
		printf("该逻辑地址%d所对应的物理地址为：%d\n",address,address_after);
	}
}	
} 
 
void show_FIFO(PCB *p){
	printf("------该FIFO的页表如下：----------------\n");
	printf("       页号  块号   状态位\n"); 
	for(int i=0;i<page_count;i++){
		printf("        %d  |  %2d      | %d\n",i,p->page_table[i],p->state_bit[i]);		
	}
	printf("-----------------------------------------\n");
	printf("内存中的序号为：\n");
	for(int i=0;i<page_size;i++){
		printf("%d ",FIFO[i]);
	}
	printf("\n");
} 
void LRU_Permutation_algorithm(PCB *p,int count_l){
	int address;
	int address_after;
	printf("输入想要变换的逻辑地址：");
	scanf("%d",&address);
	int page_num = address/BLOCK_SIZE;
	num_sum++;
	//先判断是否在内存// 1---在内存，0----不在内存 
	if(p->state_bit[page_num]==1){  //在内存 
		for(int i=0;i<page_size;i++){
			int flag_x=-1;
			if(LRU[i]==page_num){
				flag_x=i;
			}
			int j=flag_x;
			while(j<page_size-1 && LRU[j]!=-1){
				LRU[j]=LRU[j+1];
				j++;
			}
			LRU[j]=page_num;
			break;
		}
		address_after=p->page_table[page_num]*BLOCK_SIZE+address%BLOCK_SIZE;
		printf("该逻辑地址%d所对应的物理地址为：%d\n",address,address_after);
	}else{  //不在内存
	  num_miss++;
	  int flag_x=-1;
	  for(int i=0;i<page_size;i++){
	  	if(LRU[i]==-1){
	  		flag_x=i;
	  		break;
		}
	  }
	  int flag=0; 
	  if(flag_x!=-1){  //内存没有满 
	  	for(int i=0;i<MEM_SIZE/8;i++){
		 	for(int j=0;j<8;j++){
		 		if(bitmap[i][j]==0 && count_l<page_size){
		 			bitmap[i][j]=1;
		 			count_l++;
		 			p->page_table[page_num]=8*i+j;
		 			p->state_bit[page_num]=1;
		 			LRU[flag_x]=page_num;
		 			flag=1;
		 			break;
				 }
			 }
			 if(flag==1){
			 	break;
			 }
		 }	
		 address_after=p->page_table[page_num]*BLOCK_SIZE+address%BLOCK_SIZE;
		 printf("该逻辑地址%d所对应的物理地址为：%d\n",address,address_after);
		}else{  //内存满了 
	  		int temp=LRU[0];
	  		for(int i=0;i<page_size;i++){
	  		  LRU[i]=LRU[i+1];
			}
			LRU[page_size]=page_num;
			p->state_bit[temp]=0;
			p->state_bit[page_num]=1;
			p->page_table[page_num]=p->page_table[temp];
			p->page_table[temp]=-1;
			address_after=p->page_table[page_num]*BLOCK_SIZE+address%BLOCK_SIZE;
			printf("该逻辑地址%d所对应的物理地址为：%d\n",address,address_after);
	  }
		
	}
	
} 
void show_LRU(PCB *p){
	printf("------该LRU页表如下：----------------\n");
	printf("       页号  块号   状态位\n"); 
	for(int i=0;i<page_count;i++){
		printf("        %d  |  %2d      | %d\n",i,p->page_table[i],p->state_bit[i]);		
	}
	printf("-----------------------------------------\n");
	printf("内存中的序号为：\n");
	for(int i=0;i<page_size;i++){
		printf("%d ",LRU[i]);
	}
	printf("\n");
} 


void show_memoryF(){
	for(int i=0;i<page_size;i++){
		printf("%2d ",FIFO[i]);
	}
	printf("\n");	
}

//FIFO置换算法  // 2 3 2 1 5 2 4 5 3 2 5 2 -1
void FIFO_P(){
	int length=0;
  	int num_sum=0;
	int num_miss=0; 
	int array[20];
   for(int i=0;i<page_size;i++){
    	FIFO[i]=-1;
	}
	printf("请输入当前页面的访问串为：\n");
	while(1){
		scanf("%d",&array[length]);
		if(array[length]==-1){
			break;
		}
		length++;
	}
	printf("----------------------------------------------------\n");
	printf("利用FIFO置换算法时内存中存储的情况显示如下：\n");
	for(int i=0;i<length;i++){	
		num_sum++;
		//判断是否在内存
		int flag=0;
		for(int x=0;x<page_size;x++){
			if(FIFO[x]==array[i]){
				flag=1;
			}
		} 
		if(flag==0){
			num_miss++;
			//判断内存满没有满
			int flag_x=-1;
			for(int x=0;x<page_size;x++){
				if(FIFO[x]==-1){
					flag_x=x;
					break;
				}
			}
			if(flag_x!=-1){  //内存没有满
			  FIFO[flag_x]=array[i]; 
			}else{
				for(int x=0;x<page_size;x++){
			   	 FIFO[x]=FIFO[x+1];
			   	}
			   	FIFO[page_size-1]=array[i];
			}
		}
		show_memoryF();
    }
    printf("总次数为：%d\n",num_sum); 
	printf("缺页数为：%d\n",num_miss);
	printf("缺页率为：%.2f\n",(double)num_miss/(double)num_sum);
	printf("----------------------------------------------------\n");
}   

void show_memoryL(){
	for(int i=0;i<page_size;i++){
		printf("%2d ",LRU[i]);
	}
	printf("\n");	
}
//LRU置换算法 2 3 2 1 5 2 4 5 3 2 5 2 -1
void LRU_P(){
	int length=0;
  	int num_sum=0;
	int num_miss=0; 
	int array[20];
    for(int i=0;i<page_size;i++){
    	LRU[i]=-1;
	}
	printf("请输入当前页面的访问串为：\n");
	while(1){
		scanf("%d",&array[length]);
		if(array[length]==-1){
			break;
		}
		length++;
	}
	printf("----------------------------------------------------\n");
	printf("利用LRU置换算法时内存中存储的情况显示如下：\n");
	for(int i=0;i<length;i++){	
	    num_sum++;
	    //判断是否在内存
	    int flag=0;
	    int position=-1;
		for(int x=0;x<page_size;x++){
			if(LRU[x]==array[i]){
				flag=1;
				position=x;
				break;
			}
		} 
	    if(flag==1){ //在内存 
		  //找到它的位置
		  int temp=LRU[position];
		  int position_1=-1; 
		  if(position!=page_size-1){
		  	for(int x=0;x<page_size;x++){
		  		if(LRU[x]==-1){
		  			position_1=x;
		  			break;
				  }
			  }
			  //存在不是-1，即没有满的时候的位置 
			  if(position_1!=-1){
			  	for(int x=0;x<position_1-1;x++){
			  		LRU[x]=LRU[x+1];
				}
				LRU[position_1-1]=temp;
			  }else{    //全部都是满的 ,位置前面的不用动，从他开始移动 
			       for(int x=position;x<page_size;x++){
						LRU[x]=LRU[x+1];
				   }	
				LRU[page_size-1]=temp;
			  } 
		  }
		}else{//不在内存 
		  //判断内存满没有满
		  num_miss++;
		  int flag_x=-1;
		  for(int x=0;x<page_size;x++){
		  	if(LRU[x]==-1){
		  		flag_x=x;
		  		break;
			  }
		  }	
		  if(flag_x!=-1){  //没有满 
		    LRU[flag_x]=array[i];
		  }else{  //满了 
		  	  for(int x=0;x<page_size;x++){
		  		 LRU[x]=LRU[x+1];
			  }
			  LRU[page_size-1]=array[i]; 
		  } 
		}
		show_memoryL();
    }
    printf("总次数为：%d\n",num_sum); 
	printf("缺页数为：%d\n",num_miss);
	printf("缺页率为：%.2f\n",(double)num_miss/(double)num_sum);
	printf("----------------------------------------------------\n");
}


/*
	设备管理模块
	 
*/
Node *insert_node(Node *head,char *name,char *type,Node *parent){
//	printf("%s",name);
	Node *temp=(Node *)malloc(sizeof(Node));
//	printf("111");
	strcpy(temp->name,name);
	strcpy(temp->type,type);
	temp->process=NULL;
	temp->waitinglist=(PCB *)malloc(sizeof(Node));
	temp->waitinglist->next=NULL;
	temp->parent=parent;
	temp->next=NULL;
	
	Node *p=head;
	while(p->next!=NULL){
		p=p->next;
	} 
	p->next=temp;
	return temp;
	
	
}
void init_device(){
//初始化三个链表 
	CHCTs = (Node *)malloc(sizeof(Node));
	CHCTs->next=NULL;
	COCTs=(Node *)malloc(sizeof(Node)); 
	COCTs->next=NULL;
	DCTs=(Node *)malloc(sizeof(Node));
	DCTs->next=NULL;
	/*  
		开始向链表中插入具体的信息
			设备  keyboard  mouse printer monitor
			控制器	控制器1 控制器2 控制器3
			通道  通道1 通道2  
	*/ 
	Node *chct_temp;
	Node *coct_temp;
	chct_temp=insert_node(CHCTs,"通道1","-",NULL);
	coct_temp=insert_node(COCTs,"控制器1","-",chct_temp);
	insert_node(DCTs,"keyboard","I",coct_temp);
	insert_node(DCTs,"mouse","I",coct_temp);
	coct_temp=insert_node(COCTs,"控制器2","-",chct_temp);
	insert_node(DCTs,"printer","O",coct_temp);
	chct_temp=insert_node(CHCTs,"通道2","-",NULL);
	coct_temp=insert_node(COCTs,"控制器3","-",chct_temp);
	insert_node(DCTs,"mointer","O",coct_temp); 

	printf("通道为： ");
	Node *chcts=CHCTs->next;
	while(chcts!=NULL){
		printf("%s  ",chcts->name);
		chcts=chcts->next;
	} 
	printf("\n");
	printf("控制器为： ");
	Node *cocts=COCTs->next;
	while(cocts!=NULL){
		printf("%s  ",cocts->name);
		cocts=cocts->next;
	} 
	printf("\n");
	printf("设备为： ");
	Node *dcts=DCTs->next;
	while(dcts!=NULL){
		printf("%s  ",dcts->name);
		dcts=dcts->next;
	} 
	printf("\n");
} 
void show_relation_grap(){
	printf("             设备、控制器、通道的三级关系图\n");
	printf("----------------------------------------------------------------------\n");
	Node *chct;
	Node *coct;
	Node *dct;
	chct=CHCTs->next;
	while(chct!=NULL){
		printf("\n%s\n",chct->name);
		coct=COCTs->next;
		while(coct!=NULL){
			if(coct->parent==chct){
				printf("\t%s\n",coct->name);
				dct=DCTs->next;
				while(dct!=NULL){
					if(dct->parent==coct){
						printf("\t\t%s\n",dct->name);
					}
					dct=dct->next; 
				}
			}
			coct=coct->next;
		}
		chct=chct->next;
	}
	printf("----------------------------------------------------------------------\n");
} 
void add_device(){
	Node *temp=(Node *)malloc(sizeof(Node));
	char _name[10];
	char _type[10];
	char _parentName[10];
	printf("请输入想要添加设备的名称：");
	scanf("%s",_name);
	printf("请输入想要添加设备的类型：");
	scanf("%s",_type);
	printf("请输入想要添加设备的父控制器的名称："); 
	scanf("%s",_parentName);
	int flag=0;  //0---没有找到 1----找到了
	Node *coct=COCTs->next;
	while(coct!=NULL){
		if(strcmp(coct->name,temp->parent->name)==0){  //相等---0  ，不等---1 
			insert_node(DCTs,_name,_type,coct);
				flag=1;
				break;
		}
		coct=coct->next;
	}
	if(!flag){
		printf("你输入的控制器的名称不存在\n");
	}else{
		printf("设备%s添加成功\n",temp->name);
	}
}
void delet_device(){
	
}

void menu(){
	printf("\n");
	printf("*******************************************进程状态切换菜单************************************************\n");
	printf("*                                          1.创建新进程                                                   *\n");
	printf("*                                          2.执行进程时间片到                                             *\n");
	printf("*                                          3.阻塞执行进程                                                 *\n");
	printf("*                                          4.唤醒第一个阻塞进程                                           *\n");
	printf("*                                          5.终止执行进程                                                 *\n");
	printf("*                                          6.查所有状态队列以及当前空白区域的情况                         *\n");
	printf("*                                          7.查看位示图                                                   *\n");
	printf("*                                          8.实现地址转换                                                 *\n");
	printf("*                                          9.创建进程（置换的测试）                                       *\n");
	printf("*                                          10.FIFO置换算法（带内存的）                                    *\n");
	printf("*                                          11.LRU置换算法（带内存的）                                     *\n");
	printf("*                                          12.FIFO置换算法的显示                                          *\n");
	printf("*                                          13.LRU置换算法的显示                                           *\n");
	printf("*                                          20.退出程序                                                    *\n");
	printf("***********************************************************************************************************\n");
}
int main(){
	ready=(PCB*)malloc(sizeof(PCB));
    ready->next=NULL;
    running=(PCB*)malloc(sizeof(PCB));
    running->next=NULL;
    blocked=(PCB*)malloc(sizeof(PCB));
    blocked->next=NULL;
    ms=(m_segment*)malloc(sizeof(m_segment));
    ms->next=NULL;
    
    int size,com_size; 
//	printf("请输入总的内存的大小（KB）:\n"); 
//	scanf("%d",&size);
//	printf("请输入系统所占内存的大小（KB）:\n"); 
//	scanf("%d",&com_size);
	m_segment *temp=(m_segment*)malloc(sizeof(m_segment));
	temp->flag=0;
	temp->start=0;
	temp->length=1024*1024*1024;
    temp->next=NULL;
	ms->next=temp;
//	init_bitmap();
//	show_bitmap();
//	init_mapfree();
//	show_mapfree();
//	

	init_device();
//	printf("hahha");
//	show_relation_grap();
	add_device();
	show_relation_grap();
//	delete_device();	
//	menu();
//	int choice;	
//	do{
//		printf("输入你想选择的功能：\n");
//	    scanf("%d",&choice);
//		switch(choice){
//			case 1:
//				system("cls");
//				int n1;
//				do{
//					p=CreateNewProcess();
//					show_pageTable(p);
//					show();	
//					printf("是否想要继续创建？");
//					scanf("%d",&n1);
//				}while(n1==1);
//				break;
//			case 2:
//				TimeSliceOver();
//				show();
//				break;		
//			case 3:
//	            BlockingProcess();
//	            show();
//	            break;
//	        case 4:
//				WakeupProcess();
//				show();
//				break;
//			case 5:
//				RevokeProcess();
//				show();
//				break;
//			case 6:
//				show();
//				show_blank();
//				break;
//			case 7:
//				system("cls");
//				int n0; 
//				do{
//					show_bitmap();
//					show_mapfree(); 
//					printf("是否想要进行其他的操作？");
//				}while(n0==1);
//				break;
//			case 8: 
//				show_pageTable(p);
//				address_translation(p);
//				break;
//			case 9:
//				system("cls");
//				int n2;
//				do{
//					p1=Create();
//					show_pageTable(p1);	
//					printf("是否想要继续创建？");
//					scanf("%d",&n2);	
//				}while(n2==1);
//				break;
//			case 10:
//				system("cls");
//				int n;
//				do{
//					FIFO_Permutation_algorithm(p1,count_f);
//				    show_FIFO(p1);
//				    printf("还有要执行的页面吗？\n");
//					scanf("%d",&n);
//				    
//				}while(n==1);
//				printf("总次数为：%d\n",num_sum);
//				printf("缺页数为：%d\n",num_miss);
//				printf("缺页率为：%.2f\n",num_miss/(double)num_sum);
//				break; 
//			case 11:
//				system("cls");
//				int m;
//				do{
//					LRU_Permutation_algorithm(p1,count_l);
//				    show_LRU(p1);
//				    printf("还有要执行的页面吗？\n");
//					scanf("%d",&m);   
//				}while(m==1);
//				printf("总次数为：%d\n",num_sum);
//				printf("缺页数为：%d\n",num_miss);
//				printf("缺页率为：%.2f\n",num_miss/(double)num_sum);
//				break;
//		    case 12:
//		    	int n3;
//		    	system("cls");
//		    	do{
//		    		FIFO_P();
//		    		printf("还有继续吗？\n");
//					scanf("%d",&n3);
//				}while(n3==1);
//		    	break;
//			case 13:
//				int n4; 
//				system("cls");
//		    	do{
//		    		FIFO_P();
//		    		printf("还有继续吗？\n");
//					scanf("%d",&n4);
//				}while(n4==1);
//				break; 
//			case 20:
//				exit(0);
//			default:
//				printf("没有这个功能");		
//	   }
//	   	system("cls");
//		menu();
//	}while(choice!=14);
//	system("pause");
	return 0;
} 


 /*
a
5000
8
3072
  
 */
 