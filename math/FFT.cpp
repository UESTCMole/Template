fft
#include<bits/stdc++.h>
const int N=500010;
const double pi=acos(-1);
using namespace std;
struct E{
	double x,y;
	E operator+(const E&a){return(E){x+a.x,y+a.y};}
	E operator-(const E&a){return(E){x-a.x,y-a.y};}
	E operator*(const E&a){return(E){x*a.x-y*a.y,x*a.y+y*a.x};}
}a[N],b[N];
int R[N],n,m;
void FFT(E*a,int flag){
	for(int i=0;i<n;i++)if(i<R[i])swap(a[i],a[R[i]]);
	for(int i=1;i<n;i<<=1){
		E wx=(E){cos(pi/i),flag*sin(pi/i)};
		for(int j=0;j<n;j+=(i<<1)){
			E w=(E){1,0};
			for(int k=0;k<i;k++,w=w*wx){
				E x=a[j+k],y=w*a[i+j+k];
				a[j+k]=x+y,a[i+j+k]=x-y;
			}
		}
	}
	if(flag==-1){
		for(int i=0;i<n;i++){
			a[i].x/=n;
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++)scanf("%lf",&a[i].x);
	for(int i=0;i<=m;i++)scanf("%lf",&b[i].x);
	int L=0,len=n+m;
	n=max(n,m);m=n*2;
	for(n=1;n<=m;n<<=1)L++;
	for(int i=0;i<=n;i++)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
	FFT(a,1),FFT(b,1);
	for(int i=0;i<=n;i++)a[i]=a[i]*b[i];
	FFT(a,-1);
	for(int i=0;i<=len;i++)printf("%d ",int(a[i].x+0.5));
	puts("");
}
