#include "include/mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::selectMasterColor() {
    QColor color = QColorDialog::getColor(currentColor, this, tr("Select color of figures"));
    if (!color.isValid())
        return;
    currentColor = color;
    game->setMasterColor(color);
    QPixmap icon(16, 16);
    icon.fill(color);
    ui->colorButton->setIcon(QIcon(icon));
}
