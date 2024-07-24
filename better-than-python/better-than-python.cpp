#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main( int argc, char* argv[] ) {
    // default filename
    std::string filename( "main.cpp" );

    // check whether the argument was provided
    if ( argc > 1 )
        filename = argv[1];

    // open the file
    std::ifstream input_file( filename );
    if ( !input_file ) {
        std::cerr << "Cannot open file " << filename << "." << std::endl;
        return 1;
    }

    std::ostringstream oss;
    std::string line;
    std::string word;

    // read line by line
    while ( std::getline( input_file, line ) ) {
        std::string processed_line( "" );
        std::istringstream iss( line );
        std::string word;
        bool in_comment( false );
        bool in_preprocessor( false );

        // divide into words
        while ( iss >> word ) {
            // if we found the preprocessor directives
            if ( !in_preprocessor && (word[0] == '#') ) {
                processed_line += word + " ";
                in_preprocessor = true;
            }
            // if we found the comment
            else if ( !in_comment && (word == "//" || (word.size() > 1 && word[0] == '/' && word[1] == '/'))) {
                processed_line += " /*";
                in_comment = true;
            }
            
            // nothing, just add
            else {
                processed_line += word + " ";
            }
        }

        if ( in_comment ) processed_line += " */";
        else if ( in_preprocessor ) processed_line += "\n";

        // add the processed line to the file
        oss << processed_line << " ";
    }

    std::string result( oss.str() );
    // optional removal of the last space
    if ( !result.empty() )
        result.pop_back();

    input_file.close();

    // open the same file
    std::ofstream output_file( filename, std::ios::trunc );
    if ( !output_file ) {
        std::cerr << "Cannot open file " << filename << "." << std::endl;
        return 1;
    }

    // override it
    output_file << result;

    output_file.close();

    std::cout << "C++ is better than Python." << std::endl;
    return 0;
}
