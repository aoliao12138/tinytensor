
#ifndef TINYTENSOR_TENSOR_HPP
#define TINYTENSOR_TENSOR_HPP

#include <vector>
using namespace std;

/** @brief Tensor is a basic computation data structure in the neural network.
 */
class Tensor {
public:
    /**
   * @brief Constructor.
   * @param x the dimension of x
   * @param y the dimension of y
   * @param z the dimension of z
   */
    Tensor(int x = 1, int y = 1, int z = 1);
    /**
   * @brief Constructor initialized with all the same number.
   * @param x the dimension of x
   * @param y the dimension of y
   * @param z the dimension of z
   * @param num all numbers in the tensor are initialized with num
   */
    Tensor(int x, int y, int z, double num);
    /**
     *
     * @return the dimension of x
     */
    int get_nx();
    /**
     *
     * @return the dimension of y
     */
    int get_ny();
    /**
     *
     * @return the dimension of z
     */
    int get_nz();
    /**
     * @brief set the data(kernel) of the tensor.
     * @param my_kernel the data of the tensor
     */
    void set_kernel(vector<vector<vector<double> > > &my_kernel);
    /**
     * @brief find the maximal number in the tensor
     * @return the index of the maximal number in the tensor
     */
    int max_tensor_index(); //return the max element in the tensor

    /**
     * data in the tensor
     */
    vector<vector<vector<double> > > _kernel;
private:
    /**
     * the dimension of x
     */
    int _nx;
    /**
     * the dimension of y
     */
    int _ny;
    /**
     * the dimension of z
     */
    int _nz;
};




#endif //TINYTENSOR_TENSOR_HPP
