#include <stdlib.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "kfunctions.h"
#include "kfunctions.cpp"
#include <string>

using namespace std;
using std::vector;


int main(){
  // read in the data!
  ifstream data;
  data.open("iris.data");

  if(!data){                       //terminate if error opening file
    cout << "Unable to open file\n";
    exit(1); 
  }


  //arraylist of flowers goes here
  vector<vector<string> > list;  

  int id_num = 1;

  
  
  for ( string line; getline(data, line);){
    vector<string> flower;      
    
    string delimiter = ",";

    // iterate through the line
    size_t pos = 0;
    string token;

    while((pos = line.find(delimiter)) != string::npos){
      token = line.substr(0, pos);
      //add the token to the flower in the list
      flower.push_back(token);
      line.erase(0, pos + delimiter.length());
    }
    // for adding the species name to vector item
    token = line;
    flower.push_back(token);

    string id = to_string(id_num);
    flower.push_back(id);
    id_num++;
    
    list.push_back(flower);
    
  }

  data.close(); 

  
  /* KMEANS ALGORITHM */
  // inspired by pseudocode from:
  // stanford.edu/~cpiech/cs221/handouts/kmeans.html
  // trying to get species clusterong on petal length & petal width

  // initialize centroids randomly
  centroid *cluster1 = get_random_centroid();
  centroid *cluster2 = get_random_centroid();
  centroid *cluster3 = get_random_centroid();
  
  // initialize book-keeping variables
  vector<centroid> old_c1;
  vector<centroid> old_c2;
  vector<centroid> old_c3;
  
  int iterations = 0;

  // running the algorithm
  while(iterations < 20) { //need to figure out how to know when we're done
    // // save old centroids for convergence test
    old_c1.push_back(*cluster1);
    old_c2.push_back(*cluster2);
    old_c3.push_back(*cluster3);
    
    // // assign labels to each datapoint based on centroids
    assign_pts(list, cluster1, cluster2, cluster3);


    //PRINT CLUSTERS OUT (for visualization)
    cout << "Cluster 1: \n";
    print_cluster(cluster1);
    cout << "Cluster 2: \n";
    print_cluster(cluster2);
    cout << "Cluster 3: \n";
    print_cluster(cluster3);
    cout << "Number of iterations: ";
    cout << iterations << "\n";
    
    // // assign centroids based on datapoint labels
    cluster1 = calculate_centroid(cluster1);
    cluster2 = calculate_centroid(cluster2);
    cluster3 = calculate_centroid(cluster3);

    // stop running this loop if the centroids do not continue changing
    if ((compare(cluster1, &(old_c1.back())) == 0) && (compare(cluster2, &(old_c2.back())) == 0) && (compare(cluster3, &(old_c3.back())))){
	break;
    }
    iterations++;
  }
}
