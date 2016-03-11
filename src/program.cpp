#include "program.h"

#include <sstream>
#include <fstream>

#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

namespace gb {

Program::Program(const string& rom_filename, const string& bootrom_filename) {
  if (!fs::exists(rom_filename) || !fs::is_regular_file(rom_filename)) {
    return;
  }

  {
    ifstream rom_stream(rom_filename, ios::binary);
    rom_.assign(istreambuf_iterator<char>(rom_stream),
                istreambuf_iterator<char>());
  }

  if (fs::exists(bootrom_filename) && fs::is_regular_file(bootrom_filename)) {
    ifstream bootrom_stream(bootrom_filename, ios::binary);
    bootrom_.assign(istreambuf_iterator<char>(bootrom_stream),
                    istreambuf_iterator<char>());
  }
}

Program::~Program() {}
}
