 /************************************************************************************************************************
 **************************************************************************************************************************
 **                                                    MDASD v1.                                                         **
 **     Author : Mohammad albay                                                                                          **
 **     Date   : 10/8/2018                                                                                               **
 **     Information : str class was built generally just because there's no easy class to work with strings in C++,      **
 **                   str offers many features like a stability, scalability with strings and it has many methods to     **
 **                   do your job instead of creating functions that isn't useful/useable with other string functions    **
 **                                                                                                                      **
 **                                 Feel free to use/modifiy/distribute                                                  **
 **                                                                                                                      **
 **                                 ---------------------------------------------                                        **
 **                                     this software is under MIT liceins                                               **
 **************************************************************************************************************************
  ************************************************************************************************************************/
/*\
|*| changes \ updates log ( V3 ) {
|*|     + pop() method to delete last char.
|*|     + append(str p) method to add object.value() to current object.
|*|     + input(),inputs(unsigned int BufferSize) and read()[+ overload] method to read data from input stream
|*|     + append() now returns (str *) for use a chain of append. e.g: obj.append("Hello")->append(",")->append("World!") 
|*|     + fixed many bugs, now it works very well, no memory leaks were noticed- i hope so :)
|*| }
\*/
#include <vector>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

typedef vector<char *> strlist;

namespace mdasd
{
    static const unsigned int
        SBuffer = 50,
        NBuffer = 265,
        MBuffer = 265*3,
        LBuffer = 265*6;

    class str
    {
    private:
        char * val;


    public:

