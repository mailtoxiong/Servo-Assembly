#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/imgproc/types_c.h>
#include<vector>
#include<math.h>
#include<sys/timeb.h>
using namespace std;
using namespace cv;

int main()
{
	struct timeb startTime , endTime;
	
	Mat im = imread("E:\\samples_0422\\yt01\\yt_0422_01.bmp",0);
	int col=1000, row=1760, width=1560, height=90; //����ʱ�޸�
	Mat ROI = im(Rect(col,row,width,height));//(1760,1000),(1850,2560)
	Mat smallROI;
	pyrDown(ROI, smallROI, Size(ROI.cols / 2 , ROI.rows / 2));
    ftime(&startTime);

	//��ֵ�ͷָ�
	int gridy=5, thrx=45;	
	int nsizey =(int)(height/2/gridy); 
	//��������λ������
	int nmax=0;
	int ypos=0;
	vector<int> nlist;//nlistΪimgraytiny��X�ļ���

	for(int i = 0;i < nsizey; i++)//�ԵȲ���ȡ��ÿһ��
	{
		int y = i * gridy;

		vector<int> intersec;//intersecΪÿһ�н��㼯��
		bool bfirst=false;
		int nfirst=0;
		int nsecond=0;
		for(int x=1;x<width/2 ;x++)//�����������ÿһ��
		{
			int tmpgray = smallROI.at<uchar>(y,x);
			int bfrgray = smallROI.at<uchar>(y,x-1);
			if(tmpgray<thrx && bfrgray>=thrx)//����
			{
				if(!bfirst)
				{
					bfirst = true;
					nfirst = x;
				}
			}
			if(tmpgray>=thrx && bfrgray<thrx)//�뿪
			{
				if(bfirst)
				{
					bfirst = false;
					nsecond = x;
					if(nsecond-nfirst>=15 && nsecond-nfirst<40)
					{
						intersec.push_back(nfirst);
						intersec.push_back(nsecond);
					}
				}
			}
			
		}
		
		int n = intersec.size();
		if(nmax < n)   //����ʱ�޸�
		{
			nmax = n;
			ypos = y;
			nlist = intersec;
		}
		
	}
	ftime(&endTime);
	
	//�Ŵ���ROI����
	ypos *= 2;
	int n = nlist.size();
	for(int i =0;i<n;i++)
	{
		nlist[i] *= 2;
	}

	int yup = 5 , ydown = height-5;
	int maxmeanheight = 10000;		//��߳ݵ�ƽ���߶�
	int locx1=0,locx2=0;
	int gearnum=(int)(n/2);
	
	int gridx = 3,thry=120;
	for(int i=0;i<gearnum;i++)  
	{	
		int x1 = nlist[2*i],x2 = nlist[2*i+1];
		int nsizex = (int)((x2-x1)/gridx);
		vector<int> midlist;	//���һ�����ڵ�����midpos
		
		for(int j=0;j<nsizex+1;j++)	
		{
			int x = x1 + j*gridx;
			int midpos = 0;
			bool bmidfind = false;
			for(int y=yup;y<ydown;y++)
			{
				int tmpgray = ROI.at<uchar>(y,x);
				int bfrgray = ROI.at<uchar>(y-1,x);
				if(tmpgray<=thry && bfrgray>thry)
				{
					if(!bmidfind)	
					{	
						midpos = y;
						bmidfind = true;
					}
				}
			}
			midlist.push_back(midpos);
		}
		
		//��ƽ���߶�		
		int meanheight = 0;
		int midsize = midlist.size();
		int compareindex = 0;
		for(int i =0;i<midsize;i++)
		{
			int tempmid = midlist[i];
			int index = 0;
		    for(int i =0;i<midsize;i++)
			{
				if((tempmid - midlist[i])<3)  index++;
			}
			if(index>compareindex)
			{
				compareindex = index;
				meanheight = midlist[i];
			}
		}
		
		//��߳�λ����Ϣ
		if(meanheight < maxmeanheight)
		{
			maxmeanheight = meanheight;
			locx1=x1;
			locx2=x2;
		}
	}
	
	int x = (locx1+locx2)/2;
	int y = maxmeanheight;

	int PointX = x+col;
	int PointY = y+row;
	//line(im,Point(PointX-50,PointY),Point(PointX+50,PointY),Scalar(0,0,255),1,8);

	//imwrite("2307.bmp",im);
	cout << "��ʱ"<< (endTime.time-startTime.time)*1000 + (endTime.millitm - startTime.millitm) << "ms"<< endl;
	system("pause");
	return 0;
}