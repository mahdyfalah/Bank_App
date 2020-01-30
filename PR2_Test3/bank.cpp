#include<algorithm>
#include<vector>
#include<memory>
#include<iostream>
#include"bank.h"
using namespace std;

void Bank::customer(shared_ptr<Person> p){
  auto name_pair = make_pair(p->get_name(), p);
  map_name.insert(name_pair);
  vector<shared_ptr<Account>> vec_help {p->get_accounts()};
  for(auto& it : vec_help){
    auto id_pair = make_pair(it->get_number(), it);
    map_id.insert(id_pair);
  }
}

shared_ptr<Person> Bank::search_person(string name){
  return map_name.find(name)->second;
}

shared_ptr<Account> Bank::search_account(int id){
  return map_id.find(id)->second;
}

void Bank::del_person(shared_ptr<Person> p){
  auto name_del_ptr = map_name.find(p->get_name());
  map_name.erase(name_del_ptr);

  vector<shared_ptr<Account>> vec_help {p->get_accounts()};
  for(auto& it : vec_help){
    int id_help{it->get_number()};
    auto id_del_ptr = map_id.find(id_help);
    map_id.erase(id_del_ptr);
  }
}


ostream& Bank::print(ostream& o) const{
  o << "Map: [" << endl;
  for_each(map_name.begin(), map_name.end(),
           [&o](const pair<string, shared_ptr<Person>>& p)
           { o << *p.second << endl; }
           );
  o << "]";
  return o;
}

ostream& operator<<(ostream& o, const Bank& b) { return b.print(o); }
