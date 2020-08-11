/**
Frequency vocabulary test case
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
#include <catch2/catch.hpp>
#include <sstream>

#include "Vocabulary.h"

constexpr auto text_in = R"(
The time has come, the Walrus said,
to talk of many things...
)";

constexpr auto text_out =
R"(    2 the
    1 come
    1 has
    1 many
    1 of
    1 said
    1 talk
    1 things
    1 time
    1 to
    1 walrus
)";

TEST_CASE("Vocabulary") {
  auto voc = freq::Vocabulary{};
  auto iss = std::istringstream{text_in};
  iss >> voc;
  auto oss = std::ostringstream{};
  oss << voc;
  REQUIRE(oss.str() == text_out);
}
