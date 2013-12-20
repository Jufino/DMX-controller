#include <avr/io.h>
#include <util/delay.h>
asm("setPin:""\n\t"
    "push R16""\n\t"
    "ldi R16,255" "\n\t"
    "out 21,R16" "\n\t"
    "NOP"		   "\n\t"
	"NOP"		   "\n\t"
	"NOP"		   "\n\t"
    "ldi R16,8"   "\n\t"
	"cas1:"	   "\n\t"
	"NOP"		   "\n\t"
    "dec R16"	   "\n\t"
    "brne cas1"   "\n\t"
    "pop R16"	   "\n\t"
	"RET"		   "\n\t");
asm("clrPin:""\n\t"
    "push R16""\n\t"
    "ldi R16,0" "\n\t"
    "out 21,R16" "\n\t"
    "NOP"		   "\n\t"
	"NOP"		   "\n\t"
	"NOP"		   "\n\t"
	"NOP"	   "\n\t"
    "ldi R16,9"   "\n\t"
	"cas2:"	   "\n\t"
	"NOP"		   "\n\t"
    "dec R16"	   "\n\t"
    "brne cas2"   "\n\t"
    "pop R16"	   "\n\t"
	"RET"		   "\n\t"
			 );
void breakDMX(){
	asm("call clrPin" 	);	
	_delay_us(88);
}
void mabDMX(){
	asm("call setPin");
	asm("call setPin");
	asm("NOP");
	asm("NOP");
	asm("NOP");	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");	
	asm("NOP");
	asm("NOP");
}
void sendByte(unsigned char data){
int i;
	
	asm("rcall clrPin");
	for (i=1;i<129;i=i<<1){
		if ((data&i)==i)	asm("rcall setPin");
		else				asm("rcall clrPin");
	}
	asm("rcall setPin");
	asm("rcall setPin");
	asm("rcall setPin");
	asm("rcall setPin");
}
void sendDMX(unsigned char data[],int length){
	int i;
	breakDMX();
	mabDMX();
	sendByte(0x00);
	for(i=0;i<length;i++)
		sendByte(data[i]);
}	

