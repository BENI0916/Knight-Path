#include "lib/player_move3D.h"
#include "lib/var.h"
#include "lib/output_img.h"
#include "lib/initialization.h"
#include "lib/effect.h"
#include "lib/event.h"
#include "lib/bebao.h"
#include "lib/status.h"
#include "lib/shop.h"

#include <iostream>
#include <string>
using namespace std;

extern PIMAGE bg,screen;
extern int player_walk_cnt3D,bgX,bgY, inFight, isNext,key,esc,fade,metEvent,inBp,bp[3][bpL],fOn,inMaz;
extern Human player;
extern char BgName[50];
int speed = 10;
int fps = 5;
int table[] = {0,-1,0,1};
unsigned int treasurePlace = random(6);
int open = 1;

void nextOrback() {
    int mX, mY;
    PIMAGE buttom = newimage();
    PIMAGE blk = newimage();
    getimage(blk,"images\\bg\\black.png",0,0);
    getimage(buttom, "images\\menu\\nextorhome.png",0,0);
    for(;is_run();delay_fps(60)) {
        cleardevice();
        putimage(0, 0, screen);
        putimage_alphablend(NULL,blk,0,0,0xC0,0,0,wid,hih);
        putimage_withalpha(NULL,buttom,351,400);
        mousepos(&mX,&mY);
	    if((mX >= 350 && mX <= 540) && (mY >= 400 && mY <= 480) && keystate(key_mouse_l)) {
            //回家
            flushmouse();
            sprintf(BgName,"%s","images\\bg\\home2.png");
            bgX=20;
            bgY=-20;
            loadBG(BgName,1587/2,1300/2);
            mciSendString (TEXT("stop bgm"), NULL,0,NULL);
            mciSendString (TEXT("close bgm"), NULL,0,NULL);
            mciSendString (TEXT("open audio\\bgm\\home.mp3 alias bgm"), NULL,0,NULL);
	    	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
            fadeOut();
            fade = 1;
            inMaz = 0;
            break;
	    }
        if((mX >= 740 && mX <= 930) && (mY >= 400 && mY <= 480) && keystate(key_mouse_l)) {
		    //下一層
            mciSendString (TEXT("stop bgm"), NULL,0,NULL);
            mciSendString (TEXT("close bgm"), NULL,0,NULL);
            flushmouse();
            open = 1;//寶箱未開
            unsigned int cavenum = random(3);
            sprintf(BgName,"images\\bg\\cave0%u.png", cavenum + 1);
            //寶箱圖
            PIMAGE treasure = newimage();
            getimage(treasure,"images\\3D\\obj\\treasure.png");
            //傳送門圖
            PIMAGE img = newimage();
            PIMAGE msk = newimage();
            getimage(img,"images\\3D\\obj\\door_img.png");
            getimage(msk,"images\\3D\\obj\\door_msk.png");
            if(cavenum == 0) {
                mciSendString (TEXT("open audio\\bgm\\cave01.mp3 alias bgm"), NULL,0,NULL);
	    	    mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
                loadBG(BgName, 1463*1.3, 1957*1.3);
                if(random(2)) {
                    bgX = -1383;
                    bgY = -2737;
                } else {
                    bgX = -197;
                    bgY = -747;
                }
                //圖一寶箱、傳送門bg位置
                int place[6][2]={{720,217},{1308,514},{251,1137},{1309,1129},{100,1723},{1112,1722}};
                treasurePlace = random(6);
                putimage(bg, place[treasurePlace][0]*1.3, place[treasurePlace][1]*1.3, treasure, SRCCOPY);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, msk, NOTSRCERASE);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, img, SRCINVERT);
            }
            if(cavenum == 1) {
                mciSendString (TEXT("open audio\\bgm\\cave02.mp3 alias bgm"), NULL,0,NULL);
	    	    mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
                loadBG(BgName, 1480*1.3, 1374*1.3);
                if(random(2)) {
                    bgX = -1153;
                    bgY = -377;
                } else {
                    bgX = -113;
                    bgY = -1157;
                }
                int place[6][2]={{122,226},{1347,271},{1130,520},{713,818},{270,1114},{1210,1130}};
                treasurePlace = random(6);
                putimage(bg, place[treasurePlace][0]*1.3, place[treasurePlace][1]*1.3, treasure, SRCCOPY);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, msk, NOTSRCERASE);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, img, SRCINVERT);
            }
            if(cavenum == 2) {
                mciSendString (TEXT("open audio\\bgm\\cave03.mp3 alias bgm"), NULL,0,NULL);
	    	    mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
                loadBG(BgName, 1935*1.3, 1744*1.3);
                if(random(2)) {
                    bgX = -2343;
                    bgY = -1317;
                } else {
                    bgX = -893;
                    bgY = -2017;
                }
                int place[6][2]={{97,174},{1213,485},{1480,1041},{83,1039},{1389,1628},{1788,1618}};
                treasurePlace = random(6);
                putimage(bg, place[treasurePlace][0]*1.3, place[treasurePlace][1]*1.3, treasure, SRCCOPY);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, msk, NOTSRCERASE);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, img, SRCINVERT);
            }
            delimage(treasure);
            delimage(img);
            delimage(msk);

            fadeOut();
            fade = 1;
		    break;
	    }     
    }
    delimage(buttom);
    delimage(blk);
}

