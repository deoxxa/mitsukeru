#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#include "picojson.h"

#include <mitsukeru/index.h>
#include <mitsukeru/index/storage.h>
#include <mitsukeru/index/storage/memory.h>
#include <mitsukeru/tokeniser.h>

int main(int argc, char** argv)
{
  std::cout << "Starting up..." << std::endl;

  Mitsukeru::Index< std::string, uint32_t >* index = new Mitsukeru::Index< std::string, uint32_t >(new Mitsukeru::Index_Storage_Memory< std::string, uint32_t >);
  Mitsukeru::Tokeniser* tokeniser = new Mitsukeru::Tokeniser;
  std::map< uint32_t, picojson::value > docs;

  std::ifstream fh;
  std::string line;
  picojson::value v;
  std::string err;
  fh.open(argv[1]);
  while (fh.good()) {
    getline(fh, line);

    if (line.size()) {
      picojson::parse< std::string::iterator >(v, line.begin(), line.end(), &err);
      picojson::object& o = v.get< picojson::object >();

      docs[o["id"].get< double >()] = v;

      //std::cout << o["id"].get< double >() << ": " << o["title"].get< std::string >() << std::endl;
      std::vector< std::string >* tokens;

      tokens = tokeniser->tokenise(o["title"].get< std::string >());
      for (std::vector< std::string >::iterator it=tokens->begin();it!=tokens->end();++it) {
        index->add(*it, o["id"].get< double >());
      }
      delete tokens;
    }
  }
  fh.close();

  std::cout << "Ready!" << std::endl;

  std::string query;
  std::cout << "> ";
  while (getline(std::cin, query)) {
    std::vector< uint32_t >* results = index->search(query);
    for (std::vector< uint32_t >::iterator it=results->begin();it!=results->end();++it) {
      std::cout << docs[*it] << std::endl;
    }
    std::cout << "> ";
  }

  delete index;
  delete tokeniser;

  return 0;
}
