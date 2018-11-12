#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <set>
#include <map>
#include <ctime>
using namespace std;
int sw = 0;
class graphnode
{
	private:
	int id;
	

	public:
	int wt;
	map<int,int> adjlist;
	graphnode(int i,int j)
	{
		id=i;
		wt=j;
	}
	void set_id(int i)
	{
		id=i;
	}

	int get_id()
	{
		return id;
	}

	void add_edge(int a,int w)
	{
		if(adjlist.find(a)==adjlist.end())
		{
			adjlist.insert(pair<int,int>(a,w));
		}
		return;
	}
	void update_edge(int a,int w)
	{
		map<int,int>::iterator it = adjlist.find(a);
		if(it!=adjlist.end())
		{
			it->second = it->second + w;
		}
		else
		{
			adjlist.insert(pair<int,int>(a,w));
		}

	}


};

class graph
{
	public:
	vector<graphnode> nodelist;
		void add_node(graphnode g)
		{
			nodelist.push_back(g);
		}
	int get_weight()
	{
		int we = 0;
		for(int i=0;i<nodelist.size();i++)
		{
			we = we + nodelist[i].wt;
		}
		return we;
	}
}
;
void print_graph(graph gr)
{
		for(int i=0;i<10;i++)
	{

		graphnode k = gr.nodelist[i];
		map<int,int>::iterator trav = k.adjlist.begin();
		cout<<k.get_id()+1<<":"<<endl;
 		for(;trav!=k.adjlist.end();trav++)
 		{
			cout<<trav->first+1<<","<<trav->second<<" ";
		}
		cout<<endl;
	}

}
vector<int> maximal_matching(graph g)
{
 	set<int> used;
 	vector<int> match;
 	int arr[g.nodelist.size()];
 	for(int i=0;i<g.nodelist.size();i++)
 	{
 		arr[i]=i;
 	}
 	for(int i=g.nodelist.size()-1;i>0;i--)
 	{
 		//cout<<"LOLL"<<endl;
 		int k = rand()%i;
 		int temp = arr[i];
 		arr[i] = arr[k];
 		arr[k] = temp;
 	}
 	for(int i=0;i<g.nodelist.size();i++)
 	{
 		graphnode k = g.nodelist[arr[i]];
 		int p = k.get_id();
 		if(used.find(p) == used.end())
 		{
 			used.insert(p);
 			match.push_back(p);
 			int j;
 			map<int,int>::iterator trav = k.adjlist.begin();
 			int maxw=0;
 			int maxi=0;
 			for(;trav!=k.adjlist.end();trav++)
 			{
 				int pd = trav->first;
 				if(used.find(pd) == used.end())
 				{
 					if(trav->second>maxw)
 					{
 						maxw = trav->second;
 						maxi = pd;
 					}
 				}
 			}
 			if(maxw>0)
 			{
 				used.insert(maxi);
 				match.push_back(maxi);
 			}
 			else
 			{
 				match.push_back(-1);
 			}
 		}
 	}
/* 	for(int i=0;i<match.size();i++)
 	{
 		cout<<match[i]+1<<endl;
 	}*/
 	return match;
}
vector<graph> coaren_g;
vector<vector <int> > coaren_m;
graph coarse(graph g,vector<int> match)
{
	graph gn;
	vector<int> dmatch;
	for(int i=0;i<match.size();i++)
	{
		dmatch.push_back(0);
	}
	for(int i=0;i<match.size();i+=2)
	{
		dmatch[match[i]] = i/2;
		if(match[i+1]!=-1)
			dmatch[match[i+1]] = i/2;
	}
	for(int i=0;i<match.size();i+=2)
	{
		if(match[i+1]!=-1)
		{
			graphnode g1 = g.nodelist[match[i]];
			graphnode g2 = g.nodelist[match[i+1]];
			graphnode g3(i/2,g1.wt+g2.wt);
			map<int,int>::iterator trav = g1.adjlist.begin();
 			for(;trav!=g1.adjlist.end();trav++)
 			{
 				if(trav->first!=g2.get_id())
					g3.update_edge(dmatch[trav->first],trav->second);
			}
			trav = g2.adjlist.begin();
 			for(;trav!=g2.adjlist.end();trav++)
 			{
 				if(trav->first!=g1.get_id())
					g3.update_edge(dmatch[trav->first],trav->second);
			}
			gn.add_node(g3);
		}
		else
		{
			graphnode g1 = g.nodelist[match[i]];
			graphnode g3(i/2,g1.wt);
			map<int,int>::iterator trav = g1.adjlist.begin();
 			for(;trav!=g1.adjlist.end();trav++)
 			{
				g3.update_edge(dmatch[trav->first],trav->second);
			}
			gn.add_node(g3);
		}
	}
	coaren_g.push_back(g);
	coaren_m.push_back(match);
/*	for(int i=0;i<gn.nodelist.size();i++)
	{

		graphnode k = gn.nodelist[i];
		map<int,int>::iterator trav = k.adjlist.begin();
 		for(;trav!=k.adjlist.end();trav++)
 		{
			cout<<trav->first+1<<","<<trav->second<<" ";
		}
		cout<<endl;
	}*/
	return gn;
}
vector<graph> divide;
vector<map<int,int> > mappings;
vector<int> partion(graph g)
{	
	set<int> p1;
	map<int,int> v1set;
	set<pair<int,int> > minset;
	int total = g.get_weight();
	int partial = 0;
	int index=0;
	/*	int in=0;
	int arr[g.nodelist.size()];
 	for(int i=0;i<g.nodelist.size();i++)
 	{
 		arr[i]=i;
 	}
 	for(int i=g.nodelist.size()-1;i>0;i--)
 	{
 		//cout<<"LOLL"<<endl;
 		int k = rand()%i;
 		int temp = arr[i];
 		arr[i] = arr[k];
 		arr[k] = temp;
 	}*/
	while(partial<=total/2)
	{
	while(p1.find(index)!=p1.end())
		index++;
	p1.insert(index);
	partial = partial + g.nodelist[index].wt;
	graphnode tem = g.nodelist[index];
	map<int,int>::iterator trav = tem.adjlist.begin();
	//cout<<"luuulllll:"<<tem.adjlist.size()<<endl;
 	for(;trav!=tem.adjlist.end();trav++)
 		{
		int k = trav->first;
		graphnode ne = g.nodelist[k];
		int gain = 0;
		map<int,int>::iterator trav1 = ne.adjlist.begin();
 		for(;trav1!=ne.adjlist.end();trav1++)
 		{
			int m = trav1->first;
			if(p1.find(m)!=p1.end())
			{
				gain = gain + trav1->second;
			}
			else
			{
				gain = gain - trav1->second;
			}
		}
		//cout<<k<<"$"<<gain<<endl;
		v1set.insert(pair<int,int>(k,gain));
		minset.insert(pair<int,int>(gain,k));
		//cout<<"pop"<<endl;
		}
	/*if(sw==1)
	{
		cout<<"okfopskdp"<<endl;
	set<pair<int,int> >::iterator trav1 = minset.begin();
 		for(;trav1!=minset.end();trav1++)
 		{
 			cout<<trav1->first<<"#"<<trav1->second<<endl;
 		}
 	}*/
	while(partial<=total/2)
	{
		//cout<<minset.size()<<"99999999999999999999999"<<endl;
		if(minset.begin()==minset.end())
		{
			break;
		}
		set<pair<int,int> >::reverse_iterator it = minset.rbegin();
		int l = it->second;
		int lo = it->first;
		v1set.erase(l);
		minset.erase(pair<int,int>(lo,l));
		p1.insert(l);
		partial = partial + g.nodelist[l].wt;
		graphnode tem = g.nodelist[l];
		map<int,int>::iterator trav = tem.adjlist.begin();
 		for(;trav!=tem.adjlist.end();trav++)
 		{
			int el = trav->first;
			map<int,int>::iterator tpk = v1set.find(el);
			if(tpk!=v1set.end())
			{	
				pair<int,int> tol = *tpk;
				int iu = tol.first;
				int gu = tol.second + trav->second;
				v1set.erase(tpk);
				v1set.insert(pair<int,int>(iu,gu));
				minset.insert(pair<int,int>(gu,iu));
			}
			else if(p1.find(el)==p1.end())
			{
				int gain = 0;
				graphnode ne = g.nodelist[el];
				map<int,int>::iterator trav = ne.adjlist.begin();
 				for(;trav!=ne.adjlist.end();trav++)
 				{
 				int m = trav->first;
					if(p1.find(m)!=p1.end())
					{
						gain = gain + trav->second;
					}
					if(p1.find(m)!=p1.end())
					{
						gain = gain - trav->second;
					}
				}
				v1set.insert(pair<int,int>(el,gain));
				minset.insert(pair<int,int>(gain,el));
			}
		}
		

	}
	}
	vector<int> part;
	for(int i=0;i<g.nodelist.size();i++)
	{
		if(p1.find(i)!=p1.end())
		{
			part.push_back(1);
		}
		else
		{
			part.push_back(0);
		}
	}
	/*	for(int i=0;i<part.size();i++)
	{
		cout<<part[i]<<" ";
	}
	for(set<int>::iterator it=p1.begin();it!=p1.end();it++)
	{
		int k = *it;
		cout<<k+1<<endl;
	}*/
	return part;
}
vector<int> uncoarsen(vector<int> match,graph gr,vector<int> parti)
{
	vector<int> part;
	set<pair<int,int> > set1;
	set<pair<int,int> > set2;
	map<int,int> set11;
	map<int,int> set21;
	int size1 = 0;
	int size2 = 0;
	for(int i=0;i<gr.nodelist.size();i++)
		part.push_back(0);
	int ct=0;
	for(int i=0;i<match.size();i++)
	{
		if(match[i]!=-1)
		{
		if(parti[i/2]==0)
		{
			part[match[i]] = 0;
			set11.insert(pair<int,int>(match[i],0));
			ct++;
		}
		else
		{
			part[match[i]] = 1;
			ct++;
			set21.insert(pair<int,int>(match[i],0));
		}
		}
	}
	//cout<<ct<<endl;
	for(int i=0;i<gr.nodelist.size();i++)
	{
		graphnode ne = gr.nodelist[i];
		int m = 0;
		if(set11.find(i)!=set11.end())
		{
			m = -1;
		}
		else
		{
			m = 1;
		}
		int gain = 0;
		map<int,int>::iterator trav = ne.adjlist.begin();
 			for(;trav!=ne.adjlist.end();trav++)
 			{
	 			if(set11.find(trav->first)!=set11.end())
	 			{
	 				gain = gain + m*trav->second; 
	 			}
	 			else if(set21.find(trav->first)!=set21.end())
	 			{
	 				gain = gain - m*trav->second;
	 			}
 			}
 		if(m==-1)	
 		{
 			size1 = size1 + ne.wt;
 			set1.insert(pair<int,int>(gain,i));
 			set11.erase(i);
 			set11.insert(pair<int,int>(i,gain));
 		}
 		else
 		{
 			size2 = size2 + ne.wt;
 			set2.insert(pair<int,int>(gain,i));
 			set21.erase(i);
 			set21.insert(pair<int,int>(i,gain));
 		}

	}
	int stop = 0;
	set<int> swapped;
	while(stop<25)
	{
		if(size1>size2)
		{
			set<pair<int,int> >::reverse_iterator max = set1.rbegin();
			if(max->first<=0)
				stop++;
				if(swapped.find(max->second)!=swapped.end())
				{
				cout<<"TUTA"<<endl;
				break;
				}
			graphnode ne = gr.nodelist[max->second];
			size1 = size1 - ne.wt;
			size2 = size2 + ne.wt;
			swapped.insert(max->second);
			map<int,int>::iterator trav = ne.adjlist.begin();
 			for(;trav!=ne.adjlist.end();trav++)
 			{
 				map<int,int>::iterator cgain = set11.find(trav->first);
 				if(cgain!=set11.end())
 				{
 					int cg = cgain->second;
 					set1.erase(pair<int,int>(cg,trav->first));
 					cg = cg + 2*trav->second;
 					set1.insert(pair<int,int>(cg,trav->first));

 				}
 				cgain = set21.find(trav->first);
 				if(cgain!=set21.end())
 				{
 					int cg = cgain->second;
 					set2.erase(pair<int,int>(cg,trav->first));
 					cg = cg - 2*trav->second;
 					set2.insert(pair<int,int>(cg,trav->first));
 				}
 			}
 			int max1 = max->first;
 			int max2 = max->second;
 			set1.erase(pair<int,int>(max1,max2));
 			set11.erase(max2);
 			set2.insert(pair<int,int>(-1*max1,max2));
 			set21.insert(pair<int,int>(max1,-1*max2));
		}
		else
		{
			set<pair<int,int> >::reverse_iterator max = set2.rbegin();
			if(max->first<=0)
				stop++;
				if(swapped.find(max->second)!=swapped.end())
				{
				cout<<"TUTA"<<endl;
				break;
				}
			graphnode ne = gr.nodelist[max->second];
			size2 = size2 - ne.wt;
			size1 = size1 + ne.wt;
			swapped.insert(max->second);
			map<int,int>::iterator trav = ne.adjlist.begin();
 			for(;trav!=ne.adjlist.end();trav++)
 			{
 				map<int,int>::iterator cgain = set11.find(trav->first);
 				if(cgain!=set11.end())
 				{
 					int cg = cgain->second;
 					set1.erase(pair<int,int>(cg,trav->first));
 					cg = cg - 2*trav->second;
 					set1.insert(pair<int,int>(cg,trav->first));
 				}
 				cgain = set21.find(trav->first);
 				if(cgain!=set21.end())
 				{
 					int cg = cgain->second;
 					set2.erase(pair<int,int>(cg,trav->first));
 					cg = cg + 2*trav->second;
 					set2.insert(pair<int,int>(cg,trav->first));
 				}
 			}
 			int max1 = max->first;
 			int max2 = max->second;
 			set2.erase(pair<int,int>(max1,max2));
 			set21.erase(max2);
 			set1.insert(pair<int,int>(-1*max1,max2));
 			set11.insert(pair<int,int>(max2,-1*max1));
		}
	}
	ct = 0;
	for(int i=0;i<gr.nodelist.size();i++)
	{
		if(set11.find(i)!=set11.end())
		{
			part[i] = 0;
		}
		else{
			part[i] = 1;
			ct++;
 		}
	}
	return part;
}
void changenode(graph g)
{
	map<int,int> mapp;
	for(int i=0;i<g.nodelist.size();i++)
	{
		mapp.insert(pair<int,int>(g.nodelist[i].get_id(),i));
	}
	graph gp;
	for(int i=0;i<g.nodelist.size();i++)
	{
		graphnode k = g.nodelist[i];
		graphnode te(i,k.wt);
		map<int,int>::iterator trav = k.adjlist.begin();
 		for(;trav!=k.adjlist.end();trav++)
 		{
 			int l = trav->first;
 			map<int,int>::iterator tp = mapp.find(l);
 			if(tp!=mapp.end())
 				te.add_edge(tp->second,trav->second);
 		}
 		gp.add_node(te);
	}
	divide.push_back(gp);
	mappings.push_back(mapp);
}
void split_graph(graph gr)
{
	int i=0;
		cout<<"Read"<<endl;
	graph gra(gr);
	int size = gr.nodelist.size();
	while(i<30){
		gr = coarse(gr,maximal_matching(gr));
		if(size-gr.nodelist.size()<10)
		{
			cout<<i<<endl;
			break;
		}
		i++;
		size = gr.nodelist.size();
	}
	/*		for(int i=0;i<10;i++)
	{

		graphnode k = gr.nodelist[i];
		map<int,int>::iterator trav = k.adjlist.begin();
 		for(;trav!=k.adjlist.end();trav++)
 		{
			cout<<trav->first+1<<","<<trav->second<<" ";
		}
		cout<<endl;
	}*/
	vector<int> part = partion(gr);
	for(int j=coaren_m.size()-1;j>=0;j--)
	{
		part = uncoarsen(coaren_m[j],coaren_g[j],part);
	}
	coaren_m.clear();
	coaren_g.clear();
	graph g1,g2;
	for(i=0;i<gra.nodelist.size();i++)
	{
		if(part[i]==0)
		{
			g1.add_node(gra.nodelist[i]);
		}
		else
		{
			g2.add_node(gra.nodelist[i]);
		}
	}
	cout<<g1.nodelist.size()<<endl;
	cout<<g2.nodelist.size()<<endl;
	changenode(g1);
	changenode(g2);
}


