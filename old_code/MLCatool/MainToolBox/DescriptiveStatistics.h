#pragma once
#include"dense"
namespace catool
{
	namespace main_toolbox
	{
		Eigen::MatrixXd cov(Eigen::MatrixXd a)
		{
			Eigen::MatrixXd c(a.rows(), a.cols());
			for (int i = 0; i < a.cols(); ++i)
			{
				c.col(i).fill(a.col(i).mean());
			}

			c = a - c;

			return c.transpose()*c / (a.rows() - 1);
		}

	}
}