#include<stdio.h>
#include<malloc.h>
#include<math.h>
#define negative1 m1<=0||n1<=0
#define negative2 m2<=0||n2<=0 
void matrix_A(int Alr[2]);     //ȷ��һ�����A������ 
void matrix_squA(int Alr[2]);  //ȷ������A������ 
void matrix_squB(int Blr[2],int m1,int n1);  //ȷ��һ�����B������ 
double **matrix_in(int m,int n);   //�������
double **matrix_set(int m,int n);  //��Ž������ 
void matrix_out(double **p3,int m,int n);  //�������
void matrix_tra(double **p1,double **p3,int m,int n);  //ת��
void matrix_add(double **p1,double **p2,double **p3,int m,int n); //���
void matrix_sub(double **p1,double **p2,double **p3,int m,int n);  //���
void matrix_mul(double **p1,double **p2,double **p3,int m,int n,int sn);  //���
void matrix_cof(double **p1,double **p,int m1,int m,int n);  //����ʽ
double matrix_det(double **p1, int m);  //����ʽ
void matrix_adj(double **p1,double **p3,int m1); //�������A*
void matrix_inv(double **p1,double **p3,int m1);  //�����A-1
int counter_continue(double **p1,int m1,int n1);  //��ԭ�������ϼ�������
int choice1(double **p1,int m1,int n1);  //����ѡ���Ƿ�������м���
int choice2(double **p1,double **p2,int m1,int n1,int m2,int n2);  //��ѡ���Ƿ����������ѡ�񱾴μ���ԭ����a����ѡһ��
int choice3(double **p1,double **p2,double **p3,int m1,int n1,int m2,int n2,int m3,int n3);  //��ѡ���Ƿ����������ѡ�񱾴μ���ԭ����a����ѡһ��
int main() {
	int m2,n2,m,n,ord=0,wait,Alr[2]={0},Blr[2]={0};
	double **p1,**p2,**p3;
	do {
		switch(ord) {
			case 0:
				printf("�������������!\n");
				printf("!����:\n 0.�˳�;\n 1.��ת�þ���;\n 2.�����������;\n 3.�����������;\n 4.����������ĳ˻�;\n 5.������ʽ����;\n 6.���������ʽ;\n 7.����A�İ������A*;\n 8.����A�������A-1;\n");
				break;
			case 1:
				printf("@����ת��:\n");
				matrix_A(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				p3=matrix_set(Alr[1],Alr[0]);
				matrix_tra(p1,p3,Alr[0],Alr[1]);
				printf("#ת�ý����\n");
				matrix_out(p3, Alr[1], Alr[0]);
				ord=choice2(p1,p3,Alr[0],Alr[1],Alr[1],Alr[0]);
				free(p1);
				free(p3);
				break;
			case 2:
				printf("@�����������:\n");
				matrix_A(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				matrix_squB(Blr,Alr[0],Alr[1]);
				p2=matrix_in(Blr[0],Blr[1]);
				p3=matrix_set(Alr[0],Alr[1]);
				matrix_add(p1,p2,p3,Alr[0],Alr[1]);
				printf("#��ͽ����\n");
				matrix_out(p3, Alr[0], Alr[1]);
				ord=choice3(p1,p2,p3,Alr[0],Alr[1],Blr[0],Blr[1],Alr[0],Alr[1]);
				free(p1);
				free(p2);
				free(p3);
				break;
			case 3:
				printf("@�����������:\n");
				matrix_A(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				matrix_squB(Blr,Alr[0],Alr[1]);
				p2=matrix_in(Blr[0],Blr[1]);
				p3=matrix_set(Alr[0],Alr[1]);
				matrix_sub(p1,p2,p3,Alr[0],Alr[1]);
				printf("#��������\n");
				matrix_out(p3, Alr[0], Alr[1]);
				ord=choice3(p1,p2,p3,Alr[0],Alr[1],Blr[0],Blr[1],Alr[0],Alr[1]);
				free(p1);
				free(p2);
				free(p3);
				break;
			case 4:
				printf("@�����������:\n");
				matrix_A(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				printf("���������B��������������");
				scanf("%d%d",&m2,&n2);
				while(Alr[1]-m2!=0||negative2) {
					printf("����A��B���в������������������B��С��\n");
					printf("���������B��������������");
					scanf("%d%d",&m2,&n2);
				}
				printf("���������B��\n");
				p2=matrix_in(m2,n2);
				p3=matrix_set(Alr[0],n2);
				matrix_mul(p1,p2,p3,Alr[0],n2,Alr[1]);
				printf("#��˽����\n");
				matrix_out(p3, Alr[0], n2);
				ord=choice3(p1,p2,p3,Alr[0],Alr[1],m2,n2,Alr[0],n2);
				free(p1);
				free(p2);
				free(p3);
				break;
			case 5:
				printf("@������ʽ����:\n");
				matrix_squA(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				printf("������Ҫɾ�������У�\n");
				scanf("%d%d",&m,&n);
				while(m>Alr[0]||n>Alr[1]||m<=0||n<=0) {
					printf("�������д������������룡\n");
					printf("������Ҫɾ�������У�\n");
					scanf("%d%d",&m,&n);
				}
				if(Alr[0]-1!=0) {
					p3=matrix_set(Alr[0]-1,Alr[0]-1);
					matrix_cof(p1,p3,Alr[0],m-1,n-1);
					printf("#����ʽ����\n");
					matrix_out(p3, Alr[0]-1, Alr[1]-1);
					ord=choice2(p1,p3,Alr[0],Alr[1],Alr[0]-1,Alr[1]-1);
					free(p1);
					free(p3);
				} else {
					printf("#�÷��󲻴�������ʽ����\n\n");
					ord=choice1(p1,Alr[0],Alr[1]);
					free(p1);
				}
				break;
			case 6:
				printf("@���������ʽ:\n");
				matrix_squA(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				printf("#����ʽ��");
				printf("%lf\n\n",matrix_det(p1, Alr[0]));
				ord=choice1(p1,Alr[0],Alr[1]);
				free(p1);
				break;
			case 7:
				printf("@����A�İ������A*:\n");
				matrix_squA(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				if(Alr[0]-1!=0) {
					p3=matrix_set(Alr[0],Alr[1]);
					matrix_adj(p1,p3,Alr[0]);
					printf("#�������A*��\n");
					matrix_out(p3, Alr[0], Alr[1]);
					ord=choice2(p1,p3,Alr[0],Alr[1],Alr[0],Alr[1]);
					free(p1);
					free(p3);
				} else {
					printf("#�÷��󲻴��ڰ������\n\n");
					ord=choice1(p1,Alr[0],Alr[1]);
					free(p1);
				}
				break;
			case 8:
				printf("@����A�������A-1:\n");
				matrix_squA(Alr);
				p1=matrix_in(Alr[0],Alr[1]);
				if(matrix_det(p1,Alr[0])&&Alr[0]-1!=0) {
					p3=matrix_set(Alr[0],Alr[1]);
					matrix_inv(p1,p3,Alr[0]);
					printf("#�����A-1��\n");
					matrix_out(p3, Alr[0], Alr[1]);
					ord=choice2(p1,p3,Alr[0],Alr[1],Alr[0],Alr[1]);
					free(p1);
					free(p3);
				} else {
					printf("#�÷��󲻴��������\n\n");
					ord=choice1(p1,Alr[0],Alr[1]);
					free(p1);
				}
				break;
			default:
				printf("��Ч�������������!\n");
				break;
		}
		printf("�����������ʼ��һ�����㣩:");
		scanf("%d",&ord);
		if(ord==0) {
			printf("\n����������ػ���\n");
		}
	} while(ord);
	scanf("%d",&wait);
	return 0;
}
void matrix_A(int Alr[2]){
	printf("���������A��������������");
				scanf("%d%d",&Alr[0],&Alr[1]);
				while(Alr[0]<=0||Alr[1]<=0) {
					printf("�������д������������룡\n");
					printf("���������A��������������");
					scanf("%d%d",&Alr[0],&Alr[1]);
				}
				printf("�����뷽��A��\n");
}
void matrix_squA(int Alr[2]){
	printf("�����뷽��A��������������");
				scanf("%d%d",&Alr[0],&Alr[1]);
				while(Alr[0]-Alr[1]!=0||Alr[0]<=0||Alr[1]<=0) {
					printf("���Ƿ������������룡\n");
					printf("�����뷽��A��������������");
					scanf("%d%d",&Alr[0],&Alr[1]);
				}
				printf("�����뷽��A��\n");
}
void matrix_squB(int Blr[2],int m1,int n1){
	printf("���������B��������������");
				scanf("%d%d",&Blr[0],&Blr[1]);
				while(m1-Blr[0]!=0||n1-Blr[1]!=0||Blr[0]<=0||Blr[1]<=0) {
					printf("����A��B���в������������������B��С��\n");
					printf("���������B��������������");
					scanf("%d%d",&Blr[0],&Blr[1]);
				}
				printf("���������B��\n");
}
double **matrix_in(int m,int n) {
	int i,j;
	double **p;
	p=(double **)malloc(m*sizeof(double *));
	for(i=0; i<m; i++) {
		p[i]=(double *)malloc(n*sizeof(double));
	}
	for(i=0; i<m; i++) {
		printf("�������%d��:",i+1);
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
		printf("���󲻴��ڣ�\n\n");
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
			s+=pow(-1,i)*p1[0][i]*matrix_det(p4,m1-1); //���巨������ʽ
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
	printf("�������������\n&���μ���ԭ����A:\n");
	matrix_out(p1,m1,n1);
	do {
		printf("��������������������㣩:");
		scanf("%d",&ord);
		switch(ord) {
			case 0:
				printf("�������������\n\n@�����㿪ʼ:\n");
				break;
			case 1:
				printf("@����ת��:\n");
				p3=matrix_set(n1,m1);
				matrix_tra(p1, p3, m1, n1);
				printf("#ת�ý����\n");
				matrix_out(p3, n1, m1);
				ord=choice2(p1,p3,m1,n1,n1,m1);
				break;
			case 2:
				printf("@�����������:\n");
				matrix_squB(Blr,m1,n1);
				p2=matrix_in(Blr[0],Blr[1]);
				p3=matrix_set(m1,n1);
				matrix_add(p1, p2, p3, m1, n1);
				printf("#��ͽ����\n");
				matrix_out(p3, m1, n1);
				ord=choice3(p1,p2,p3,m1,n1,Blr[0],Blr[1],m1,n1);
				break;
			case 3:
				printf("@�����������:\n");
				matrix_squB(Blr,m1,n1);
				p2=matrix_in(Blr[0],Blr[1]);
				p3=matrix_set(m1,n1);
				matrix_sub(p1, p2, p3, m1, n1);
				printf("#��������\n");
				matrix_out(p3, m1, n1);
				ord=choice3(p1,p2,p3,m1,n1,Blr[0],Blr[1],m1,n1);
				break;
			case 4:
				printf("@�����������:\n");
				printf("���������B��������������");
				scanf("%d%d",&m2,&n2);
				while(n1-m2!=0||negative2) {
					printf("����A��B���в������������������B��С��\n");
					printf("���������B��������������");
					scanf("%d%d",&m2,&n2);
				}
				printf("���������B��\n");
				p2=matrix_in(m2,n2);
				p3=matrix_set(m1,n2);
				matrix_mul(p1, p2, p3, m1, n2, n1);
				printf("#��˽����\n");
				matrix_out(p3, m1, n2);
				ord=choice3(p1,p2,p3,m1,n1,m2,n2,m1,n2);
				break;
			case 5:
				printf("@������ʽ����:\n");
				if(m1-n1!=0) {
					printf("#���Ƿ���������ʽ����\n\n");
					ord=choice1(p1,m1,n1);
				} else {
					if(m1-1!=0) {
						printf("������Ҫɾ�������У�\n");
						scanf("%d%d",&m,&n);
						while(m>m1||n>n1||m<=0||n<=0) {
							printf("�������д������������룡\n");
							printf("������Ҫɾ�������У�\n");
							scanf("%d%d",&m,&n);
						}
						p3=matrix_set(m1-1, n1-1);
						matrix_cof(p1, p3, m1, m-1, n-1);
						printf("#����ʽ����\n");
						matrix_out(p3, m1-1, n1-1);
						ord=choice2(p1,p3,m1,n1,m1-1,n1-1);
					} else {
						printf("#�÷��󲻴�������ʽ����\n\n");
						ord=choice1(p1,m1,n1);
					}
				}
				break;
			case 6:
				printf("@���������ʽ:\n");
				if(m1-n1!=0) {
					printf("#���Ƿ���������ʽ��\n\n");
				} else {
					printf("#����ʽ��");
					printf("%lf\n",matrix_det(p1, m1));
				}
				ord=choice1(p1,m1,n1);
				break;
			case 7:
				printf("@����A�İ������A*:\n");
				if(m1-n1!=0) {
					printf("#���Ƿ����ް������\n\n");
					ord=choice1(p1,m1,n1);
				} else {
					if(m1-1!=0) {
						p3=matrix_set(m1,n1);
						matrix_adj(p1,p3,m1);
						printf("#�������A*��\n");
						matrix_out(p3, m1, n1);
						ord=choice2(p1,p3,m1,n1,m1,n1);
					} else {
						printf("#�÷��󲻴��ڰ������\n\n");
						ord=choice1(p1,m1,n1);	
					}
				}
				break;
			case 8:
				printf("@����A�������A-1:\n");
				if(m1-n1!=0) {
					printf("#���Ƿ����������\n\n");
					ord=choice1(p1,m1,n1);
				} else {
					if(m1-1!=0&&matrix_det(p1,m1)) {
						p3=matrix_set(m1,n1);
						matrix_inv(p1,p3,m1);
						printf("#�����A-1��\n");
						matrix_out(p3, m1, n1);
						ord=choice2(p1,p3,m1,n1,m1,n1);
					} else {
						printf("#�÷��󲻴��������\n\n");
						ord=choice1(p1,m1,n1);
					}
				}
				break;
			default:
				printf("��Ч�������������!\n");
				break;
		}
	} while(ord);
	return 0;
}
int choice1(double **p1,int m1,int n1) {
	int ord=0;
	do {
		printf("�Ƿ����ϴμ���ԭ����A��Ϊ���μ���ԭ����������㣿\n 1.��;\n 0.��;\n�Ƿ������������:");
		scanf("%d",&ord);
		if(ord-1==0) {
			ord=counter_continue(p1,m1,n1);    //�˳���������ʱ����0
			break;
		} else if(!ord) {
			printf("�������������\n\n@�����㿪ʼ:\n");
			break;
		} else {
			printf("��Чѡ��������ѡ���Ƿ�����������㣡\n");
		}
	} while(ord);
	return 0;
}
int choice2(double **p1,double **p2,int m1,int n1,int m2,int n2) {
	int ord=0,smallord=0;
	do {
		printf("�Ƿ�����������㣿\n 1.��;\n 0.��;\n�Ƿ������������:");
		scanf("%d",&ord);
		if(ord-1==0) {
			while(1) {
				printf("��ѡ���ϴμ����ԭ�������������Ϊ���μ����ԭ����:\n 1.�ϴμ����ԭ����A;\n 2.�ϴμ���Ľ������;\n��ѡ�񱾴μ���ԭ����:");
				scanf("%d",&smallord);
				if(smallord-1==0) {
					ord=counter_continue(p1,m1,n1);
					break;
				} else if(smallord-2==0) {
					ord=counter_continue(p2,m2,n2);
					break;
				} else {
					printf("��Чѡ��������ѡ�񱾴μ���ԭ����\n");
				}
			}
			break;
		} else if(!ord) {
			printf("�������������\n\n@�����㿪ʼ:\n");
			break;
		} else {
			printf("��Чѡ��������ѡ���Ƿ�������μ��㣡\n");
		}
	} while(ord);
	return 0;
}
int choice3(double **p1,double **p2,double **p3,int m1,int n1,int m2,int n2,int m3,int n3) {
	int ord=0,smallord=0;
	do {
		printf("�Ƿ�����������㣿\n 1.��;\n 0.��;\n�Ƿ������������:");
		scanf("%d",&ord);
		if(ord-1==0) {
			while(1) {
				printf("��ѡ���ϴμ����ԭ�������������Ϊ���μ���ľ���:\n 1.�ϴμ����ԭ����A;\n 2.�ϴμ����ԭ����B;\n 3.�ϴμ���Ľ������;\n��ѡ�񱾴μ���ԭ����:");
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
					printf("��Чѡ��������ѡ�񱾴μ���ԭ����\n");
				}
			}
			break;
		} else if(!ord) {
			printf("�������������\n\n@�����㿪ʼ:\n");
			break;
		} else {
			printf("��Чѡ��������ѡ���Ƿ�����������㣡\n");
		}
	} while(ord);
	return 0;
}
