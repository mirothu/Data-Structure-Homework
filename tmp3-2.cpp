#include<iostream>
#include<cstring>
using namespace std;

struct bridge
{
	long long P;//最小花费值；
	long long V;//最小美化度；
	bool flag;
	bridge():P(0),V(0),flag(false){
	}
	bridge(int a, int b):P(a),V(b),flag(false){
	}
};

struct material
{
	long long H;//费用 
	long long D;//增加美化度 
	bool flag;
	material():H(0),D(0),flag(false){
	}
	material(int a, int b):H(a),D(b),flag(false){
	}
};

bool cmp(material A, material B)//两材料的比较函数 
{
	if ( A.H < B.H || (A.H==B.H && A.D < B.D))//材料A的价格低于B或两者等价且A的美化度较低则返回true 
		return true;
	else//否则false 
		return false;
}

bool cmp(bridge A,bridge B)//两桥的比较函数 
{
	if ( A.V > B.V || ( A.V== B.V && A.P > B.P ))//桥A的美化度高于B或美化度相同但A价格较高则返回true 
		return true;
	else
		return false;
}

void quicksort ( material pt[] , int low , int high )//快排  参考http://www.cnblogs.com/asiacao/archive/2012/12/17/2822090.html
{
	if ( low>=high )//这组点中只有一个或零个元素结束递归 
		return;
	material standard (pt[low].H,pt[low].D);//选择第一个点为基准 
	int i = low;
	for ( int j = low + 1 ; j <= high ; j++ )
	{
		if ( cmp ( pt[j] , standard ))//比较第j个点与基准点 
		{
			i++;
			if ( i != j )
			{
				//交换第i和第j个点 
				material tmp1 (pt[i].H,pt[i].D);
				pt[i].H=pt[j].H;
				pt[i].D=pt[j].D;
				pt[j].H=tmp1.H;
				pt[j].D=tmp1.D;
			}
		}
	}
				material tmp1 (pt[i].H,pt[i].D);
				pt[i].H=pt[low].H;
				pt[i].D=pt[low].D;
				pt[low].H=tmp1.H;
				pt[low].D=tmp1.D;//交换基准点与第i个点 
	quicksort(pt,low,i-1);//递归 
	quicksort(pt,i+1,high);//递归 
}

void quicksort ( bridge pt[] , int low , int high )//快排  参考http://www.cnblogs.com/asiacao/archive/2012/12/17/2822090.html
{
	if ( low>=high )//这组点中只有一个或零个元素结束递归 
		return;
	bridge standard (pt[low].P,pt[low].V);//选择第一个点为基准 
	int i = low;
	for ( int j = low + 1 ; j <= high ; j++ )
	{
		if ( cmp ( pt[j] , standard ))//比较第j个点与基准点 
		{
			i++;
			if ( i != j )
			{
				//交换第i和第j个点 
				bridge tmp1 (pt[i].P,pt[i].V);
				pt[i].P=pt[j].P;
				pt[i].V=pt[j].V;
				pt[j].P=tmp1.P;
				pt[j].V=tmp1.V;
			}
		}
	}
				bridge tmp1 (pt[i].P,pt[i].V);
				pt[i].P=pt[low].P;
				pt[i].V=pt[low].V;
				pt[low].P=tmp1.P;
				pt[low].V=tmp1.V;//交换基准点与第i个点 
	quicksort(pt,low,i-1);//递归 
	quicksort(pt,i+1,high);//递归 
}

int main()
{
	int n = 0 , m = 0 ;
	long long min_cost = 0 ;
	scanf("%d",&n);
	scanf("%d",&m);
	bridge* Bri=new bridge[n];
	material* Mat=new material[m];
	
	bool* bri_flag = new bool [n];
	bool* mat_flag = new bool [m];
	for ( int i = 0 ; i < n ; i++ )//读入桥的数据 
	{
		scanf("%d",&Bri[i].P);
		scanf("%d",&Bri[i].V);
		bri_flag[i]=false;
	}

	for ( int j = 0 ; j < m ; j++ )//读取材料的数据 
	{
		scanf("%d",&Mat[j].H);
		scanf("%d",&Mat[j].D);
		mat_flag[j] = false;
	}
	quicksort(Bri,0,n-1);//将桥按照美化度从高到低排序（第二关键词为价格从高到低） 
	quicksort(Mat,0,m-1);//将材料按照价格从低到高排序（第二关键词为美化度从低到高） 
	int count = 0;
	
	for ( int i = 0 ; i < n ; i++ )//对每座桥 
	{
		for ( int j= 0 ; j < m ; j++ )//遍历每种材料 
		{
			if ( mat_flag[j]==false && Mat[j].H >= Bri[i].P && Mat[j].D >= Bri[i].V )//符合修理条件则修理之 
			{
				long long tmp = Mat[j].H;
				min_cost +=tmp;//更新花费 
				mat_flag[j]=true;
				break;//结束循环 
			}
		}
	}
	cout << min_cost << endl; 
	return 0;
}