void setup(void){
	PORTA=0x00;
	DDRA=0x1E; 
	PORTB=0x00;
	DDRB=0x00;
	PORTC=0x01;
	DDRC=0x01;
	PORTD=0x01;
	DDRD=0x01;
}
char klavesnica(char x,char y){
	PORTA|=0x0F;
    switch(y){
        case 4: PORTA&=0b00001101; break;
        case 3: PORTA&=0b00001011; break;
        case 2: PORTA&=0b00000111; break;
        case 1: PORTA&=0b00001111; break;
    }
    switch(x){
        case 3: return !((PINA&0x20)>>5); break;
        case 1: return !((PINA&0x40)>>6); break;
        case 2: return !((PINA&0x80)>>7); break;
        default: return 0;      break;
    }
}
char klavesnicaPor(){
   if (klavesnica(1,1)==1)         	return '1';
    else if (klavesnica(2,1)==1)   	return '2';
    else if (klavesnica(3,1)==1)   	return '3';
    else if (klavesnica(1,2)==1)   	return '4';
    else if (klavesnica(2,2)==1)   	return '5';
    else if (klavesnica(3,2)==1)   	return '6';
    else if (klavesnica(1,3)==1)   	return '7';
    else if (klavesnica(2,3)==1)   	return '8';
    else if (klavesnica(3,3)==1)   	return '9';
    else if (klavesnica(2,4)==1)   	return '0';
    else if (klavesnica(1,4)==1)	return '_';
	else if (klavesnica(3,4)==1)	return 'O';
	else return -1;
}
int main(void){
setup();
unsigned char dmx[100];
int por=0;
int por1=0;
int dir=0;
int dir8=0;
int test = 2;
int por1hod=3;
int dva =0;
int rgb[4];
unsigned char jas = 255;
char last_push='-1';
for(por=0;por<41;por++) dmx[por] = 0;
		sendDMX(dmx,41);
rgb[0]=test;
rgb[1]=test;
rgb[2]=test;
rgb[3]=0;
while(1){
	switch(klavesnicaPor()){
		case '1':dmx[0] = 0;		//pas
				 dmx[1] = 0;
				 dmx[2] = 0;
				 dmx[3] = 240;
    			 dmx[4] = 150;
				 dmx[5] = 0;
    			 dmx[6] = 255;
				 //-----------------------
    			 dmx[7] = 255;	//kruhy
    			 dmx[8] = 0;
    			 dmx[9] = 255;
    			 dmx[10] = 195;
				 //-----------------------
    			 dmx[11]=88;		//polgula
				 dmx[12]=255;
			     dmx[13]=0;     
    			 dmx[14]=0;      
    			 dmx[15]=0;       
    			 dmx[16]=0;       
    			 dmx[17]=0;       
				 dmx[18]=255;
				 //------------------------ 
			     dmx[19]=0;		//reflektory
				 dmx[20]=0;
				 dmx[21]=0;     
    			 dmx[22]=0;      
    			 dmx[23]=0;       
    			 dmx[24]=0;       
    			 dmx[25]=200;       
				 dmx[26]=250;	
				  //------------------------ 
				  dmx[27]=0;		//1x reflektor
				  dmx[28]=0;
				  dmx[29]=0;     
    			  dmx[30]=0;      
    			  dmx[31]=0;       
    			  dmx[32]=0;       
    			  dmx[33]=200;       
				  dmx[34]=250;	
				  //------------------------ 	
				  dmx[35]=0;		//2x reflektor
				  dmx[36]=0;
				  dmx[37]=0;     
    			  dmx[38]=0;      
    			  dmx[39]=0;           
				  dmx[40]=255;	
				  //------------------------ 	
				 last_push = '1';
				 break;
//-----------------------------------------------------------   
		case '2':last_push = '2'; 	break;	
//-----------------------------------------------------------  
		case '3':dmx[0] = 0;		//pas
				 dmx[1] = 0;
				 dmx[2] = 0;
				 dmx[3] = 28;
    			 dmx[4] = 0;
				 dmx[5] = 0;
				 dmx[6] = jas;
				 //-----------------------
    			 dmx[7] = 0;	//kruhy
    			 dmx[8] = 0;
    			 dmx[9] = 0;
    			 dmx[10] = 0;
				 //-----------------------
    			 dmx[11]=88;		//polgula
				 dmx[12]=255;
				 dmx[13]=0;     
    			 dmx[14]=0;      
    			 dmx[15]=255;       
    			 dmx[16]=0;       
    			 dmx[17]=0;       
				 dmx[18]=0;
				 //------------------------ 
				 dmx[19]=0;		//reflektory
				 dmx[20]=jas;
				 dmx[21]=0;     
    			 dmx[22]=0;      
    			 dmx[23]=0;       
    			 dmx[24]=0;       
    			 dmx[25]=0;       
				 dmx[26]=255;
				  //------------------------ 
				  dmx[27]=0;		//1x reflektor
				  dmx[28]=jas;
				  dmx[29]=0;     
    			  dmx[30]=0;      
    			  dmx[31]=0;       
    			  dmx[32]=0;       
    			  dmx[33]=0;       
				  dmx[34]=255;	
				  //------------------------
				  dmx[35]=0;		//2x reflektor
				  dmx[36]=jas;
				  dmx[37]=0;     
    			  dmx[38]=0;      
    			  dmx[39]=0;       
    			  dmx[40]=0;       	
				  //------------------------  

				 last_push = '3';
				 break;
//-----------------------------------------------------------    
		case '4': dmx[0] = 0;		//pas
				 dmx[1] = 0;
				 dmx[2] = 0;
				 dmx[3] = 12;
    			 dmx[4] = 0;
				 dmx[5] = 0;
    			 dmx[6] = jas;
				 //-----------------------
    			 dmx[7] = 0;	//kruhy
    			 dmx[8] = 0;
    			 dmx[9] = 0;
    			 dmx[10] = 0;
				 //-----------------------
    			 dmx[11]=88;		//polgula
				 dmx[12]=255;
				 dmx[13]=0;     
    			 dmx[14]=255;      
    			 dmx[15]=0;       
    			 dmx[16]=0;       
    			 dmx[17]=0;       
				 dmx[18]=0;
				 //------------------------ 
				 dmx[19]=jas;		//reflektory
				 dmx[20]=0;
				 dmx[21]=0;     
    			 dmx[22]=0;      
    			 dmx[23]=0;       
    			 dmx[24]=0;       
    			 dmx[25]=0;       
				 dmx[26]=255;
				  //------------------------ 
				  dmx[27]=jas;		//1x reflektor
				  dmx[28]=0;
				  dmx[29]=0;     
    			  dmx[30]=0;      
    			  dmx[31]=0;       
    			  dmx[32]=0;       
    			  dmx[33]=0;       
				  dmx[34]=255;	
				  //------------------------ 
				  dmx[35]=jas;		//2x reflektor
				  dmx[36]=0;
				  dmx[37]=0;     
    			  dmx[38]=0;      
    			  dmx[39]=0;       
    			  dmx[40]=0;       	
				  //------------------------ 
				 last_push = '4';
				 break;
//-----------------------------------------------------------  	
		case '5':dmx[0] = 0;		//pas
				 dmx[1] = 0;
				 dmx[2] = 0;
				 dmx[3] = 20;
    			 dmx[4] = 0;
				 dmx[5] = 0;
    			 dmx[6] = jas;
				 //-----------------------
    			 dmx[7] = 0;	//kruhy
    			 dmx[8] = 0;
    			 dmx[9] = 0;
    			 dmx[10] = 0;
				 //-----------------------
    			 dmx[11]=88;		//polgula
				 dmx[12]=255;
				 dmx[13]=0;     
    			 dmx[14]=255;      
    			 dmx[15]=255;       
    			 dmx[16]=0;       
    			 dmx[17]=0;       
				 dmx[18]=0;
				 //------------------------ 
				 dmx[19]=jas;		//reflektory
				 dmx[20]=jas;
				 dmx[21]=0;     
    			 dmx[22]=0;      
    			 dmx[23]=0;       
    			 dmx[24]=0;       
    			 dmx[25]=0;       
				 dmx[26]=255;
				  //------------------------ 
				  dmx[27]=jas;		//1x reflektor
				  dmx[28]=jas;
				  dmx[29]=0;     
    			  dmx[30]=0;      
    			  dmx[31]=0;       
    			  dmx[32]=0;       
    			  dmx[33]=0;       
				  dmx[34]=255;	
				  //------------------------ 
				  dmx[35]=jas;		//2x reflektor
				  dmx[36]=jas;
				  dmx[37]=0;     
    			  dmx[38]=0;      
    			  dmx[39]=0;       
    			  dmx[40]=0;       	
				  //------------------------ 
				 last_push = '5';
				 break;
//-----------------------------------------------------------   
		case '6': dmx[0] = 0;		//pas
				 dmx[1] = 0;
				 dmx[2] = 0;
				 dmx[3] = 42;
    			 dmx[4] = 0;
				 dmx[5] = 0;
    			 dmx[6] = jas;
				 //-----------------------
    			 dmx[7] = 0;	//kruhy
    			 dmx[8] = 0;
    			 dmx[9] = 0;
    			 dmx[10] = 0;
				 //-----------------------
    			 dmx[11]=88;		//polgula
			     dmx[12]=255;
				 dmx[13]=0;     
    			 dmx[14]=0;      
    			 dmx[15]=0;       
    			 dmx[16]=255;       
    			 dmx[17]=0;       
				 dmx[18]=0;
				 //------------------------ 
				 dmx[19]=0;		//reflektory
				 dmx[20]=0;
				 dmx[21]=jas;     
    			 dmx[22]=0;      
    			 dmx[23]=0;       
    			 dmx[24]=0;       
    			 dmx[25]=0;       
				 dmx[26]=255;
				  //------------------------ 
				  dmx[27]=0;		//1x reflektor
				  dmx[28]=0;
				  dmx[29]=jas;     
    			  dmx[30]=0;      
    			  dmx[31]=0;       
    			  dmx[32]=0;       
    			  dmx[33]=0;       
				  dmx[34]=255;	
				  //------------------------ 
				  dmx[35]=0;		//2x reflektor
				  dmx[36]=0;
				  dmx[37]=jas;     
    			  dmx[38]=0;      
    			  dmx[39]=0;       
    			  dmx[40]=0;       
				  //------------------------ 
				 last_push = '6';
				 break;
//-----------------------------------------------------------   
		case '7': dmx[0] = 0;		//pas
				  dmx[1] = 0;
				  dmx[2] = 0;
				  dmx[3] = 50;
    			  dmx[4] = 0;
				  dmx[5] = 0;
    			  dmx[6] = jas;
				  //-----------------------
    			  dmx[7] = 255;	//kruhy
    			  dmx[8] = 0;
    			  dmx[9] = 255;
    			  dmx[10] = 0;
				  //-----------------------
    			  dmx[11]=88;		//polgula
				  dmx[12]=255;
				  dmx[13]=0;     
    			  dmx[14]=255;      
    			  dmx[15]=0;       
    			  dmx[16]=255;       
    			  dmx[17]=0;       
				  dmx[18]=0;
				  //------------------------ 
				  dmx[19]=jas;		//reflektory
				  dmx[20]=0;
				  dmx[21]=jas;     
    			  dmx[22]=0;      
    			  dmx[23]=0;       
    			  dmx[24]=0;       
    			  dmx[25]=0;       
				  dmx[26]=255;
				  //------------------------ 
				  dmx[27]=jas;		//1x reflektor
				  dmx[28]=0;
				  dmx[29]=jas;     
    			  dmx[30]=0;      
    			  dmx[31]=0;       
    			  dmx[32]=0;       
    			  dmx[33]=0;       
				  dmx[34]=255;	
				  //------------------------ 
				  dmx[35]=jas;		//2x reflektor
				  dmx[36]=0;
				  dmx[37]=jas;     
    			  dmx[38]=0;      
    			  dmx[39]=0;       
    			  dmx[40]=0;       	
				  //------------------------ 
				  last_push = '7';
				  break;
//-----------------------------------------------------------  
		case '8': dmx[0] = 0;		//pas
				  dmx[1] = 0;
				  dmx[2] = 0;
				  dmx[3] = 0;
    			  dmx[4] = 0;
				  dmx[5] = 0;
    			  dmx[6] = 0;
						  //-----------------------
    			  dmx[7] = 255;	//kruhy
    			  dmx[8] = 36;
    			  dmx[9] = 122;
    			  dmx[10] = 0;
				  //-----------------------
    			  dmx[11]=0;		//polgula
				  dmx[12]=255;
				  dmx[13]=0;     
    			  dmx[14]=0;      
    			  dmx[15]=0;       
    			  dmx[16]=0;       
    			  dmx[17]=0;       
				  dmx[18]=0;
					//------------------------ 
				  dmx[19]=0;		//reflektory
				  dmx[20]=0;
				  dmx[21]=0;     
    			  dmx[22]=0;      
    			  dmx[23]=0;       
    			  dmx[24]=0;       
    			  dmx[25]=0;       
				  dmx[26]=0;	
				  //------------------------ 
				  dmx[27]=0;		//1x reflektor
				  dmx[28]=0;
				  dmx[29]=0;     
    			  dmx[30]=0;      
    			  dmx[31]=0;       
    			  dmx[32]=0;       
    			  dmx[33]=0;       
				  dmx[34]=0;	
				  //------------------------ 
				  dmx[35]=0;		//2x reflektor
				  dmx[36]=0;
				  dmx[37]=0;     
    			  dmx[38]=0;      
    			  dmx[39]=0;       
    			  dmx[40]=0;    
				  dir8=0;
				  rgb[0]=test;
				  rgb[1]=test;
				  rgb[2]=test;
				  rgb[3] = 0;   	
				  last_push = '8';
				  break;	
//-----------------------------------------------------------  
		case '9': dmx[0] = 0;		//pas
				  dmx[1] = 0;
				  dmx[2] = 0;
				  dmx[3] = 0;
    			  dmx[4] = 0;
				  dmx[5] = 0;
    			  dmx[6] = 0;
				  //-----------------------
    			  dmx[7] = 255;	//kruhy
    			  dmx[8] = 0;
    			  dmx[9] = 255;
    			  dmx[10] = 35;
				  //-----------------------
    			  dmx[11]=0;		//polgula
				  dmx[12]=255;
				  dmx[13]=0;     
    			  dmx[14]=0;      
    			  dmx[15]=0;       
    			  dmx[16]=0;       
    			  dmx[17]=0;       
				  dmx[18]=0;
		//------------------------ 
				  dmx[19]=0;		//reflektory
				  dmx[20]=0;
				  dmx[21]=0;     
    			  dmx[22]=0;      
    			  dmx[23]=0;       
    			  dmx[24]=0;       
    			  dmx[25]=0;       
				  dmx[26]=0;	
				  //------------------------ 
				  dmx[27]=0;		//1x reflektor
				  dmx[28]=0;
				  dmx[29]=0;     
    			  dmx[30]=0;      
    			  dmx[31]=0;       
    			  dmx[32]=0;       
    			  dmx[33]=0;       
				  dmx[34]=0;	
				  //------------------------ 
				  dmx[35]=0;		//2x reflektor
				  dmx[36]=0;
				  dmx[37]=0;     
    			  dmx[38]=0;      
    			  dmx[39]=0;       
    			  dmx[40]=0;  
				  dir8=0;
				  rgb[0]=test;
				  rgb[1]=test;
				  rgb[2]=test;
				  rgb[3] = 0;   
				  last_push = '9';	break;
//-----------------------------------------------------------	  	
		case '0': dmx[0] = 0;		//pas
				  dmx[1] = 0;
				  dmx[2] = 0;
				  dmx[3] = 0;
    			  dmx[4] = 0;
				  dmx[5] = 0;
    			  dmx[6] = 0;
						  //-----------------------
    			  dmx[7] = 255;	//kruhy
    			  dmx[8] = 36;
    			  dmx[9] = 31;
    			  dmx[10] = 0;
				  //-----------------------
    			  dmx[11]=0;		//polgula
				  dmx[12]=255;
				  dmx[13]=0;     
    			  dmx[14]=0;      
    			  dmx[15]=0;       
    			  dmx[16]=0;       
    			  dmx[17]=0;       
				  dmx[18]=0;
				//------------------------ 
				  dmx[19]=0;		//reflektory
				  dmx[20]=0;
				  dmx[21]=0;     
    			  dmx[22]=0;      
    			  dmx[23]=0;       
    			  dmx[24]=0;       
    			  dmx[25]=0;       
				  dmx[26]=0;	
				  //------------------------ 
				  dmx[27]=0;		//1x reflektor
				  dmx[28]=0;
				  dmx[29]=0;     
    			  dmx[30]=0;      
    			  dmx[31]=0;       
    			  dmx[32]=0;       
    			  dmx[33]=0;       
				  dmx[34]=0;	
				  //------------------------ 
				  dmx[35]=0;		//2x reflektor
				  dmx[36]=0;
				  dmx[37]=0;     
    			  dmx[38]=0;      
    			  dmx[39]=0;       
    			  dmx[40]=0;  
				  rgb[0]=test;
				  rgb[1]=test;
				  rgb[2]=test;
				  rgb[3] = 0;   
				  dir8=0;
				  last_push = '0';	break;	
//-----------------------------------------------------------  
		case '_':for(por=0;por<27;por++) dmx[por]=0;
				 for(por=35;por<41;por++) dmx[por]=0;
				 last_push = '_';	break;
//-----------------------------------------------------------  
		case 'O': if (jas==255)	jas=30;
				  else          jas=255;
				  _delay_ms(500);
				  break;		
//-----------------------------------------------------------  
	}
		if(last_push == '8') {por1hod = 15;}
		else if(last_push == '9') {por1hod = 7;}
		else{	por1hod = 3;}
	if(last_push == '8' || last_push == '9' || last_push == '0'){
		if (por1>=por1hod){
			if(dir8==0){
				  dmx[0] += rgb[0] ;		//pas
				  dmx[1] += rgb[1];
				  dmx[2] += rgb[2];
				  dmx[3] = 0;
    			  dmx[4] = 0;
				  dmx[5] = 0;
				  dmx[6] = 255;
				  //------------------------
				  dmx[14]+=rgb[0];      
    			  dmx[15]+=rgb[1];       
    			  dmx[16]+=rgb[2];       
    			  dmx[17]+=((rgb[0]*rgb[1]*rgb[2])/4);   
				  //----------------- 
				  dmx[19]+=rgb[0];		//reflektory
				  dmx[20]+=rgb[1];
				  dmx[21]+=rgb[2]; 
				  dmx[22]+=((rgb[0]*rgb[1]*rgb[2])/4);  
    			  dmx[23]=0;       
    			  dmx[24]=0;       
    			  dmx[25]=0;       
				  dmx[26]=0; 
				  //--------------------
				  dmx[27]+=rgb[0];		//1x reflektor
				  dmx[28]+=rgb[1];
				  dmx[29]+=rgb[2];     
    			  dmx[30]+=((rgb[0]*rgb[1]*rgb[2])/4);
				  dmx[31]=0;       
    			  dmx[32]=0;       
    			  dmx[33]=0;       
				  dmx[34]=0;
				  //---------
				  dmx[35]+=rgb[0];		//2x reflektor
				  dmx[36]+=rgb[1];
				  dmx[37]+=rgb[2];
				  dmx[38]=0;      
    			  dmx[39]=0;       
    			  dmx[40]=0;    
				  rgb[3]+=test;
			}
			else{
				if((dmx[0] > 0 || dmx[1] > 0 || dmx[2] > 0) && rgb[3]<230 ){
				  dmx[0] -= rgb[0];		//pas
				  dmx[1] -= rgb[1];
				  dmx[2] -= rgb[2];	  
				  }
				  dmx[3] = 0;
    			  dmx[4] = 0;
				  dmx[5] = 0;
    			  dmx[6] = 255;
				  //------------------------
				  dmx[14]-=rgb[0];      
    			  dmx[15]-=rgb[1];       
    			  dmx[16]-=rgb[2];       
    			  dmx[17]-=((rgb[0]*rgb[1]*rgb[2])/4);  
				  //------------------------ 
				  dmx[19]-=rgb[0];		//reflektory
				  dmx[20]-=rgb[1];
				  dmx[21]-=rgb[2]; 
				  dmx[22]-=((rgb[0]*rgb[1]*rgb[2])/4);      
    			  dmx[23]=0;       
    			  dmx[24]=0;       
    			  dmx[25]=0;       
				  dmx[26]=0; 
				  //--------------------
				  dmx[27]-=rgb[0];		//1x reflektor
				  dmx[28]-=rgb[1];
				  dmx[29]-=rgb[2];     
    			  dmx[30]-=((rgb[0]*rgb[1]*rgb[2])/4);
				  dmx[31]=0;       
    			  dmx[32]=0;       
    			  dmx[33]=0;       
				  dmx[34]=0;
				  //---------
				  dmx[35]-=rgb[0];		//2x reflektor
				  dmx[36]-=rgb[1];
				  dmx[37]-=rgb[2];
				  dmx[38]=0;      
    			  dmx[39]=0;       
    			  dmx[40]=0;    
				  rgb[3]-=test;
			}
			if(rgb[3]>=254){ dir8=1;}
			else if(rgb[3] <= 0){ 
				dir8=0;
				dmx[0] = 0;		//pas
				  dmx[1] = 0;
				  dmx[2] = 0;
				  dmx[3] = 0;
    			  dmx[4] = 0;
				  dmx[5] = 0;
    			  dmx[6] = 0;
				if(rgb[0] == test && rgb[1] == 0 && rgb[2] == 0){
					rgb[0] = test;
					rgb[1] = test;
					rgb[2] = 0;

				}
				else if(rgb[0] == test && rgb[1] == test && rgb[2] == 0){
					rgb[0] = 0;
					rgb[1] = test;
					rgb[2] = 0;
				}
				else if(rgb[0] == 0 && rgb[1] == test && rgb[2] == 0){
					rgb[0] = 0;
					rgb[1] = test;
					rgb[2] = test;
				}
				else if(rgb[0] == 0 && rgb[1] == test && rgb[2] == test){
					rgb[0] = test;
					rgb[1] = 0;
					rgb[2] = test;
				}
				else if(rgb[0] == test && rgb[1] == 0 && rgb[2] == test){
					rgb[0] = 0;
					rgb[1] = 0;
					rgb[2] = test;
				}
				else if(rgb[0] == 0 && rgb[1] == 0 && rgb[2] == test){
					rgb[0] = test;
					rgb[1] = test;
					rgb[2] = test;
				}
				else if(rgb[0] == test && rgb[1] == test && rgb[2] == test){
					rgb[0] = test;
					rgb[1] = 0;
					rgb[2] = 0;
				}
			}
			por1=0;
		}
		else{ por1++;}
	}
	if ((last_push >= '3' && last_push <= '8')){
		if(por == 200){ 
			if (dir == 0){
				if (dmx[11]<100)	dmx[11]+=1;
    			else dir =1;
			}
			else{ 
				if (dmx[11]>0)	dmx[11]-=1;
    			else dir=0;
			}
			por = 0;
		}
		else por++;
	}
	else if ((last_push == '9' || last_push == '0')){
		if(por >= 20){ 
			if (dir == 0){
				if (dmx[11]<100)	dmx[11]+=6;
    			else dir =1;
			}
			else{ 
				if (dmx[11]>0)	dmx[11]-=6;
    			else dir=0;
			}
			por = 0;
		}
		else por++;
	}
	else if(last_push == '2'){
		if(por > 30){ 
			if (dir == 0){
 				  dmx[0] = 255;		//pas
				  dmx[1] = 255;
				  dmx[2] = 255;
				  dmx[3] = 0;
    			  dmx[4] = 0;
				  dmx[5] = 0;
    			  dmx[6] = 255;
				  //-----------------------
				  dmx[7] = 255;	//kruhy
    			  dmx[8] = 0;
    			  dmx[9] = 255;
    			  dmx[10] = 0;
				  //-----------------------
    			  dmx[11]=0;		//polgula
				  dmx[12]=255;
				  dmx[13]=0;     
    			  dmx[14]=255;      
    			  dmx[15]=255;       
    			  dmx[16]=255;       
    			  dmx[17]=255;       
				  dmx[18]=0;
				  //------------------------ 
				  dmx[19]=255;		//reflektory
				  dmx[20]=255;
				  dmx[21]=255;     
    			  dmx[22]=255;      
    			  dmx[23]=0;       
    			  dmx[24]=0;       
    			  dmx[25]=0;       
				  dmx[26]=0;	
				  //------------------------ 
				  dmx[27]=255;		//1x reflektor
				  dmx[28]=255;
				  dmx[29]=255;     
    			  dmx[30]=255;      
    			  dmx[31]=0;       
    			  dmx[32]=0;       
    			  dmx[33]=0;       
				  dmx[34]=0;	
				  //------------------------ 
				  dmx[35]=255;		//2x reflektor
				  dmx[36]=255;
				  dmx[37]=255;     
    			  dmx[38]=0;      
    			  dmx[39]=0;       
    			  dmx[40]=0;       	
				  //------------------------ 
    			dir =1;
			}
			else{ 
				for(por=0;por<41;por++) dmx[por]=0;
				dir = 0;
			}
			por = 0;
		}
		else por++;
	
	}
	sendDMX(dmx,41);	
}



return 0;
}
