#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat bin_image;

/****************************************Ѱ����������****************************************/
#define ROW 108
#define COL 192
#define WHITE 255
#define BLACK 0
#define MidLine 107
#define effective_left 15
#define effective_right COL-16

int   MiddleLine[ROW];
int   RightEdge[ROW];
int   LeftEdge[ROW];
int   Width[ROW];//��̬·��

int   MidPri = MidLine;
int   LeftLose = 0;
int   RightLose = 0;
int   AllLose = 0;
int   signalFlag_row = 0;
int   signalFlag_frame = 0;

//ȫ��ɨ��ͱ�Ե�����ȡ����������
//ǰʮ��ȫ��ɨ��
//ʣ�µ��У�������һ�е�Ѱ�������������ǰ�е�Ѱ�߷�ʽ�����
int findTrack()
{
	int16_t i = 0;
	int16_t j = 0;
	uint8_t jj = 0;

	LeftLose = 0;//��������
	RightLose = 0;
	AllLose = 0;
	for (i = 0; i < ROW; i++)//����ֵ
	{
		RightEdge[i] = COL - 1;
		LeftEdge[i] = 0;
		MiddleLine[i] = MidLine;
		Width[i] = 77+0.2447*i;     //��̬·��
	}

	for (i = ROW - 1; i >= ROW - 10; i--) //������ǰʮ�У�ȫ��ɨ��
	{
		signalFlag_row = 0;
		if (i == ROW - 1)//���о���ͼ��������Ϊɨ�����
		{
			j = MidPri;
		}
		else
		{
			j = MiddleLine[i + 1];//���������һ���е��λ����Ϊ����ɨ�����
		}
		if (j <= effective_left)
		{
			j = effective_left;
		}
		while (j >= effective_left)//j>=effective_left��Ч��Χ�ڽ�����Ѱ
		{
			if (bin_image.at<uchar>(i, j) == WHITE && bin_image.at<uchar>(i, j - 1) == BLACK && bin_image.at<uchar>(i, j - 2) == BLACK)//���������ҵ��׺ں�����
			{
				LeftEdge[i] = j;//�ҵ���ֵ �Ҳ�������ԭֵ0
				break;//��������Ѱ��
			}
			j--;//���������ƶ�
		}
		if (i == ROW - 1) //�����ұ߽�
		{
			j = MidPri;//������У���ͼ�����Ŀ�ʼ��Ѱ
		}
		else
		{
			j = MiddleLine[i + 1];//�������һ������λ�ÿ�ʼ��Ѱ
		}
		if (j >= effective_right)//��Ч��Χ����Ѱ����
		{
			j = effective_right;
		}
		while (j <= effective_right)
		{
			if (bin_image.at<uchar>(i, j) == WHITE && bin_image.at<uchar>(i, j + 1) == BLACK && bin_image.at<uchar>(i, j + 2) == BLACK)//���������ҵ��װ׺������
			{
				RightEdge[i] = j;//�ҵ���ֵ   �Ҳ�������ԭֵ
				break;//��������Ѱ��
			}
			j++;//���������ƶ�
		}
		if (LeftEdge[i] > 60) {
			LeftEdge[i] = 0;//��־��Ӱ��߽磬ֱ���ж�Ϊ����
			signalFlag_row = 1;
			signalFlag_frame = 1;
		}
		if (RightEdge[i] < 145) {
			RightEdge[i] = COL - 1;
			signalFlag_row = 1;
			signalFlag_frame = 1;
		}
		if (LeftEdge[i] >= effective_left && RightEdge[i] <= effective_right)//�����жϣ�û�ж���
		{
			MiddleLine[i] = (LeftEdge[i] + RightEdge[i]) / 2;
		}
		else if (LeftEdge[i] >= effective_left && RightEdge[i] > effective_right)//��������,û�ж�����
		{
			if (!signalFlag_row)
			{
				RightLose++;
			}
			//������е�
			if (i != ROW - 1 && ((RightEdge[i] - LeftEdge[i]) >= (RightEdge[i + 1] - LeftEdge[i + 1] + 5)))//ͻ��
			{
				MiddleLine[i] = MiddleLine[i + 1];
			}
			else
			{
				MiddleLine[i] = LeftEdge[i] + Width[i] / 2;//�����Ļ����ð��
			}
		}
		else if (LeftEdge[i] < effective_left && RightEdge[i] <= effective_right)//��������
		{
			if (!signalFlag_row)
			{
				LeftLose++;
			}
			if (i != ROW - 1 && (RightEdge[i] - LeftEdge[i]) >= (RightEdge[i + 1] - LeftEdge[i + 1] + 5))//ͻ��
			{
				MiddleLine[i] = MiddleLine[i + 1];
			}
			else
			{
				MiddleLine[i] = RightEdge[i] - Width[i] / 2;//�߿�
			}
		}
		else if (LeftEdge[i]<effective_left && RightEdge[i]>effective_right)//���߶����˵Ļ�
		{
			if (!signalFlag_row)
			{
				AllLose++;
			}
			if (i == ROW - 1)//��������о���ͼ��������Ϊ�е�
			{
				MiddleLine[i] = MidPri;
			}
			else
			{
				MiddleLine[i] = MiddleLine[i + 1];//����������о�����һ�е�������Ϊ�����е�
			}
		}

		if (MiddleLine[ROW - 1] >= effective_right)
		{
			MidPri = effective_right;
		}
		else if (MiddleLine[ROW - 1] <= effective_left)
		{
			MidPri = effective_left;
		}
		else
		{
			MidPri = MiddleLine[ROW - 1];//��¼��֡ͼ���63�е�����ֵ����Ϊ��һ��ͼ���63��ɨ����ʼ��
		}
	}
	for (i = ROW - 11; i >= 25; i--)//����ʣ����
	{
		signalFlag_row = 0;
		if (LeftEdge[i + 1] >= effective_left && RightEdge[i + 1] <= effective_right) //��һ�����߶��ҵ� ���ñ���ɨ��
		{
			j = ((LeftEdge[i + 1] + 10) > effective_right) ? effective_right : (LeftEdge[i + 1] + 10);//������߽�
			jj = ((LeftEdge[i + 1] - 5) < effective_left) ? effective_left : (LeftEdge[i + 1] - 5);
			while (j >= jj)
			{
				if (bin_image.at<uchar>(i, j) == WHITE && bin_image.at<uchar>(i, j - 1) == BLACK && bin_image.at<uchar>(i, j - 2) == BLACK)
				{
					LeftEdge[i] = j;
					break;
				}
				j--;
			}
			j = ((RightEdge[i + 1] - 10) < effective_left) ? effective_left : (RightEdge[i + 1] - 10); //�����ұ߽�
			jj = ((RightEdge[i + 1] + 5) > effective_right) ? effective_right : (RightEdge[i + 1] + 5);
			while (j <= jj)
			{
				if (bin_image.at<uchar>(i, j) == WHITE && bin_image.at<uchar>(i, j + 1) == BLACK && bin_image.at<uchar>(i, j + 2) == BLACK)
				{
					RightEdge[i] = j;
					break;
				}
				j++;
			}
		}
		else if (LeftEdge[i + 1] >= effective_left && RightEdge[i + 1] > effective_right)//��һ��ֻ�ҵ���߽�
		{
			j = ((LeftEdge[i + 1] + 10) > effective_right) ? effective_right : (LeftEdge[i + 1] + 10);//��߽��ñ���ɨ��
			jj = ((LeftEdge[i + 1] - 5) < effective_left) ? effective_left : (LeftEdge[i + 1] - 5);
			while (j >= jj)
			{
				if (bin_image.at<uchar>(i, j) == WHITE && bin_image.at<uchar>(i, j - 1) == BLACK && bin_image.at<uchar>(i, j - 2) == BLACK)
				{
					LeftEdge[i] = j;
					break;
				}
				j--;
			}
			j = MiddleLine[i + 1];//��һ�ж����ұ߽���ȫ��ɨ��
			if (j >= effective_right)
			{
				j = effective_right;
			}
			while (j <= effective_right)
			{
				if (bin_image.at<uchar>(i, j) == WHITE && bin_image.at<uchar>(i, j + 1) == BLACK && bin_image.at<uchar>(i, j + 2) == BLACK)
				{
					RightEdge[i] = j;
					break;
				}
				j++;
			}
		}
		else if (LeftEdge[i + 1] < effective_left && RightEdge[i + 1] <= effective_right) //��һ��ֻ�ҵ��ұ߽�
		{
			j = ((RightEdge[i + 1] - 10) < effective_left) ? effective_left : (RightEdge[i + 1] - 10);//��Ե׷�����ұ߽�
			jj = ((RightEdge[i + 1] + 5) > effective_right) ? effective_right : (RightEdge[i + 1] + 5);
			while (j <= jj)
			{
				if (bin_image.at<uchar>(i, j) == WHITE && bin_image.at<uchar>(i, j + 1) == BLACK && bin_image.at<uchar>(i, j + 2) == BLACK)
				{
					RightEdge[i] = j;
					break;
				}
				j++;
			}
			j = MiddleLine[i + 1]; //ȫ��ɨ������߽�
			if (j < effective_left)
			{
				j = effective_left;
			}
			while (j >= effective_left)
			{
				if (bin_image.at<uchar>(i, j) == WHITE && bin_image.at<uchar>(i, j - 1) == BLACK && bin_image.at<uchar>(i, j - 2) == BLACK)
				{
					LeftEdge[i] = j;
					break;
				}
				j--;
			}
		}
		else if (LeftEdge[i + 1] < effective_left && RightEdge[i + 1] > effective_right)  //��һ��û�ҵ��߽磬������ʮ�ֻ��߻��λ����Ǳ�־��Ӱ��
		{
			j = MiddleLine[i + 1];   //ȫ������߽�
			while (j >= effective_left)
			{
				if (bin_image.at<uchar>(i, j) == WHITE && bin_image.at<uchar>(i, j - 1) == BLACK && bin_image.at<uchar>(i, j - 2) == BLACK)
				{
					LeftEdge[i] = j;
					break;
				}
				j--;
			}
			j = MiddleLine[i + 1];   //ȫ�����ұ߽�
			while (j <= effective_right)
			{
				if (bin_image.at<uchar>(i, j) == WHITE && bin_image.at<uchar>(i, j + 1) == BLACK && bin_image.at<uchar>(i, j + 2) == BLACK)
				{
					RightEdge[i] = j;
					break;
				}
				j++;
			}
		}
		if (LeftEdge[i] > 60) {
			LeftEdge[i] = 0;//��־��Ӱ��߽磬ֱ���ж�Ϊ����
			signalFlag_row = 1;
		}
		if (RightEdge[i] < 145) {
			RightEdge[i] = COL - 1;
			signalFlag_row = 1;
		}
		if ((RightEdge[i] - LeftEdge[i]) >= (RightEdge[i + 1] - LeftEdge[i + 1] + 5))//ͻ��
		{
			MiddleLine[i] = MiddleLine[i + 1];//����һ��
		}
		else
		{
			if (LeftEdge[i] >= effective_left && RightEdge[i] <= effective_right)//������
			{
				MiddleLine[i] = (LeftEdge[i] + RightEdge[i]) / 2;
			}
			else if (LeftEdge[i] >= effective_left && RightEdge[i] > effective_right)//lose right
			{
				if (!signalFlag_row)
				{
					RightLose++;
				}

				if (LeftEdge[i + 1] >= effective_left)
				{
					MiddleLine[i] = MiddleLine[i + 1] + LeftEdge[i] - LeftEdge[i + 1];
				}
				else
				{
					MiddleLine[i] = LeftEdge[i] + Width[i] / 2;
				}
			}
			else if (LeftEdge[i] < effective_left && RightEdge[i] <= effective_right)//lose left
			{
				if (!signalFlag_row)
				{
					LeftLose++;
				}
				if (RightEdge[i + 1] <= effective_right)
				{
					MiddleLine[i] = MiddleLine[i + 1] + RightEdge[i] - RightEdge[i + 1];
				}
				else
				{
					MiddleLine[i] = RightEdge[i] - Width[i] / 2;
				}
			}
			else if (LeftEdge[i]<effective_left && RightEdge[i]>effective_right)//���߶���
			{
				if (!signalFlag_row)
				{
					AllLose++;
				}
				MiddleLine[i] = MiddleLine[i + 1];
			}
		}
		uint16_t m = MiddleLine[i];
		if (m < effective_left)
		{
			m = effective_left;
		}
		if (m > effective_right)
		{
			m = effective_right;
		}
	}
	return 0;
}

