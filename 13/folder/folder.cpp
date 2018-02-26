#include"folder.h"
msg::msg(const msg &p):name(p.name),folders(p.folders){
	add_to_folders(p);
}
msg& msg::operator=(const msg &p){
	rm_from_folders();
	folders.clear();
	name = p.name;
	folders = p.folders;
	add_to_folders(p);	
}
void msg::add_to_folders(const msg &p){
	for(auto b = p.folders.begin(),e = p.folders.end();b!=e;++b){
		(*b)->save(*this);
	}
}
void msg::rm_from_folders(){
	for(auto b = folders.begin(),e = folders.end();b!=e;++b){
		(*b)->remove(*this);
	}

}
void msg::save(folder &p){
	add_folder(&p);
	p.save(*this);		
}
void msg::remove(folder &p){
	rm_folder(&p);
	p.remove(*this);
}
folder::folder(const folder &p):name(p.name),messages(p.messages){
	add_to_msg(p);
}
void folder::add_to_msg(const folder &p){
	for(auto b = p.messages.begin(),e = p.messages.end();b!=e;++b){
		(*b)->save(*this);
	}
}
void folder::rm_from_msg(){
	for(auto b = messages.begin(),e = messages.end();b!=e;++b){
		(*b)->remove(*this);
	}
}
void folder::save(msg &p){
	add_msg(&p);
	p.save(*this);
}
void folder::remove(msg &p){
	rm_msg(&p);
	p.remove(*this);
}











