/***********************************
	鏈┍鍔ㄦ枃浠朵粎閫傞厤HAL搴撶増鏈�?
***********************************/
#include "stm32f4xx_hal.h"	//閾炬帴HAL搴擄紝浣犵殑鏄粈涔堣姱鐗囧氨鏀规垚浠€涔�
#include "OLED_Font.h"	 //瀛楀簱鏂囦欢
#include "OLED.h"		//澹版�?
#include "i2c.h"

#define i2c_set hi2c1
uint8_t CMD_Data[]={
0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1, 0xA6, 0xA8, 0x3F,
					
0xC8, 0xD3, 0x00, 0xD5, 0x80, 0xD8, 0x05, 0xD9, 0xF1, 0xDA, 0x12,
					
0xD8, 0x30, 0x8D, 0x14, 0xAF};      //鍒濆鍖栧懡浠�


void WriteCmd(void)
{
	uint8_t i = 0;
	for(i=0; i<27; i++)
	{
		HAL_I2C_Mem_Write(&i2c_set ,0x78,0x00,I2C_MEMADD_SIZE_8BIT,CMD_Data+i,1,0x100);
	}
}
//鍚戣澶囧啓鎺у埗鍛戒�?
void OLED_WR_CMD(uint8_t cmd)
{
	HAL_I2C_Mem_Write(&i2c_set ,0x78,0x00,I2C_MEMADD_SIZE_8BIT,&cmd,1,0x100);
}
//鍚戣澶囧啓鏁版�?
void OLED_WR_DATA(uint8_t data)
{
	HAL_I2C_Mem_Write(&i2c_set ,0x78,0x40,I2C_MEMADD_SIZE_8BIT,&data,1,0x100);
}
//鍒濆鍖杘led灞忓�?
void OLED_Init(void)
{ 	
	HAL_Delay(200);
 
	WriteCmd();
}
//娓呭�?
void OLED_Clear(void)
{
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_CMD(0xb0+i);
		OLED_WR_CMD (0x00); 
		OLED_WR_CMD (0x10); 
		for(n=0;n<128;n++)
			OLED_WR_DATA(0);
	} 
}
//寮€鍚疧LED鏄剧�?    
void OLED_Display_On(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC鍛戒�?
	OLED_WR_CMD(0X14);  //DCDC ON
	OLED_WR_CMD(0XAF);  //DISPLAY ON
}
//鍏抽棴OLED鏄剧�?     
void OLED_Display_Off(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC鍛戒�?
	OLED_WR_CMD(0X10);  //DCDC OFF
	OLED_WR_CMD(0XAE);  //DISPLAY OFF
}

void OLED_Set_Pos(uint8_t x, uint8_t y) 
{ 	
	OLED_WR_CMD(0xb0+y);
	OLED_WR_CMD(((x&0xf0)>>4)|0x10);
	OLED_WR_CMD(x&0x0f);
} 
 