//int BlackEndMR = 0;
//int BlackEndML = 0;
//int BlackEndLL = 0;
//int BlackEndRR = 0;
//int BlackEndL = 0;
//int BlackEndM = 0;
//int BlackEndR = 0;
//int BlackEndMaxMax = 0;
//int BlackEndMax = 0;
//int DropRow = 0;

////��ȡͼ�������
////ѡȡ���У���ͼ��ײ�����ɨ��
////��ȡ���߽�ֹ��
//static void GetBlackEndParam()
//{
//	unsigned char LEndFlag = 0;//��־λ
//	unsigned char MEndFlag = 0;
//	unsigned char REndFlag = 0;
//	unsigned char MREndFlag = 0;
//	unsigned char MLEndFlag = 0;
//	unsigned char LLEndFlag = 0;
//	unsigned char RREndFlag = 0;
//
//	int i = 0;
//
//	BlackEndMR = 0;//����
//	BlackEndML = 0;
//	BlackEndLL = 0;
//	BlackEndRR = 0;
//	BlackEndL = 0;
//	BlackEndM = 0;
//	BlackEndR = 0;
//
//	for (i = ROW - 1; i >= 25; i--)
//	{
//		if (bin_image.at<uchar>(i, COL / 2) == WHITE && !MEndFlag)//94
//		{
//			BlackEndM++;//�к��߽�����
//		}
//		else if (bin_image.at<uchar>(i-1, COL / 2) == BLACK && bin_image.at<uchar>(i-2, COL / 2) == BLACK)//���������Ǻ�ɫ
//		{
//			MEndFlag = 1;
//		}
//		if (bin_image.at<uchar>(i, COL / 4) == WHITE && !LEndFlag)//47
//		{
//			BlackEndL++;//����߽�����
//		}
//		else if (bin_image.at<uchar>(i-1, COL / 4) == BLACK &&bin_image.at<uchar>(i-2, COL / 4) == BLACK)
//		{
//			LEndFlag = 1;
//		}
//		if (bin_image.at<uchar>(i, COL * 3 / 4) == WHITE && !REndFlag)//141
//		{
//			BlackEndR++;//�Һ��߽�����
//		}
//		else if (bin_image.at<uchar>(i-1, COL * 3 / 4) == BLACK && bin_image.at<uchar>(i-2, COL * 3 / 4) == BLACK)
//		{
//			REndFlag = 1;
//		}
//		if (bin_image.at<uchar>(i, COL * 3 / 8) == WHITE && !MLEndFlag)//ƫ��
//		{
//			BlackEndML++;
//		}
//		else if (bin_image.at<uchar>(i-1, COL * 3 / 8) == BLACK && bin_image.at<uchar>(i-2, COL * 3 / 8) == BLACK)
//		{
//			MLEndFlag = 1;
//		}
//		if (bin_image.at<uchar>(i, COL * 5 / 8) == WHITE && !MREndFlag)
//		{
//			BlackEndMR++;
//		}
//		else if (bin_image.at<uchar>(i-1, COL * 5 / 8) == BLACK && bin_image.at<uchar>(i-2, COL * 5 / 8) == BLACK)
//		{
//			MREndFlag = 1;
//		}
//		if (bin_image.at<uchar>(i, COL / 8) == WHITE && !LLEndFlag)
//		{
//			BlackEndLL++;
//		}
//		else if (bin_image.at<uchar>(i-1, COL / 8) == BLACK && bin_image.at<uchar>(i-2, COL / 8) == BLACK)
//		{
//			LLEndFlag = 1;
//		}
//		if (bin_image.at<uchar>(i, COL * 7 / 8) == WHITE && !RREndFlag)
//		{
//			BlackEndRR++;
//		}
//		else if (bin_image.at<uchar>(i-1, COL * 7 / 8) == BLACK && bin_image.at<uchar>(i - 2, COL * 7 / 8) == BLACK)
//		{
//			RREndFlag = 1;
//		}
//	}
//
//	BlackEndMax = MAX(BlackEndL, BlackEndM);//ȡ��ֵ
//	BlackEndMax = MAX(BlackEndMax, BlackEndR);
//	BlackEndMaxMax = MAX(BlackEndMax, BlackEndMR);
//	BlackEndMaxMax = MAX(BlackEndMax, BlackEndML);
//	BlackEndMaxMax = MAX(BlackEndMax, BlackEndLL);
//	BlackEndMaxMax = MAX(BlackEndMax, BlackEndRR);
//	DropRow = ROW - BlackEndMaxMax;//���߽�ֹ��
//}

