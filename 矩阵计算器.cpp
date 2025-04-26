#include<stdio.h>
#include<malloc.h>
#include<math.h>
#define negative1 m1<=0||n1<=0
#define negative2 m2<=0||n2<=0 
void matrix_A(int Alr[2]);     //确定一般矩阵A的行列 
void matrix_squA(int Alr[2]);  //确定方阵A的行列 
void matrix_squB(int Blr[2],int m1,int n1);  //确定一般矩阵B的行列 
double **matrix_in(int m,int n);   //输入矩阵
double **matrix_set(int m,int n);  //存放结果矩阵 
void matrix_out(double **p3,int m,int n);  //输出矩阵
void matrix_tra(double **p1,double **p3,int m,int n);  //转置
void matrix_add(double **p1,double **p2,double **p3,int m,int n); //求和
void matrix_sub(double **p1,double **p2,double **p3,int m,int n);  //相减
void matrix_mul(double **p1,double **p2,double **p3,int m,int n,int sn);  //相乘
void matrix_cof(double **p1,double **p,int m1,int m,int n);  //余子式
double matrix_det(double **p1, int m);  //行列式
void matrix_adj(double **p1,double **p3,int m1); //伴随矩阵A*
void matrix_inv(double **p1,double **p3,int m1);  //逆矩阵A-1
int counter_continue(double **p1,int m1,int n1);  //在原计算结果上继续运算
int choice1(double **p1,int m1,int n1);  //仅能选择是否继续进行计算
int choice2(double **p1,double **p2,int m1,int n1,int m2,int n2);  //既选择是否继续计算又选择本次计算原矩阵a（二选一）
int choice3(double **p1,double **p2,double **p3,int m1,int n1,int m2,int n2,int m3,int n3);  //既选择是否继续计算又选择本次计算原矩阵a（三选一）
int main() {
	int m2,n2,m,n,ord=0,wait,Alr[2]={0},Blr[2]={0};
	double **p1,**p2,**p3;
	do {
		switch(ord) {
			case 0:
				printf("矩阵计算器启动!\n");
				printf("!命令:\n 0.退出;\n 1.求转置矩阵;\n 2.两个矩阵相加;\n 3.两个矩阵相减;\n 4.求两个矩阵的乘积;\n 5.求余子式矩阵;\n 6.求方阵的行列式;\n 7.求方阵A的伴随矩阵A*;\n 8.求方阵A的逆矩阵A-1;\n");
				break;
			case 1:
				printf("@矩阵转置:\n");
				matrix_A(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				p3=matrix_set(Alr[1],Alr[0]);
				matrix_tra(p1,p3,Alr[0],Alr[1]);
				printf("#转置结果：\n");
				matrix_out(p3, Alr[1], Alr[0]);
				ord=choice2(p1,p3,Alr[0],Alr[1],Alr[1],Alr[0]);
				free(p1);
				free(p3);
				break;
			case 2:
				printf("@两个矩阵相加:\n");
				matrix_A(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				matrix_squB(Blr,Alr[0],Alr[1]);
				p2=matrix_in(Blr[0],Blr[1]);
				p3=matrix_set(Alr[0],Alr[1]);
				matrix_add(p1,p2,p3,Alr[0],Alr[1]);
				printf("#求和结果：\n");
				matrix_out(p3, Alr[0], Alr[1]);
				ord=choice3(p1,p2,p3,Alr[0],Alr[1],Blr[0],Blr[1],Alr[0],Alr[1]);
				free(p1);
				free(p2);
				free(p3);
				break;
			case 3:
				printf("@两个矩阵相减:\n");
				matrix_A(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				matrix_squB(Blr,Alr[0],Alr[1]);
				p2=matrix_in(Blr[0],Blr[1]);
				p3=matrix_set(Alr[0],Alr[1]);
				matrix_sub(p1,p2,p3,Alr[0],Alr[1]);
				printf("#相减结果：\n");
				matrix_out(p3, Alr[0], Alr[1]);
				ord=choice3(p1,p2,p3,Alr[0],Alr[1],Blr[0],Blr[1],Alr[0],Alr[1]);
				free(p1);
				free(p2);
				free(p3);
				break;
			case 4:
				printf("@两个矩阵相乘:\n");
				matrix_A(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				printf("请输入矩阵B的行数和列数：");
				scanf("%d%d",&m2,&n2);
				while(Alr[1]-m2!=0||negative2) {
					printf("矩阵A与B行列不符，请重新输入矩阵B大小！\n");
					printf("请输入矩阵B的行数和列数：");
					scanf("%d%d",&m2,&n2);
				}
				printf("请输入矩阵B：\n");
				p2=matrix_in(m2,n2);
				p3=matrix_set(Alr[0],n2);
				matrix_mul(p1,p2,p3,Alr[0],n2,Alr[1]);
				printf("#相乘结果：\n");
				matrix_out(p3, Alr[0], n2);
				ord=choice3(p1,p2,p3,Alr[0],Alr[1],m2,n2,Alr[0],n2);
				free(p1);
				free(p2);
				free(p3);
				break;
			case 5:
				printf("@求余子式矩阵:\n");
				matrix_squA(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				printf("请输入要删除的行列：\n");
				scanf("%d%d",&m,&n);
				while(m>Alr[0]||n>Alr[1]||m<=0||n<=0) {
					printf("输入行列错误，请重新输入！\n");
					printf("请输入要删除的行列：\n");
					scanf("%d%d",&m,&n);
				}
				if(Alr[0]-1!=0) {
					p3=matrix_set(Alr[0]-1,Alr[0]-1);
					matrix_cof(p1,p3,Alr[0],m-1,n-1);
					printf("#余子式矩阵：\n");
					matrix_out(p3, Alr[0]-1, Alr[1]-1);
					ord=choice2(p1,p3,Alr[0],Alr[1],Alr[0]-1,Alr[1]-1);
					free(p1);
					free(p3);
				} else {
					printf("#该方阵不存在余子式矩阵！\n\n");
					ord=choice1(p1,Alr[0],Alr[1]);
					free(p1);
				}
				break;
			case 6:
				printf("@求方阵的行列式:\n");
				matrix_squA(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				printf("#行列式：");
				printf("%lf\n\n",matrix_det(p1, Alr[0]));
				ord=choice1(p1,Alr[0],Alr[1]);
				free(p1);
				break;
			case 7:
				printf("@求方阵A的伴随矩阵A*:\n");
				matrix_squA(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				if(Alr[0]-1!=0) {
					p3=matrix_set(Alr[0],Alr[1]);
					matrix_adj(p1,p3,Alr[0]);
					printf("#伴随矩阵A*：\n");
					matrix_out(p3, Alr[0], Alr[1]);
					ord=choice2(p1,p3,Alr[0],Alr[1],Alr[0],Alr[1]);
					free(p1);
					free(p3);
				} else {
					printf("#该方阵不存在伴随矩阵！\n\n");
					ord=choice1(p1,Alr[0],Alr[1]);
					free(p1);
				}
				break;
			case 8:
				printf("@求方阵A的逆矩阵A-1:\n");
				matrix_squA(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				if(matrix_det(p1,Alr[0])&&Alr[0]-1!=0) {
					p3=matrix_set(Alr[0],Alr[1]);
					matrix_inv(p1,p3,Alr[0]);
					printf("#逆矩阵A-1：\n");
					matrix_out(p3, Alr[0], Alr[1]);
					ord=choice2(p1,p3,Alr[0],Alr[1],Alr[0],Alr[1]);
					free(p1);
					free(p3);
				} else {
					printf("#该方阵不存在逆矩阵！\n\n");
					ord=choice1(p1,Alr[0],Alr[1]);
					free(p1);
				}
				break;
			default:
				printf("无效命令，请重新输入!\n");
				break;
		}
		printf("请输入命令（开始新一次运算）:");
		scanf("%d",&ord);
		if(ord==0) {
			printf("\n矩阵计算器关机！\n");
		}
	} while(ord);
	scanf("%d",&wait);
	return 0;
}
void matrix_A(int Alr[2]){
	printf("请输入矩阵A的行数和列数：");
				scanf("%d%d",&Alr[0],&Alr[1]);
				while(Alr[0]<=0||Alr[1]<=0) {
					printf("输入行列错误，请重新输入！\n");
					printf("请输入矩阵A的行数和列数：");
					scanf("%d%d",&Alr[0],&Alr[1]);
				}
				printf("请输入方阵A：\n");
}
void matrix_squA(int Alr[2]){
	printf("请输入方阵A的行数和列数：");
				scanf("%d%d",&Alr[0],&Alr[1]);
				while(Alr[0]-Alr[1]!=0||Alr[0]<=0||Alr[1]<=0) {
					printf("不是方阵，请重新输入！\n");
					printf("请输入方阵A的行数和列数：");
					scanf("%d%d",&Alr[0],&Alr[1]);
				}
				printf("请输入方阵A：\n");
}
void matrix_squB(int Blr[2],int m1,int n1){
	printf("请输入矩阵B的行数和列数：");
				scanf("%d%d",&Blr[0],&Blr[1]);
				while(m1-Blr[0]!=0||n1-Blr[1]!=0||Blr[0]<=0||Blr[1]<=0) {
					printf("矩阵A与B行列不符，请重新输入矩阵B大小！\n");
					printf("请输入矩阵B的行数和列数：");
					scanf("%d%d",&Blr[0],&Blr[1]);
				}
				printf("请输入矩阵B：\n");
}
double **matrix_in(int m,int n) {
	int i,j;
	double **p;
	p=(double **)malloc(m*sizeof(double *));
	for(i=0; i<m; i++) {
		p[i]=(double *)malloc(n*sizeof(double));
	}
	for(i=0; i<m; i++) {
		printf("请输入第%d行:",i+1);
		for(j=0; j<n; j++) {
			scanf("%lf",&p[i][j]);
		}
	}
	return p;
}
double **matrix_set(int m,int n) {
	int i;
	double **p;
	p=(double **)malloc(m*sizeof(double *));
	for(i=0; i<m; i++) {
		p[i]=(double *)malloc(n*sizeof(double));
	}
	return p;
}
void matrix_out(double **p3,int m,int n) {
	int i,j;
	if(m&&n) {
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				printf(" %.3lf ",p3[i][j]);
			}
			printf("\n");
		}
	} else {
		printf("矩阵不存在！\n\n");
	}
}
void matrix_tra(double **p1, double **p3,int m,int n) {
	int i,j;
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++) {
			p3[j][i]=p1[i][j];
		}
	}
}
void matrix_add(double **p1, double **p2,double **p3,int m,int n) {
	int i,j;
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++) {
			p3[i][j]=p1[i][j]+p2[i][j];
		}
	}
}
void matrix_sub(double **p1, double **p2, double **p3, int m, int n) {
	int i,j;
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++) {
			p3[i][j]=p1[i][j]-p2[i][j];
		}
	}
}
void matrix_mul(double **p1, double **p2, double **p3, int m, int n,int sn) {
	int i,j,k;
	double s;
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++) {
			s=0;
			for(k=0; k<sn; k++) {
				s+=p1[i][k]*p2[k][j];
			}
			p3[i][j]=s;
		}
	}
}
void matrix_cof(double **p1, double **p3, int m1, int m, int n) {
	int i,j;
	for(i=0; i<m1-1; i++) {
		for(j=0; j<m1-1; j++) {
			if(i<m&&j<n) {
				p3[i][j]=p1[i][j];
			} else if(i>=m&&j<n) {
				p3[i][j]=p1[i+1][j];
			} else if(i<m&&j>=n) {
				p3[i][j]=p1[i][j+1];
			} else if(i>=m&&j>=n) {
				p3[i][j]=p1[i+1][j+1];
			}
		}
	}
}
double matrix_det(double **p1,int m1) {
	int i;
	double s=0;
	double **p4;
	if(m1-1==0) {
		s=p1[0][0];
	} else {
		p4=matrix_set(m1-1,m1-1);
		for(i=0; i<m1; i++) {
			matrix_cof(p1,p4,m1,0,i);
			s+=pow(-1,i)*p1[0][i]*matrix_det(p4,m1-1); //定义法求行列式
		}
	}
	return s;
}
void matrix_adj(double **p1,double **p3,int m1) {
	int i,j;
	double **p4;
	double **p5;
	p4=matrix_set(m1-1,m1-1);
	p5=matrix_set(m1,m1);
	for(i=0; i<m1; i++) {
		for(j=0; j<m1; j++) {
			matrix_cof(p1,p4,m1,i,j);
			p5[i][j]=matrix_det(p4,m1-1)*pow(-1,(i+1)+(j+1));
		}
	}
	matrix_tra(p5,p3,m1,m1);
}
void matrix_inv(double **p1,double **p3,int m1) {
	int i,j;
	double **p4;
	p4=matrix_set(m1,m1);
	matrix_adj(p1,p4,m1);
	for(i=0; i<m1; i++) {
		for(j=0; j<m1; j++) {
			p3[i][j]=p4[i][j]/matrix_det(p1,m1);
		}
	}
}
int counter_continue(double **p1,int m1,int n1) {
	int m2,n2,m,n,ord=0,smallord=0,Blr[2]={0};
	double **p2,**p3;
	printf("本次运算继续！\n&本次计算原矩阵A:\n");
	matrix_out(p1,m1,n1);
	do {
		printf("请输入命令（继续本次运算）:");
		scanf("%d",&ord);
		switch(ord) {
			case 0:
				printf("本次运算结束！\n\n@新运算开始:\n");
				break;
			case 1:
				printf("@矩阵转置:\n");
				p3=matrix_set(n1,m1);
				matrix_tra(p1, p3, m1, n1);
				printf("#转置结果：\n");
				matrix_out(p3, n1, m1);
				ord=choice2(p1,p3,m1,n1,n1,m1);
				break;
			case 2:
				printf("@两个矩阵相加:\n");
				matrix_squB(Blr,m1,n1);
				p2=matrix_in(Blr[0],Blr[1]);
				p3=matrix_set(m1,n1);
				matrix_add(p1, p2, p3, m1, n1);
				printf("#求和结果：\n");
				matrix_out(p3, m1, n1);
				ord=choice3(p1,p2,p3,m1,n1,Blr[0],Blr[1],m1,n1);
				break;
			case 3:
				printf("@两个矩阵相减:\n");
				matrix_squB(Blr,m1,n1);
				p2=matrix_in(Blr[0],Blr[1]);
				p3=matrix_set(m1,n1);
				matrix_sub(p1, p2, p3, m1, n1);
				printf("#相减结果：\n");
				matrix_out(p3, m1, n1);
				ord=choice3(p1,p2,p3,m1,n1,Blr[0],Blr[1],m1,n1);
				break;
			case 4:
				printf("@两个矩阵相乘:\n");
				printf("请输入矩阵B的行数和列数：");
				scanf("%d%d",&m2,&n2);
				while(n1-m2!=0||negative2) {
					printf("矩阵A与B行列不符，请重新输入矩阵B大小！\n");
					printf("请输入矩阵B的行数和列数：");
					scanf("%d%d",&m2,&n2);
				}
				printf("请输入矩阵B：\n");
				p2=matrix_in(m2,n2);
				p3=matrix_set(m1,n2);
				matrix_mul(p1, p2, p3, m1, n2, n1);
				printf("#相乘结果：\n");
				matrix_out(p3, m1, n2);
				ord=choice3(p1,p2,p3,m1,n1,m2,n2,m1,n2);
				break;
			case 5:
				printf("@求余子式矩阵:\n");
				if(m1-n1!=0) {
					printf("#不是方阵，无余子式矩阵！\n\n");
					ord=choice1(p1,m1,n1);
				} else {
					if(m1-1!=0) {
						printf("请输入要删除的行列：\n");
						scanf("%d%d",&m,&n);
						while(m>m1||n>n1||m<=0||n<=0) {
							printf("输入行列错误，请重新输入！\n");
							printf("请输入要删除的行列：\n");
							scanf("%d%d",&m,&n);
						}
						p3=matrix_set(m1-1, n1-1);
						matrix_cof(p1, p3, m1, m-1, n-1);
						printf("#余子式矩阵：\n");
						matrix_out(p3, m1-1, n1-1);
						ord=choice2(p1,p3,m1,n1,m1-1,n1-1);
					} else {
						printf("#该方阵不存在余子式矩阵！\n\n");
						ord=choice1(p1,m1,n1);
					}
				}
				break;
			case 6:
				printf("@求方阵的行列式:\n");
				if(m1-n1!=0) {
					printf("#不是方阵，无行列式！\n\n");
				} else {
					printf("#行列式：");
					printf("%lf\n",matrix_det(p1, m1));
				}
				ord=choice1(p1,m1,n1);
				break;
			case 7:
				printf("@求方阵A的伴随矩阵A*:\n");
				if(m1-n1!=0) {
					printf("#不是方阵，无伴随矩阵！\n\n");
					ord=choice1(p1,m1,n1);
				} else {
					if(m1-1!=0) {
						p3=matrix_set(m1,n1);
						matrix_adj(p1,p3,m1);
						printf("#伴随矩阵A*：\n");
						matrix_out(p3, m1, n1);
						ord=choice2(p1,p3,m1,n1,m1,n1);
					} else {
						printf("#该方阵不存在伴随矩阵！\n\n");
						ord=choice1(p1,m1,n1);	
					}
				}
				break;
			case 8:
				printf("@求方阵A的逆矩阵A-1:\n");
				if(m1-n1!=0) {
					printf("#不是方阵，无逆矩阵！\n\n");
					ord=choice1(p1,m1,n1);
				} else {
					if(m1-1!=0&&matrix_det(p1,m1)) {
						p3=matrix_set(m1,n1);
						matrix_inv(p1,p3,m1);
						printf("#逆矩阵A-1：\n");
						matrix_out(p3, m1, n1);
						ord=choice2(p1,p3,m1,n1,m1,n1);
					} else {
						printf("#该方阵不存在逆矩阵！\n\n");
						ord=choice1(p1,m1,n1);
					}
				}
				break;
			default:
				printf("无效命令，请重新输入!\n");
				break;
		}
	} while(ord);
	return 0;
}
int choice1(double **p1,int m1,int n1) {
	int ord=0;
	do {
		printf("是否以上次计算原矩阵A作为本次计算原矩阵继续运算？\n 1.是;\n 0.否;\n是否继续本次运算:");
		scanf("%d",&ord);
		if(ord-1==0) {
			ord=counter_continue(p1,m1,n1);    //退出继续运算时返回0
			break;
		} else if(!ord) {
			printf("本次运算结束！\n\n@新运算开始:\n");
			break;
		} else {
			printf("无效选择，请重新选择是否继续本次运算！\n");
		}
	} while(ord);
	return 0;
}
int choice2(double **p1,double **p2,int m1,int n1,int m2,int n2) {
	int ord=0,smallord=0;
	do {
		printf("是否继续本次运算？\n 1.是;\n 0.否;\n是否继续本次运算:");
		scanf("%d",&ord);
		if(ord-1==0) {
			while(1) {
				printf("请选择上次计算的原矩阵或结果矩阵作为本次计算的原矩阵:\n 1.上次计算的原矩阵A;\n 2.上次计算的结果矩阵;\n请选择本次计算原矩阵:");
				scanf("%d",&smallord);
				if(smallord-1==0) {
					ord=counter_continue(p1,m1,n1);
					break;
				} else if(smallord-2==0) {
					ord=counter_continue(p2,m2,n2);
					break;
				} else {
					printf("无效选择，请重新选择本次计算原矩阵！\n");
				}
			}
			break;
		} else if(!ord) {
			printf("本次运算结束！\n\n@新运算开始:\n");
			break;
		} else {
			printf("无效选择，请重新选择是否继续本次计算！\n");
		}
	} while(ord);
	return 0;
}
int choice3(double **p1,double **p2,double **p3,int m1,int n1,int m2,int n2,int m3,int n3) {
	int ord=0,smallord=0;
	do {
		printf("是否继续本次运算？\n 1.是;\n 0.否;\n是否继续本次运算:");
		scanf("%d",&ord);
		if(ord-1==0) {
			while(1) {
				printf("请选择上次计算的原矩阵或结果矩阵作为本次计算的矩阵:\n 1.上次计算的原矩阵A;\n 2.上次计算的原矩阵B;\n 3.上次计算的结果矩阵;\n请选择本次计算原矩阵:");
				scanf("%d",&smallord);
				if(smallord-1==0) {
					ord=counter_continue(p1,m1,n1);
					break;
				} else if(smallord-2==0) {
					ord=counter_continue(p2,m2,n2);
					break;
				} else if(smallord-3==0) {
					ord=counter_continue(p3,m3,n3);
					break;
				} else {
					printf("无效选择，请重新选择本次计算原矩阵！\n");
				}
			}
			break;
		} else if(!ord) {
			printf("本次运算结束！\n\n@新运算开始:\n");
			break;
		} else {
			printf("无效选择，请重新选择是否继续本次运算！\n");
		}
	} while(ord);
	return 0;
}
