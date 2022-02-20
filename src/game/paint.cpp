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
    double cellWidth =
            floor(double(width()) /
                  int(universeSizeX) + 1); // width of the widget / number of cells at one row
    for (double k = 0; k < width(); k += cellWidth) {
        p.drawLine(int(k), 0, int(k), height());
    }
    double cellHeight = floor(double(
            height() /
            int(universeSizeY)) + 1); // height of the widget / number of cells at one row
    for (double k = 0; k < height(); k += cellHeight) {
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
    double cellWidth = floor(double(width()) / int(universeSizeX) + 1);
    double cellHeight = floor(double(height() / int(universeSizeY)) + 1);
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

                int fark = max_value - min_value;

                if (fark > 0) {

                    if (elapsedTime < 5) {
                        neighbourhood(i, j);
                    }

                    int palet = limit(fark, 0, 255);

                    double oran = double(value[index] - min_value) / fark;
                    double oran2 = powerValue[index] / 8. / max_value * 4;
                    double oran3 = power[index] / 8. * 4;

                    int r = int(palet * limit(oran, 0., 1.));
                    int g = int(palet * limit(oran2, 0., 1.));
                    int b = int(palet * limit(oran3, 0., 1.));

                    red = limit(limit(palet, red, 255) - r, 0, 255);
                    green = limit(limit(palet, green, 255) - g, 0, 255);
                    blue = limit(limit(palet, blue, 255) - b, 0, 255);
                }

                QColor color = QColor(red, green, blue);

                p.fillRect(R, QBrush(color)); // fill cell with brush of main color
            }
        }
    }
}
