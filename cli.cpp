/*
    Copyright 2014 Alessandro Ranellucci, Miro Hrončok
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <sstream>
#include "stlsplit.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " file.stl" << std::endl;
    return 1;
  }
  stl_file stl_in;
  stl_open(&stl_in, argv[1]);
  stl_exit_on_error(&stl_in);
  
  std::vector<stl_file*> parts = stl_split(&stl_in);
  
  unsigned int namecounter = 0;
  
  for (std::vector<stl_file*>::const_iterator part = parts.begin(); part != parts.end(); part++) {
    std::stringstream ss;
    ss << argv[1] << ".part" << ++namecounter << ".stl";
    stl_write_binary(*part, ss.str().c_str(), "stlsplit");
    stl_exit_on_error(*part);
    stl_close(*part);
    delete *part;
  }
  
  stl_close(&stl_in);
}

