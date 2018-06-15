#pragma once
#include<algorithm>
#include<dense>
namespace catool
{
	namespace main_toolbox
	{
		template<class T,int Row,int Col>
		void sort(Eigen::Matrix<T, Row, Col>& m, int dim = 0)
		{
			if (dim == 0)
			{
				sortCol(m);
			}
			else
			{
				sortRow(m);
			}
		}

		template<class T, int Row, int Col>
		void sortCol(Eigen::Matrix<T, Row, Col>& m)
		{
			for (int i=0;i<m.cols();++i)
			{
				Eigen::Matrix<T, Row, Col> col = m.col(i);
				std::sort(col.data(),col.data()+col.size());
				m.col(i) = col;
			}
		}

		template<class T, int Row, int Col>
		void sortRow(Eigen::Matrix<T, Row, Col>& m)
		{
			for (int i = 0; i<m.rows(); ++i)
			{
				Eigen::Matrix<T, Row, Col> row = m.row(i);
				std::sort(row.data(), row.data() + row.size());
				m.row(i) = row;
			}
		}
	}
}