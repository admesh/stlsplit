#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#include <sstream>
#include <admesh/stl.h>

int main(int argc, char **argv) {
  stl_file stl_in;
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " file.stl" << std::endl;
    return 1;
  }
  stl_open(&stl_in, argv[1]);
  stl_exit_on_error(&stl_in);
  stl_repair(&stl_in, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0); // Default repair

  std::vector<stl_file*> meshes;
  std::set<int> seen_facets;
  
  // loop while we have remaining facets
  while (1) {
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
    if (facet_queue.empty()) break;
    
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
    
    stl_file* mesh = new stl_file;
    meshes.push_back(mesh);
    mesh->stats.type = inmemory;
    mesh->stats.number_of_facets = facets.size();
    mesh->stats.original_num_facets = mesh->stats.number_of_facets;
    stl_clear_error(mesh);
    stl_allocate(mesh);
    
    int first = 1;
    for (std::deque<int>::const_iterator facet = facets.begin(); facet != facets.end(); facet++) {
      mesh->facet_start[facet - facets.begin()] = stl_in.facet_start[*facet];
      stl_facet_stats(mesh, stl_in.facet_start[*facet], first);
      first = 0;
    }
  }
  
  unsigned int namecounter = 0;
  
  for (stl_file* m : meshes) {
    namecounter++;
    std::stringstream ss;
    ss << argv[1] << ".part" << namecounter << ".stl";
    stl_write_binary(m, ss.str().c_str(), "stlsplit");
    stl_exit_on_error(m);
  }

  return 0;
}

