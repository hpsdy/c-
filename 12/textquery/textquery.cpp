#include"head.h"
class textquery{
	public:
		typedef shared_ptr<vector<string>> keylist;
		typedef map<string,set<int>> keyset; 
		textquery(string filename):text(new vector<string>){
			string line;
			ifstream fn(filename,ios::in);
			if(fn.fail()){
				throw runtime_error("打开文件失败");
			}
			stringstream ss;
			string key;
			int num=0;
			while(!fn.eof()){
				++num;
				getline(fn,line);
				text->push_back(line);		
				ss.clear();
				ss.str(line);
				while(ss>>key){
					auto ret = retmap.find(key);
					if(ret==retmap.end()){
						set<int> tmp;
						retmap.insert({key,tmp});	
					}
					ret = retmap.find(key);
					auto &scores = ret->second;
				        scores.insert(num);	
				}
			}
			fn.close();
		}
		textresult query(string key){
		/*	for(auto &c:retmap){
				cout<<"key:"<<(c.first)<<endl;
				for(auto &ic:c.second){
					cout<<ic<<'\t';
				}
				cout<<endl;
			}*/
			auto ret = retmap.find(key);
			if(ret == retmap.end()){
				set<int> tmp;
				vector<string> vec;
				return {"",tmp,vec};
			}else{
				string key = ret->first;
				auto scores = ret->second;
				vector<string> tmp;
				for(auto &c:scores){
					auto line = (*text)[c-1];
					tmp.push_back(line);
				}
				return {key,scores,tmp};
			}	
		}
		~textquery(){		
		}
		

	private:
		keylist text;
		keyset retmap; 
	

}; 
