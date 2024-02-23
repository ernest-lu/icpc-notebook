/**
 * Author:
 * Date: 
 * License: 
 * Source: cp-algorithms
 * Description: Minkowski sum of two convex polygons
    * Assumes the polygons are sorted ccw
 * Time Complexity: O(|P| + |Q|)
 * Status: 
 */
#include <vector>
#include "Point.h" 

template <typename P>
void reorder_polygon(std::vector<P>& poly) {
    int pos = 0;
    for (int i = 1; i < poly.size(); i++) {
        if (poly[i].y < poly[pos].y || (poly[i].y == poly[pos].y && poly[i].x < poly[pos].x)) 
            pos = i;
    }
    rotate(poly.begin(), poly.begin() + pos, poly.end());
}

template <typename P>
std::vector<P> minkowski(std::vector<P> poly1, std::vector<P> poly2) {
    reorder_polygon(poly1), reorder_polygon(poly2);
    poly1.push_back(poly1[0]);
    poly1.push_back(poly1[1]);
    poly2.push_back(poly2[0]);
    poly2.push_back(poly2[1]);
    std::vector<P> result;
    int i = 0, j = 0;
    while (i < poly1.size() - 2 || j < poly2.size() - 2) {
        result.push_back(poly1[i] + poly2[j]);
        auto cr = (poly1[i + 1] - poly1[i]).cross(poly2[j + 1] - poly2[j]);
        if (cr >= 0 && i < poly1.size() - 2) i++;
        if (cr <= 0 && j < poly2.size() - 2) j++;
    }
    return result;
}