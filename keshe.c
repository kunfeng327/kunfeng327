#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Goods{
	int num;
	char name[10];
	char sort[10];
	char brand[10];
	float price;
	int kucun;
}good[20];
void menu(){		//菜单
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
	\n欢迎使用文具店商品库存管理系统\
	\n1.批量录入初始商品信息\
	\n2.浏览商品信息\
	\n3.查询商品信息\
	\n4.增加商品信息\
	\n5.删除商品信息\
	\n6.修改商品信息\
	\n7.按类别统计商品数量\
	\n8.按价格对商品排序\
	\n9.得到当前库存商品的总价值\
	\n10.退出\
	\n谢谢使用\
	\n");
}
void write(int cnt){		//尝试在命令行输入txt内容
	int num;
	char name[10];
	char sort[10];
	char brand[10];
	float price;
	int kucun;
	int i;
	FILE *fp;
	fp=fopen("test.txt","a");
	if(fp==NULL){
		printf("无法打开此文件");
		exit(0);
	}
	for(i=0;i<cnt;i++){
		scanf("%d%s%s%s%f%d",&num,name,sort,brand,&price,&kucun);
		fprintf(fp,"%d\t%s\t%s\t%s\t%f\t%d",num,name,sort,brand,price,kucun);
	}
	fclose(fp);
}

int luru(){		//把txt内容每行依次录入结构体变量
	int num;
	char name[10];
	char sort[10];
	char brand[10];
	float price;
	int kucun;
	int i=0,j,flag=1;
	char row[80];
	FILE *fp;

	fp=fopen("test.txt","r");
	if(fp==NULL){
		printf("无法打开此文件\n");
		exit(0);
	}
	while(fgets(row,80,fp)!=NULL){
		sscanf(row,"%d%s%s%s%f%d",&num,name,sort,brand,&price,&kucun);
		for(j=0;j<i;j++){
			if(good[j].num==num){
				printf("商品序号%d已存在，跳过此商品\n",num);
				flag=0;
			}
		}
	
		if(flag==1){
			good[i].num=num;
			strcpy(good[i].name,name);
			strcpy(good[i].sort,sort);
			strcpy(good[i].brand,brand);
			good[i].price=price;
			good[i].kucun=kucun;
			i++;
		}
	}
	printf("已成功录入%d条商品信息\n",i);
	fclose(fp);
	return i;
}

void liulan(int cnt){	//浏览商品信息
	int i;
	printf("序号|商品编号|商品名称	|商品类别|	商品品牌|	商品单价|商品库存\n");
	for(i=0;i<cnt;i++){
		
		printf("%d\t%d\t%s\t%s\t\t%s\t\t%.2f\t%d\n",i+1,good[i].num,good[i].name,good[i].sort,good[i].brand,good[i].price,good[i].kucun);
	}
}

void chaxun(int cnt){	//查询商品信息
	int num,flag=0;
	void print(int i);
	printf("请选择查询方式\
	\n1.根据商品编号查询\
	\n2.根据商品名称查询\
	\n3.根据商品品牌查询\
	\n4.根据商品类别查询\
	\n请输入您的选择（1-4）：\n");
	scanf("%d",&num);
	switch(num){
		case 1:{
			int no,i;
			printf("请输入商品编号：");
			scanf("%d",&no);
			for(i=0;i<cnt;i++)
				if(no==good[i].num)
					{print(i);flag=1;}
						
			if(flag==0) printf("未查询到商品信息！\n");
			break;
		}
		case 2:{
			int i;
			char name[10];
			printf("请输入商品名称：");
			scanf("%s",name);
			for(i=0;i<cnt;i++)
				if(strcmp(name,good[i].name)==0)
					{print(i);flag=1;}
			if(flag==0) printf("未查询到商品信息！\n");
			break;
		}
		case 3:{
			int i;
			char brand[10];
			printf("请输入商品品牌：");
			scanf("%s",brand);
			for(i=0;i<cnt;i++)
				if(strcmp(brand,good[i].brand)==0)
					{print(i);flag=1;}
			if(flag==0) printf("未查询到商品信息！\n");
			break;
		}
		case 4:{
			int i;
			char sort[10];
			printf("请输入商品类别：");
			scanf("%s",sort);
			for(i=0;i<cnt;i++)
				if(strcmp(sort,good[i].sort)==0)
					{print(i);flag=1;}
			if(flag==0) printf("未查询到商品信息！\n");
			break;
		}
		default:printf("输入无效！\n");
	}
}

void print(int i){	//打印格式
	printf("============================\
	\n商品编号：	%d\
				\n商品名称：	%s\
				\n商品类别：	%s\
				\n商品品牌：	%s\
				\n商品价格：	%.2f\
				\n商品库存:	%d\n",good[i].num,good[i].name,good[i].sort,good[i].brand,good[i].price,good[i].kucun);
}

