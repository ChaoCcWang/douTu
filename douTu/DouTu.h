//
// Created by cc on 2020/6/15.
//

#ifndef DOUTU_DOUTU_H
#define DOUTU_DOUTU_H

#include <QDialog>
#include <vector>

class QTableWidget;
class DouTu : public QDialog {
    Q_OBJECT
public:
    explicit DouTu(QWidget* parent = nullptr);

private:
    void initUi();
    void showEmoji(const QVector<QPair<QString, QString>>&);

private:
    QTableWidget *_wgt{};
    std::vector<QWidget*> _cells;
};


#endif //DOUTU_DOUTU_H
