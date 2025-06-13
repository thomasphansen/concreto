#include <QApplication>
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../concreto.h"

class ConcretoWindow : public QWidget {
public:
    ConcretoWindow(QWidget *parent = nullptr) : QWidget(parent) {
        auto *layout = new QVBoxLayout(this);
        auto *form = new QFormLayout();
        ratioEdit = new QLineEdit();
        granulEdit = new QLineEdit();
        volumeEdit = new QLineEdit();
        form->addRow("Traço (a-b-c):", ratioEdit);
        form->addRow("Granulometria (mm):", granulEdit);
        form->addRow("Volume (m³):", volumeEdit);
        layout->addLayout(form);
        auto *btnLayout = new QHBoxLayout();
        runButton = new QPushButton("Run");
        closeButton = new QPushButton("Close");
        btnLayout->addWidget(runButton);
        btnLayout->addWidget(closeButton);
        layout->addLayout(btnLayout);
        resultArea = new QTextEdit();
        resultArea->setReadOnly(true);
        layout->addWidget(resultArea);

        connect(runButton, &QPushButton::clicked, this, &ConcretoWindow::run);
        connect(closeButton, &QPushButton::clicked, qApp, &QApplication::quit);
        setWindowTitle("Concreto");
    }

private slots:
    void run() {
        MixRatio ratio;
        if (!parse_ratio(ratioEdit->text().toUtf8().constData(), &ratio)) {
            resultArea->setText("Formato de traço inválido.");
            return;
        }
        bool ok1, ok2;
        double granul = granulEdit->text().toDouble(&ok1);
        double volume = volumeEdit->text().toDouble(&ok2);
        if (!ok1 || !ok2 || granul <= 0 || volume <= 0) {
            resultArea->setText("Valores inválidos.");
            return;
        }
        Volumes vols = compute_volumes(volume, ratio);
        Masses masses = compute_masses(vols, granul);
        double water_vol = masses.water / DENSITY_WATER;

        QString res;
        res += QString("Cimento: %1 kg (%2 L)\n").arg(masses.cement, 0, 'f', 2).arg(vols.cement * 1000.0, 0, 'f', 2);
        res += QString("Agua: %1 kg (%2 L)\n").arg(masses.water, 0, 'f', 2).arg(water_vol * 1000.0, 0, 'f', 2);
        res += QString("Areia: %1 kg (%2 L)\n").arg(masses.sand, 0, 'f', 2).arg(vols.sand * 1000.0, 0, 'f', 2);
        res += QString("Brita: %1 kg (%2 L)\n").arg(masses.gravel, 0, 'f', 2).arg(vols.gravel * 1000.0, 0, 'f', 2);
        resultArea->setText(res);
    }

private:
    QLineEdit *ratioEdit;
    QLineEdit *granulEdit;
    QLineEdit *volumeEdit;
    QPushButton *runButton;
    QPushButton *closeButton;
    QTextEdit *resultArea;
};


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ConcretoWindow w;
    w.show();
    return app.exec();
}
