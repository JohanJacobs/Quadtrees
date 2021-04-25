# QuadTrees
 Implementations of Quadtree algorithm

# Point Region Quadtree :
 Quadtree that stores points within a specific region. For this quad tree a maximum value of points is required. The region gets split as soon as that many points are inside the region. Sub regions are created by deviding the current region into 4 equal sized areas. 
 
 In this data structure more memory is used, for the data structure, in exchange for faster lookup times when querying the data. Queries usually represent an area and the quad tree returns all the points within that area.
