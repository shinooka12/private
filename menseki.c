#include<stdio.h>

#define Max_Vertex 100
#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))

typedef struct st_zahyou{
	int x;
	int y;
}ty_zahyou; 
ty_zahyou a[Max_Vertex+1];

typedef struct st_edge{
	int left;
	int right;
}ty_edge;
ty_edge edge[Max_Vertex];
ty_edge tmp;

int n = 4;

void input_xy(){

	int i;
	int x[5]={5,1,1,-7,5}; //n+1の要素数　最後の要素に最初の要素の値を入れる
	int y[5]={-3,0,7,-1,-3}; //上と同様
	
	for(i=0;i<n+1;i++){
		a[i].x = x[i];
		a[i].y = y[i];
		//printf("x=%d y=%d\n",a[i].x,a[i].y);
	}

}


void compute_x(int i,int y,int *xl,int *xr){
	
	int den,num,w;

	den = a[i+1].y-a[i].y;
	num = (y-a[i].y)*(a[i+1].x-a[i].x);
	w = a[i].x+num/den;

	if(num%den == 0){
		*xl = w;
		*xr = w;
	}else if((num%den)*den < 0){
		*xl = w-1;
		*xr = w;
	}else{
		*xl = w;
		*xr = w+1;
	}
}


int main(){

	int ymin;
	int ymax;
	int xla,xra,xlb,xrb;
	int i,j,y,prev,count;
	int area=0; //正方形の数
	int k=0;

	input_xy();
	ymin=2000;
	ymax=-2000;

	for(i=0;i<n;i++){
		if(a[i].y < ymin){
			ymin = a[i].y;
		}
		if(a[i].y > ymax){
			ymax = a[i].y;
		}
	}

	count=1;

	for(y = ymin;y < ymax; y++){
		k=0;
		for (i=0;i<n;i++){
			if((a[i].y <= y && a[i+1].y <= y) || (a[i].y >= y+1 && a[i+1].y >= y+1))
				continue;
			
			compute_x(i,y,&xla,&xra);
			compute_x(i,y+1,&xlb,&xrb); //切り捨て
			//printf("xl(y)=%d xl(y+1)=%d xr(y)=%d xr(y+1)%d\n",xla,xlb,xra,xrb);
			edge[k].left=min(xla,xlb);
			edge[k].right=max(xra,xrb);
			//printf("k=%d left=%d right=%d\n",k,edge[k].left,edge[k].right);
			k++;
		}


		for(i=0;i<k;i++){
			for(j=i+1;j<k;j++){
				if((edge[i].left > edge[j].left) || (edge[i].left == edge[j].left && edge[i].right > edge[j].right)){
					tmp = edge[i];
					edge[i] = edge[j];
					edge[j] = tmp;
				}
			}
		}

		prev = -2000;
		for(i=0;i<k;i+=2){
			//printf("left=%d right=%d area=%d\n",max(edge[i].left,prev),edge[i+1].right,edge[i+1].right - max(edge[i].left,prev));
			area += edge[i+1].right - max(edge[i].left,prev);
			prev = edge[i+1].right;
		}
		printf("下から%d段目の四角形=%d\n",count,area);
		count++;
	}
	printf("\n四角形の合計=%d\n",area);

	return 0;

}




