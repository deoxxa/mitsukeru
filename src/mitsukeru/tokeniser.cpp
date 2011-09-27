#include <string>
#include <vector>
#include <cstring> // for size_t

#include <mitsukeru/tokeniser.h>

std::vector< std::string >* Mitsukeru::Tokeniser::tokenise(std::string data)
{
  std::vector< std::string >* result = new std::vector< std::string >;

  size_t len = 0;
  for (size_t i=0;i<=data.size();++i) {
    if (((data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' && data[i] <= 'Z') || (data[i] >= '0' && data[i] <= '9')) && (i < data.size())) {
      len++;
    } else {
      if (len > 0) {
        result->push_back(std::string(data.substr(i-len, len)));
      }

      len = 0;
    }
  }

  return result;
}
