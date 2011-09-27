#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#include "picojson.h"

#include <mitsukeru/index.h>
#include <mitsukeru/tokeniser.h>

int main(int argc, char** argv)
{
  std::cout << "Starting up..." << std::endl;

  Mitsukeru::Index* index = new Mitsukeru::Index;
  Mitsukeru::Tokeniser* tokeniser = new Mitsukeru::Tokeniser;
  std::map< uint32_t, picojson::value > docs;

  std::ifstream fh;
  std::string line;
  picojson::value v;
  std::string err;
  fh.open("data.json");
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
        index->add(o["id"].get< double >(), *it);
      }
      delete tokens;

      if ((o.find("comment") != o.end()) && o["comment"].is<std::string>()) {
        tokens = tokeniser->tokenise(o["comment"].get< std::string >());
        for (std::vector< std::string >::iterator it=tokens->begin();it!=tokens->end();++it) {
          index->add(o["id"].get< double >(), *it);
        }
        delete tokens;
      }
    }
  }
  fh.close();

  std::cout << "Ready!" << std::endl;

  std::string query;
  std::cout << "> ";
  while (getline(std::cin, query)) {
    std::vector< std::string >* terms = tokeniser->tokenise(query);
    std::vector< uint32_t >* results = index->search(*terms);
    for (std::vector< uint32_t >::iterator it=results->begin();it!=results->end();++it) {
      std::cout << docs[*it] << std::endl;
    }
    std::cout << "> ";
  }

  delete index;
  delete tokeniser;

  return 0;
}