/****************************************�ж���������****************************************/
typedef struct
{
	unsigned char InflectionPointRow;//�յ��������
	unsigned char InflectionPointCol;//�յ��������
	unsigned char InflectionPointFlag;//�յ�ı�־λ
	unsigned char ScanInflectionPointStart;//ɨ��յ����ʼ��
	unsigned char ScanInflectionPointEnd;//ɨ��յ������ 
	unsigned char InflectionPointNumber;//�յ�ĸ���

}InflectionPoint;//�����յ�ṹ��

typedef struct
{
	unsigned char CrossLR;//ʮ��
	unsigned char CrossL;//���·
	unsigned char CrossR;//�Ҳ�·

}CrossType;//����ʮ�����͵Ľṹ��

//���ұ��߽��в�����������ڶ���յ�Ѱ������Ĺյ�
//prt:����һ���ṹ������ĵ�ַ
//Start��ɨ�����ʼ��
//End ��ɨ��Ľ�����
void FindInflectionPointR(InflectionPoint *prt, unsigned char Start, unsigned char End)
{
	int i;
	//��ʼ���ṹ�����
	prt->ScanInflectionPointStart = Start;//����ɨ�����ʼ��
	prt->ScanInflectionPointEnd = End;//����ɨ��Ľ�����
	prt->InflectionPointRow = 0;
	prt->InflectionPointCol = 0;
	prt->InflectionPointFlag = 0;

	for (i = prt->ScanInflectionPointStart; i >= prt->ScanInflectionPointEnd; i--) //����ɨ��̫Զ�����������
	{
		if (RightEdge[i] != COL - 1 && RightEdge[i + 1] != COL - 1)
		{
			if ((RightEdge[i] - RightEdge[i + 1] <= 0) && (RightEdge[i - 1] - RightEdge[i]) >= 1 && (RightEdge[i - 2] - RightEdge[i]) >= 2)//�ҵ��ұ����йյ�
			{
				prt->InflectionPointRow = i;//��¼�յ����
				prt->InflectionPointCol = RightEdge[i];//��¼�յ����
				prt->InflectionPointFlag = 1;//����ҵ��ҹյ�
				break;//�˳�for
			}
		}
	}
}

