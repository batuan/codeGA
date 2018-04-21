#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#define R_c 0.75
#define R_m 0.01
#include <time.h>



typedef struct {
	int maGen[6];
	float r_c;
	float r_m;
	int fitness;
}Gen;

void doiHeSo(float r_c, float r_m){
	float r_c1 = ((float)rand())/((float)RAND_MAX);
	r_c = r_c1;
	float r_m1 = ((float)rand())/((float)RAND_MAX);
	r_m = r_m1;
}	

void show(Gen A){
	int i;
	int sum = 0;
	for(i =0 ; i<6; i++){
		sum += A.maGen[i];
		printf("%d ", A.maGen[i]);
		}
	printf("R_c = %f  ", A.r_c);
	printf("R_m = %f  ", A.r_m);
	printf("sum = %d ", sum);
	printf("fitness = %d ", A.fitness);
	printf("\n");
}

int *KetQua;
Gen *Population;
int *tapLaiGhep;
int *mang;

int check(int A[6]){
	int i;
	for(i =1; i<46; i++){
		if((A[0]!=i)&&(A[1]!=i)&&(A[2]!=i)&&(A[3]!=i)&&(A[4]!=i)&(A[5]!=i)) return i;
	}
}



int max(int A[6]){
	int i, max=A[0];
	for( i = 1; i < 6; i++){
		if(max<A[i]){
			max= A[i];
		}
	}
	return max;
}

int min(int A[6]){
	int i, min=A[0];
	for( i = 1; i < 6; i++){
		if(min>A[i]){
			min= A[i];
		}
	}
	return min;
}



//neu trong gen co 2 nst bang nhau thi thay the 1 cai boi so nho nhat  khac voi cac so trong gen
void thayDoiGen(int A[6], int a){
	int i, j;
	for( i = 0 ; i <a; i++){
		for(j =5; j>a;j--){
			if(A[i]==A[j]){
				A[j] = check(A); 
			}
		}
	}
}

void swapGen(int ma1[], int ma2[], int a){
	int i, temp;
	for( i  = 5; i > a; i--){
		temp = ma1[i];
		ma1[i] = ma2[i];
		ma2[i] =  temp;
	}
}
void LaiGhep(Gen genBo, Gen genMe){
		

		swapGen(genBo.maGen, genMe.maGen, 2);
		thayDoiGen(genBo.maGen,2);
		thayDoiGen(genMe.maGen,2);
		doiHeSo(genBo.r_c, genBo.r_m);
		doiHeSo(genMe.r_c, genMe.r_m);
}

void Dotbien(int A[6]){
	int diemdotbien = rand()%5;
	A[diemdotbien] = 45 - A[diemdotbien];
}

//void DotBien(Gen gen){
//	
//		int diemdotbien = rand()%5;
//		printf("%d ", diemdotbien);
//		printf("\n");
//		gen.maGen[diemdotbien] =  45 - gen.maGen[diemdotbien];
//		doiHeSo(gen);
//}

int xacXuat[46];

void khoiTao(int KetQua[]){
	FILE *fp;
 	fp =  fopen( "ketqua.txt", "r");
 	int i=0;
	 while(!feof(fp)){
 		 		 int buff;
		 		fscanf((FILE*)fp, "%d",&buff);
		 		if(buff<46){
		 			int d = (int) buff;
		 			xacXuat[d]+=1;
				 }
		 		KetQua[i] =buff;
		 		i+=1;
			 }
			 for(i= 1 ; i<46; i++){
			xacXuat[i]-=1;
			//printf("%d ", xacXuat[i]);
		}
		 }
 		
void khoiTaoQuanThe(Gen Population[], int KetQua[]){
	int i,j;
		for(i=0; i<250; i++){
			Population[i].r_c = ((float)rand())/((float)RAND_MAX);
			Population[i].r_m = ((float)rand())/((float)RAND_MAX);
			for(j = 0; j< 6; j++ ){
			Population[i].maGen[j] = KetQua[i*7+j+1];
			Population[i].fitness += (float) KetQua[i*7+j+1];
			}
			Population[i].fitness =  Population[i].fitness/(float) 1500;
		}
	}	

void giaiThuat(){
	int soluong = 0;
		int i,j;
		mang = (int*)malloc(250*sizeof(int));
		for( i = 0; i<250; i++){
		float laighep = Population[i].r_c;
		if(laighep > R_c ) {
		mang[i] =1;
		soluong +=1;
		}
		float dotBien = Population[i].r_m;
		if(dotBien<R_m) {		
			printf("dotbien diem: %d ", i);
			printf("\n");
//			show(Population[i]);
			Dotbien(Population[i].maGen);
			thayDoiGen(Population[i].maGen, 2);
			Population[i].r_c = (float)rand()/RAND_MAX;
			Population[i].r_m = (float)rand()/RAND_MAX;
//			show(Population[i]);			
		}
		}
						
		tapLaiGhep = (int*)malloc(soluong*sizeof(int));
		soluong = 0;
		
		for(i=0; i<250; i++){
		if(mang[i]==1) {
			tapLaiGhep[soluong] = i;
			soluong+=1;
		}
	}
	
	if(soluong%2!=0){
		soluong = soluong -1;
	}
	
	
	for(i = 0; i< soluong; i+=2){
	
		int d1 = tapLaiGhep[i];
		int d2 = tapLaiGhep[i+1];
		printf("lai ghep diem %d va diem %d ", d1,d2);
		printf("\n");
		swapGen(Population[d1].maGen, Population[d2].maGen,2);
		thayDoiGen(Population[d1].maGen,2);		
		thayDoiGen(Population[d2].maGen,2);	
		}
	 //cap nhat lai r_m, r_c
	 for(i = 0 ; i < 250; i++){
	 	Population[i].r_c = (float)rand()/RAND_MAX;
	 	Population[i].r_m = (float)rand()/RAND_MAX;
	 }
	
}


	
	int main(){
		time_t t;
		srand((unsigned) time(&t));
		int d = 1750; 
		KetQua = (int*)malloc(d*sizeof(int));
		Population =(Gen*) malloc(250*sizeof(Gen));
		khoiTao(KetQua);
		khoiTaoQuanThe(Population, KetQua);
		int i;
		for(i =0 ; i<250; i++){
		printf("Diem thu %d  ", i);
		show(Population[i]);
	}	
	printf("\n");
	printf("\n");
	printf("\n");	
		for(i=0; i<100; i++){
			printf("Vong thu : %d", i);
			printf("\n");
			printf("\n");
			printf("\n");
			giaiThuat();
		}
	
	int j;
//	for(i = 0; i < 46; i++){
//		printf("%d  ", xacXuat[i]);
//		}
	
	for(i =0 ; i < 250; i++){
		int fitness = 0;
		for(j = 0; j<6; j++){
			int d = Population[i].maGen[j];
			fitness += xacXuat[d];
		}
		Population[i].fitness = fitness;
	}
	
	int ketquavietlot, min = Population[0].fitness;
	
	for(i = 0; i< 250; i++){
		int d =Population[i].fitness;
		if(min > d){
			min = d;
			ketquavietlot = i;
		}
		
	printf("Diem thu %d  ", i);
	show(Population[i]);
	}
	
		
	printf("min = %d, ketquavietlot = %d ", min, ketquavietlot);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("Ket qua vietlot ngay hom nay la:   ");
	show(Population[ketquavietlot]);
}
	
