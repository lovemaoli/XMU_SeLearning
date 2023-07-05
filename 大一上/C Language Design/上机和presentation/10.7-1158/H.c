#include <stdio.h>
#include <string.h>
int m_year_flag,m_year,m_month,m_day; 
int ruen(int year){
	if(year % 4 != 0){
    	return 0;
	}
	if(year % 100 == 0 && year % 400 != 0){
    	return 0;
	}
	return 1;
}
int is_Japan_ruen(){
	if(m_year_flag == 1){
		return ruen(1867 + m_year);
	}
	if(m_year_flag == 2){
		return ruen(1911 + m_year);
	}
	if(m_year_flag == 3){
		return ruen(1925 + m_year);
	}
	if(m_year_flag == 4){
		return ruen(1988 + m_year);
	}
	if(m_year_flag == 5){
		return ruen(2018 + m_year);
	}
}
void next_day(){
	switch(m_month){
		case 1:
			if(m_day!=31){
				m_day++;
			}else{
				m_month=2;
				m_day = 1;
			}
			check_next_year();
			break;
		case 2:
			if(is_Japan_ruen()){
				if(m_day!=28)m_day++;
				else{
					m_month=3;
					m_day=1;
				}
			}else{
				if(m_day!=29)m_day++;
				else{
					m_month=3;
					m_day=1; 
				}
			} 
			break;
		case 3:
			if(m_day!=31){
				m_day++;
			}else{
				m_month=4;
				m_day = 1;
			}
			break;
		case 4:
			if(m_day!=30){
				m_day++;
			}else{
				m_month=5;
				m_day = 1;
			}
			check_next_year();
			break;
		case 5:
			if(m_day!=31){
				m_day++;
			}else{
				m_month=6;
				m_day = 1;
			}
			break;
		case 6:
			if(m_day!=30){
				m_day++;
			}else{
				m_month=7;
				m_day = 1;
			}
			break;
		case 7:
			if(m_day!=31){
				m_day++;
			}else{
				m_month=8;
				m_day = 1;
			}
			check_next_year();
			break;
		case 8:
			if(m_day!=31){
				m_day++;
			}else{
				m_month=9;
				m_day = 1;
			}
			break;
		case 9:
			if(m_day!=30){
				m_day++;
			}else{
				m_month=10;
				m_day = 1;
			}
			break;
		case 10:
			if(m_day!=31){
				m_day++;
			}else{
				m_month=11;
				m_day = 1;
			}
			break;
		case 11:
			if(m_day!=30){
				m_day++;
			}else{
				m_month=12;
				m_day = 1;
			}
			break;
		case 12:
			if(m_day!=31){
				m_day++;
			}
			check_next_year();
			break;
	}
}
void check_next_year(){
	if(m_month==12&&m_day==31){
		m_month=1;
		m_day=1;
		m_year++;
		return;
	}
	if(m_year_flag==1&&m_year==45&&m_month==7&&m_day==30){
		m_year_flag++;m_year=1;
	}
	if(m_year_flag==2&&m_year==15&&m_month==12&&m_day==25){
		m_year_flag++;m_year=1;
	}
	if(m_year_flag==3&&m_year==64&&m_month==1&&m_day==7){
		m_year_flag++;m_year=1;
	}
	if(m_year_flag==4&&m_year==31&&m_month==4&&m_day==30){
		m_year_flag++;m_year=1;
	}
}
int main(void)
{
	char c[20];
    while(scanf("%s",&c)!=EOF){ 
    	if(c[0]=='M')m_year_flag=1;
    	if(c[0]=='T')m_year_flag=2;
    	if(c[0]=='S')m_year_flag=3;
    	if(c[0]=='H')m_year_flag=4;
    	if(c[0]=='R')m_year_flag=5;
    	int point = 1;
    	m_year=0; 
    	while(c[point]!='/'){
    		m_year *= 10;
			m_year = m_year + c[point] - '0';
			point++;  
		}
		point++;
		m_month=0;
		while(c[point]!='/'){
    		m_month *= 10;
			m_month = m_month + c[point] - '0';
			point++;  
		}
		point++;
		m_day=0;
		while(c[point]!='\0'){
    		m_day *= 10;
			m_day = m_day + c[point] - '0';
			point++;  
		}
		scanf("%d",&point);
		while(point){
			point--;
			next_day();
		}
		if(m_year_flag==1)printf("M");
		if(m_year_flag==2)printf("T");
		if(m_year_flag==3)printf("S");
		if(m_year_flag==4)printf("H");
		if(m_year_flag==5)printf("R");
		printf("%d/%d/%d\n",m_year,m_month,m_day); 
	} 
	return 0;
}