//������߽��в�����������ڶ���յ�Ѱ������Ĺյ�
//prt:����һ���ṹ������ĵ�ַ
//Start��ɨ�����ʼ��
//End ��ɨ��Ľ�����
void FindInflectionPointL(InflectionPoint *prt, unsigned char Start, unsigned char End)
{
	int i;
	//��ʼ���ṹ�����
	prt->ScanInflectionPointStart = Start;//����ɨ�����ʼ��
	prt->ScanInflectionPointEnd = End;//����ɨ��Ľ�����
	prt->InflectionPointRow = 0;
	prt->InflectionPointCol = 0;
	prt->InflectionPointFlag = 0;

	//��յ�
	for (i = prt->ScanInflectionPointStart; i > prt->ScanInflectionPointEnd; i--)
	{
		if (LeftEdge[i] != 0 && LeftEdge[i + 1] != 0)
		{
			if ((LeftEdge[i] - LeftEdge[i + 1] >= 0) && (LeftEdge[i] - LeftEdge[i - 1] >= 3) && (LeftEdge[i] - LeftEdge[i - 2] >= 5))//�ҵ��յ�
			{
				prt->InflectionPointRow = i;//��¼�ùյ����
				prt->InflectionPointCol = LeftEdge[i];//��¼�ùյ����
				prt->InflectionPointFlag = 1;//����ҵ���յ�
				break;//�ҵ��˳�
			}
		}
	}
}