int main()
{
	graph gr;
	ifstream fr("sample_test_file");
	int n,e;
	char k2;
	fr>>n>>e;
	string line;
	getline(fr,line);
 	srand(time(NULL));
	for(int i=0;i<n;i++)
		{
			getline(fr,line);
			stringstream ss(line);
			graphnode temp(i,1);
			while(!ss.eof())
			{
				int k;
				ss>>k;
				temp.add_edge(k-1,1);
			}
			gr.add_node(temp);
		}
	divide.push_back(gr);
	int k = 4;
	int tgraph = 2*k - 1;
	for(int i=0;i<tgraph/2;i++)
	{
		cout<<"Splitting "<<i;
		split_graph(divide[i]);
	}
	map<int,int> final_div;
	int coun[k];
	for(int i=0;i<k;i++)
	{
		coun[i]=0;
	}
	cout<<"Reverse"<<endl;
	for(int i=0;i<gr.nodelist.size();i++)
	{
		int st=0;
		int find=i;
		while(st<tgraph-1)
		{
		map<int,int>::iterator tem = mappings[st].find(find);
		if(tem!=mappings[st].end())
		{
			find = tem->second;
			st = (st+1)*2;
			continue;
		}
		tem = mappings[st+1].find(find);
		if(tem!=mappings[st+1].end())
		{
			find = tem->second;
			st = (st+2)*2;
		}
		}
		st = st/2 - 1;
		st = st - k + 2;
		coun[st]++;
		final_div.insert(pair<int,int>(i,st));
	}
	cout<<endl;
	/////final_div mai sab labels hai jo print karne hai
	for(int i=0;i<k;i++)
	{
		cout<<coun[i]<<" ";
	}

	// for(int i=0;i<gr.nodelist.size();i++)
	// {
	// 	graphnode k = gr.nodelist[i];
	// 	map<int,int>::iterator myc  = final_div.find(i);
	// 	map<int,int>::iterator trav = k.adjlist.begin();
 // 		for(;trav!=k.adjlist.end();trav++)
 // 			{
 // 				map<int,int>::iterator myk  = final_div.find(trav->first);
 // 				if(myc->second!=myk->second)
 // 					edge++;
 // 			}
	// }

	int edge =0;
	for(int i=0;i<gr.nodelist.size();i++)
	{
		graphnode k = gr.nodelist[i];
		map<int,int>::iterator myc  = final_div.find(i);
		map<int,int>::iterator trav = k.adjlist.begin();
 		for(;trav!=k.adjlist.end();trav++)
 			{
 				map<int,int>::iterator myk  = final_div.find(trav->first);
 				if(myc->second!=myk->second)
 					edge++;
 			}
	}
	cout<<edge/2;
/*	for(int i=0;i<gr.nodelist.size();i++)
	{
		graphnode k = gr.nodelist[i];
		map<int,int>::iterator trav = k.adjlist.begin();
 		for(;trav!=k.adjlist.end();trav++)
 		{
			cout<<trav->first+1<<" ";
		}
		cout<<endl;
	}	
	cout<<"READ";*/
	// #pragma omp parallel
	// {
	// 	int t_no=omp_get_thread_num();
	// 	graph g1;

	// }
	// graphnode k = gr.nodelist[0];
	// cout<<k.get_id()<<" ";
	// cout<<k.adjlist[0];
	
}
