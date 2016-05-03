#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "Primitives.h"

#include <omp.h>

#include "plydatareader.h"

void main() {

  PlyDataReader::getSingletonPtr()->readDataInfo("big_porsche.ply", nullptr, 0);
  unsigned int nVertices = PlyDataReader::getSingletonPtr()->getNumVertices();
  unsigned int nFaces = PlyDataReader::getSingletonPtr()->getNumFaces();

  std::vector<float> vertices(3*nVertices+1);
  std::vector<int>       indices(nFaces * 3);

  PlyDataReader::getSingletonPtr()->readData((float*)vertices.data(), indices.data());

  //for(int i = 0; i < )
  const glm::vec3 ray_origin(0, 0, -2);
  const glm::vec3 ray_dir(0.57735026918962576450914878050196, -0.57735026918962576450914878050196, 00.57735026918962576450914878050196);

  bool intersect = false;

#pragma omp parallel
  {
    if(omp_get_thread_num() == 1) std::cout << "Number of threads = " << omp_get_num_threads() << std::endl;
#pragma omp for
    for(int i = 0; i < nFaces; i++){
      float t = 0;
      const glm::vec3 p0(vertices[3 * indices[3*i+0] + 0], vertices[3 * indices[3*i+0] + 1], vertices[3 * indices[3*i+0] + 2]);
      const glm::vec3 p1(vertices[3 * indices[3*i+1] + 0], vertices[3 * indices[3*i+1] + 1], vertices[3 * indices[3*i+1] + 2]);
      const glm::vec3 p2(vertices[3 * indices[3*i+2] + 0], vertices[3 * indices[3*i+2] + 1], vertices[3 * indices[3*i+2] + 2]);
      if(rayTriangleIntersection(ray_origin, ray_dir, p0, p1, p2, t)){
        glm::vec3 intersect_point = ray_origin + t * ray_dir;
        std::cout << "interstest at distance " << t << " with triangle " << i << " at " << intersect_point.x << " " << intersect_point.y << " " << intersect_point.z << ".\n" ;
        intersect = true;
      }
    }
  }

  if(!intersect)
    std::cout << "no intersect!\n";

}