InflectionPoint  InflectionPointL;//������߹յ�ṹ�����
InflectionPoint  InflectionPointR;//�����ұ߹յ�ṹ�����
uint8_t RCross_flag = 0;
uint8_t LCross_flag = 0;
uint8_t LRCross_flag = 0;
uint8_t turn_count = 0;
unsigned char LeftScanCol[COL];
unsigned char RightScanCol[COL];

//void CrossRecognition(CrossType *prt)
//{
//	int i, j, ScanEndCol;
//
//	//��ʼ������
//	prt->CrossLR = 0;
//	prt->CrossL = 0;
//	prt->CrossR = 0;
//
//	//Ѱ�����ҹյ�
//	FindInflectionPointR(&InflectionPointR, ROW - 4, 25);
//	FindInflectionPointL(&InflectionPointL, ROW - 4, 25);
//	//�����߽���ұ߽�ͬʱ���ߴ���10�У�����Ϊ������ʮ��
//	if (AllLose >= 10)
//	{
//		cout << "ʮ��" << std::endl;
//		prt->CrossLR = 1;//ʮ��
//	}
//	//�ж��ҷֲ�·
//	else if (InflectionPointR.InflectionPointFlag //�����ұ߹յ�
//		&&InflectionPointL.InflectionPointFlag == 0//���Ҳ�������߹յ�
//		&& RightLose >= 5)
//	{
//		cout << "�ҹյ�" << std::endl;
//		for (i = 0; i < COL - 1; i++)
//		{
//			RightScanCol[i] = 0;//��ʼ������
//		}
//		//ѡ����Զ����һ��
//		if (BlackEndM >= BlackEndML && BlackEndM >= BlackEndLL)//�м����Ұ��Զ
//		{
//			ScanEndCol = COL / 2;
//		}
//		else if (BlackEndML > BlackEndM&&BlackEndML > BlackEndLL)//�м�ƫ����Ұ��Զ
//		{
//			ScanEndCol = COL * 3 / 8;
//		}
//		else if (BlackEndLL > BlackEndM&&BlackEndLL > BlackEndML)//������Ұ��Զ
//		{
//			ScanEndCol = COL / 4;
//		}
//		//���ҹյ������Ϊ��׼����Ұ��Զ��һ����Ϊ������������������ɨ��
//		//Ѱ��ʮ�������ֱ��
//		for (j = InflectionPointR.InflectionPointCol; j > ScanEndCol; j--)
//		{
//			//�Թյ����Ϊ��ʼ��׼����Զ�е�����Ϊ������
//			for (i = InflectionPointR.InflectionPointRow; i > DropRow; i--)
//			{
//				if (bin_image.at<uchar>(i, j) == WHITE && bin_image.at<uchar>(i-1, j) == BLACK && bin_image.at<uchar>(i-2, j) == BLACK)
//				{
//					RightScanCol[j] = i - 1;
//					break;
//				}
//			}
//		}
//		for (j = InflectionPointR.InflectionPointCol; j > ScanEndCol; j--)
//		{
//			if (RightScanCol[j] >= 2 && RightScanCol[j - 1] >= 2 && RightScanCol[j + 1] >= 2)
//				if (RightScanCol[j] - RightScanCol[j + 1] >= 0 && RightScanCol[j] - RightScanCol[j - 1] >= 1)
//				{
//					prt->CrossR = 1;
//					break;
//				}
//		}
//	}
//	//�ж���ֲ�·
//	else if (InflectionPointR.InflectionPointFlag == 0//���Ҳ������ұ߹յ�
//		&& InflectionPointL.InflectionPointFlag//������߹յ�
//		&& LeftLose >= 5)
//	{
//		cout << "��յ�" << std::endl;
//		for (i = 0; i < COL - 1; i++)
//		{
//			LeftScanCol[i] = 0;//��ʼ������
//		}
//		//ѡ����Զ����һ��
//		if (BlackEndM >= BlackEndMR && BlackEndM >= BlackEndRR)
//		{
//			ScanEndCol = COL / 2;
//		}
//		else if (BlackEndMR > BlackEndM&&BlackEndMR > BlackEndRR)
//		{
//			ScanEndCol = COL * 5 / 8;
//		}
//		else if (BlackEndRR > BlackEndM&&BlackEndRR > BlackEndMR)
//		{
//			ScanEndCol = COL * 3 / 4;
//		}
//		for (j = InflectionPointL.InflectionPointCol; j < ScanEndCol; j++)
//		{
//			//�Թյ����Ϊ��ʼ��׼����Զ�е�����Ϊ������
//			for (i = InflectionPointL.InflectionPointRow; i > DropRow; i--)
//			{
//				if (bin_image.at<uchar>(i, j) == WHITE && bin_image.at<uchar>(i-1, j) == BLACK && bin_image.at<uchar>(i-2, j) == BLACK)
//				{
//					LeftScanCol[j] = i - 1;
//					break;
//				}
//			}
//		}
//		for (j = InflectionPointL.InflectionPointCol; j < ScanEndCol; j++)
//		{
//			if (LeftScanCol[j] >= 2 && LeftScanCol[j - 1] >= 2 && LeftScanCol[j + 1] >= 2)
//				if (LeftScanCol[j] - LeftScanCol[j + 1] >= 1 && LeftScanCol[j] - LeftScanCol[j - 1] >= 0)
//				{
//					prt->CrossL = 1;//��־���·
//					break;
//				}
//		}
//	}
//}

