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
#include <set>
#include <queue>
#include <deque>
#include <sstream>
#include <admesh/stl.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " file.stl" << std::endl;
    return 1;
  }
  stl_file stl_in;
  stl_open(&stl_in, argv[1]);
  stl_exit_on_error(&stl_in);
  stl_repair(&stl_in, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0); // Default repair

  std::set<int> seen_facets;
  
  // loop while we have remaining facets
  for (unsigned int namecounter = 1; ; namecounter++) {
    // get the first facet
    std::queue<int> facet_queue;
    std::deque<int> facets;
    for (int facet_idx = 0; facet_idx < stl_in.stats.number_of_facets; facet_idx++) {
      if (seen_facets.find(facet_idx) == seen_facets.end()) {
        // if facet was not seen put it into queue and start searching
        facet_queue.push(facet_idx);
        break;
      }
    }
    if (facet_queue.empty()) {
      stl_close(&stl_in);
      return 0;
    }
    
    while (!facet_queue.empty()) {
      int facet_idx = facet_queue.front();
      facet_queue.pop();
      if (seen_facets.find(facet_idx) != seen_facets.end()) continue;
      facets.push_back(facet_idx);
      for (int j = 0; j <= 2; j++) {
        facet_queue.push(stl_in.neighbors_start[facet_idx].neighbor[j]);
      }
      seen_facets.insert(facet_idx);
    }
    
    stl_file stl_out;
    stl_out.stats.type = inmemory;
    stl_out.stats.number_of_facets = facets.size();
    stl_out.stats.original_num_facets = stl_out.stats.number_of_facets;
    stl_out.v_indices = NULL;
    stl_out.v_shared = NULL;
    stl_out.neighbors_start = NULL;
    stl_clear_error(&stl_out);
    stl_allocate(&stl_out);
    
    int first = 1;
    for (std::deque<int>::const_iterator facet = facets.begin(); facet != facets.end(); facet++) {
      stl_out.facet_start[facet - facets.begin()] = stl_in.facet_start[*facet];
      stl_facet_stats(&stl_out, stl_in.facet_start[*facet], first);
      first = 0;
    }
    
    std::stringstream ss;
    ss << argv[1] << ".part" << namecounter << ".stl";
    stl_write_binary(&stl_out, ss.str().c_str(), "stlsplit");
    stl_exit_on_error(&stl_out);
    stl_close(&stl_out);
  }
}

