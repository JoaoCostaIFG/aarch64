 std::vector<std::string> decomp_line(std::string& original_str, std::string delimiter, int paramater_num){
     /*
        Devides an input line (saved on a string) based on the given delimiter
        Return a vector of strings that contain each one of the contents given by the line
     */
    std::stringstream temp_stream; //helps format lines that need it
    std::string temp_str, holder_str = ""; //helper strings
    std::vector<std::string> result_struct; //vector that will contain the required struct values
    size_t i = 0;
    temp_stream << original_str; //move that line to temporary stringstream

    while(i < paramater_num){
        temp_stream >> temp_str;
        if(temp_str == delimiter){
            i++;
            result_struct.push_back(holder_str);
            holder_str = "";
        }
        else{
            holder_str.append(temp_str);
            holder_str.append(" ");
        }
    }
    
    std::cout << result_struct[0] << "\n";
    std::cout << result_struct[1] << "\n";
    std::cout << result_struct[2] << "\n";
    std::cout << result_struct[3] << "\n";
    std::cout << result_struct[4] << "\n";
    return result_struct;
}


void line_decomp(std::vector<std::string>& return_vec, std::string line, char delim){
    std::stringstream temp_stream; //helps format lines that need it
    std::string temp_str;
    bool flag = true; //swtiches to false when we've read all the clients' info present in the file

    temp_stream << line; //move that line to temporary stringstream

    while(flag){
        getline(temp_stream, temp_str, delim);
        temp_str = temp_str.substr(temp_str.find_first_not_of(" "), temp_str.find_last_not_of(" ") - temp_str.find_first_not_of(" ") + 1); //trim white spaces from beggining and end of string
        return_vec.push_back(temp_str);
        getline(temp_stream,temp_str);
        std::cout << temp_str << "\n";
        system("pause");
        if(temp_str == "::::::::::")
            flag = false; //checks if there are more clients to read
    }

    /*
    for(size_t i =0; i < argument_size; i++){
        getline(temp_stream, temp_str, delim);
        temp_str = temp_str.substr(temp_str.find_first_not_of(" "), temp_str.find_last_not_of(" ") - temp_str.find_first_not_of(" ") + 1); //trim white spaces from beggining and end of string
        return_vec.push_back(temp_str);
    }*/
}