        str(const char * p)
        {
            val = (char *)malloc(strlen(p)*sizeof(char*));
            if(!val)
            {
                cout << "<str::str(const char * p)> : Memory allocation error" <<endl; exit(1);
            }
            strcpy(val,p);
            val[strlen(p)] = '\0';

        }
        str() {val = "";}
        str * ptr()
        {
            return this;
        }
        ~str()
    {
        free(val);
    }
        void   clear()
        {
            free(val);
            val = "";
        }
        void   print()
        {
            cout << val << endl;
        }
        str * append(const char * p)
        {
            char* temp = val;
            size_t s = strlen(p)+strlen(val);
            val = (char *)malloc(s*sizeof(char*)+sizeof(char*));
            if(!val)
            {
                cout << "<str::append(const char * p)> : Memory allocation error" <<endl; exit(1);
            }
            unsigned int point = 0;
            for(;point < strlen(temp);point++)
            {
                val[point] = temp[point];
            }
            for(int i = 0;i < strlen(p);point++,i++)
            {
                val[point] = p[i];
            }
            val[s] = '\0';
            free(temp);
            return this;
        }
        void   append(str p) {
            append(p.value());
        }
        void   append(char chr)
        {
            append((const char *)chr);
        }
        void   set(unsigned int at ,char chr)
        {
            if(at >= length()) {cout << "<str::set(unsigned int at,char chr)> : Out of string range, index=" << at << " length=" << length() << endl; exit(1);}
            val[at] = chr;
        }
        void   set(char * p)
        {
            val = p;
        }
        void   pop()
        {
            unsigned int len = length()-1,nlen = len+1;
            char * temp = new char[nlen+1];
            strcpy(temp,val);
            temp[nlen] = '\0';
            free(val);
            val = (char *)malloc(len*sizeof(char*));
            if(!val)
            {
                cout << "<str::str(const char * p)> : Memory allocation error" <<endl; exit(1);
            }
            strcpy(val,temp);
            val[len] = '\0';
        }
        void   read()
        {
            append(str::input());
        }
        void   read(unsigned int BufferSize)
        {
            append(str::inputs(BufferSize));
        }
        char * value() {return val;}
        char * replace(const char Old,const char New)
        {
            for(int i = 0;i < strlen(val);i++)
            {
                if(val[i] == Old)
                {
                    val[i] = New;
                }
            }
            return val;
        }
        char * replaceFirst(const char Old,const char New)
        {
            for(int i = 0;i < strlen(val);i++)
            {
                if(val[i] == Old)
                {
                    val[i] = New; break;
                }
            }
            return val;
        }
        char * trim(const char * p)
        {
            int index = 0;
            for(unsigned int k  = 0;k<strlen(p);k++)
            {
                if(p[k] != ' ') {index = k;break;}
            }
            cout << index << endl;

            return slice(index);
        }
        char * trim() { return trim(val); }
        char * slice(unsigned int from)
    {
         if(from >= length()) {cout << "<str::slice(unsigned int from)> : Out of string range, from=" << from << " length=" << length() << endl; exit(1);}
         unsigned int len = length()-from;
         char * result = (char *)malloc(len*sizeof(char *)+1);
         for(int i = 0;i < len && from < length(); i++,from++)
         {
             result[i] = val[from];
         }
         result[len] = '\0';
         return result;
    }
        char * slice(unsigned int from,unsigned int count)
    {
         if(from >= length()) {cout << "<str::slice(unsigned int from,unsgined int to)> : Out of string range, from=" << from << " length=" << length() << endl; exit(1);}
         if(count >= length()) {cout << "<str::slice(unsigned int from,unsgined int to)> : Out of string range, to=" << count << " length=" << length() << endl; exit(1);}
         unsigned int len = length()-from-count;
         char * result = (char *)malloc(len);
         if(!result) { cout << "<str::slice(unsigned int from,unsigned int count)> : Memory allocation error" <<endl; exit(1);}
         for(int i = 0;i < count && from < length(); i++,from++)
         {
             result[i] = val[from];
         }
         return result;
    }
        char   charAt(unsigned int at)
    {
        if(at >= length()) {cout << "<str::charAt(unsigned int at)> : Out of string range, index=" << at << " length=" << length() << endl; exit(1);}
        return val[at];
    }
        unsigned int length ()
    {
        return strlen(val);
    }
        unsigned int startsWith(const char *sample)
    {
        if(sample[0] != val[0]) {return 0;}
        int result = 1;
        for(int i = 0;i<length()&&i<strlen(sample);i++)
        {
            if(val[i] != sample[i]) {result = 0;break;}
        }
        return result;
    }
        unsigned int startsWith(const char *sample,unsigned int caseSensitive)
    {
        if(sample[0] != val[0]) {return 0;}
        int result = 1;
        if(caseSensitive == 0)
        {
            for(int i = 0;i<length()&&i<strlen(sample);i++)
            {
                if(val[i] != sample[i]) {result = 0;break;}
            }
        }
        else
        {
            for(int i = 0;i<length()&&i<strlen(sample);i++)
            {
                char secondValue = ((int) sample[i] > 96) ? sample[i] - 32 : sample[i] + 32;
                if(val[i] != sample[i] && secondValue != val[i]) {result = 0;break;}
            }
        }
        return result;
    }
        unsigned int endsWith(const char *sample)
    {
        if(sample[strlen(sample)-1] != val[length()-1]) {return 0;}
        int result = 1;
        for(int i = length()-1,k = strlen(sample)-1;i>-1&&k>-1;i--,k--)
        {
            if(val[i] != sample[k]) {result = 0;break;}
        }
        return result;
    }
        unsigned int endsWith(const char *sample,unsigned int caseSensitive)
    {
        if(sample[strlen(sample)-1] != val[length()-1]) {return 0;}
        int result = 1;
        if(caseSensitive == 0)
        {
            for(int i = length()-1,k = strlen(sample)-1;i>-1&&k>-1;i--,k--)
            {
                if(val[i] != sample[k]) {result = 0;break;}
            }
        }
        else
        {
            for(int i = length()-1,k = strlen(sample)-1;i>-1&&k>-1;i--,k--)
            {
                char secondValue = ((int) sample[k] > 96) ? sample[k] - 32 : sample[k] + 32;
                if(val[i] != sample[k] && val[i] != secondValue) {result = 0;break;}
            }
        }
        return result;
    }
        unsigned int containes(const char *sample)
    {
        int result = 0;
        for(int i = 0;i<length();i++)
        {
            if(val[i] == sample[0])
            {
                result = 1;
                for(int k = 1,j = i+1;k<strlen(sample)&&j<length();k++,j++)
                {
                    if(sample[k] != val[j]) {result = 0;}
                    else {result = 1;}
                }
            }
        }
        return result;
    }
        unsigned int indexOf(char chr)
        {
            for(int i = 0;i<length();i++)
            {
                if(val[i] == chr) {return i;}
            }
            return 0;
        }
        unsigned int lastIndexOf(char chr)
        {
            for(int i = length()-1;i>-1;i--)
            {
                if(val[i] == chr) {return i;}
            }
            return 0;
        }
        unsigned int countOf(char chr)
        {
            int k = 0;
            for(int i = 0;i<length();i++)
            {
                if(val[i] == chr) {k++;}
            }
            return k;
        }
        unsigned int equals(str obj)
        {
            return (obj.value() == val) ? 1 : 0;
        }
        unsigned int equals(const char * p)
        {
            return (value() == p) ? 0 : 1;
        }
        strlist split(const char * chr)
        {
            if(chr == "")
            {
                cout << "<str::split(const char * chr)> : cannot split str with '' as delimiter, instead you can use toCharArray() method" << endl; exit(1);
            }
            char * nv = (char *)malloc(length()+1);
            if(!nv)
            {
                cout << "<str::split(const char * chr)> : Memory allocation error" <<endl; exit(1);
            }
            for(int i = 0;i<length(); i++)
            {
                nv[i] = val[i];
            }
            nv[length()]='\0';
            nv = strtok(nv,chr);
            strlist v;
            while(nv)
            {
                v.push_back(nv);
                nv = strtok(NULL,chr);
            }
            free(nv);
            return v;
        }
        // static members
        // v2


        static void print(const char * p)
        {
            cout << p << endl;
        }
        static void print(str p)
        {
            cout << p.value() << endl;
        }

        static char * inputs(unsigned int BufferSize)
        {
            char * buffer = new char[BufferSize];
            cin >> buffer;
            return buffer;
        }
        static char * input()
        {
            return inputs(NBuffer);
        }
        static char * readFile(const char * fp)
        {

            FILE * f = fopen(fp,"r");
            if(f)
            {
                str content = str();
                char * data = new char[265];
                while(fgets(data,265,f))
                {
                    content.append(data);
                }
                fclose(f);
                return content.value();
            }
            else
            {
                cout << "<str:readFile(const char * fp)> : file doesn't exists" << endl; exit(1);
            }
        }

    };

}
