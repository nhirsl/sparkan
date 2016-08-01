#pragma once

#include <string>
#include <cstring>
#include <vector>

namespace StringUtils {
    std::wstring ToWideString(std::string str);
    
    double ToDouble(std::string str);
    
    int ToInt(std::string str);
    
    unsigned int ToUnsignedInt(std::string str);
    
    bool ToBool(std::string str);
    
    std::string ToLowerCase(std::string str);

    std::string ToUpperCase(std::string str);
   
    std::string RightTrim(std::string str);
   
    std::string LeftTrim(std::string str);
        
    std::string Trim(std::string str);

    std::string Join(std::vector<std::string> strs, std::string joint);
    
    std::string ToTitle(std::string str);
    
    std::string ToCapitalize(std::string s);
    
    bool CaseInsensitiveEqual(std::string str1, std::string str2);
    
    int CaseInsensitiveCompare(std::string str1, std::string str2);
    
    std::string Reverse(std::string str);
    
    std::string ToggleCase(std::string str);
    
    std::vector<std::string> Split(std::string str);
    
    std::vector<std::string> Split(std::string str, std::string delimeter);
    
    std::vector<std::string> Split(std::string str, std::string delimeter, int n);
    
    std::string EncodeURIComponent(std::string uriComponent);
}
