#include "include/gamewidget.h"

unsigned int GameWidget::neighbourhood(unsigned int row, unsigned int col) {
    unsigned int neighbour = 0;

    unsigned int index = row * universeSizeX + col;

    power[index] = 0;
    powerValue[index] = 0;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            // Do not process itself
            if (!(i == 0 && j == 0)) {
                if (int(row) + i >= 0 && int(row) + i < int(universeSizeY) && int(col) + j >= 0 &&
                    int(col) + j < int(universeSizeX)) {
                    unsigned int row_ = unsigned(int(row) + i);
                    unsigned int col_ = unsigned(int(col) + j);

                    unsigned int tempIndex = row_ * universeSizeX + col_;
                    power[index] += universe[tempIndex];
                    powerValue[index] += unsigned(value[tempIndex]);

                    neighbour++;
                }
            }
        }
    }

    return neighbour;
}
