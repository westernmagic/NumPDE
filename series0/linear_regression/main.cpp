#include <iostream>
#include <Eigen/Dense>


int main(int argc, char **argv){

  // Declare Eigen vector type for doubles
  using vector_t =  Eigen::VectorXd ;
  
  // Initialize Eigen vector containing body weight in Kg(X)
  vector_t X(15);
  X << 2 , 2.2 , 2.4 , 2.2 , 2.6 , 2.2 , 2.4 , 2.4 , 2.5 , 2.7 , 2.6 , 2.2 ,
       2.5 , 2.5 , 2.5 ;

  // Initialize Eigen vector containing heart weight in g (Y)
  vector_t Y(15);
  Y << 6.5 , 7.2 , 7.3 , 7.6 , 7.7 , 7.9 , 7.9 , 7.9 , 7.9 , 8.0 , 8.3, 8.5 ,
       8.6 , 8.8 , 8.8;

  // TODO: Initialize Eigen Matrix A
  Eigen::MatrixXd A(15,2);
// (write your solution here)

  // Create LHS = A'*A
  Eigen::MatrixXd LHS = A.transpose()*A;

  // TODO: Create RHS = A'*Y
// (write your solution here)

  // TODO: Solve system and output coefficients b_0 and b_1
// (write your solution here)

  return 0;
}
