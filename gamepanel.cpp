#include "gamepanel.h"


gamepanel::gamepanel(void){
	red=0;blue=0;green=0;
	cnt=0;num=0;flg=0;wait=0;wait2=0;flg2=0;

	hBack =LoadGraph("pic/back32.png");
	hBack2=LoadGraph("pic/back3_2.png");
	
	font = "font/Cultstup.ttf";
	if (AddFontResourceEx(font, FR_PRIVATE, NULL) > 0);
	else MessageBox(NULL,"ÉtÉHÉìÉgì«çûé∏îs","",MB_OK);
	
}


gamepanel::~gamepanel(void){
}


void gamepanel::run(KeyManager* key){

	if(MODE=='w'){
		filewrite();
		flg=4;
	}
	else{
		if(flg==0){
			fileread();
			max_check();
			flg=1;
		}
		if(flg==1){
			cnt++;
			wait2++;
			if(cnt%4==0){
				do{
					num=GetRand(STUDENT_MAX-1);
					red=GetRand(150);
					green=GetRand(150);
					blue=GetRand(150);
				}while(dat[1][num]!=0);
			}

			if(CheckHitKeyAll()!=0 && wait2>50)flg=2;

		}

		if(flg==2){
			dat[1][num]=1;
			if((wait++)>100){
				if(CheckHitKeyAll()!=0)flg=3;
			}
		}
		if(flg==3){
			save();
			flg=4;
		}
	}
}

void gamepanel::draw(){

	DrawGraph(0,0,hBack,true);
	if((wait>100 && flg==2) || (wait2>50 && flg==1))DrawGraph(0,0,hBack2,true);

	if(OUT_MODE==1){
		ChangeFont("Cultural Stupidity");
		SetFontSize(30);
		ChangeFontType( DX_FONTTYPE_ANTIALIASING );
		DrawString(25,240,"Group of ",GetColor(0,0,0),true);
		if(max==0)DrawFormatString(480,370,GetColor(229,255,236),"%02dst",max+1);
		else if(max==1)DrawFormatString(480,370,GetColor(229,255,236),"%02dnd",max+1);
		else if(max==2)DrawFormatString(480,370,GetColor(229,255,236),"%02drd",max+1);
		else DrawFormatString(480,370,GetColor(229,255,236),"%02dth",max+1);
	}

	SetFontSize(120);
	SetFontThickness(8);
	ChangeFontType( DX_FONTTYPE_ANTIALIASING );
	
	if(flg2==0){
		ChangeFont("Cultural Stupidity");
		if(OUT_MODE==0)DrawFormatString(220,180,GetColor(red,green,blue),"%d",dat[0][num]);
		else DrawFormatString(250,180,GetColor(red,green,blue),"%d",(dat[0][num]/GROUP_MAX)+1/*,(dat[0][num]%GROUP_MAX)+1*/);
	}else if(flg2==1){
		ChangeFont("ÇlÇr ÉSÉVÉbÉN");
		DrawFormatString(220,180,GetColor(red,green,blue),"ñûé∫",dat[0][num]);
	}
}

void gamepanel::fileread(){
	if((fp=fopen("dat/dat.dat","r"))==NULL)exit(1);
	for(int i=0;i<STUDENT_MAX;i++){
		fscanf(fp,"%d %d",&dat[0][i],&dat[1][i]);
	}
	fclose(fp);
}

void gamepanel::filewrite(){

	if((fp=fopen("dat/dat.dat","w"))==NULL)exit(1);

	for(int i=0;i<STUDENT_MAX;i++){
		fprintf(fp,"%d 0\n",i+1);
	}
	
	fclose(fp);
}

bool gamepanel::isEnd(){
	if(flg==4)return true;
	else return false;
}

void gamepanel::init(){
	cnt=0;num=0;flg=0;wait=0;wait2=0;flg2=0;
}

void gamepanel::save(){
	if((fp=fopen("dat/dat.dat","w"))==NULL)exit(1);
	for(int i=0;i<STUDENT_MAX;i++){
		if(i==num)fprintf(fp,"%d %d\n",i+1,max+1);
		else fprintf(fp,"%d %d\n",i+1,dat[1][i]);
	}
	fclose(fp);
}


void gamepanel::rest_check(){
	for(int i=0;i<STUDENT_MAX;i++){
		if(dat[1][i]==0)return;
		else flg2=1;
	}
}


void gamepanel::max_check(){
	max=dat[1][0];
	for(int i=1;i<STUDENT_MAX;i++){
		if(dat[1][i]>=max)max=dat[1][i];
	}
}