#include "lib/var.h"
#include "lib/status.h"

extern PIMAGE bloodLine, blood[], dropImg[];
extern int bp[3][bpL];

void playerBlood(int hp,int fhp) {
    putimage_withalpha(NULL,blood[hp*20/fhp],20,680);
    putimage_withalpha(NULL,bloodLine,20,680);
    xyprintf(170,689,"%d/%d",hp,fhp);
}

void monBlood(int hp,int fhp) {
    putimage_withalpha(NULL,blood[hp*20/fhp],960,680);
    putimage_withalpha(NULL,bloodLine,960,680);
    xyprintf(1110,689,"%d/%d",hp,fhp);
}

void putMoney() {
    putimage_withalpha(NULL,dropImg[0],30,640);
    xyprintf(100,664," x %d",bp[0][0]);
}