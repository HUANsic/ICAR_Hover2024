#include "img_process.h"

// An highlighted block
/*************************************************************************
 *  函数名称：short GetOSTU (unsigned char tmImage[LCDH][LCDW])
 *  功能说明：大津法求阈值大小
 *  参数说明：tmImage ： 图像数据
 *  函数返回：无
 *  修改时间：2011年10月28日
 *  备    注：  GetOSTU(Image_Use);//大津法阈值
Ostu方法又名最大类间差方法，通过统计整个图像的直方图特性来实现全局阈值T的自动选取，其算法步骤为：
1) 先计算图像的直方图，即将图像所有的像素点按照0~255共256个bin，统计落在每个bin的像素点数量
2) 归一化直方图，也即将每个bin中像素点数量除以总的像素点
3) i表示分类的阈值，也即一个灰度级，从0开始迭代 1
4) 通过归一化的直方图，统计0~i 灰度级的像素(假设像素值在此范围的像素叫做前景像素) 所占整幅图像
        的比例w0，        并统计前景像素的平均灰度u0；统计i~255灰度级的像素(假设像素值在此范围的像素叫做背
        景像素)  * 所占整幅图像的比例w1，并统计背景像素的平均灰度u1；
5) 计算前景像素和背景像素的方差 g = w0*w1*(u0-u1) (u0-u1)
6) i++；转到4)，直到i为256时结束迭代
7) 将最大g相应的i值作为图像的全局阈值
缺陷:OSTU算法在处理光照不均匀的图像的时候，效果会明显不好，因为利用的是全局像素信息。
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
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
    uint16_t MinValue, MaxValue;
    uint16_t Threshold = 0;
    uint8_t HistoGram[256];              //

    for (j = 0; j < 256; j++)
        HistoGram[j] = 0; //初始化灰度直方图

    for (j = 0; j < IMGH; j++)
    {
        for (i = 0; i < IMGW; i++)
        {
            HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //获取最大灰度的值

    if (MaxValue == MinValue)
        return MaxValue;         // 图像中只有一个颜色
    if (MinValue + 1 == MaxValue)
        return MinValue;        // 图像中只有二个颜色

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  像素总数

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        Pixelshortegral += HistoGram[j] * j;        //灰度值总数
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];     //前景像素点数
        PixelFore = Amount - PixelBack;           //背景像素点数
        OmegaBack = (float) PixelBack / Amount;   //前景像素百分比
        OmegaFore = (float) PixelFore / Amount;   //背景像素百分比
        PixelshortegralBack += HistoGram[j] * j;  //前景灰度值
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //背景灰度值
        MicroBack = (float) PixelshortegralBack / PixelBack;   //前景灰度百分比
        MicroFore = (float) PixelshortegralFore / PixelFore;   //背景灰度百分比
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //计算类间方差
        if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //返回最佳阈值;
}

// An highlighted block
/*---------------------------------------------------------------
 【函    数】Bin_Image_Filter
 【功    能】过滤噪点
 【参    数】无
 【返 回 值】无
 【注意事项】
 ----------------------------------------------------------------*/
void Bin_Image_Filter()
{
    uint16_t nr; //行
    uint16_t nc; //列

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



