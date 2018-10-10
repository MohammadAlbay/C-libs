#include <iostream>
#include "str.cpp"
#include <cstring>
using namespace std;
using namespace mdasd;

int main(int argc, char *argv[])
{
        str mydata = str(); // now value() will reutrn ""
        // +1 overload set(unsigned int at,char chr)
        mydata.set("Operation systems:");
        // use chain of append(s)
        mydata.append("Windows ")->append(",MacOS")
                ->append(" ,Linux")->append(" ,Unix")->append(" ,Chrome")
                ->append("and i like > ")->append(str::input());

        // you can use str::inputs(unsigned int BufferSize)
        mydata.print();
        mydata.clear(); // only free memory and set value() to ""
}
