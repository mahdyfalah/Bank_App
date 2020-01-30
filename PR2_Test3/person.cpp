#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<algorithm>
#include"person.h"
#include"konto.h"
using namespace std;

Person::Person(string s){
  if(s == "")
    throw runtime_error("Error! Empty name is not allowed.");
  name = s;
}
string Person::get_name() const { return name; }

int Person::add_account(int type = 0){
  //type 1 means business
  if(type == 1){
    auto acc = make_shared<BusinessAccount>(shared_from_this());
    accounts.push_back(acc);
    return acc->get_number();
  } else {
    auto acc = make_shared<GiroAccount>(shared_from_this());
    accounts.push_back(acc);
    return acc->get_number();
  }
}



bool Person::share(shared_ptr<Person> _pers, shared_ptr<Account> _sma){
  //check if this has an Account to share
  auto this_acc = find_if(accounts.begin(), accounts.end(),
                          [&_sma](const shared_ptr<Account> ptr_acc)
                          { return _sma == ptr_acc; }
                          );
  if(this_acc == accounts.end()){
    throw runtime_error(get_name() + " doesn't have an Account to share!");
    return false;
  }

  //check if other Person doesn't already have the sharable Account
  auto _pers_acc = find_if(_pers->accounts.begin(), _pers->accounts.end(),
                           [&_sma](const shared_ptr<Account> ptr_acc)
                           { return _sma == ptr_acc; }
                          );
  if (_pers_acc != _pers->accounts.end()){
    throw runtime_error(_pers->get_name() + " is already an Owner of this account!");
    return false;
  }
  _sma->add_person(_pers);
  _pers->accounts.push_back(_sma);
  return true;
}

bool Person::has_authority(shared_ptr<Account> k){
  auto it = find_if(accounts.begin(),accounts.end(), 
		[&] (shared_ptr<Account> poi) { return poi == k; });

	return it != accounts.end() ? true : false;

}



bool Person::give_up_account(shared_ptr<Account> k){
  auto result = find_if(accounts.begin(), accounts.end(),
                       [&k](const shared_ptr<Account>& ptr)
                       { return k == ptr; }
                       );
  if(result != accounts.end()) {
    accounts.erase(result);
    return true;
  } else {
    return false;
  }
}

void Person::delete_account(shared_ptr<Account> k){
  vector<weak_ptr<Person>> auth_list{ k->get_authorized_list() };
  bool flag{false};
  for(auto& it : auth_list){
    shared_ptr<Person> sh_it = it.lock(); 
    if(sh_it->get_name() == get_name()) flag = true;
  }
  if(flag){
    for(auto& it : k->get_authorized_list()){
      shared_ptr<Person> sh_it = it.lock(); 
      sh_it->give_up_account(k);
    }
  }else{
    cout << "Person not authorized!" << endl;
  }
}


ostream& Person::print(ostream& o) const{
  o << "[Name: " << name << ", ";
  o << "Account: {";
  size_t count_accounts = accounts.size();
  for_each(accounts.begin(), accounts.end(),
           [&o, &count_accounts](const shared_ptr<Account>& ptr){
             --count_accounts;
             ptr->print(o);
             if(count_accounts > 0) o << ", ";
           });
  o << "}]";
  return o;
}

ostream& Person::print_small(ostream& o) const{
  o << name;
  return o;
}

const vector<shared_ptr<Account>>& Person::get_accounts() const { return accounts; }

shared_ptr<Account> Person::get_account(size_t i) const {
	if (i >= accounts.size()) throw runtime_error("Ung. Index!");
	return accounts.at(i);
}

ostream& operator<<(ostream& o, const Person& pers) { return pers.print(o); }




















