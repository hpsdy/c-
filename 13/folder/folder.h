#ifndef MSG
#define MSG
#include<set>
#include<string>
class folder;
class msg{
	friend class folder;
	friend void swap(msg &,msg &);
	public:
		msg(const std::string &str=""):name(str){}
		msg(const msg &);
		msg& operator=(const msg &);
		msg& operator=(const std::string &str);
		~msg(){};
		void save(folder &);
		void remove(folder &);
	private:
		std::string name;
		std::set<folder*> folders;	
		void add_to_folders(const msg&);
		void rm_from_folders();
		void add_folder(folder *p){folders.insert(p);}
		void rm_folder(folder *p){folders.erase(p);}
};
void swap(msg &,msg &);
class folder{
	friend class msg;
	friend void swap(folder &,folder &);
	public:
		folder(std::string str=""):name(str){}
		folder(const folder &);
		void save(msg &);
		void remove(msg &);
		~folder(){};
	private:
		std::string name;
		std::set<msg*> messages;
		void add_to_msg(const folder&);
		void rm_from_msg();
		void add_msg(msg *p){messages.insert(p);}
		void rm_msg(msg *p){messages.erase(p);}
};
void swap(folder &,folder &);
#endif