void CrossRecognition(CrossType *prt)
{
	//��ʼ������
	prt->CrossLR = 0;
	prt->CrossL = 0;
	prt->CrossR = 0;

	//Ѱ�����ҹյ�
	FindInflectionPointR(&InflectionPointR, ROW - 1, 30);
	FindInflectionPointL(&InflectionPointL, ROW - 1, 30);
	//�����߽���ұ߽�ͬʱ���ߴ���5�У�����Ϊ������ʮ��
	if (InflectionPointR.InflectionPointFlag
		&&InflectionPointL.InflectionPointFlag
		&&AllLose >= 3)
	{
		prt->CrossLR = 1;//ʮ��
	}
	//�ж��ҷֲ�·
	else if (InflectionPointR.InflectionPointFlag //�����ұ߹յ�
		&& RightLose >= 5 && LeftLose < 3 && AllLose < 3)
	{
		prt->CrossR = 1;
	}
	//�ж���ֲ�·
	else if (InflectionPointL.InflectionPointFlag//������߹յ�
		&& LeftLose >= 5 && RightLose < 3 && AllLose < 3)
	{
		prt->CrossL = 1;//��־���·
	}
}

CrossType Cross;//����ʮ�ֽṹ�����
//��·����Ҫ��ָ��
#define cross_straight  1
#define cross_right     2
#define cross_left      3
int cross_state = cross_straight;