void openbox() {
    int mX, mY;
    PIMAGE UI = newimage();
    PIMAGE blk = newimage();
    PIMAGE gray = newimage();
    PIMAGE money = newimage();
    getimage(money,"images\\3D\\drop\\0.png",0,0);
    getimage(gray,"images\\menu\\bk.png",0,0);
    getimage(blk,"images\\bg\\black.png",0,0);
    getimage(UI, "images\\menu\\openboxUI.png",0,0);
    int dropmoney = random(20)*100+100;
    bp[0][0]+= dropmoney;
    for(;is_run();delay_fps(60)) {
        cleardevice();
        putimage(0, 0, screen);
        putimage_alphablend(NULL,blk,0,0,0xC0,0,0,wid,hih);
        putimage_withalpha(NULL,UI,0,0);
        putimage_alphablend(NULL,gray,190,300-6,0x70,0,0,442,45);
        putimage_withalpha(NULL,money,226-getwidth(money)/2,300);
        xyprintf(411,300+getheight(money)/2,"%s",dropName[0]);
        xyprintf(596,300+getheight(money)/2,"%d",dropmoney);
        mousepos(&mX,&mY);
        if((mX >= 1000 && mX <= 1187) && (mY >= 649 && mY <= 702) && keystate(key_mouse_l)) {
            flushmouse();
            break;
        }
    }
    delimage(UI);
    delimage(blk);
    delimage(gray);
    delimage(money);
}

void itemwall(int xl, int xr, int yu, int yd) {
    if(bgX <= xl && bgX >= xr && bgY <= yu &bgY >= yd) {
    switch (key) {
		case 97:  // 輸入 a 
			bgX -= speed;
			break;
        case 100:  // 輸入 d
			bgX += speed;
			break;
        case 115:  // 輸入 s
			bgY += speed;
			break;
        case 119:  // 輸入 w
			bgY -= speed;
			break;
		default:
			break;
    }}
}

