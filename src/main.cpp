/**
Frequency vocabulary application
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
#include <fstream>
#include <iostream>
#include <string_view>

#include "Vocabulary.h"

void usage(std::string_view name) {
  std::cout << "Usage: " << name << ": <in_file.txt> <out_file.txt>\n";
}

int main(int argc, char** argv) {
  // Check arguments count
  if (argc != 3) {
    usage(argv[0]);
    std::cout << "Error: wrong argument number: " << argc << '\n';
    exit(1);
  }

  std::ifstream ifs(argv[1]);
  // Check if the file has been opened successfully.
  if (!ifs.is_open()) {
    usage(argv[0]);
    std::cout << "Error: can't open input file: " << argv[1] << '\n';
    exit(2);
  }
  auto voc = freq::Vocabulary{};
  // Read data into Vocabulary
  ifs >> voc;

  std::ofstream ofs(argv[2]);
  // Check if the file has been opened successfully.
  if (!ofs.is_open()) {
    usage(argv[0]);
    std::cout << "Error: can't open output file: " << argv[2] << '\n';
    exit(3);
  }
  // Write data from Vocabulary
  ofs << voc << std::flush;
  return 0;
}
