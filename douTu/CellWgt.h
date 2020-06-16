//
// Created by cc on 2020/6/15.
//

#ifndef DOUTU_CELLWGT_H
#define DOUTU_CELLWGT_H

#include <QFrame>

class CellWgt : public QFrame{
    Q_OBJECT
public:
    explicit CellWgt(const QString& url, const QString& toolTip, QWidget* parent = nullptr);

Q_SIGNALS:
    void sgSetImage(const QString&);

protected:
    void paintEvent(QPaintEvent* e) override;
    void setCellImage(const QString&);
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override ;
    void mouseMoveEvent(QMouseEvent *e) override;

private:
    QMovie* _mov{};
    QString _path;

    bool    _press{};
};


#endif //DOUTU_CELLWGT_H
