#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#include <admesh/stl.h>

int main(int argc, char **argv) {
  stl_file stl_in;
  char *filename = (char *)"model.stl";
  stl_open(&stl_in, filename);
  stl_exit_on_error(&stl_in);

  int      fixall_flag = 1;
  int      exact_flag = 0;
  int      tolerance_flag = 0;
  float    tolerance = 0;
  int      increment_flag = 0;
  float    increment = 0;
  int      nearby_flag = 0;
  int      iterations = 2;
  int      remove_unconnected_flag = 0;
  int      fill_holes_flag = 0;
  int      normal_directions_flag = 0;
  int      normal_values_flag = 0;
  int      reverse_all_flag = 0;
  int      verbose_flag = 0;

  stl_repair(&stl_in,
             fixall_flag,
             exact_flag,
             tolerance_flag,
             tolerance,
             increment_flag,
             increment,
             nearby_flag,
             iterations,
             remove_unconnected_flag,
             fill_holes_flag,
             normal_directions_flag,
             normal_values_flag,
             reverse_all_flag,
             verbose_flag);

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

  return 0;
}