void zenjia(){	//增加商品信息
	int num,sor,bra;
	char name[10];
	char sort[4][10]={"笔类","本类","颜料类","其他"};
	char brand[5][10]={"晨光","得力","百乐","zebra","辉柏嘉"};
	float price;
	int kucun;
	FILE *fp;
	fp=fopen("test.txt","a");
	if(fp==NULL){
		printf("无法打开此文件");
		exit(0);
	}
	printf("请输入新增商品信息~\n请输入商品序号：");
	scanf("%d",&num);
	printf("请输入商品名称：");
	scanf("%s",name);
	printf("请输入商品类别(1.笔类,2.本类,3.颜料类,4.其他)：");
	scanf("%d",&sor);
	printf("请输入商品品牌(1.晨光,2.得力,3.百乐,4.zebra,5.辉柏嘉)：");
	scanf("%d",&bra);
	printf("请输入商品价格：");
	scanf("%f",&price);
	printf("请输入商品库存：");
	scanf("%d",&kucun);
	fprintf(fp,"%d\t%s\t\t%s\t\t%s\t\t%.2f\t%d\n",num,name,sort[sor-1],brand[bra-1],price,kucun);
	printf("商品信息已成功添加\n商品信息已成功保存到test.txt\n");
	fclose(fp);
}

void shanchu(int cnt){	//删除商品信息
	int op,i,flag=0,flag1=0;	//flag是表示是否确定删除,flag1表示有没有录入该商品信息
	char op1;
	int num,fnum;
	char name[10],fname[10];
	char sort[10];
	char brand[10];
	char *filename="test.txt";
	float price;
	int kucun;
	char row[80];//row用来查找,row1用来暂存读入文件每一行的内容

	printf("请选择删除方式：\n1.按商品编号删除\n2.按商品名称删除\n输入你的选择：");
	scanf("%d",&op);
	if(!(op==1||op==2)) printf("输入不符合要求！\n");
	else{
		if(op==1){
			printf("请输入要删除的商品编号：");
			scanf("%d",&num);
			op1=getchar();	//存换行
			FILE *fd,*fx;
			fd=fopen(filename,"r");
			fx=fopen("temp.txt","w");
			
//			if(cnt==0) printf("暂未录入商品信息~");
			if(fd==NULL||fx==NULL){
				printf("无法打开此文件\n");
				exit(0);}
			for(i=0;i<cnt;i++){
				
				while(fgets(row,80,fd)!=NULL){
					sscanf(row,"%d%s%s%s%f%d",&fnum,fname,sort,brand,&price,&kucun);
					if(num==fnum) {
						flag1=1;
						print(i);
						printf("是否确定删除？(y/n):");
						op1=getchar();
						if(op1=='n') {
							flag=1;break;}
					}
					
					if(num!=fnum){
						fprintf(fx,"%d\t%s\t%s\t%s\t%.2f\t%d\n",fnum,fname,sort,brand,price,kucun);
					}
				
				}
			}
			if(flag1==0) printf("未录入该商品信息！\n");
			fclose(fd);
			fclose(fx);
			if(flag==0){
				remove(filename);
				rename("temp.txt",filename);
				if(flag1!=0)
					printf("删除成功\n");}
		}
		if(op==2){
			printf("请输入要删除的商品名称：");
			scanf("%s",name);
			op1=getchar();	//存换行
			FILE *fd,*fx;
			fd=fopen(filename,"r");
			fx=fopen("temp.txt","w");
			
//			if(cnt==0) printf("暂未录入商品信息~");
			if(fd==NULL||fx==NULL){
				printf("无法打开此文件\n");
				exit(0);}
			for(i=0;i<cnt;i++){
				
				while(fgets(row,80,fd)!=NULL){
					sscanf(row,"%d%s%s%s%f%d",&fnum,fname,sort,brand,&price,&kucun);
					if(strcmp(fname,name)==0) {
						flag1=1;
						print(i);
						printf("是否确定删除？(y/n):");
						op1=getchar();
						if(op1=='n') {
							flag=1;break;}
					}
					
					if(strcmp(fname,name)!=0){
						fprintf(fx,"%d\t%s\t%s\t%s\t%.2f\t%d\n",fnum,fname,sort,brand,price,kucun);
					}
				
				}
			}
			if(flag1==0) printf("未录入该商品信息！\n");
			fclose(fd);
			fclose(fx);
			if(flag==0){
				
				remove(filename);
				rename("temp.txt",filename);
				if(flag1!=0)
					printf("删除成功\n");}
		}
	}
}


