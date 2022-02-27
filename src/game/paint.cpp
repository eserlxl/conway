#include "include/gamewidget.h"

void GameWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

void GameWidget::setMasterColor(const QColor &color) {
    m_masterColor = color;
    update();
}

QColor GameWidget::getMasterColor() {
    return m_masterColor;
}

void GameWidget::paintGrid(QPainter &p) {

    unsigned cellWidth = getCellWidth();
    unsigned cellHeight = getCellHeight();

    QRect borders(0, 0, universeSizeX * cellWidth - 1, universeSizeY * cellHeight - 1); // borders of the universe
    QColor gridColor = m_masterColor; // color of the grid
    gridColor.setAlpha(10); // must be lighter than main color
    p.setPen(gridColor);

    for (unsigned k = 0; k < universeSizeX * cellWidth; k += cellWidth) {
        p.drawLine(k, 0, k, universeSizeY * cellHeight);
    }

    for (unsigned k = 0; k < universeSizeY * cellHeight; k += cellHeight) {
        p.drawLine(0, k, universeSizeX * cellWidth, k);
    }
    p.drawRect(borders);
}

void GameWidget::paintUniverse(QPainter &p) {
    int maXValue = -1;
    int minValue = 1e9;

    double meanValue = 0;
    double meanPower = 0;
    double meanPowerValue = 0;
    for (unsigned i = 0; i < universeSizeY; i++) {
        for (unsigned j = 0; j < universeSizeX; j++) {
            unsigned index = i * universeSizeX + j;
            if (value[index] < minValue) {
                minValue = value[index];
            }
            if (value[index] > maXValue) {
                maXValue = value[index];
            }
            meanValue = value[index];
            meanPower += power[index];
            meanPowerValue += powerValue[index];
        }
    }
    meanValue /= max(1., (double) population);
    meanPower /= max(1., (double) population);
    meanPowerValue /= max(1., (double) population);


    unsigned cellWidth = getCellWidth();
    unsigned cellHeight = getCellHeight();
    for (unsigned i = 0; i < universeSizeY; i++) {
        for (unsigned j = 0; j < universeSizeX; j++) {
            unsigned index = i * universeSizeX + j;
            if (universe[index] ==
                true) { // if there is any sense to paint it
                double left = double(cellWidth * j); // margin from left
                double top = double(cellHeight * i); // margin from top
                QRectF R(left, top, double(cellWidth), double(cellHeight));

                QColor masterColor = getMasterColor();
                int red = masterColor.red();
                int green = masterColor.green();
                int blue = masterColor.blue();

                if (elapsedTime < 5) {
                    neighbourhood(i, j);
                }

                double ratio1 = double(value[index]) / max(1., meanValue);
                double ratio2 = double(powerValue[index]) / max(1., meanPowerValue);
                double ratio3 = power[index] / max(1., meanPower);

                int r = int(255 * limit(ratio1, 0., 1.));
                int g = int(255 * limit(ratio2, 0., 1.));
                int b = int(255 * limit(ratio3, 0., 1.));

                red = (256 + red - r) % 256;
                green = (256 + green - g) % 256;
                blue = (256 + blue - b) % 256;

                QColor color = QColor(red, green, blue);

                p.fillRect(R, QBrush(color)); // fill cell with brush of main color
            }
        }
    }
}
