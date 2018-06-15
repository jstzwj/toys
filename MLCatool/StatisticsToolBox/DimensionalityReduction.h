#pragma once

#include"dense"

#include"DescriptiveStatistics.h"

namespace catool
{
	namespace statistics_toolbox
	{
		Eigen::MatrixXcd princomp(Eigen::MatrixXd a)
		{
			Eigen::MatrixXd c(a.rows(), a.cols());

			c = main_toolbox::cov(a);

			Eigen::EigenSolver<Eigen::MatrixXd> eigenSolver(c);
			if (eigenSolver.info() != Eigen::Success) {
				std::cout << "eig fail." << std::endl;
			}

			// std::cout << eigenSolver.eigenvalues() << std::endl << std::endl;
			// 
			// std::cout << eigenSolver.eigenvectors() << std::endl;

			Eigen::MatrixXd eigRst = eigenSolver.eigenvectors().real();

			catool::main_toolbox::sort(eigRst, 1);

			// std::cout << eigRst;

			return eigRst;
		}
	}
}
