/**
 * Author: Unknwon
 * Date: 2024-05-22
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * Input should be a vector of (dest, global edge index), where
 * for undirected graphs, forward/backward edges have the same index.
 * Returns a list of nodes in the Eulerian path/cycle with src at both start and
 * end, or empty list if no cycle/path exists. To get edge indices back, add
 * .second to s and ret. Time: O(V + E) Status: stress-tested
 */
#pragma once

using ei = array<int, 3>;    // edge info: [edge id, from, to]
vector<pair<int, ei>> stack; // node, edge info
stack.pb({0, ei{-1, -1, 0}});
vector<ei> path;
vector<bool> v_edge(m);

while (!stack.empty()) {
  auto [g, edge_info] = stack.back();
  int f = 0;
  auto [edge_id, x, y] = edge_info;
  while (!e[g].empty()) {
    // edges are pairs [to, edge_index]
    auto [u, i] = e[g].back();
    e[g].pop_back();
    if (!v_edge[i]) {
      stack.push_back({u, ei{(int)i, g, (int)u}});
      v_edge[i] = 1;
      f = 1;
      break;
    }
  }
  if (!f) {
    stack.pop_back();
    if (edge_id != -1) // comment this out to get edges
      path.push_back(edge_info);
  }
}
reverse(path.begin(), path.end());