#ifndef STRINGS_H
#define STRINGS_H

std::string capitalized(std::string s){
	std::string buffer;
	if(s.length() > 0){
		for(int i = 0; i < s.length(); ++i){
			if(i == 0){
				buffer.push_back(toupper(s[i]));
			}else{
				buffer.push_back(tolower(s[i]));
			}
		}
	}
	return buffer;
}

std::string lowercase(std::string s){
	std::string buffer;
	for(int i = 0; i < s.length(); ++i){
		buffer.push_back(tolower(s[i]));
	}
	return buffer;
}

std::string uppercase(std::string s){
	std::string buffer;
	for(int i = 0; i < s.length(); ++i){
		buffer.push_back(toupper(s[i]));	
	}
	return buffer;
}

std::string spacer(std::string s, int space){
	std::string buffer;
	buffer = s;
	int total = space - s.length();
	for(int i = 0; i < total; ++i){
		buffer.push_back(' ');
	}
	return buffer;
}

#endif // STRINGS_H