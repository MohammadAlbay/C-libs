#include <iostream>
#include "str.cpp";

using namespace std;
using namespace mdasd;

int main(int argc, char *argv[])
{

        str mydata = str("Hellow, World!");
        mydata.append(" this is C++ string class");
        cout << "The value is : " << mydata.value() << endl;
        mydata.clear(); //
        mydata.append("3 2 1");
        //strlist list = mydata.split(""); // Error! you cannot split with("") nothing in str(basically in cstring)
        strlist list = mydata.split(" ");
        str::print(list[0]); // output: 3
        //list.pop_back(); delete last element
        //list.clear(); // size() = 0
        cout << "list size is : " << list.size() << endl;
}