void keyListener() {
    fOn=0;
    if (kbhit()) { // 檢測是否有鍵盤輸入 
		key = getch();
        //printf("%d\n",key);
    }
    switch (key) {
		case 97:  // 輸入 a 
			player.output_idx = 30 + table[player_walk_cnt3D++/fps];
		    bgX += speed;
            if (player_walk_cnt3D/fps==4) player_walk_cnt3D = 0; 
            if (inMaz) metEvent = event();
			break;
        case 100:  // 輸入 d
			player.output_idx = 36 + table[player_walk_cnt3D++/fps];
		    bgX -= speed;
            if (player_walk_cnt3D/fps==4) player_walk_cnt3D = 0;
            if (inMaz) metEvent = event();
			break;
        case 115:  // 輸入 s
			player.output_idx = 33 + table[player_walk_cnt3D++/fps];
		    bgY -= speed;
            if (player_walk_cnt3D/fps==4) player_walk_cnt3D = 0;
            if (inMaz) metEvent = event();
			break;
        case 119:  // 輸入 w
			player.output_idx = 27 + table[player_walk_cnt3D++/fps];
		    bgY += speed;
            if (player_walk_cnt3D/fps==4) player_walk_cnt3D = 0;
            if (inMaz) metEvent = event();
			break;
        case 101:
            inBp = 1;
            break;
        case key_esc:
            esc = 1;
            break; 
		default:
			break;
	}
    //home2樓設定
    if (strcmp(BgName, "images\\bg\\home2.png")==0) {
        //地圖牆
        if(bgX  <-360) bgX = -360;
        if(bgX > 375) bgX = 375;
        if(bgY  <-192) bgY = -192;
        if(bgY > 285) bgY = 285;
        //物件牆
        itemwall(75,-39, 180, 54); //電視
        itemwall(370,237,105,-48); //床
        //itemwall(375,313,250,210);
        //itemwall(370,211,98,-75);
        itemwall(-78,-168,285,174);
        itemwall(-78,-246,219,180);
        //背景轉換
        if(bgX >= -214 && bgX <= -169&& bgY >=220 && bgY <=285) {
            sprintf(BgName,"%s","images\\bg\\home1.png");
            loadBG(BgName,1587/2,1300/2); //讀取背景
        }
    }
    //home1樓設定
    else if (strcmp(BgName, "images\\bg\\home1.png")==0) {
        //地圖牆
        if(bgX  <-360) bgX = -360;
        if(bgX > 375) bgX = 375;
        if(bgY  <-192) bgY = -192;
        if(bgY > 285) bgY = 285;
        //物件牆
        itemwall(-231,-360,225,192);
        itemwall(189,-360,-177,-220);
        itemwall(375,273,-177,-220);
        itemwall(375,165,285,264);
        itemwall(135,24,285,264);
        itemwall(138,-30,174,27); //桌子
        //背景轉換
        //上樓
        if(bgX <= -270 && bgY >=228 && bgY <=285) {
            sprintf(BgName,"%s","images\\bg\\home2.png");
            loadBG(BgName,1587/2,1300/2);
        }
        //出門
        if(bgX >= 190 && bgX <= 270 && bgY <= -186) {
            sprintf(BgName,"%s","images\\bg\\village.png");
            loadBG(BgName, 1859*1.2, 1542*1.3);
            bgX = -483;
            bgY = -1077;
            mciSendString (TEXT("stop bgm"), NULL,0,NULL);
            mciSendString (TEXT("close bgm"), NULL,0,NULL);
            mciSendString (TEXT("open audio\\bgm\\village.mp3 alias bgm"), NULL,0,NULL);
	    	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
            fadeOut();
            fade = 1;
        }
    }
    //村莊設定
    else if (strcmp(BgName, "images\\bg\\village.png")==0) {
        //地圖牆
        if(bgX < -2028) bgX = -2028;
        if(bgX > -126) bgX = -126;
        if(bgY < -2016) bgY = -2016;
        if(bgY > -288) bgY = -288;
        //物件牆
        itemwall(-333,-816,-603,-1035); //左上房
        itemwall(-252,-333,-903,-1035); //郵箱
        itemwall(-1137,-1623,-603,-1035); //右上房
        itemwall(-1056,-1137,-903,-1035); //郵箱
        itemwall(-1047,-1713,-1179,-1614); //右下房
        itemwall(-126,-1011,-288,-483); //左上樹
        itemwall(-1122,-1854,-288,-483); //右上樹
        itemwall(-1839,-1959,-480,-1068);
        itemwall(-1839,-1959,-1269,-2016); //右下樹
        itemwall(-126,-912,-1908,-2016); //左下湖
        itemwall(-330,-819,-1326,-1419); //左下柵欄
        itemwall(-336,-456,-1617,-1710);
        itemwall(-1044,-1629,-1809,-1905); //右下柵欄
        //背景轉換
        //回家
        if(bgX >= -510 && bgX <=-459 && bgY >=-1041 && bgY <=-1023) {
            bgX=219;
            bgY=-171;
            sprintf(BgName,"%s","images\\bg\\home1.png");
            loadBG(BgName,1587/2,1300/2);
            mciSendString (TEXT("stop bgm"), NULL,0,NULL);
            mciSendString (TEXT("close bgm"), NULL,0,NULL);
            mciSendString (TEXT("open audio\\bgm\\home.mp3 alias bgm"), NULL,0,NULL);
	    	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
            fadeOut();
            fade = 1;
        }
        //雜貨店
        if(bgX >= -1323 && bgX <=-1263 && bgY >=-1041 && bgY <=-1023) {
            bgX=269;
            bgY=-171;
            sprintf(BgName,"%s","images\\bg\\shop.png");
            loadBG(BgName,1587/2,1300/2);
            mciSendString (TEXT("stop bgm"), NULL,0,NULL);
            mciSendString (TEXT("close bgm"), NULL,0,NULL);
            mciSendString (TEXT("open audio\\bgm\\shop.mp3 alias bgm"), NULL,0,NULL);
	    	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
            fadeOut();
            fade = 1;
        }
        //賭場
        /*if(bgX >= -1404 && bgX <=-1359 && bgY >=-1620 && bgY <=-1596) {
            bgX=219;
            bgY=-171;
            sprintf(BgName,"%s","images\\bg\\home1.png");
            loadBG(BgName,1587/2,1300/2);
            mciSendString (TEXT("stop villagemusic"), NULL,0,NULL);
            mciSendString (TEXT("close villagemusic"), NULL,0,NULL);
            mciSendString (TEXT("open audio\\bgm\\shop.mp3 alias shopmusic"), NULL,0,NULL);
	    	mciSendString (TEXT("play shopmusic repeat"), NULL,0,NULL);
            fadeOut();
            fade = 1;
        }*/
        //村子右邊BOSS傳送門
        if(bgX < -1956) {
            inFight=1;
            isNext = 1;
            player.x = 20;
	        player.y = hih * 0.6;
            player.output_idx = 0;
	        player.high = 66;
	        player.width = 76;
            bgX = -1940;
            sprintf(BgName,"%s","images\\bg\\back_ground_01.png");
            loadBG(BgName);
            mciSendString (TEXT("stop bgm"), NULL,0,NULL);
            mciSendString (TEXT("close bgm"), NULL,0,NULL);
        }
        //村子上方刷怪副本
        if(bgY > -300 && bgX > -1123 && bgX < -1003) {
            mciSendString (TEXT("stop bgm"), NULL,0,NULL);
            mciSendString (TEXT("close bgm"), NULL,0,NULL);
            //還沒做完
            open = 1;//寶箱未開
            unsigned int cavenum = random(3);
            sprintf(BgName,"images\\bg\\cave0%u.png", cavenum + 1);
            //寶箱圖
            PIMAGE treasure = newimage();
            getimage(treasure,"images\\3D\\obj\\treasure.png");
            //傳送門圖
            PIMAGE img = newimage();
            PIMAGE msk = newimage();
            getimage(img,"images\\3D\\obj\\door_img.png");
            getimage(msk,"images\\3D\\obj\\door_msk.png");
            if(cavenum == 0) {
                mciSendString (TEXT("open audio\\bgm\\cave01.mp3 alias bgm"), NULL,0,NULL);
	    	    mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
                loadBG(BgName, 1463*1.3, 1957*1.3);
                if(random(2)) {
                    bgX = -1383;
                    bgY = -2737;
                } else {
                    bgX = -197;
                    bgY = -747;
                }
                //圖一寶箱、傳送門bg位置
                int place[6][2]={{720,217},{1308,514},{251,1137},{1309,1129},{100,1723},{1112,1722}};
                treasurePlace = random(6);
                putimage(bg, place[treasurePlace][0]*1.3, place[treasurePlace][1]*1.3, treasure, SRCCOPY);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, msk, NOTSRCERASE);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, img, SRCINVERT);
            }
            if(cavenum == 1) {
                mciSendString (TEXT("open audio\\bgm\\cave02.mp3 alias bgm"), NULL,0,NULL);
	    	    mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
                loadBG(BgName, 1480*1.3, 1374*1.3);
                if(random(2)) {
                    bgX = -1153;
                    bgY = -377;
                } else {
                    bgX = -113;
                    bgY = -1157;
                }
                int place[6][2]={{122,226},{1347,271},{1130,520},{713,818},{270,1114},{1210,1130}};
                treasurePlace = random(6);
                putimage(bg, place[treasurePlace][0]*1.3, place[treasurePlace][1]*1.3, treasure, SRCCOPY);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, msk, NOTSRCERASE);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, img, SRCINVERT);
            }
            if(cavenum == 2) {
                mciSendString (TEXT("open audio\\bgm\\cave03.mp3 alias bgm"), NULL,0,NULL);
	    	    mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
                loadBG(BgName, 1935*1.3, 1744*1.3);
                if(random(2)) {
                    bgX = -2343;
                    bgY = -1317;
                } else {
                    bgX = -893;
                    bgY = -2017;
                }
                int place[6][2]={{97,174},{1213,485},{1480,1041},{83,1039},{1389,1628},{1788,1618}};
                treasurePlace = random(6);
                putimage(bg, place[treasurePlace][0]*1.3, place[treasurePlace][1]*1.3, treasure, SRCCOPY);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, msk, NOTSRCERASE);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, img, SRCINVERT);
            }
            delimage(treasure);
            delimage(img);
            delimage(msk);

            inMaz = 1;
            fadeOut();
            fade = 1;
        }
    }
    //雜貨店
    else if (strcmp(BgName, "images\\bg\\shop.png")==0) {
        //地圖牆
        if(bgX  <-360) bgX = -360;
        if(bgX > 375) bgX = 375;
        if(bgY  <-192) bgY = -192;
        if(bgY > 285) bgY = 285;
        //物件牆
        itemwall(375,115,285,149);
        itemwall(115,55,285,245);
        itemwall(-5,-360,285,85);
        itemwall(-230,-360,-52,-192);
        //買東西
        if (bgX<-170 && bgX>-230 && bgY<85 && bgY>28) {
            fOn = 1;
            if(key==102){
                shop();
            }
        }
        //出門
        if(bgX > 189 && bgX < 339 && bgY <= -186) {
            sprintf(BgName,"%s","images\\bg\\village.png");
            loadBG(BgName, 1859*1.2, 1542*1.3);
            bgX = -1293;
            bgY = -1077;
            mciSendString (TEXT("stop bgm"), NULL,0,NULL);
            mciSendString (TEXT("close bgm"), NULL,0,NULL);
            mciSendString (TEXT("open audio\\bgm\\village.mp3 alias bgm"), NULL,0,NULL);
	    	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
            fadeOut();
            fade = 1;
        }
    }
    //副本
    else if (strcmp(BgName, "images\\bg\\cave01.png")==0) {
        //地圖牆
        if(bgX < -1443) bgX = -1443;
        if(bgX > 237) bgX = 237;
        if(bgY < -2767) bgY = -2767;
        if(bgY > -647) bgY = -647;
        //物件牆
        itemwall(-673,-793,-647,-817);
        itemwall(237,-273,-817,-1027);
        itemwall(-413,-1053,-817,-1027);
        itemwall(-1193,-1443,-817,-1027);
        itemwall(237,-533,-1207,-1417);
        itemwall(-673,-1053,-1207,-1417);
        itemwall(-1193,-1443,-1207,-1417);
        itemwall(-1393,-1443,-1417,-1477);
        itemwall(-933,-1053,-1207,-1807);
        itemwall(107,-1053,-1597,-1807);
        itemwall(-153,-273,-1597,-2767);
        itemwall(-1193,-1313,-1597,-2197);
        itemwall(107,-273,-1987,-2197);
        itemwall(-413,-1053,-1987,-2197);
        itemwall(-1193,-1443,-1987,-2197);
        itemwall(-933,-1053,-1987,-2587);
        itemwall(237,-13,-2377,-2587);
        itemwall(-413,-1313,-2377,-2587);
        itemwall(-1193,-1313,-2377,-2767);
        itemwall(-33,-143,-1877,-1977);
        //寶箱牆
        int loc[6][4]={{-583,-643,-707,-747},{-1343,-1413,-1087,-1127},{27,-23,-1897,-1947},{-1343,-1413,-1887,-1927},{227,157,-2657,-2697},{-1093,-1153,-2657,-2697}};
        if(open) itemwall(loc[treasurePlace][0],loc[treasurePlace][1],loc[treasurePlace][2],loc[treasurePlace][3]);
        if(open && bgX<loc[treasurePlace][0]+20 && bgX>loc[treasurePlace][1]-20 && bgY<loc[treasurePlace][2]+20 && bgY>loc[treasurePlace][3]-20) {
            fOn = 1;
            if(key == 102){
                //獎勵畫面
                openbox();
                open = 0;//寶箱已開
                loadBG(BgName, 1463*1.3, 1957*1.3);
                int place[6][2]={{720,217},{1308,514},{251,1137},{1309,1129},{100,1723},{1112,1722}};
                PIMAGE img = newimage();
                PIMAGE msk = newimage();
                getimage(img,"images\\3D\\obj\\door_img.png");
                getimage(msk,"images\\3D\\obj\\door_msk.png");
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, msk, NOTSRCERASE);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, img, SRCINVERT);
                delimage(img);
                delimage(msk);
            }
        }
        //背景轉換
        if(bgX<loc[5-treasurePlace][0]+3 && bgX>loc[5-treasurePlace][1]-3 && bgY<loc[5-treasurePlace][2]+3 && bgY>loc[5-treasurePlace][3]-3) {
            nextOrback();
        }
    }
    else if (strcmp(BgName, "images\\bg\\cave02.png")==0) {
        //地圖牆
        if(bgX < -1473) bgX = -1473;
        if(bgX > 217) bgX = 217;
        if(bgY < -1607) bgY = -1607;
        if(bgY > -277) bgY = -277;
        //物件牆
        itemwall(-1223,-1333,-277,-647);
        itemwall(-1373,-1473,-277,-367);
        itemwall(217,-553,-447,-647);
        itemwall(-703,-1333,-447,-647);
        itemwall(-443,-553,-657,-1037);
        itemwall(-963,-1073,-657,-1037);
        itemwall(77,-293,-837,-1037);
        itemwall(-443,-813,-837,-1037);
        itemwall(-963,-1333,-837,-1037);
        itemwall(77,-33,-1037,-1427);
        itemwall(-703,-813,-1037,-1427);
        itemwall(77,-293,-1227,-1427);
        itemwall(-443,-813,-1227,-1427);
        itemwall(-963,-1473,-1227,-1427);
        itemwall(-183,-293,-1227,-1607);
        itemwall(-663,-693,-1117,-1217);
        itemwall(-123,-173,-1437,-1607);
        itemwall(-63,-173,-1557,-1607);
        itemwall(-1313,-1473,-1497,-1607);//地洞
        //寶箱牆
        int loc[6][4]={{187,117,-337,-377},{-1403,-1473,-397,-437},{-1123,-1193,-717,-757},{-583,-653,-1107,-1147},{-3,-73,-1497,-1527},{-1233,-1293,-1507,-1547}};
        if(open) itemwall(loc[treasurePlace][0],loc[treasurePlace][1],loc[treasurePlace][2],loc[treasurePlace][3]);
        if(open && bgX<loc[treasurePlace][0]+20 && bgX>loc[treasurePlace][1]-20 && bgY<loc[treasurePlace][2]+20 && bgY>loc[treasurePlace][3]-20) {
            fOn = 1;
            if(key == 102) {
                //獎勵畫面
                openbox();
                open = 0;//寶箱已開
                loadBG(BgName, 1480*1.3, 1374*1.3);
                int place[6][2]={{122,226},{1347,271},{1130,520},{713,818},{270,1114},{1210,1130}};
                PIMAGE img = newimage();
                PIMAGE msk = newimage();
                getimage(img,"images\\3D\\obj\\door_img.png");
                getimage(msk,"images\\3D\\obj\\door_msk.png");
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, msk, NOTSRCERASE);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, img, SRCINVERT);
                delimage(img);
                delimage(msk);
            }
        }
        //背景轉換
        if(bgX<loc[5-treasurePlace][0]+3 && bgX>loc[5-treasurePlace][1]-3 && bgY<loc[5-treasurePlace][2]+3 && bgY>loc[5-treasurePlace][3]-3) {
            nextOrback();
        }
    }
    else if (strcmp(BgName, "images\\bg\\cave03.png")==0) {
        //地圖牆
        if(bgX < -2403) bgX = -2403;
        if(bgX > -33) bgX = -33;
        if(bgY < -2497) bgY = -2497;
        if(bgY > -457) bgY = -457;
        //物件牆
        itemwall(-33,-523,-637,-877);
        itemwall(-663,-1333,-637,-877);
        itemwall(-1423,-1763,-637,-877);
        itemwall(-1853,-2263,-637,-877);
        itemwall(-1163,-1333,-637,-1257);
        itemwall(-1603,-1863,-707,-1257);
        itemwall(-163,-1773,-1017,-1257);
        itemwall(-1913,-2403,-1017,-1257);
        itemwall(-663,-833,-1017,-1937);
        itemwall(-33,-523,-1387,-1627);
        itemwall(-913,-1573,-1387,-1627);
        itemwall(-1663,-2403,-1387,-1627);
        itemwall(-1413,-1573,-1387,-1937);
        itemwall(-33,-273,-1697,-1937);
        itemwall(-413,-1023,-1697,-1937);
        itemwall(-1103,-1573,-1697,-1937);
        itemwall(-1663,-2333,-1697,-1937);
        itemwall(-163,-2023,-2077,-2317);
        itemwall(-2163,-2403,-2077,-2317);
        itemwall(-1853,-2023,-2077,-2497);
        itemwall(-693,-803,-457,-507);//河
        itemwall(-693,-803,-567,-627);
        itemwall(-1343,-1383,-707,-797);
        itemwall(-1753,-1863,-1317,-1687);
        itemwall(-1613,-1653,-1837,-1917);
        itemwall(-1003,-1113,-1837,-2377);
        itemwall(-1003,-1113,-2437,-2497);
        //寶箱牆
        int loc[6][4]={{-73,-143,-507,-547},{-1523,-1593,-917,-947},{-1873,-1943,-1637,-1677},{-53,-123,-1637,-1667},{-1753,-1823,-2397,-2437},{-2273,-2343,-2387,-2427}};
        if(open) itemwall(loc[treasurePlace][0],loc[treasurePlace][1],loc[treasurePlace][2],loc[treasurePlace][3]);
        if(open && bgX<loc[treasurePlace][0]+20 && bgX>loc[treasurePlace][1]-20 && bgY<loc[treasurePlace][2]+20 && bgY>loc[treasurePlace][3]-20) {
            fOn = 1;
            if(key == 102){
                //獎勵畫面
                openbox();
                open = 0;//寶箱已開
                loadBG(BgName, 1935*1.3, 1744*1.3);
                int place[6][2]={{97,174},{1213,485},{1480,1041},{83,1039},{1389,1628},{1788,1618}};
                PIMAGE img = newimage();
                PIMAGE msk = newimage();
                getimage(img,"images\\3D\\obj\\door_img.png");
                getimage(msk,"images\\3D\\obj\\door_msk.png");
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, msk, NOTSRCERASE);
                putimage(bg, place[5-treasurePlace][0]*1.3, place[5-treasurePlace][1]*1.3, img, SRCINVERT);
                delimage(img);
                delimage(msk);
            }
        }
        //背景轉換
        if(bgX<loc[5-treasurePlace][0]+3 && bgX>loc[5-treasurePlace][1]-3 && bgY<loc[5-treasurePlace][2]+3 && bgY>loc[5-treasurePlace][3]-3) {
            nextOrback();
        }
    }
    //cout << bgX << " " << bgY << "       \r";

    key = 0;
}

//g++ *.cpp -o test.exe -lgraphics64 -luuid -lmsimg32 -lgdi32 -limm32 -lole32 -loleaut32 -lwinmm -lgdiplus