#include<bits/stdc++.h>
using namespace std;
map<int,set<pair<int , int > > >adj;
map<int,pair<string,pair<float, float>> > pinLocation;
map<int,string> pinCodeToPlaceNameMap;
map<int,int>meta;


void generateAmenities(){

	cout<<"Enter Pin-Code whose nearest pin-code you want to get : \n";
	int code,K;
	cin>>code;
	cout<<"Enter No of Pin-Codes Closest to this one : \n";
	cin>>K;

	float x = pinLocation[code].second.first;
	float y = pinLocation[code].second.second;
    cout<<pinLocation[code].first;
	vector<vector<float>> points;

	for(auto it = pinLocation.begin();it != pinLocation.end();it++){

		pair<float,float> tmp = it->second.second;

		vector<float>vec;
		vec.push_back(tmp.first);
		vec.push_back(tmp.second);
		points.push_back(vec);
	}
	priority_queue<pair<float,int> ,vector<pair<float,int>>, greater<pair<float,int>>>pq;
        for(int i=0;i<points.size();i++)
        {
        	float xVal = abs(points[i][0] - x);
        	float yVal = abs(points[i][1] - y);
            float distance = sqrt(pow(xVal,2)+pow(yVal,2));
            pq.push(make_pair(distance,i));
        }
        int cnt=0;
        vector<vector<float>>ans;
        vector<int>pins;
        while(cnt<K && pq.empty()==false)
        {
            pair<float,int> top=pq.top();
            pq.pop();
            int pos = top.second;
            ans.push_back(points[pos]);
            pins.push_back(pos);
            cnt++;
        }
        cout<<"Closest "<<K<<" Pin-Codes to this Pin-Code are : \n\n";

        for(int i = 0;i < ans.size();i++){

        	auto it = pinLocation.begin();
        	advance(it,pins[i]);
        	cout<<it->first<<"  "<<it->second.first<<" ";
        	for(int j = 0;j < ans[i].size();j++){
        		cout<<ans[i][j]<<"  ";
			}
			cout<<"\n";
		}
		cout<<"\n";
}
void disaster(){

	int thresh,current;
	cout<<"Enter Threshold Population to be notified\n";
	cin>>thresh;
	cout<<"Enter Current Pin-Code\n";
	cin>>current;

	int curTotal = 0;
	queue<int>q;
	q.push(current);
	map<int,bool>visited;
	visited[current] = true;
	vector<int>danger1;
	vector<int>danger2;
	vector<int>danger3;
	int level = 0;
	while(q.empty() == false){
		int size = q.size();

		for(int i = 0;i < size;i++){
			int top = q.front();
			q.pop();

			set<pair<int,int> > s= adj[top];
			for(auto x: s){
				if(visited[x.first] == false){
					visited[x.first] = true;
					q.push(x.first);

					if(level == 0)
						danger1.push_back(x.first);
					else if(level == 1)
						danger2.push_back(x.first);
					else if(level == 2)
						danger3.push_back(x.first);
				}
			}

		}
		level++;
	}
	cout<<"Danger Level 1 : \n";
	for(int i = 0;i < danger1.size();i++){
		cout<<danger1[i]<<"("<<pinCodeToPlaceNameMap[danger1[i]]<<")"<<"   ";
	}
	cout<<"\nDanger Level 2 : \n";
	for(int i = 0;i < danger2.size();i++){
		cout<<danger2[i]<<"("<<pinCodeToPlaceNameMap[danger2[i]]<<")"<<"   ";
	}
	cout<<"\nDanger Level 3 : \n";
	for(int i = 0;i < danger3.size();i++){
		cout<<danger3[i]<<"("<<pinCodeToPlaceNameMap[danger3[i]]<<")"<<"   ";
	}
}
void Bail(){

	int start,finish;
	cout<<"Enter Pin-Code 1\n";
	cin>>start;
	cout<<"Enter Pin-Code 2\n";
	cin>>finish;

	map<int,int>dp;
	map<int,bool>visited;

	priority_queue<pair<double,int>>pq;

		pq.push({0.0000,start});

        while(pq.empty() == false)
        {
            pair<double,int> element = pq.top();
            pq.pop();

            if(visited[element.second])
                continue;

            visited[element.second] = true;
            set<pair<int, int> > s = adj[element.second];

            for(auto it: s)
            {
                if(visited[it.first] == false)
                {
                    int tmp = dp[it.first];
                    dp[it.first] = max(dp[it.first],dp[element.second] + (it).second);

                    if(tmp != dp[it.first])
                    {
                        pq.push({dp[it.first],it.first});
                    }
                }
            }
        }
        cout<<"While Going From Pin-Code : "<<start<<"("<<pinCodeToPlaceNameMap[start]<<")"<<" to Pin-Code : "<<finish<<"("<<pinCodeToPlaceNameMap[finish]<<")"<<endl;

        cout<<"Covers Maximum "<<dp[finish]<<" people";

        cout<<"\n\n";
}
int main(){

	ifstream ip("C:\\Users\\admin\\Desktop\\geopin-demo\\PinCode.csv");
	ifstream metaData("C:\\Users\\admin\\Desktop\\geopin-demo\\metaData.csv");
	ifstream loc("C:\\Users\\admin\\Desktop\\geopin-demo\\IN.csv");

	if(!metaData.is_open())
		cout<<"Error Found";

	if(!ip.is_open())
		cout<<"Error opening file";

	if(!loc.is_open())
		cout<<"Error opening file";


	string pin,population,val1,val2,val3,temp;

	while(loc.good()){
		getline(loc,val1,',');
		getline(loc,val2,',');
		//
		getline(loc,temp,',');
        getline(loc,val3,'\n');
		if(val1 == "" || val2 == "" || temp == "")
			break;
		int code = stoi(val1);
		float lati = stof(val2);
		float longi = stof(temp);

		string place=val3;
		pinCodeToPlaceNameMap[code]=place;
		pinLocation[code] = make_pair(place,make_pair(lati,longi));
		//cout<<lati<<" "<<longi<<"\n";
	}
	loc.close();
	while(metaData.good()){

		getline(metaData,pin,',');
		getline(metaData,population,'\n');

		if(pin == "")
			break;

		int pinI = stoi(pin);
		int popI = stoi(population);

		meta[pinI] = popI;
	}
//	for(auto it = meta.begin();it != meta.end();it++){
//		cout<<it->first<<" "<<it->second<<"\n";
//	}



	while(ip.good()){
		getline(ip,val1,',');
		getline(ip,val2,'\n');

		if(val1 == "")
			break;

		int v1 = stoi(val1);
		int v2 = stoi(val2);
		int wt = (meta[v1] + meta[v2])/2;

		adj[v1].insert({v2,wt});
		adj[v2].insert({v1,wt});

	}
	ip.close();



//	for(auto it = adj.begin();it != adj.end();it++){
//		cout<<"first: "<<it->first<<" : ";
//
//		set<pair<int,int> >vec = it->second;
//		cout<<"\n\n";
//
//		for(auto x: vec){
//			cout<<"{ "<<x.first<<" , "<<x.second<<"} ,";
//		}
//		cout<<"\n\n";
//	}

	cout<<"1: Generation Of Nearest Hospitals/Fire-Stations etc\n\n";
	cout<<"2: Disaster Management\n\n";
	cout<<"3: Maximum People between 2 pin-codes\n\n";
	cout<<"Enter Code Of Application To Consider\n";

	int ans;
	cin>>ans;
	switch(ans){
		case 1:
			generateAmenities();
			break;
		case 2:
			disaster();
			break;
		case 3:
			Bail();
			break;
		default:
		cout<<"Enter Valid Code\n";
		break;
	}
	return 0;
}