void OLED_On(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_CMD(0xb0+i);    //璁剧疆椤靛湴鍧€锛�0~7锛�
		OLED_WR_CMD(0x00);      //璁剧疆鏄剧ず浣嶇疆鈥斿垪浣庡湴鍧�?
		OLED_WR_CMD(0x10);      //璁剧疆鏄剧ず浣嶇疆鈥斿垪楂樺湴鍧�?   
		for(n=0;n<128;n++)
			OLED_WR_DATA(1); 
	} //鏇存柊鏄剧ず
}
unsigned int oled_pow(uint8_t m,uint8_t n)
{
	unsigned int result=1;	 
	while(n--)result*=m;    
	return result;
}
//鏄剧ず鐭╅樀鍥惧�?
void OLED_ShowRectangle(uint8_t x,uint8_t y,uint8_t high)
{
	int n;
	OLED_Set_Pos(x,y);
	for(n=0;n<high;n++)
	{
  OLED_WR_DATA(0xff);
	}
}
/*
   OLED鏄剧ず鏁板瓧锛堝崄杩涘埗锛屽甫绗﹀彿鏁帮級
   X,Y涓鸿捣濮嬪潗鏍囩�?
    Num 瑕佹樉绀虹殑鏁板瓧锛岃寖鍥达�?-2147483648~2147483647
    Len 瑕佹樉绀烘暟瀛楃殑闀垮害锛岃寖鍥达細1~10
*/
void OLED_ShowSignedNum(uint8_t x,uint8_t y,int num,uint8_t len,uint8_t size2)
{
	uint8_t t,temp;
	uint8_t enshow=0;	
if(num>0)
{
	OLED_ShowChar(x,y,'+',12);
}
else if(num<0)
{
	OLED_ShowChar(x,y,'-',12);
	num=-num;
}
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(6+x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(6+x+(size2/2)*t,y,temp+'0',size2); 
	}
}
//x,y :璧风偣鍧愭爣	 
//len :鏁板瓧鐨勪綅鏁�
//size2:瀛椾綋澶у皬锛�?16鎴�12锛�
//num:鏁板€�(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 
//鍦ㄦ寚瀹氫綅缃樉绀轰竴涓瓧绗�?,鍖呮嫭閮ㄥ垎瀛楃�?
//x:0~127
//y:0~63		 
//size:閫夋嫨瀛椾�? 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//寰楀埌鍋忕Щ鍚庣殑鍊�			
		if(x>128-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_DATA(F8X16[c*16+i]);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_DATA(F8X16[c*16+i+8]);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_DATA(F6x8[c][i]);
				
			}
}
 
//鏄剧ず涓€涓瓧绗﹀彿涓�?
//x,y涓哄潗鏍囷紝chr涓哄瓧绗︿覆锛孋har_Size涓哄崟涓瓧姣嶆垨绗﹀彿鍗犵敤鐨勫儚绱犻暱搴�
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

//鏄剧ず姹夊瓧
//hzk 鐀��彇妯¤蒋浠跺緱鍑虹殑鏁扮粍
//x,y涓哄潗鏍囷紝no涓篛LED_Font.h涓殑绗�?202琛屽紑濮嬬殑鏁扮粍涓殑姹夊瓧鐨勯『搴忓彿
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_DATA(Hzk[2*no][t]);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_DATA(Hzk[2*no+1][t]);
				adder+=1;
      }					
}
//鏄剧�?128x64 BMP鍥剧�?
void OLED_Draw12864BMP(uint8_t num)//鍏朵腑鐨勫彉閲忎负绗嚑寮犲浘鐗�
{
    uint16_t j=0;
    uint8_t x,y;
    for(y=0; y<8; y++)
    {
        OLED_Set_Pos(0,y);
        for(x=0; x<128; x++)
        {
#if DISPLAY_MODE
            OLED_WR_DATA(BMP[num-1][y]);
#else
            OLED_WR_DATA(BMP[num-1][j++]);
#endif
        }
    }
}
//灏忔暟鏄剧ずAPI鍑芥�?
//z_len涓烘暣鏁版樉绀轰綅鏁帮紝f_len涓哄皬鏁版樉绀轰綅鏁帮紝size2涓哄瓧浣撳ぇ灏�
void OLED_Showdecimal(uint8_t x,uint8_t y,float num,uint8_t z_len,uint8_t f_len,uint8_t size2)
{         	
	uint8_t t,temp;
	uint8_t enshow;
	int z_temp,f_temp;      
	z_temp=(int)num;
	//鏁存暟閮ㄥ垎
	for(t=0;t<z_len;t++)
	{
		temp=(z_temp/oled_pow(10,z_len-t-1))%10;
		if(enshow==0 && t<(z_len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}
			else
			enshow=1;
		}
		OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
	//灏忔暟鐐�?
	OLED_ShowChar(x+(size2/2)*(z_len),y,'.',size2); 
	
	f_temp=(int)((num-z_temp)*(oled_pow(10,f_len)));
  //灏忔暟閮ㄥ垎
	for(t=0;t<f_len;t++)
	{
		temp=(f_temp/oled_pow(10,f_len-t-1))%10;
		OLED_ShowChar(x+(size2/2)*(t+z_len)+5,y,temp+'0',size2); 
	}
}



