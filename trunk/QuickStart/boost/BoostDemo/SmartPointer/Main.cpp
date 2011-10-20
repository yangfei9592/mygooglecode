#include <iostream>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

using namespace std;

void autoPtr()
{
  auto_ptr<string> MyOwnString(new string("This is mine to keep!")); 
  auto_ptr<string> NoItsMine(MyOwnString);

  if (MyOwnString.get() == NULL)
  {
    cout<<"MyOwnString is NULL"<<endl;
  }
  else
  {
    cout << MyOwnString->c_str() << endl;
  }

  if (NoItsMine.get() == NULL)
  {
    cout<<"NoItsMine is NULL"<<endl;
  }
  else
  {
    cout << NoItsMine->c_str() << endl;
  }
}

void shardPtr()
{
  using namespace boost;
  shared_ptr<string> p(new string("shard Ptr!"));
  shared_ptr<string> p2(p);
  cout<<p->c_str()<<endl;
  cout<<p2->c_str()<<endl;
}

void scopedPtr()
{
  using namespace boost;
  scoped_ptr<string> p(new string("shard Ptr!"));
  //forbid to transfer pointer
  //scoped_ptr<string> p2(p);
  cout<<p->c_str()<<endl;
  //cout<<p2->c_str()<<endl;
}

int main()
{
  shardPtr();
}