//�õ�ʮ�����͵���ر�־��Ϊ���Ʊ�־λ
static void Crossflag(void)
{
	if (Cross.CrossLR)//ʮ��
	{
		cout << "ʮ��" << std::endl;
		if (cross_state == cross_straight)//ֱ���ź�
		{
			cout << "ʮ�ֿ���ֱ��" << std::endl;
			LRCross_flag = cross_straight;
			cross_state = 0;
		}
		else if (cross_state == cross_right)//��ת�ź�
		{
			cout << "ʮ�ֿ�����ת" << std::endl;
			LRCross_flag = cross_right;
			cross_state = 0;
		}
		else if (cross_state == cross_left)//��ת�ź�
		{
			cout << "ʮ�ֿ�����ת" << std::endl;
			LRCross_flag = cross_left;
			cross_state = 0;
		}
	}
	else if (Cross.CrossR)//�ҷֲ�
	{
		cout << "�ҷֲ�" << std::endl;
		if (cross_state == cross_straight)//ֱ���ź�
		{
			cout << "�ҷֲ����ֱ��" << std::endl;
			RCross_flag = cross_straight;
			cross_state = 0;
		}
		else if (cross_state == cross_right)//��ת�ź�
		{
			cout << "�ҷֲ������ת" << std::endl;
			RCross_flag = cross_right;
			cross_state = 0;
		}
	}
	else if (Cross.CrossL)//��ֲ�
	{
		cout << "��ֲ�" << std::endl;
		if (cross_state == cross_straight)//ֱ���ź�
		{
			cout << "��ֲ����ֱ��" << std::endl;
			LCross_flag = cross_straight;
			cross_state = 0;
		}
		else if (cross_state == cross_left)//��ת�ź�
		{
			cout << "��ֲ������ת" << std::endl;
			LCross_flag = cross_left;
			cross_state = 0;
		}
	}
}

