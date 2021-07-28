 void ltrim(std::string& s) {
        while(s[0] == ' '){
            s.erase(0,1);
        }
    }
    
    void rtrim(std::string& s) { 
        while(s[s.size()-1] == ' '){
            s.erase(s.size()-1,1);
        }
    }
    
    void trim(std::string& s){
        ltrim(s);
        rtrim(s);
    }
