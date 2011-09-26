#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdint.h>

#include "picojson.h"

namespace Mitsukeru
{
  struct Index
  {
  protected:
    std::map< std::string, std::vector< uint32_t > > terms;
  public:
    void add(uint32_t, std::string);
    std::vector< uint32_t >* search(std::vector< std::string >);
  };

  class Tokeniser
  {
  public:
    std::vector< std::string >* tokenise(std::string data);
  };
};

void Mitsukeru::Index::add(uint32_t id, const std::string term)
{
  terms[term].push_back(id);
}

std::vector< uint32_t >* Mitsukeru::Index::search(std::vector< std::string > _terms)
{
  std::vector< uint32_t >* result = new std::vector< uint32_t >;

  for (std::vector< std::string >::iterator it_a=_terms.begin();it_a!=_terms.end();++it_a) {
    if (terms.find(*it_a) != terms.end()) {
      for (std::vector< uint32_t >::iterator it_b=terms[*it_a].begin();it_b!=terms[*it_a].end();++it_b) {
        result->push_back(*it_b);
      }
    }
  }

  return result;
}

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
