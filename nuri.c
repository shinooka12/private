#include<stdio.h>

#define True 1
#define False 0
#define MAX_Vertex 100
#define Barrier_Down 0x01
#define Barrier_Up 0x02
#define Barrier_Left 0x04
#define Barrier_Right 0x08
#define Inside 0x10
#define Outside 0x20
#define Max_Queue 1000
#define max(x,y) ((x)>(y) ? (x):(y))
#define min(x,y) ((x)<(y) ? (x):(y))
int n=4;
int xsize=14;
int ysize=12;
int map[20][20]={};
int q_head;
int q_tail;
int q_count;

											
typedef struct zahyou{
  int x;
  int y;
}ty_zahyou;
ty_zahyou a[MAX_Vertex+1];
ty_zahyou queue[Max_Queue];

/*
  void paint(int x,int y){

  if(mark[x][y]==True){
  return;
  }

  mark[x][y]=True;
  paint(x+1, y);
  paint(x-1,y);
  paint(x,y+1);
  paint(x,y-1);

  }
*/

void input_a(){

  int i;
  int x[5]={5,1,1,-7,5};
  int y[5]={-3,0,7,-1,-3};

  for(i=0;i<n+1;i++){
    a[i].x=x[i]+8; //平行移動（一番小さいのを加算）
    a[i].y=y[i]+4; //
  }
}


void put_queue(int x,int y,int mark){

  if(x<0 || y<0 || x>=xsize || y>=ysize){
    return;
  }
  if((map[x][y]&(Inside|Outside))!=0){
    return;
  }

  map[x][y] |= mark;
  queue[q_head].x=x;
  queue[q_head].y=y;
  q_head=(q_head+1)%Max_Queue;
  q_count++;

}

void set_mark(int x,int y,int mark){

  q_head=0;
  q_tail=0;
  q_count=0;
  put_queue(x,y,mark);
  while(q_count>0){
    x=queue[q_tail].x;
    y=queue[q_tail].y;
    q_tail=(q_tail+1)%Max_Queue;
    q_count--;

    if((map[x][y]&Barrier_Left)==0){
      put_queue(x-1,y,mark);
    }
    if((map[x][y]&Barrier_Right)==0){
      put_queue(x+1,y,mark);
    }
    if((map[x][y]&Barrier_Up)==0){
      put_queue(x,y+1,mark);
    }
    if((map[x][y]&Barrier_Down)==0){
      put_queue(x,y-1,mark);
    }
  }

}

int compute_area(){

  int x,y,mark,area;

  for(x=0;x<xsize;x++){
    for(y=0;y<ysize;y++){
      if((map[x][y]&(Inside|Outside))==0){

	if(is_inside(x+0.5,y+0.5)){
	  mark=Inside;
	}else{
	  mark=Outside;
	}
	set_mark(x,y,mark);
      }
    }
  }

  area=0;
  for(x=0;x<xsize;x++){
    for(y=0;y<ysize;y++){

      if((map[x][y]&Inside)!=0){
	area++;
      }
    }
  }
  return (area);
}


int is_inside(double x,double y){

  int count,i;
  double r,w;

  count=0;
  for(i=0;i<n;i++){
    if(max(a[i].y,a[i+1].y)<y){
      continue;
    }
    if(min(a[i].y,a[i+1].y)>y){
      continue;
    }

    r=(double)(a[i+1].x-a[i].x)/(double)(a[i+1].y-a[i].y);

    w=r*(y-a[i].y)+a[i].x;
    if(w>x){
      count++;
    }
  }

  if(count%2 != 0){
    return (True);
  }else{
    return (False);
  }
}

void print_map(){///***test
  int i, j;
  printf("========\n");
  for(i = 0; i < ysize+1; i++){
    for(j = 0; j < xsize+1; j++){
      printf("%2d ", map[j][ysize-i]);
    }
    printf("\n");
  }
  printf("\n");
}

void print_a(){
  int i, j, k;
  int flag;
  for(i = 0; i < ysize+1; i++){
    for(j = 0; j < xsize+1; j++){
      flag = 0;
      for(k = 0; k < n; k++){
	if(a[k].y == ysize-i && a[k].x == j){
	  printf("@@ ");
	  flag = 1;
	}
      }
      if(!flag){
	printf("++ ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

int main(){

  int s,t,x,y,i,j;
  int distance;
  int dx,dy,xa,xb;
  int area;

  input_a();
  //print_a();///***test

  for(i=0;i<n;i++){
    //print_map();///***test

    if(a[i].y==a[i+1].y){

      distance=abs(a[i].x-a[i+1].x);
      if(a[i].x<a[i+1].x){

	for(j=a[i].x;j<distance+a[i].x;j++){
	  map[j][a[i].y] |= Barrier_Down;
	  map[j][a[i].y-1] |= Barrier_Up;

	}
      }else{

	for(j=a[i+1].x;j<distance+a[i+1].x;j++){
	  map[j][a[i].y] |= Barrier_Down;
	  map[j][a[i].y-1] |= Barrier_Up;
	}
      }
    }


    if(a[i].x==a[i+1].x){

      distance=abs(a[i].y-a[i+1].y);
      if(a[i].y<a[i+1].y){

	for(j=a[i].y;j<distance+a[i].y;j++){
	  map[a[i].x][j] |= Barrier_Left;
	  map[a[i].x-1][j] |= Barrier_Right;
	}
      }else{

	for(j=a[i+1].y;j<distance+a[i+1].y;j++){
	  map[a[i].x][j] |= Barrier_Left;
	  map[a[i].x-1][j] |= Barrier_Right;
	}
      }
    }


    if(a[i].y < a[i+1].y){
      s=i;
      t=i+1;
    }else{
      s=i+1;
      t=i;
    }

    dx=a[t].x-a[s].x;
    dy=a[t].y-a[s].y;
    xa=a[s].x*dy;
    for (y=a[s].y;y<a[t].y;y++){
      xb=xa+dx;
      for(x=min(xa,xb)/dy;x<(max(xa,xb)+dy-1)/dy;x++){
	map[x][y] |= Inside;
      }
      xa=xb;
    }

  }
  //print_map();///***test
  area=compute_area();
  printf("area=%d\n",area);
  //print_map();///***test

  return 0;
}

																				
