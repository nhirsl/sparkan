#include "StringUtils.h"

#include <algorithm>
#include <sstream>
#include <functional>

namespace StringUtils {
    std::wstring ToWideString(std::string str) {
        return std::wstring(str.begin(), str.end());
    }
    
    int ToInt(std::string str) {
        return atoi(str.c_str());
    }

    double ToDouble(std::string str) {
        return atof(str.c_str());
    }    
    
    unsigned int ToUnsignedInt(std::string str) {
        return (unsigned int)atoi(str.c_str());
    }
    
    bool ToBool(std::string str) {
        if( CaseInsensitiveEqual(Trim(str), "true" )   || 
            CaseInsensitiveEqual(Trim(str), "on"   )   || 
            CaseInsensitiveEqual(Trim(str), "yes"  )   || 
            ToDouble(Trim(str)) != 0) {
            return true;
        }
        return false;
    }
    
    std::string ToLowerCase(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    std::string ToUpperCase(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }
    
    std::string RightTrim(std::string str) {
        char* raw = const_cast<char*>(str.c_str());
        size_t len = str.length();
        char* tail = raw + len - 1;
        while(isspace(*tail--) && len--) {}
        return std::string(raw, len);
    }
    
    std::string LeftTrim(std::string str) {
        char* raw = const_cast<char*>(str.c_str());
        size_t len = str.length();
        while(isspace(*raw) && len--) {raw++;}
        return std::string(raw, len);
    }
    
    std::string Trim(std::string str) {
        return LeftTrim(RightTrim(str));
    }

    bool CaseInsensitiveEqual(std::string str1, std::string str2) {
        return ToLowerCase(std::move(str1)) == ToLowerCase(std::move(str2));
    }
    
    std::string Join(std::vector<std::string> strs, std::string joint) {
        std::string result;
        size_t m = strs.size() - 1;
        for(int i = 0; i < m; i++) {
            result += (strs.at(i) + joint);
        }
        result += strs.at(strs.size() - 1);
        return result;
    }
    
    int CaseInsensitiveCompare(std::string str1, std::string str2) {
        return ToLowerCase(std::move(str1)).compare(ToLowerCase(std::move(str2)));
    }
    
    std::string ToggleCase(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), [](char c) {
            return isalpha(c) ? (isupper(c) ? tolower(c) : toupper(c)) : c;
        });
        return str;
    }
    
    std::string ToTitle(std::string str) {
        str = ToLowerCase(str);
        std::string::iterator iter = str.begin();
        std::string::iterator end = str.end();
        while(iter != end) {
            iter = std::find_if(iter, end, [](char c) { return isalpha(c); });
            if(iter != end) { *iter = toupper(*iter); }
            iter = std::find_if(iter, end, [](char c) { return !isalpha(c); });
        }
        return str;
    }
    
    std::string ToCapitalize(std::string s) {
        std::string::iterator iter = s.begin();
        std::string::iterator end = s.end();    
        while(iter != end && !isalpha(*iter)) { iter++; }
        *iter = toupper(*iter);
        return s;
    }    
    
    std::string Reverse(std::string str) {
        // ToDo: Implement using iterators
        for(int left = 0, right = str.length() - 1; left < right; left++, right--) {
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;
        }
        return str;
    }
    
    std::vector<std::string> Split(std::string str) {
        str = Trim(str);
        if(str.empty()) {
            return {};
        } else {
            std::vector<std::string> result;
            size_t pos;
            while((pos = str.find_first_of(" \n\t\f\v\r")) != std::string::npos) {
                result.push_back(str.substr(0, pos));
                str.erase(0, pos);
                str = LeftTrim(str);
            }
            result.push_back(str);
            return result;
        }
    }
    
    std::vector<std::string> Split(std::string str, std::string delimeter) {
        if(delimeter == "") {
            return std::vector<std::string>({str});
        } else {          
            std::vector<std::string> result;
            size_t pos;
            while((pos = str.find(delimeter)) != std::string::npos) {
                result.push_back(str.substr(0, pos));
                str.erase(0, pos + delimeter.length());
            }
            result.push_back(str);
            return result;
        }
    }
    
    std::vector<std::string> Split(std::string str, std::string delimeter, int n) {
        if(delimeter == "") {
            return std::vector<std::string>({str});
        } else {
            std::vector<std::string> result;
            size_t pos;
            while((pos = str.find(delimeter)) != std::string::npos && n--) {
                result.push_back(str.substr(0, pos));
                str.erase(0, pos + delimeter.length());
            }
            result.push_back(str);
            return result;
        }
    }
    
    std::string EncodeURIComponent(std::string uriComponent) {
        std::stringstream ss;
        for(char c : uriComponent) {
            switch(c) {
            case ' ' :   ss << "%20"; break;
            case '!' :   ss << "%21"; break;
            case '\"':   ss << "%22"; break;
            case '#' :   ss << "%23"; break;
            case '$' :   ss << "%24"; break;
            case '&' :   ss << "%26"; break;
            case '\'':   ss << "%27"; break;
            case '(' :   ss << "%28"; break;
            case ')' :   ss << "%29"; break;
            case '*' :   ss << "%2A"; break;
            case '+' :   ss << "%2B"; break;
            case ',' :   ss << "%2C"; break;
            case '/' :   ss << "%2F"; break;
            case ':' :   ss << "%3A"; break;
            case ';' :   ss << "%3B"; break;
            case '=' :   ss << "%3D"; break;
            case '?' :   ss << "%3F"; break;
            case '@' :   ss << "%40"; break;
            default  :   ss << c    ; break;
            }
        }
        return ss.str();
    }
}
