#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <vector>
#include <tuple>
#include <limits>
#include <cmath>

//g++ -O2 -Wall -shared -std=c++20 -fPIC `python3.12 -m pybind11 --includes` hierarchical_clustering.cpp -o hierarchical_clustering`python3.12-config --extension-suffix`
//g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3.12 -m pybind11 --includes) hierarchical_clustering.cpp -o hierarchical_clustering$(python3.12-config --extension-suffix)

namespace py = pybind11;

using Cluster = std::vector<int>;
using DistanceMatrix = std::vector<std::vector<double>>;

// Compute Euclidean distance between two points
inline double euclidean_distance(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return std::sqrt(sum);
}

// Initialize distance matrix
DistanceMatrix compute_distance_matrix(const std::vector<std::vector<double>>& data) {
    size_t n = data.size();
    DistanceMatrix dist_matrix(n, std::vector<double>(n, 0.0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            dist_matrix[i][j] = dist_matrix[j][i] = euclidean_distance(data[i], data[j]);
        }
    }
    return dist_matrix;
}

// Hierarchical clustering using single linkage
std::vector<std::tuple<int, int, double, int>> hierarchical_clustering(const std::vector<std::vector<double>>& data) {
    size_t n = data.size();
    DistanceMatrix dist_matrix = compute_distance_matrix(data);
    std::vector<Cluster> clusters(n);
    std::vector<int> cluster_sizes(n, 1);
    for (size_t i = 0; i < n; ++i) clusters[i] = {static_cast<int>(i)};
    
    std::vector<std::tuple<int, int, double, int>> result;
    int next_cluster_index = n;
    
    for (size_t step = 0; step < n - 1; ++step) {
        int c1 = -1, c2 = -1;
        double min_dist = std::numeric_limits<double>::max();
        
        for (size_t i = 0; i < clusters.size(); ++i) {
            for (size_t j = i + 1; j < clusters.size(); ++j) {
                for (int p1 : clusters[i]) {
                    for (int p2 : clusters[j]) {
                        if (dist_matrix[p1][p2] < min_dist) {
                            min_dist = dist_matrix[p1][p2];
                            c1 = i;
                            c2 = j;
                        }
                    }
                }
            }
        }
        
        int new_cluster_size = cluster_sizes[c1] + cluster_sizes[c2];
        result.push_back({clusters[c1][0], clusters[c2][0], min_dist, new_cluster_size});
        
        clusters[c1].insert(clusters[c1].end(), clusters[c2].begin(), clusters[c2].end());
        clusters.erase(clusters.begin() + c2);
        cluster_sizes[c1] = new_cluster_size;
        cluster_sizes.erase(cluster_sizes.begin() + c2);
        
        next_cluster_index++;
    }
    return result;
}

PYBIND11_MODULE(hierarchical_clustering, m) {
    m.def("hierarchical_clustering", &hierarchical_clustering, "Perform hierarchical clustering using single linkage");
}
