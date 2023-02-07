#include <cctype>
#include <stdexcept>
# include <string>
#include <stack>
#include <unordered_map>

using namespace std;

// typedef int defaultFunc(int , int);

class Parser {
    public:
        stack<string> s;
        // unordered_map<string, defaultFunc> f;

        Parser(){
            // f["ADD"] = [](int x, int y){return x + y;};
            // f["SUB"] = [](int x, int y){return x - y;};
            ;
        }

        int getLambda(string xs, string ys, string str){
            int x = stoi(xs) , y = stoi(ys);
            // return this -> f[str];
            if(str == "ADD") return x + y;
            else if(str == "SUB") return x - y;
            else throw invalid_argument("operation not supported: " + str);
        }

        int parseString(string str){
            if(str.empty()){
                return 0;
            }
            string buf = "";
            string left;
            int output = 0;
            string right;
            for(char c : str){
                if(isdigit(c)){
                    buf+=c;
                }
                else if( c == '('){
                    s.push(buf);
                    buf = "";
                }
                else if( c == ')'){
                    // if(!left.empty()){
                    if(!buf.empty()){
                        right = buf;
                        left = s.top();
                        s.pop();
                        output = this -> getLambda(left, right, s.top());
                        s.pop();
                        buf = "";
                        s.push(to_string(output));
                    }
                    else{
                        right = s.top();
                        s.pop();
                        left = s.top();
                        s.pop();
                        output = this -> getLambda(left, right, s.top());
                        s.pop();
                        s.push(to_string(output));
                    }
                }
                else if( c == ','){
                    // if(!buf.empty()){
                    //     left = buf;
                    // }
                    // else{
                    //     left = "0";
                    // }
                    if(!buf.empty()){
                        s.push(buf);
                        buf = "";
                    }
                }
                else{
                    buf += c;
                }
            }
            return stoi(s.top());

        }

};

int main() {
    Parser p;
    string test1 = "ADD(1,2)"; // 3
    assert (p.parseString(test1) == 3);
    string test2 = "SUB(ADD(2,3),2)"; // 3
    assert(p.parseString(test2) == 3);
    string test3 = "ADD(1,SUB(2,1))"; // 2
    assert(p.parseString(test3) == 2);
    string test4 = "SUB(ADD(1,2),SUB(2,3))"; // 4
    assert(p.parseString(test4) == 4);
    string test5 = "SUB(ADD(SUB(3,1),2),SUB(ADD(2,SUB(2,1)),3))"; // 4
    assert(p.parseString(test4) == 4);
    return 0;
}