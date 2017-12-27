//����ͼƬ��������ʾ  
#include <vector>
#include <pcl\io\pcd_io.h>  
#include <pcl\io\ply_io.h>
#include <pcl\point_types.h>  
#include <pcl\visualization\cloud_viewer.h>   
#include <opencv2\core\core.hpp>  
#include <opencv2\contrib\contrib.hpp>
#include <opencv2\highgui\highgui.hpp>  
#include <opencv2\imgproc\imgproc.hpp>  


using namespace std;
using namespace pcl;

int main()
{
	string dir_path = "F:\\AppData\\vs2015\\PCL\\NumberCloud\\NumberCloud\\number_Image\\";
	cv::Directory dir;
	vector<string> number_path = dir.GetListFiles(dir_path, "*.png", true);

	// ѭ������ͼ��
	for(int k =6;k<number_path.size();k++)
	{
		cv::Mat srcImage = cv::imread(number_path.at(k));
		cv::Mat grayImage;
		cv::cvtColor(srcImage, grayImage, CV_BGR2GRAY);
		cv::Mat Binary_Image;
		cv::threshold(grayImage, Binary_Image, 50, 255, cv::THRESH_BINARY_INV);
		// opencv �е� sum �����ǶԸ��������ֱ������Ͳ���
		cv::Scalar s = cv::sum(Binary_Image);
		// ��0ͨ���õ��ĺͳ��� 255 �Ľ��Ҳ����������ĵ�
		unsigned int image_point_size = s[0] / 255;

		// �ٶ�ͼ����б���������Ǻ�ɫ���򣬱�����������
		// Ȼ���ڷ��� PCL ����Ӧ���ƽ��и�ֵ������Ĳ���

		pcl::PointCloud<pcl::PointXYZ>::Ptr number_PC(new pcl::PointCloud<pcl::PointXYZ>);

		// Fill in the cloud data  
		// height = 1 ��ʾ�����������
		number_PC->width = image_point_size * 15;
		number_PC->height = 1;
		number_PC->points.resize(number_PC->width * number_PC->height);
		for (size_t i = 0; i < number_PC->points.size();)
		{
			for (size_t m = 0; m < 15; m++)		// m�������� z ���������
			{
				// �ڲ����ͼ���������أ�������� 0 ��������д洢
				for (int a = 0; a < Binary_Image.rows; a = a++)
				{
					for (int b = 0; b < Binary_Image.cols; b = b++)
					{
						cout << "���ڽ��е� "<<k+1<<" ��ͼ��ĵ� " << m+1 << " �㣬" << a << " �� " << b << " �У�" ;
						cout << "�ܽ���������� " << k+1 << "/10 "<< endl;
						if (Binary_Image.at<uchar>(a, b) != 0)
						{
							number_PC->points[i].x = b;
							number_PC->points[i].y = a;
							number_PC->points[i].z = m;
							i++;
						}
						else
							continue;
					}
				}



			}
		}

		// ��ʾ����
		/*boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("PCL"));
		viewer->setBackgroundColor(255, 255, 255);
		pcl::visualization::PointCloudGeometryHandlerXYZ<pcl::PointXYZ>color(number_PC);
		viewer->addPointCloud<pcl::PointXYZ>(number_PC, color, "src_ruler");*/
		string save_pathh = "F:\\AppData\\vs2015\\PCL\\NumberCloud\\NumberCloud\\number_PointCloud\\";
		pcl::io::savePLYFileASCII(save_pathh + to_string(k) + ".ply", *number_PC); //�����Ʊ��浽PCD�ļ���







		//int a = 0;
	}




	cv::waitKey();
	return 0;
}