//��ʮ�ֽ��д����ó�����Ŀ�������
void CrossProcess(void)
{
	Crossflag();
	//ʮ��
	if (LRCross_flag == cross_straight) {//ֱ��

	}
	else if (LRCross_flag == cross_right) {//��ת
		if (turn_count >= 2)
		{
		}
		else
		{
			if (InflectionPointR.InflectionPointFlag == 0
				&& AllLose >= 3) {
				turn_count++;
			}
			else {
				turn_count = 0;
			}
		}
	}
	else if (LRCross_flag == cross_left) {//��ת
		if (turn_count >= 2)
		{
		}
		else
		{
			if (InflectionPointL.InflectionPointFlag == 0
				&& AllLose >= 3) {
				turn_count++;
			}
			else {
				turn_count = 0;
			}
		}
	}
	//�Ҳ�·
	if (RCross_flag == cross_straight) {//ֱ��
	}
	else if (RCross_flag == cross_right) {//��ת
		if (turn_count >= 7)
		{
		}
		else
		{
			if (InflectionPointR.InflectionPointFlag == 0
				&& InflectionPointL.InflectionPointFlag == 0
				&& RightLose >= 5 && LeftLose < 3 && AllLose < 3) {
				turn_count++;
			}
			else {
				turn_count = 0;
			}
		}
	}
	//���·
	if (LCross_flag == cross_straight) {//ֱ��
	}
	else if (LCross_flag == cross_left) {//��ת
		if (turn_count >= 7)
		{
		}
		else
		{
			if (InflectionPointR.InflectionPointFlag == 0
				&& InflectionPointL.InflectionPointFlag == 0
				&& LeftLose >= 5 && RightLose < 3 && AllLose < 3) {
				turn_count++;
			}
			else {
				turn_count = 0;
			}
		}
	}

	//��ͼ��ָ����������ñ�־λ
	if (LeftLose < 3 && RightLose < 3 && AllLose < 3
		&& fabs(LeftEdge[40] + Width[40] / 2 - MidLine) < 13 && fabs(RightEdge[40] - Width[40] / 2 - MidLine) < 13
		&& fabs(LeftEdge[70] + Width[70] / 2 - MidLine) < 13 && fabs(RightEdge[70] - Width[70] / 2 - MidLine) < 13
		&& fabs(LeftEdge[100] + Width[100] / 2 - MidLine) < 13 && fabs(RightEdge[100] - Width[100] / 2 - MidLine) < 13
		&& (RCross_flag || LCross_flag || LRCross_flag))
	{
		RCross_flag = 0; LCross_flag = 0; LRCross_flag = 0;
		turn_count = 0;
		signalFlag_frame = 0;
		cout << "���óɹ�" << std::endl;
	}
}


int movieProcess()
{
	VideoCapture capVideo("..\\movie\\test2.mp4");
	//�����Ƶ��ʧ��
	if (!capVideo.isOpened()) {
		std::cout << "Unable to open video!" << std::endl;
		return -1;
	}

	double scale = 0.1;

	Mat frame;
	Mat rframe;
	Mat frame_gray;
	Mat frame_bin;

	std::vector<cv::Point> points;

	while (1)
	{
		capVideo >> frame;
		if (frame.empty()) break;//����Ƶ���������˳�
		Size ResImgSize = Size(frame.cols*scale, frame.rows*scale);
		rframe = Mat(ResImgSize, frame.type());
		resize(frame, rframe, ResImgSize, INTER_LINEAR);
		cvtColor(rframe, frame_gray, COLOR_BGR2GRAY);
		threshold(frame_gray, frame_bin, 100, 255, THRESH_OTSU);//��򷨶�ֵ��

		bin_image = frame_bin;

		findTrack();
		CrossRecognition(&Cross);
		CrossProcess();

		//cout << "leftlose:" << LeftLose << " rightlose:" << RightLose << " alllose:" << AllLose << std::endl;
		points.clear();
		for (int i = ROW - 1; i >= 25; i--)
		{
			if (fabs(MiddleLine[i] - MiddleLine[i + 1]) > 3 && i != ROW - 1)//ƽ������
			{
				MiddleLine[i] = MiddleLine[i + 1];
			}
			//cout << "row" << i << " leftEdge:" << LeftEdge[i] << " rightEdge:" << RightEdge[i] << " middle:" << MiddleLine[i] << std::endl;
			points.push_back(Point(MiddleLine[i], i));
			//cout << "row" << i << " rightEdge-leftEdge:" << RightEdge[i] - LeftEdge[i] << std::endl;
		}

		polylines(rframe, points, false, Scalar(255, 255, 0), 2, 8, 0);//�������

		imshow("rframe", rframe);
		imshow("bin_frame", frame_bin);
		waitKey(30);
	}

	return 0;
}

int main()
{
	//��ʼ��ʱ
	double start = static_cast<double>(cvGetTickCount());

	movieProcess();

	//������ʱ
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//��ʾʱ��
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//�ȴ�������Ӧ�����������������
	system("pause");
	return 0;
}