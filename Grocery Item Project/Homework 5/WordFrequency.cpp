#include "WordFrequency.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <locale>     // tolower()


namespace
{
  std::string sanitize( const std::string & word )
  {
    constexpr char bad_char[] = " \t\n\b\v_-\"'(){}+/*,=.!?:;";            // leading and trailing characters to be removed
    static std::locale locality;

    auto startIndex = word.find_first_not_of( bad_char );                  // start with the first non-bad character
    if( startIndex == std::string::npos ) startIndex = word.size();        // if the word contains only bad characters ...
                                                                           
    std::size_t count    = 0;                                              // assume the word contains only bad characters ...
    auto        endIndex = word.find_last_not_of( bad_char );              // end with the first non-bad character

    if( endIndex != std::string::npos ) count = endIndex - startIndex + 1; // number of characters to use in results
                                                                           
    auto result = word.substr( startIndex, count );                        // strip the leading and trailing bad characters   
    for( auto & c : result ) c = std::tolower( c, locality );              // convert to lower case 

    return result;              
  }
}    // namespace




///////////////////////// TO-DO //////////////////////////////
  /// Implement WordFrequency � This (default) constructor takes a reference to a standard input stream as a parameter defaulted to
  /// console input (e.g. std::cin).  This function is to 
  ///  i.  read from standard input (std::cin) a single word at a time (delimited by whitespace as defined in standard C++) until
  ///      end of file, and
  /// ii.  increment the number of times this word has appeared in the text if it has been seen before, otherwise add it to the hash
  ///      table and initialize the frequency. 
  /// Constraint: Only the �sanitized� word should be added to the hashtable.  For example, end punctuation (. ? !), opening &
  /// closing parentheses and brackets should be removed, but intra-word punctuation (' -) should remain.

  WordFrequency::WordFrequency( std::istream & iStream)
  {
      
     unsigned int frequency = 1; // How many times the word appears
     std::string input; 
    
     while (iStream >> input ) 
     {
       std::string word = sanitize(input); //Reduce the number of times sanitize is called

       if (data.count(word)) //Return true or false (1 or 0) if the word is found within the table
       {
         data[word] += 1;         
         
       }
       else
       {
         data.insert({ word, frequency});
        
       }
       
     }
    
  }  



/////////////////////// END-TO-DO ////////////////////////////



///////////////////////// TO-DO //////////////////////////////
  /// Implement numberOfWords � This function takes no arguments and returns the number of unique words.

  std::size_t WordFrequency::numberOfWords() const
  {
  
    size_t numUnique = data.size();

    return numUnique;
  }

/////////////////////// END-TO-DO ////////////////////////////



///////////////////////// TO-DO //////////////////////////////
  /// Implement wordCount � This function takes a constant reference to a standard string as a parameter and returns the frequency
  /// of occurrence of the that sanitized word.

  std::size_t WordFrequency::wordCount( const std::string & word ) const
  {
    
    if (data.count(sanitize(word)))
   {
     std::size_t count  = data.find(sanitize(word))->second;
     return count;
   }
    else
    {
      return 0;
    }
    
  }

/////////////////////// END-TO-DO ////////////////////////////



///////////////////////// TO-DO //////////////////////////////
  /// Implement mostFrequentWord � This function takes no arguments and returns the most frequent word.

  std::string WordFrequency::mostFrequentWord() const
  {
    std::string            word;
    int           largestFrequency = 0;
    size_t      maxBuckets = data.bucket_count(); 
   



    for( unsigned buckets = 0 ;  buckets < maxBuckets ; ++ buckets ) //iterates through the buckets 
    {

      
      for (auto  element = data.begin(buckets) ; element != data.end(buckets) ; ++ element) //traverses through the elements within the bucket

      {

       if ( element->second > largestFrequency  )
       {
         largestFrequency = element->second;
         word = element->first;
       }
 
      }
      
    }

    return word;
  }

/////////////////////// END-TO-DO ////////////////////////////




///////////////////////// TO-DO //////////////////////////////
  /// Implement maxBucketSize � This function takes no arguments and returns the size of the largest bucket in the hash table
  ///
  /// Hint: see the unordered_map's bucket interface at https://en.cppreference.com/w/cpp/container/unordered_map

  std::size_t WordFrequency::maxBucketSize() const
  {
    size_t largestBucket = 0;
    unsigned long int maxBuckets = data.bucket_count();

    for( unsigned bucket = 0 ; bucket < maxBuckets ; ++bucket )
    {
      
       if( data.bucket_size(bucket) > largestBucket) //Compares bucket size 
       {
         largestBucket = data.bucket_size(bucket);
       }

    }

    return largestBucket;
   

  }

/////////////////////// END-TO-DO ////////////////////////////
