#include <iostream>
#include <getopt.h>
#include <fstream>
#include <algorithm>
#include "uforia/uforia.h"

using namespace std;

#define DEBUG 1
#if DEBUG
#define LOG(x) cout << colored(x, Red) << endl
#else
#define LOG(x)
#endif

ifstream file, filter;
ofstream write;
vector<string> vec;
int minimal = 0, maximal = 255;
bool flag_file, flag_write, flag_verbose, flag_sort_ascending, flag_sort_descending,
flag_length_ascending, flag_length_descending, flag_digital, flag_nondigital,
flag_add, flag_filter;

bool is_digital(string s){
    string digits = "0123456789!@#$%^&*()-=_+,.<>";
    for(int i = 0; i < digits.length(); ++i){
        char c = digits[i];
        if(has(c, s)){
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    // TODO: Add filter/add list


    // Getopt
    int c;

    while ((c = getopt (argc, argv, "f:o:vmMsSlLdDa:A:")) != -1)
        switch (c)
        {
        case 'f':
            file.open(optarg);
            flag_file = true;
            LOG(optarg);
            break;
        case 'o':
            write.open(optarg);
            flag_file = true;
            break;
        case 'v':
            flag_verbose = true;
            LOG("Verbose is flagged");
            break;
        case 's':
            flag_sort_ascending = true;
            break;
        case 'S':
            flag_sort_descending = true;
            break;
        case 'l':
            flag_length_ascending = true;
            break;
        case 'L':
            flag_length_descending = true;
            break;
        case 'd':
            flag_digital = true;
            break;
        case 'D':
            flag_nondigital = true;
            break;
        case 'a':
            flag_add = true;
            filter.open(optarg);
            break;
        case 'A':
            flag_filter = true;
            filter.open(optarg);
            break;
        case '?':
            if (optopt == 'c')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Unknown option character `\\x%x'.\n",
                         optopt);
            return 1;
        default:
            abort ();
        }

    // If no file is given the program will be aborted
    if(!flag_file){
        error("No file was given", true);
    }

    // Create vector from file
    string buffer;
    while(file >> buffer){
        vec.push_back(buffer);
    }
    file.close();

    // Add a list
    if(flag_add){
        string buffer;
        while(filter >> buffer){
            vec.push_back(buffer);
        }
    }

    // Filter with a list
    if(flag_filter){
        string buffer;
        vector<string> temp;
        while(filter >> buffer){
            bool match;
            for(int i = 0; i < vec.size(); ++i){
                string line = vec[i];
                if(line == buffer){
                    match = true;
                }
            }
            if(!match){
                temp.push_back(buffer);
            }
        }
        vec = temp;
    }

    // Sort vector alphabeticaly ascending
    if(flag_sort_ascending){
        sort(vec.begin(), vec.end(), [](string a, string b){return a < b;});
    }

    // Sort vector alphabeticaly descending
    if(flag_sort_descending){
        sort(vec.begin(), vec.end(), [](string a, string b){return a > b;});
    }

    // Sort vector by length ascending
    if(flag_length_ascending){
        sort(vec.begin(), vec.end(), [](string a, string b){return a.length() < b.length();});
    }

    // Sort vector by length descending
    if(flag_length_descending){
        sort(vec.begin(), vec.end(), [](string a, string b){return a.length() > b.length();});
    }

    // Remove digital strings
    if(flag_nondigital){
        vector<string> buffer;
        for(int i = 0; i < vec.size(); ++i){
            if(!is_digital(vec[i])){
                buffer.push_back(vec[i]);
            }
        }
        vec = buffer;
    }

    // Remove non-digital strings
    if(flag_digital){
        vector<string> buffer;
        for(int i = 0; i < vec.size(); ++i){
            if(is_digital(vec[i])){
                buffer.push_back(vec[i]);
            }
        }
        vec = buffer;
    }

    // Write to file
    if(flag_write){
        for(int i = 0; i < vec.size(); ++i){
            string line = vec[i];
            write << line;
        }
        write.close();
    }

    // Print file
    if(flag_verbose){
        for(int i = 0; i < vec.size(); ++i){
            cout << vec[i] << endl;
        }
    }

}