void xiugai(int cnt){	//修改商品信息
	int i,op;
	int main();
	int num,fnum;
	char newname[10],fname[10];
	char sort[10];
	char brand[10];
	char row[80];
	float price,newprice;
	int kucun,newkucun;
	int newsort,newbrand;
	int flag=0;		//用来标记输入的编号是否在文件里面
	char sortlst[4][10]={"笔类","本类","颜料类","其他"};
	char brandlst[5][10]={"晨光","得力","百乐","zebra","辉柏嘉"};
	char filename[10]="test.txt";
	FILE *fd,*fx;
	fd=fopen(filename,"r");
	fx=fopen("temp.txt","w");
	printf("请输入要修改的商品编号：");
	scanf("%d",&num);
	for(i=0;i<cnt;i++)
		if(good[i].num==num){
			print(i);flag=1;}
	if(flag==0) printf("无该商品编号！\n");
	else{
	
	printf("请选择要修改的商品信息：\
	\n1.商品名称\
	\n2.商品类别\
	\n3.商品品牌\
	\n4.商品单价\
	\n5.商品库存\
	\n请输入选择(1-5)\n");
	scanf("%d",&op);
	
	switch(op){
		case 1:{
			printf("请输入商品名称：");
			scanf("%s",newname);
			while(fgets(row,80,fd)!=NULL){
				sscanf(row,"%d%s%s%s%f%d",&fnum,fname,sort,brand,&price,&kucun);
				if(fnum!=num) {
					fprintf(fx,"%d\t%s\t%s\t%s\t%.2f\t%d\n",fnum,fname,sort,brand,price,kucun);	
				}
				else if(fnum==num){
					fprintf(fx,"%d\t%s\t%s\t%s\t%.2f\t%d\n",fnum,newname,sort,brand,price,kucun);
				}
			}
//			for(i=0;i<cnt)
			break;
		}
		case 2:{
			printf("请输入商品类别(1.笔类,2.本类,3.颜料类,4.其他)：");
			scanf("%d",&newsort);
			while(fgets(row,80,fd)!=NULL){
				sscanf(row,"%d%s%s%s%f%d",&fnum,fname,sort,brand,&price,&kucun);
				if(fnum!=num) {
					fprintf(fx,"%d\t%s\t%s\t%s\t%.2f\t%d\n",fnum,fname,sort,brand,price,kucun);	
				}
				else if(fnum==num){
					fprintf(fx,"%d\t%s\t%s\t%s\t%.2f\t%d\n",fnum,fname,sortlst[newsort-1],brand,price,kucun);
				}
			}
			break;
		}
		case 3:{
			printf("请输入商品品牌(1.晨光,2.得力,3.百乐,4.zebra,5.辉柏嘉)：");
			scanf("%d",&newbrand);
			while(fgets(row,80,fd)!=NULL){
				sscanf(row,"%d%s%s%s%f%d",&fnum,fname,sort,brand,&price,&kucun);
				if(fnum!=num) {
					fprintf(fx,"%d\t%s\t%s\t%s\t%.2f\t%d\n",fnum,fname,sort,brand,price,kucun);	
				}
				else if(fnum==num){
					fprintf(fx,"%d\t%s\t%s\t%s\t%.2f\t%d\n",fnum,fname,sort,brandlst[newbrand-1],price,kucun);
				}
			}
			break;
		}
		case 4:{
			printf("请输入商品单价：");
			scanf("%f",&newprice);
			while(fgets(row,80,fd)!=NULL){
				sscanf(row,"%d%s%s%s%f%d",&fnum,fname,sort,brand,&price,&kucun);
				if(fnum!=num) {
					fprintf(fx,"%d\t%s\t%s\t%s\t%.2f\t%d\n",fnum,fname,sort,brand,price,kucun);	
				}
				else if(fnum==num){
					fprintf(fx,"%d\t%s\t%s\t%s\t%.2f\t%d\n",fnum,fname,sort,brand,newprice,kucun);
				}
			}
			break;
		}
		case 5:{
			printf("请输入商品库存：");
			scanf("%d",&newkucun);
			while(fgets(row,80,fd)!=NULL){
				sscanf(row,"%d%s%s%s%f%d",&fnum,fname,sort,brand,&price,&kucun);
				if(fnum!=num) {
					fprintf(fx,"%d\t%s\t%s\t%s\t%.2f\t%d\n",fnum,fname,sort,brand,price,kucun);	
				}
				else if(fnum==num){
					fprintf(fx,"%d\t%s\t%s\t%s\t%.2f\t%d\n",fnum,fname,sort,brand,price,newkucun);
				}
			}
			break;
		}
		default:printf("输入无效！\n");
		
	}
	fclose(fd);
	fclose(fx);	
	remove(filename);
	rename("temp.txt",filename);
	printf("修改成功\n");
	}
}

