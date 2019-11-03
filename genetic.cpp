 /*
 _     _                             
| |__ | |__   __ _  __ _ _   _  __ _ 
| '_ \| '_ \ / _` |/ _` | | | |/ _` |
| |_) | | | | (_| | (_| | |_| | (_| |
|_.__/|_| |_|\__,_|\__, |\__, |\__,_|
                   |___/ |___/       
*/
#include<bits/stdc++.h>

#define ll          long long
#define pb          push_back
#define ppb         pop_back
#define	endl		'\n'
#define mii         map<ll int,ll int>
#define msi         map<string,ll int>
#define mis         map<ll int, string>
#define mpi         map<pair<ll int,ll int>,ll int>
#define pii         pair<ll int,ll int>
#define vi          vector<ll int>
#define vs          vector<string>
#define all(a)      (a).begin(),(a).end()
#define F           first
#define S           second
#define sz(x)       (ll int)x.size()
#define hell        1000000007
#define lbnd        lower_bound
#define ubnd        upper_bound
#define bs          binary_search
#define mp          make_pair
#define what_is(x)  cerr << #x << " is " << x << endl;
using namespace std;

#define N  100

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct chromosome
{
	ll int gene[20];

	void print()
	{
		for(ll int i=0;i<10;i++) cout<<gene[i];
		cout<<"  	";
		for(ll int i=11;i<20;i++) cout<<gene[i];
		cout<<endl;
	}

	chromosome()
	{
		for(ll int i=0;i<20;i++)
		{
			gene[i]=rng()%2;
		}
	}

	double fun(double x,double y)
	{
		double den=(x*x+y*y-5);
		double e=.99;
		double ret=1.0/(den*den+e);
		return ret;
	}

	double getX()
	{
		// calculate value of x
		double x=0,tmp=1;
		for(ll int i=5;i>=0;i--)
		{
			x+=gene[i]*tmp;
			tmp*=2;
		}
		tmp=0.5;
		for(ll int i=6;i<10;i++)
		{
			x+=gene[i]*tmp;
			tmp/=2.0;
		}
		return x;
	}

	double getY()
	{
		double y=0;
		double tmp=1;
		for(ll int i=15;i>=10;i--)
		{
			y+=gene[i]*tmp;
			tmp*=2;
		}
		tmp=0.5;
		for(ll int i=16;i<20;i++)
		{
			y+=gene[i]*tmp;
			tmp/=2.0;
		}
		return y;
	}

	void Roulette_wheel()
	{
		if(rng()%100==40) random_shuffle(gene,gene+20);
		double cumprob[20];
		// for(ll int i=0;i<20;i++) cumprob[i]=cumprob[i-1]+gene[i].getFitness();
		double SigmaFitness=0;
		// for(ll int i=0;i<20;i++) SigmaFitness+=gene[i].getFitness();
		for(ll int i=0;i<20;i++) cumprob[i]=cumprob[i]/SigmaFitness;

	}

	double getFitness()
	{
		// calculate value of x
		double x=0,tmp=1;
		for(ll int i=5;i>=0;i--)
		{
			x+=gene[i]*tmp;
			tmp*=2;
		}
		tmp=0.5;
		for(ll int i=6;i<10;i++)
		{
			x+=gene[i]*tmp;
			tmp/=2.0;
		}
		// calculate value of 
		double y=0;
		tmp=1;
		for(ll int i=15;i>=10;i--)
		{
			y+=gene[i]*tmp;
			tmp*=2;
		}
		tmp=0.5;
		for(ll int i=16;i<20;i++)
		{
			y+=gene[i]*tmp;
			tmp/=2.0;
		}
		// return value of fitness corresponding to x & y
		return fun(x,y);
	}
};

bool comp(pair<double,chromosome> a,pair<double,chromosome> b)
{
	return a.F<b.F;
}

struct population
{
	chromosome arr[N];

	chromosome getFittest()
	{
		vector<pair<double,chromosome>> v;
		for(ll int i=0;i<N;i++)
		{
			v.pb({arr[i].getFitness(),arr[i]});
		}
		sort(all(v),comp);
		reverse(all(v));
		return v[0].S;
	}

	chromosome getSecondFittest()
	{
		vector<pair<double,chromosome>> v;
		for(ll int i=0;i<N;i++)
		{
			v.pb({arr[i].getFitness(),arr[i]});
		}
		sort(all(v),comp);
		reverse(all(v));
		return v[1].S;
	}

	ll int getLeastFittestIndex()
	{
		double mini=1e18;
		ll int idx=-1;
		for(ll int i=0;i<N;i++)
		{
			if(arr[i].getFitness()<mini)
			{
				mini=arr[i].getFitness();
				idx=i;
			}
		}
		return idx;
	}


};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int TESTS=1;
	// cin>>TESTS;
	while(TESTS--)
	{
		population p;
		chromosome fittest;
		chromosome secondFittest;
		ll int steps=1;
		double avg=rng()%234;
		while(true)
		{
			// selection

			fittest=p.getFittest();
			secondFittest=p.getSecondFittest();

			// crossover

			for(ll int i=0;i<20;i++)
			{
				if(rng()%100<20)
				{
					swap(fittest.gene[i],secondFittest.gene[i]);
				}
			} 

			// mutation

			for(ll int i=0;i<20;i++)
			{
				if(rng()%1000<8)
				{
					fittest.gene[i]=1-fittest.gene[i];
				}
			}

			for(ll int i=0;i<20;i++)
			{
				if(rng()%1000<8)
				{
					secondFittest.gene[i]=1-secondFittest.gene[i];
				}
			}

			// least fittest offspring die

			p.arr[p.getLeastFittestIndex()]=fittest;

			if(abs(fittest.getFitness()-avg)<0.001) break;

			avg=(avg*steps+fittest.getFitness())/(1.0+steps);

			cout<<"generation : "<<steps<<endl;
			cout<<"x = "<<fittest.getX()<<"  y = "<<fittest.getY()<<endl;
			cout<<avg<<" "<<fittest.getFitness() <<endl<<endl;
			steps++;

		}
		chromosome c=p.getFittest();
		cout<<"Solution "<<endl;
		cout<<"x = "<<c.getX()<<"  y = "<<c.getY()<<"   x^2 + y^2 ="<<c.getX()*c.getX()+c.getY()*c.getY()<<endl<<endl;
		c.print();
	}
	return 0;
}