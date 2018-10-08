 /************************************************************************************************************************
 **************************************************************************************************************************
 **                             MDASD v1.                                                                                **
 **     Author : Mohammad albay                                                                                          **
 **     Date   : 10/8/2018                                                                                               **
 **     Information : str class was built generaly just because there's no easy class to work with strings in C++,       **
 **                   str offers many features like a stability, scalibility with strings and it has many methods to     **
 **                   do your job instead of creating functions that isn't useful/use-able with other string functions   **
 **                                                                                                                      **
 **                                 Feel free to use/modifiy/distribute                                                  **
 **                                                                                                                      **
 **                                 ---------------------------------------------                                        **
 **                                     this software is under MIT liceins                                               **
 **************************************************************************************************************************
  ************************************************************************************************************************/
#include <vector>

using namespace std;

typedef vector<char *> strlist;

namespace mdasd
{
    class str
    {
    private:
        char * val;
        int dest = 0;
        char *trim(const char * p)
    {
        int index = 0;
        for(unsigned int k  = 0;k<strlen(p);k++)
        {
            if(p[k] != ' ') {index = k;break;}
        }
        char *result = (char *)malloc((strlen(p)-index)+1);
        if(result == NULL) {
            cout << "<str::trim(const char * p)> : Memory allocation error" <<endl; exit(1);
        }
        for(unsigned int k = 0;index<strlen(p);k++,index++)
        {
            result[k] = p[index];
        }
        return result;
    }
    public:

        str(const char * p)
    {
        val = (char *)malloc(strlen(p)+1);
        if(val == NULL) {
            cout << "<str::str(const char * p)> : Memory allocation error" <<endl; exit(1);
        }
        strcpy(val,p);
        val[strlen(p)] = '\0';

    }
        str * ptr()
    {
        return this;
    }
        ~str()
    {
        dest  =1;
        free(val);
    }
        void   clear() {
            if(val && dest == 0) {free(val);}
        }
        void   append(const char * p)
    {
        char* temp = val;
        size_t s = strlen(p)+strlen(val);
        val = (char *)malloc(s+1);
        if(val == NULL) // allocation failed
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
        //delete temp;
        free(temp);
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
        char * value() {return val;}
        char * replace(const char Old,const char New)
    {
        // do something
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
        // do something
        for(int i = 0;i < strlen(val);i++)
        {
            if(val[i] == Old)
            {
                val[i] = New; break;
            }
        }
        return val;
    }
        char * trim() { return trim(val); }
        char * slice(unsigned int from)
    {
         if(from >= length()) {cout << "<str::slice(unsigned int from)> : Out of string range, from=" << from << " length=" << length() << endl; exit(1);}
         unsigned int len = length()-from;
         char * result = (char *)malloc(len);
         for(int i = 0;i < len && from < length(); i++,from++)
         {
             result[i] = val[from];
         }
         return result;
    }
        char * slice(unsigned int from,unsigned int count)
    {
         if(from >= length()) {cout << "<str::slice(unsigned int from,unsgined int to)> : Out of string range, from=" << from << " length=" << length() << endl; exit(1);}
         if(count >= length()) {cout << "<str::slice(unsigned int from,unsgined int to)> : Out of string range, to=" << count << " length=" << length() << endl; exit(1);}
         unsigned int len = length()-from-count;
         char * result = (char *)malloc(len);
         if(result == NULL) { cout << "<str::slice(unsigned int from,unsigned int count)> : Memory allocation error" <<endl; exit(1);}
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
        unsigned int countOf(const char * chr)
    {
        int k = 0;
        for(int i = 0;i<length();i++)
        {
            if(val[i] == chr[0]) {k++;}
        }
        return k;
    }
        strlist split(const char * chr)
    {
            char * nv = (char *)malloc(length());
            for(int i = 0;i<length(); i++)
            {
                nv[i] = val[i];
            }
        nv = strtok(nv,chr);
        strlist v;
        //v.push_back(nv);
        while(nv)
        {
            v.push_back(nv);
            nv = strtok(NULL,chr);
            //cout << nv << endl;
        }
        free(nv);
       std::cout << val << std::endl;
        return v;

    }
    };

}

