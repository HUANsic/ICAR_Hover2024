#include "img_process.h"

// An highlighted block
/*************************************************************************
 *  �������ƣ�short GetOSTU (unsigned char tmImage[LCDH][LCDW])
 *  ����˵�����������ֵ��С
 *  ����˵����tmImage �� ͼ������
 *  �������أ���
 *  �޸�ʱ�䣺2011��10��28��
 *  ��    ע��  GetOSTU(Image_Use);//�����ֵ
Ostu������������������ͨ��ͳ������ͼ���ֱ��ͼ������ʵ��ȫ����ֵT���Զ�ѡȡ�����㷨����Ϊ��
1) �ȼ���ͼ���ֱ��ͼ������ͼ�����е����ص㰴��0~255��256��bin��ͳ������ÿ��bin�����ص�����
2) ��һ��ֱ��ͼ��Ҳ����ÿ��bin�����ص����������ܵ����ص�
3) i��ʾ�������ֵ��Ҳ��һ���Ҷȼ�����0��ʼ���� 1
4) ͨ����һ����ֱ��ͼ��ͳ��0~i �Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ���ǰ������) ��ռ����ͼ��
        �ı���w0��        ��ͳ��ǰ�����ص�ƽ���Ҷ�u0��ͳ��i~255�Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ�����
        ������)  * ��ռ����ͼ��ı���w1����ͳ�Ʊ������ص�ƽ���Ҷ�u1��
5) ����ǰ�����غͱ������صķ��� g = w0*w1*(u0-u1) (u0-u1)
6) i++��ת��4)��ֱ��iΪ256ʱ��������
7) �����g��Ӧ��iֵ��Ϊͼ���ȫ����ֵ
ȱ��:OSTU�㷨�ڴ�����ղ����ȵ�ͼ���ʱ��Ч�������Բ��ã���Ϊ���õ���ȫ��������Ϣ��
*************************************************************************/
void threhold_update(){
    threhold = GetOSTU (Image_Gray);
}

uint16_t GetOSTU (uint8_t tmImage[IMGH][IMGW])
{
    int16_t i, j;
    uint32_t Amount = 0;
    uint32_t PixelBack = 0;
    uint32_t PixelshortegralBack = 0;
    uint32_t Pixelshortegral = 0;
    int32_t PixelshortegralFore = 0;
    int32_t PixelFore = 0;
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��;
    uint16_t MinValue, MaxValue;
    uint16_t Threshold = 0;
    uint8_t HistoGram[256];              //

    for (j = 0; j < 256; j++)
        HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ

    for (j = 0; j < IMGH; j++)
    {
        for (i = 0; i < IMGW; i++)
        {
            HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //��ȡ��С�Ҷȵ�ֵ
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //��ȡ���Ҷȵ�ֵ

    if (MaxValue == MinValue)
        return MaxValue;         // ͼ����ֻ��һ����ɫ
    if (MinValue + 1 == MaxValue)
        return MinValue;        // ͼ����ֻ�ж�����ɫ

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  ��������

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        Pixelshortegral += HistoGram[j] * j;        //�Ҷ�ֵ����
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];     //ǰ�����ص���
        PixelFore = Amount - PixelBack;           //�������ص���
        OmegaBack = (float) PixelBack / Amount;   //ǰ�����ذٷֱ�
        OmegaFore = (float) PixelFore / Amount;   //�������ذٷֱ�
        PixelshortegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //�����Ҷ�ֵ
        MicroBack = (float) PixelshortegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
        MicroFore = (float) PixelshortegralFore / PixelFore;   //�����ҶȰٷֱ�
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //������䷽��
        if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //���������ֵ;
}

// An highlighted block
/*---------------------------------------------------------------
 ����    ����Bin_Image_Filter
 ����    �ܡ��������
 ����    ������
 ���� �� ֵ����
 ��ע�����
 ----------------------------------------------------------------*/
void Bin_Image_Filter()
{
    uint16_t nr; //��
    uint16_t nc; //��

    for (nr = 1; nr < IMGH - 1; nr++)
    {
        for (nc = 1; nc < IMGW - 1; nc = nc + 1)
        {
            if ((Image_Bin[nr][nc] == 0)
                    && (Image_Bin[nr - 1][nc] + Image_Bin[nr + 1][nc] + Image_Bin[nr][nc + 1] + Image_Bin[nr][nc - 1] > 2))
            {
                Image_Bin[nr][nc] = 1;
            }
            else if ((Image_Bin[nr][nc] == 1)
                    && (Image_Bin[nr - 1][nc] + Image_Bin[nr + 1][nc] + Image_Bin[nr][nc + 1] + Image_Bin[nr][nc - 1] < 2))
            {
                Image_Bin[nr][nc] = 0;
            }
        }
    }
}


int32_t err_0, err_1, err_2, err_3, err_4;
int32_t get_err(){
    int32_t left=0, right=0;
    for(uint8_t i = 0; i < IMGH; i++){
        for(uint8_t j = 0; j < IMGW / 2; j++){
            if(Image_Bin[i][j]){
                left++;
            }
        }
        for(uint8_t j = IMGW / 2; j < IMGW; j++){
            if(Image_Bin[i][j]){
                right++;
            }
        }
    }
    err_4 = err_3;
    err_3 = err_2;
    err_2 = err_1;
    err_1 = err_0;
    err_0 = left - right;
    return (err_4 + err_3 + err_2 + err_1 + err_0) / 5;
}



