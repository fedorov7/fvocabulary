/**
Frequency vocabulary implementation
Copyright © 2020 Alexander Fedorov

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
#include "Vocabulary.h"

#include <iostream>
#include <iterator>
#include <utility>

namespace freq {

auto is_alpha = [](unsigned char c) { return std::isalpha(c); };
auto is_not_alpha = [](unsigned char c) { return std::isalpha(c); };
auto to_lower = [](unsigned char c) { return std::tolower(c); };

void Vocabulary::Parse(std::string_view text) {
  for (const auto* it = text.begin(); it != text.end(); ++it) {
    // find start of word
    const auto* s = std::find_if(it, text.end(), is_alpha);
    if (s == text.end()) {
      break;
    }
    // find end of word
    const auto* e = std::find_if_not(s, text.end(), is_not_alpha);

    // transform found word to lower register and save
    auto word = std::string{s, e};
    std::transform(word.begin(), word.end(), word.begin(), to_lower);
    InsertWord(std::move(word));
    if (e == text.end()) {
      break;
    }
    // adjust iterator to end of word
    it = e;
  }
}

void Vocabulary::InsertWord(std::string word) {
  auto number = 1;
  for (auto& [freq, set_of_words] : map_) {
    // try to find word in map
    auto it = set_of_words.find(word);
    if (it != set_of_words.end()) {
      // delete word from old set
      set_of_words.erase(it);
      // increase word frequency
      number = freq + 1;
    }
  }
  // try to find set for requirement frequency
  auto existing_set = map_.find(number);
  if (existing_set != map_.end()) {
    // insert word in existing set
    existing_set->second.insert(std::move(word));
  } else {
    // create new set with word
    map_.insert(std::make_pair(number, std::set<std::string>{std::move(word)}));
  }
}

std::istream& operator>>(std::istream& is, Vocabulary& voc) {
  for (std::string str; std::getline(is, str);) {
    voc.Parse(str);
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const Vocabulary& voc) {
  for (auto& [freq, set_of_words] : voc.map()) {
    for (const auto& word : set_of_words) {
      os << "    " << freq << ' ' << word << '\n';
    }
  }
  return os;
}

}  // namespace freq
