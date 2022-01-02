#include<bits/stdc++.h>
using namespace std;
#define max(a,b) (a<b?b:a)
#define F(i,L,R) for (int i = L; i < R; i++)
#define FE(i,L,R) for (int i = L; i <= R; i++)
#define RF(i,L,R) for (int i = L; i > R; i--)
#define RFE(i,L,R) for (int i = L; i >= R; i--)
#define getI(a) scanf("%d", &a)
#define getII(a,b) scanf("%d%d", &a, &b)
#define getIII(a,b,c) scanf("%d%d%d", &a, &b, &c)
#define VgetI(n) int (n); scanf("%d",&(n))
#define VgetII(n,m) int (n),(m); scanf("%d %d",&(n),&(m))
#define VgetIII(n,m,k) int (n),(m),(k); scanf("%d %d %d",&(n),&(m),&(k))
#define pb push_back
#define ll long long
#define INF 2000000000
#define nINF -2000000000
#define MOD 1e9+7
#define PI 3.1415926535897932384626
const double proteinMElow=0.4,proteinMEhigh=0.45,fatMElow=0.45,fatMEhigh=0.6,carboHydratehigh=0.1,phosphorusHigh=200;
struct can{
	//data
	double protein,fat,carboHydrate,water,phosphorus,calories,weight;
	//	   蛋白質 脂肪 碳水化合物   水分  磷		 熱量	  重量
	double percent;
	//	   一次用幾%的罐頭
	bool isFish;
	//	 含魚嗎
	int avaliable;
}cans[100];
bool use[100];
int n;
bool checkME(can a,can b,can c,can &avg){
	double proteinTot,fatTot,carboHydrateTot,calTot;
	proteinTot=a.protein*a.percent*a.weight+b.protein*b.percent*b.weight+c.protein*c.percent*c.weight;
	fatTot=a.fat*a.percent*a.weight+b.fat*b.percent*b.weight+c.fat*c.percent*c.weight;
	carboHydrateTot=a.carboHydrate*a.percent*a.weight+b.carboHydrate*b.percent*b.weight+c.carboHydrate*c.percent*c.weight;
	//weightTot=a.percent*a.weight+b.percent*b.weight+c.percent*c.weight;
	calTot=a.calories*a.weight*a.percent+b.calories*b.weight*b.percent+c.calories*c.weight*c.percent;//kcal
	//double proteinAvg,fatAvg,carboHydrateAvg;
	double proteinCalories=proteinTot*3.5;
	double fatCalories=fatTot*8.5;
	double carboHydrateCalories=carboHydrateTot*3.5;
	double proteinME=proteinCalories/calTot*10;
	double fatME=fatCalories/calTot*10;
	double carboHydrateME=carboHydrateCalories/calTot*10;
	avg.protein=proteinME;
	avg.fat=fatME;
	avg.carboHydrate=carboHydrateME;
	if(proteinME<proteinMElow||proteinME>proteinMEhigh){
		//puts("Protein");
		//printf("%lf\n",proteinME);
		return false;
	}
	if(fatME<fatMElow||fatME>fatMEhigh){
		//puts("fat");
		return false;
	}
	if(carboHydrateME>carboHydratehigh){
		//puts("Carbo");
		return false;
	}
	return true;
}
bool checkPhosphorus(can a,can b,can c,can &avg){
	double calTot,phosphorusTot;
	calTot=a.calories*a.weight*a.percent+b.calories*b.weight*b.percent+c.calories*c.weight*c.percent;//kcal/g
	phosphorusTot=a.phosphorus*a.weight*a.percent+b.phosphorus*b.weight*b.percent+c.phosphorus*c.weight*c.percent;
	double calAvg,phosphorusAvg;
	calAvg=calTot/3/((a.percent*a.weight+b.percent*b.weight+c.percent*c.weight)/3);
	phosphorusAvg=phosphorusTot/3/((a.percent*a.weight+b.percent*b.weight+c.percent*c.weight)/3);
	double phosphorusAns=phosphorusAvg/calAvg*1000000;
	avg.phosphorus=phosphorusAns;
	return phosphorusAns<phosphorusHigh;
}
bool legal(can &avg){
	vector<can> Using;
	F(i,0,n) if(use[i]) Using.pb(cans[i]);
	//check
	int fishAmount=0;
	for(can i:Using) if(i.isFish) fishAmount++;
	if(fishAmount!=1) return false;
	can fish;
	can notFish[3];
	int index=0;
	for(can i:Using) if(i.isFish) fish=i;
	for(can i:Using) if(!i.isFish) notFish[index++]=i;
	bool okME=checkME(notFish[0],notFish[1],notFish[2],avg);
	bool okPhosphorus=checkPhosphorus(notFish[0],notFish[1],notFish[2],avg);
	if(!okME||!okPhosphorus) return false;
	can nothing;
	F(i,0,3) F(j,i+1,3){
		bool okME=checkME(fish,notFish[i],notFish[j],nothing);
		bool okPhosphorus=checkPhosphorus(fish,notFish[i],notFish[j],nothing);
		if(!okME||!okPhosphorus) return false;
	}
	return true;
}
void tryAllCombinations(){
	F(i,0,n) F(j,i+1,n) F(k,j+1,n) F(l,k+1,n){
		use[i]=use[j]=use[k]=use[l]=1;
		can avg;
		if(legal(avg)&&cans[i].avaliable&&cans[j].avaliable&&cans[k].avaliable&&cans[l].avaliable) printf("%d %d %d %d\n",i+3,j+3,k+3,l+3);
		use[i]=use[j]=use[k]=use[l]=0;
	}
}
int main(){
	getI(n);
	F(i,0,n){
		//input for can's data
		scanf("%lf %lf %lf %lf %lf %lf",&cans[i].protein,&cans[i].fat,&cans[i].carboHydrate,&cans[i].water,&cans[i].phosphorus,&cans[i].calories);
		scanf("%d",&cans[i].isFish);
		scanf("%lf%lf",&cans[i].weight,&cans[i].percent);
		//scanf("%d",&cans[i].avaliable);
		cans[i].avaliable=1;
	}
	F(i,0,n) use[i]=0;
	can nothing;
	tryAllCombinations();
}
