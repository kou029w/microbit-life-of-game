#include "MicroBit.h"

MicroBit uBit;
MicroBitImage field("0,1,0,0,0\n0,0,1,1,0\n1,1,0,0,0\n0,0,1,0,0\n0,0,0,0,0\n");
enum Life {DIE = 0, LIVE = 255};

Life deadOrAlive(int x, int y) {
    int survivor = 0;

    for (int row = (y > 0 ? -1 : 0); row <= (y < 4 ? 1 : 0); row++) {
        for (int col = (x > 0 ? -1 : 0); col <= (x < 4 ? 1 : 0); col++) {
            if (col == 0 && row == 0)
                continue;

            if (field.getPixelValue(x + col, y + row))
                survivor++;
        }
    }

    if (field.getPixelValue(x, y)) {
        if (survivor == 2 || survivor == 3)
            return LIVE;
        else
            return DIE;
    } else {
        if (survivor == 3)
            return LIVE;
        else
            return DIE;
    }
}

void fieldUpdate() {
    MicroBitImage nextGeneration(5, 5);

    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            nextGeneration.setPixelValue(x, y, deadOrAlive(x, y));
        }
    }

    field.paste(nextGeneration);
}

void lifeOfGame() {
    while(1) {
        uBit.sleep(1000);
        uBit.display.image.paste(field);
        fieldUpdate();
    }
}

int main() {
    uBit.init();

    while(1)
        lifeOfGame();
}
