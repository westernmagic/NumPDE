#pragma once
#include <Eigen/Core>
#include <functional>


//! Approximates the integral
//! 
//! \f[\int_K f(x, y) \; dV\f]
//!
//! where K is the triangle spanned by (0,0), (1,0) and (0, 1).
inline double integrate2d(const std::function<double(double, double)>& f)
{
    Eigen::VectorXd weights(7);
    weights << 9. / 80.,
        (155 + sqrt(15)) / 2400,
        (155 + sqrt(15)) / 2400,
        (155 + sqrt(15)) / 2400,
        (155 - sqrt(15)) / 2400,
        (155 - sqrt(15)) / 2400,
        (155 - sqrt(15)) / 2400;


    Eigen::Matrix<double, Eigen::Dynamic, 2, Eigen::RowMajor> points(7, 2);
    points << 1.0 / 3., 1. / 3., 
        (6 + sqrt(15)) / 21.,  (6 + sqrt(15)) / 21.,
        (9 - 2 * sqrt(15)) / 21,   (6 + sqrt(15)) / 21,
        (6 + sqrt(15)) / 21,  (9 - 2 * sqrt(15)) / 21,
        (6 - sqrt(15)) / 21, (9 + 2 * sqrt(15)) / 21,
        (9 + 2 * sqrt(15)) / 21,   (6 - sqrt(15)) / 21,
        (6 - sqrt(15)) / 21,  (6 - sqrt(15)) / 21;
    
    double integral = 0.0;
    for (int i = 0; i < points.rows(); ++i) {
        integral += weights(i) * f(points(i, 0), points(i, 1));
    }

    return integral;
}


//! Approximates the integral
//! 
//! \f[\int_{-1}^1 f(x) \; dx\f]
//!
//! through Gauss-Legendre polynomials.

inline double integrate1d(const std::function<double(double)>& f) {
    Eigen::VectorXd points(5);
    points << 0,
        -1.0 / 3.0*std::sqrt(5 - 2 * std::sqrt(10 / 7)),
         1.0 / 3.0*std::sqrt(5 - 2 * std::sqrt(10 / 7)),
        -1.0 / 3.0*std::sqrt(5 + 2 * std::sqrt(10 / 7)),
         1.0 / 3.0*std::sqrt(5 + 2 * std::sqrt(10 / 7));

    Eigen::VectorXd weights(5);
    weights << 128. / 225.,
        (322 + 13 * std::sqrt(70)) / 900,
        (322 + 13 * std::sqrt(70)) / 900,
        (322 - 13 * std::sqrt(70)) / 900,
        (322 - 13 * std::sqrt(70)) / 900;

    double integral = 0.0;
    for (int i = 0; i < points.rows(); ++i) {
        integral += weights[i] * f(points(i));
    }

    return integral;
}
