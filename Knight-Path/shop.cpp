#include "lib/var.h"
#include "lib/bebao.h"
#include "lib/status.h"

extern PIMAGE screen, escBG, gray, swordImg[], potionImg[];
extern int bp[3][bpL], bpAmount[0], bpIdx[3][bpL];
int swordPrice[3] = {1000, 10000, 1};
int potionPrice[2] = {10000, 50000};

void shop(){
    int mX, mY;
    PIMAGE Agil = newimage();
    PIMAGE money = newimage();
    PIMAGE shopbuy1 = newimage();
    PIMAGE shopbuy2 = newimage();
    PIMAGE shopsell = newimage();
    PIMAGE confirm = newimage();
    PIMAGE cancel = newimage();
    PIMAGE quantity = newimage();
    PIMAGE choose = newimage();
    getimage(money,"images\\3D\\drop\\0.png",0,0);
    getimage(Agil, "images\\menu\\Agil2.png",0,0);
    getimage(shopbuy1, "images\\menu\\shopbuy1.png",0,0);
    getimage(shopbuy2, "images\\menu\\shopbuy2.png",0,0);
    getimage(shopsell, "images\\menu\\shopsell.png",0,0);
    getimage(confirm, "images\\menu\\confirm.png",0,0);
    getimage(cancel, "images\\menu\\cancel.png",0,0);
    getimage(quantity, "images\\menu\\quantity.png",0,0);
    getimage(choose, "images\\menu\\choose.png",0,0);
    for(;is_run();delay_fps(60)) {
        cleardevice();
        putimage(0, 0, screen);
        putimage_withalpha(NULL,Agil,0,0);
        mousepos(&mX,&mY);
        //按買
        if((mX >= 1003 && mX <= 1261) && (mY >= 463 && mY <= 536) && keystate(key_mouse_l)) {
            int buymode = 1;
            for(;is_run();delay_fps(60)) {
                flushmouse();
                cleardevice();
                putimage(0, 0, screen);
                putimage_alphablend(NULL,escBG,0,0,0xC0,0,0,wid,hih);
                if ((mX >= 1144 && mX <= 1263) && (mY >= 251 && mY <= 361) && keystate(key_mouse_l)) {
                    //武器
                    flushmouse();
                    buymode = 1;
	            }
                if ((mX >= 1144 && mX <= 1263) && (mY >= 362 && mY <= 473) && keystate(key_mouse_l)) {
                    //藥水
                    flushmouse();
                    buymode = 0;
	            }
                if (buymode) {
                    //武器
                    putimage_withalpha(NULL,shopbuy1,0,0);
                    //輸出商品圖片
                    for (int i = 0;i<3;i++) {
                        int x,y;
                        i > 4 ? x = 477 : x = 0;
                        i > 4 ? y = 60*(i-5)+320 : y = 60*i+320;
                        putimage_alphablend(NULL,gray,180+x,y-6,0x70,0,0,442,45);
                        putimage_withalpha(NULL,swordImg[i],216+x-getwidth(swordImg[i])/2,y);
                        xyprintf(401+x,y+getheight(swordImg[i])/2,"%s",swordName[i]);
                        xyprintf(586+x,y+getheight(swordImg[i])/2,"%d",swordPrice[i]);
                    }
                    for(int i=0;i<3;i++){
                        int x,y;
                        i > 4 ? x = 477 : x = 0;
                        i > 4 ? y = 60*(i-5)+320 : y = 60*i+320;
                        if((mX >= 180+x && mX <= 180+x+442) && (mY >= y-6 && mY <= y-6+45) && keystate(key_mouse_l)) {
                            //按商品
                            for(;is_run();delay_fps(60)) {
                                flushmouse();
                                cleardevice();
                                putimage(0, 0, screen);
                                putimage_alphablend(NULL,escBG,0,0,0xC0,0,0,wid,hih);
                                putimage_withalpha(NULL,shopbuy1,0,0);
                                //輸出商品圖片
                                for (int j = 0;j<3;j++) {
                                    int x,y;
                                    j > 4 ? x = 477 : x = 0;
                                    j > 4 ? y = 60*(j-5)+320 : y = 60*j+320;
                                    putimage_alphablend(NULL,gray,180+x,y-6,0x70,0,0,442,45);
                                    putimage_withalpha(NULL,swordImg[j],216+x-getwidth(swordImg[j])/2,y);
                                    xyprintf(401+x,y+getheight(swordImg[j])/2,"%s",swordName[j]);
                                    xyprintf(586+x,y+getheight(swordImg[j])/2,"%d",swordPrice[j]);
                                }
                                putMoney();
                                putimage_withalpha(NULL,cancel,1156,624);
                                putimage_withalpha(NULL,choose,180+x,y-6);
                                putimage_withalpha(NULL,confirm,1156,532);
                                mousepos(&mX,&mY);
                                //按確認
                                if((mX >= 1156 && mX <= 1265) && (mY >= 532 && mY <= 619) && keystate(key_mouse_l)) {
                                    int have=0;
                                    for(;is_run();delay_fps(60)) {
                                        if(keystate(key_mouse_l)==0) break;
                                    }
                                    for (int j = 0;j<bpAmount[1];j++) {
                                        if (bpIdx[1][j]==i) {
                                            have = 1;
                                            break;
                                        }
                                    }
                                    if(have){
                                        //已經有了
                                    }
                                    else if(bp[0][0] >= swordPrice[i] && bpAmount[1] < 10) {
                                        //錢夠
                                        bp[0][0]-= swordPrice[i]; 
                                        //更新背包
                                        updateBp(1,i,-1);
                                    }
                                    else {
                                        //錢不夠
                                    }
                                    break;
                                }
                                //按取消
                                if((mX >= 1156 && mX <= 1265) && (mY >= 624 && mY <= 712) && keystate(key_mouse_l)) {
                                    for(;is_run();delay_fps(60)) {
                                        if(keystate(key_mouse_l)==0) break;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                } else {
                    //藥水
                    putimage_withalpha(NULL,shopbuy2,0,0);
                    //輸出商品圖片
                    for (int i = 0;i<2;i++) {
                        int x,y;
                        i > 4 ? x = 477 : x = 0;
                        i > 4 ? y = 60*(i-5)+320 : y = 60*i+320;
                        putimage_alphablend(NULL,gray,180+x,y-6,0x70,0,0,442,45);
                        putimage_withalpha(NULL,potionImg[i],216+x-getwidth(potionImg[i])/2,y);
                        xyprintf(401+x,y+getheight(potionImg[i])/2,"%s",potionName[i]);
                        xyprintf(586+x,y+getheight(potionImg[i])/2,"%d",potionPrice[i]);
                    }
                    for(int i=0;i<2;i++){
                        int x,y;
                        i > 4 ? x = 477 : x = 0;
                        i > 4 ? y = 60*(i-5)+320 : y = 60*i+320;
                        if((mX >= 180+x && mX <= 180+x+442) && (mY >= y-6 && mY <= y-6+45) && keystate(key_mouse_l)) {
                            //按商品
                            //int num = 0;
                            for(;is_run();delay_fps(60)) {
                                flushmouse();
                                cleardevice();
                                putimage(0, 0, screen);
                                putimage_alphablend(NULL,escBG,0,0,0xC0,0,0,wid,hih);
                                putimage_withalpha(NULL,shopbuy2,0,0);
                                //輸出商品圖片
                                for (int j = 0;j<2;j++) {
                                    int x,y;
                                    j > 4 ? x = 477 : x = 0;
                                    j > 4 ? y = 60*(j-5)+320 : y = 60*j+320;
                                    putimage_alphablend(NULL,gray,180+x,y-6,0x70,0,0,442,45);
                                    putimage_withalpha(NULL,potionImg[j],216+x-getwidth(potionImg[j])/2,y);
                                    xyprintf(401+x,y+getheight(potionImg[j])/2,"%s",potionName[j]);
                                    xyprintf(586+x,y+getheight(potionImg[j])/2,"%d",potionPrice[j]);
                                }
                                putMoney();
                                putimage_withalpha(NULL,cancel,1156,624);
                                putimage_withalpha(NULL,choose,180+x,y-6);
                                putimage_withalpha(NULL,confirm,1156,532);
                                mousepos(&mX,&mY);
                                //按確認
                                if((mX >= 1156 && mX <= 1265) && (mY >= 532 && mY <= 619) && keystate(key_mouse_l)) {
                                    for(;is_run();delay_fps(60)) {
                                        if(keystate(key_mouse_l)==0) break;
                                    }
                                    if(potionPrice[i] < bp[0][0] && bpAmount[2] < 10) {
                                        //錢夠
                                        bp[0][0]-= potionPrice[i]; 
                                        updateBp(2,i,-1);
                                    }
                                    else {
                                        //錢不夠
                                    }
                                    break;
                                }
                                //按取消
                                if((mX >= 1156 && mX <= 1265) && (mY >= 624 && mY <= 712) && keystate(key_mouse_l)) {
                                    for(;is_run();delay_fps(60)) {
                                        if(keystate(key_mouse_l)==0) break;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
                putMoney();
                putimage_withalpha(NULL,cancel,1156,624);
                mousepos(&mX,&mY);
                if ((mX >= 1156 && mX <= 1265) && (mY >= 624 && mY <= 712) && keystate(key_mouse_l)) break; //按取消
            }
            break;
        }
        //按賣
        if((mX >= 1003 && mX <= 1261) && (mY >= 541 && mY <= 614) && keystate(key_mouse_l)) {
            for(;is_run();delay_fps(60)) {
                flushmouse();
                cleardevice();
                putimage(0, 0, screen);
                putimage_alphablend(NULL,escBG,0,0,0xC0,0,0,wid,hih);
                putimage_withalpha(NULL,shopsell,0,0);
                putBpItem(0);
                putMoney();
                putimage_withalpha(NULL,cancel,1156,624);
                mousepos(&mX,&mY);
                if((mX >= 1156 && mX <= 1265) && (mY >= 624 && mY <= 712) && keystate(key_mouse_l)) break; //按取消
                for(int i=0;i<bpAmount[0];i++){
                    int x,y;
                    i > 4 ? x = 477 : x = 0;
                    i > 4 ? y = 60*(i-5)+320 : y = 60*i+320;
                    if((mX >= 180+x && mX <= 180+x+442) && (mY >= y-6 && mY <= y-6+45) && keystate(key_mouse_l)) {
                        //按素材
                        int num = 0;
                        for(;is_run();delay_fps(60)) {
                            flushmouse();
                            cleardevice();
                            putimage(0, 0, screen);
                            putimage_alphablend(NULL,escBG,0,0,0xC0,0,0,wid,hih);
                            putimage_withalpha(NULL,shopsell,0,0);
                            putBpItem(0);
                            putMoney();
                            putimage_withalpha(NULL,cancel,1156,624);
                            putimage_withalpha(NULL,choose,180+x,y-6);
                            putimage_withalpha(NULL,quantity,861,636);
                            putimage_withalpha(NULL,confirm,1156,532);
                            mousepos(&mX,&mY);
                            xyprintf(994,677,"%d",num);
                            //按+
                            if((mX >= 1094 && mX <= 1128) && (mY >= 636 && mY <= 719) && keystate(key_mouse_l)) {
                                for(;is_run();delay_fps(60)) {
                                    if(keystate(key_mouse_l)==0) break;
                                }
                                if(num<bp[0][bpIdx[0][i]]) num++;
                            }
                            //按-
                            if((mX >= 861 && mX <= 896) && (mY >= 636 && mY <= 719) && keystate(key_mouse_l)) {
                                for(;is_run();delay_fps(60)) {
                                    if(keystate(key_mouse_l)==0) break;
                                }
                                if(num>0) num--;
                            }
                            //按確認
                            if((mX >= 1156 && mX <= 1265) && (mY >= 532 && mY <= 619) && keystate(key_mouse_l)) {
                                for(;is_run();delay_fps(60)) {
                                    if(keystate(key_mouse_l)==0) break;
                                }
                                bp[0][0]+=num*1000;
                                bp[0][bpIdx[0][i]]-=num;
                                if(bp[0][bpIdx[0][i]]==0) updateBp(0,bpIdx[0][i],1);
                                break;
                            }
                            //按取消
                            if((mX >= 1156 && mX <= 1265) && (mY >= 624 && mY <= 712) && keystate(key_mouse_l)) {
                                for(;is_run();delay_fps(60)) {
                                    if(keystate(key_mouse_l)==0) break;
                                }
                                break;
                            }
                        }
                    }
                }      
            }
            break;
        }
        //按算了
        if((mX >= 1003 && mX <= 1261) && (mY >= 619 && mY <= 692) && keystate(key_mouse_l)) {
            flushmouse();
            flushkey();
            break;
        }
        
    }
    delimage(Agil);
    delimage(money);
    delimage(shopbuy1);
    delimage(shopbuy2);
    delimage(shopsell);
    delimage(confirm);
    delimage(cancel);
    delimage(quantity);
    flushkey();
}
