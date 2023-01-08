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


void help(){
    HelpMaker help("lister");
    help.add_usage("lister -f <FILE> -o <FILE> [[OPTIONS] | [-a | -A] <FILE>");
    help.add_argument("-a", "Define removal file");
    help.add_argument("-A", "Define additional file");
    help.add_argument("-d", "Filter non-digital words");
    help.add_argument("-D", "Filter digital words");
    help.add_argument("-l", "Sort by character count ascending");
    help.add_argument("-L", "Sort by character count descending");
    help.add_argument("-m", "Define minimal character count");
    help.add_argument("-M", "Define maximal character count");
    help.add_argument("-s", "Sort alphabetically ascending");
    help.add_argument("-S", "Sort alphabetically descending");
    help.add_argument("-v", "Set verbosity");
    help.add_example("lister -f mylist.txt -o output.txt -m 6 -M 12 -s");
    help.add_example("lister -f mylist.txt -o output.txt -a filter.txt");
    help.print();
}

int main(int argc, char* argv[])
{
    if(argc < 2){
        help();
    }

    // Getopt
    int c;

    while ((c = getopt (argc, argv, "f:o:vmMsSlLdDa:A:")) != -1){
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
            LOG("Sort ascending flagged");
            break;
        case 'S':
            flag_sort_descending = true;
            LOG("Sort descending flagged");
            break;
        case 'l':
            flag_length_ascending = true;
            LOG("Sort by length ascending flagged");
            break;
        case 'L':
            flag_length_descending = true;
            LOG("Sort by length descending flagged");
            break;
        case 'd':
            flag_digital = true;
            LOG("Show flagged");
            break;
        case 'D':
            flag_nondigital = true;
            LOG("Show non-digital flagged");
            break;
        case 'a':
            flag_add = true;
            filter.open(optarg);
            LOG("Add list flagged");
            break;
        case 'A':
            flag_filter = true;
            filter.open(optarg);
            LOG("Filter list flagged");
            break;
        default:
            abort();
        }
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
            LOG(buffer);
            vec.push_back(buffer);
        }
        filter.close();
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
        filter.close();
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