void tongji(int cnt){	//按类别统计商品数量
	int op;		//选择1-4
	int n=0,i;
	char sortlst[4][10]={"笔类","本类","颜料类","其他"};
	printf("请选择要统计的商品类别：\
	\n1.笔类\
	\n2.本类\
	\n3.颜料类\
	\n4.其他\
	\n请输入类别编号(1-4):");
	scanf("%d",&op);
	switch(op){
		case 1:{
			for(i=0;i<cnt;i++){
				if(strcmp(good[i].sort,sortlst[0])==0)
					n++;
			}
			printf("商品类别%s中共有 %d 个商品\n",sortlst[0],n);
			break;
		}
		case 2:{
			for(i=0;i<cnt;i++){
				if(strcmp(good[i].sort,sortlst[1])==0)
					n++;
			}
			printf("商品类别%s中共有 %d 个商品\n",sortlst[1],n);
			
			break;
		}
		case 3:{
			for(i=0;i<cnt;i++){
				if(strcmp(good[i].sort,sortlst[2])==0)
					n++;
			}
			printf("商品类别%s中共有 %d 个商品\n",sortlst[2],n);
			
			break;
		}
		case 4:{
			for(i=0;i<cnt;i++){
				if(strcmp(good[i].sort,sortlst[3])==0)
					n++;
			}
			printf("商品类别%s中共有 %d 个商品\n",sortlst[3],n);
			
			break;
		}
		default:printf("输入无效！\n");
	}
}

int shen(int n){//冒泡排序
	int i,j;
	struct Goods *p1=good,*p2=good;
	for(i=0;i<n-1;i++,p1++,p2++)
		for(j=0;j<n-1-i;j++)
			if(good[j].price>good[j+1].price){
				*p1=good[j+1];
				*p2=good[j];
			}
	for(i=0;i<n;i++){
		print(i);
	}
	return 0;
}

int jiang(int n){
	int i,j;
	struct Goods *p1=good,*p2=good;
	for(i=0;i<n-1;i++,p1++,p2++)
		for(j=0;j<n-1-i;j++)
			if(good[j].price<good[j+1].price){
				*p1=good[j+1];
				*p2=good[j];
			}
	for(i=0;i<n;i++){
		print(i);
	}
	return 0;
}

void paixu(int cnt){	//按单价对商品排序
	int op,n=cnt;
	int i,j;
	struct Goods *p1=good,*p2=good,temp;
	printf("请输入排序方式：\
	\n1.按价格升序排序\
	\n2.按价格降序排序\
	\n请输入选项(1-2):");
	scanf("%d",&op);
	if(op!=1&&op!=2)printf("无效输入！\n");
	else{
	
		if(op==1){
			for(i=0;i<n-1;i++)
				for(j=0;j<n-1-i;j++,p1++,p2++)
					if(good[j].price>good[j+1].price){
						temp=*p2;
						good[j+1]=*p1;
						good[j]=temp;
					}
			for(i=0;i<n;i++){
				print(i);
			}
		}
		if(op==2){
			for(i=0;i<n-1;i++){
				p1=good;
				p2=good+1;
				for(j=0;j<n-1-i;j++,p1++,p2++)
					if(p1->price<p2->price){
						temp=*p2;
						good[j+1]=*p1;
						good[j]=temp;
					}
				}
			for(i=0;i<n;i++){
				print(i);
			}
		}
	}
}

void zongjia(int cnt){	//计算当前商品总价值
	float total=0;
	int i;
	struct Goods *p=good;
	for(i=0;i<cnt;i++,p++){
		total+=p->price*p->kucun;
		printf("%.2f\n",p->price*p->kucun);
	}
	printf("当前仓库%d个商品总价值为%.2f",i,total);
}

int tuichu(){
	int ch;
	printf("是否确认退出(y/n):");
	getchar();
	ch=getchar();
	if(ch=='y')return 0;
	else{
		 if(ch!='n' && ch!='y')printf("输入无效\n");
		 return 1;
	}
	
}

int main(){		//主函数
	int opt;
	int cnt;
	int res=1;
	menu();
	while(res){	
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
		\n请输入您的选择：");
		scanf("%d",&opt);
		
		switch(opt){
			case 1:cnt=luru();break;
			case 2:liulan(cnt);break;
			case 3:chaxun(cnt);break;
			case 4:zenjia();break;
			case 5:shanchu(cnt);break;
			case 6:xiugai(cnt);break;
			case 7:tongji(cnt);break;
			case 8:paixu(cnt);break;
			case 9:zongjia(cnt);break;
			case 10:res=tuichu();break;
			default:printf("请输入数字1-10！\n");
		}
	}
	return 0;
}
