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
    QRect borders(0, 0, width() - 1, height() - 1); // borders of the universe
    QColor gridColor = m_masterColor; // color of the grid
    gridColor.setAlpha(10); // must be lighter than main color
    p.setPen(gridColor);
    double cellWidth = floor(double(width()) / universeSizeX) + 1;
    double cellHeight = floor(double(height()) / universeSizeY) + 1;

    for (unsigned k = 0; k < width(); k += cellWidth) {
        p.drawLine(int(k), 0, int(k), height());
    }

    for (unsigned k = 0; k < height(); k += cellHeight) {
        p.drawLine(0, int(k), width(), int(k));
    }
    p.drawRect(borders);
}

void GameWidget::paintUniverse(QPainter &p) {
    int max_value = -1;
    int min_value = 1e9;
    for (unsigned int i = 0; i < universeSizeY; i++) {
        for (unsigned int j = 0; j < universeSizeX; j++) {
            if (value[i * universeSizeX + j] < min_value) {
                min_value = value[i * universeSizeX + j];
            }
            if (value[i * universeSizeX + j] > max_value) {
                max_value = value[i * universeSizeX + j];
            }
        }
    }
    double cellWidth = floor(double(width()) / universeSizeX) + 1;
    double cellHeight = floor(double(height()) / universeSizeY) + 1;
    for (unsigned int i = 0; i < universeSizeY; i++) {
        for (unsigned int j = 0; j < universeSizeX; j++) {
            unsigned int index = i * universeSizeX + j;
            if (universe[index] ==
                true) { // if there is any sense to paint it
                double left = double(cellWidth * j); // margin from left
                double top = double(cellHeight * i); // margin from top
                QRectF R(left, top, double(cellWidth), double(cellHeight));

                QColor masterColor = getMasterColor();
                int red = masterColor.red();
                int green = masterColor.green();
                int blue = masterColor.blue();

                int diff = max_value - min_value;

                if (diff > 0) {

                    if (elapsedTime < 5) {
                        neighbourhood(i, j);
                    }

                    int palette = limit(diff, 0, 255);

                    double ratio1 = double(value[index] - min_value) / diff;
                    double ratio2 = powerValue[index] / 8. / max_value * 4;
                    double ratio3 = power[index] / 8. * 4;

                    int r = int(palette * limit(ratio1, 0., 1.));
                    int g = int(palette * limit(ratio2, 0., 1.));
                    int b = int(palette * limit(ratio3, 0., 1.));

                    red = limit(limit(palette, red, 255) - r, 0, 255);
                    green = limit(limit(palette, green, 255) - g, 0, 255);
                    blue = limit(limit(palette, blue, 255) - b, 0, 255);
                }

                QColor color = QColor(red, green, blue);

                p.fillRect(R, QBrush(color)); // fill cell with brush of main color
            }
        }
    }
}
