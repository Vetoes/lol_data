#include "mainwindow.h"
#include "Champions.h"
#include <fstream>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <stdexcept>
#include <vector>

std::vector<Champions> champions;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // 중앙 위젯 설정
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // 레이아웃 설정
    QVBoxLayout *layout = new QVBoxLayout(centralWidget); // 검색창 생성
    searchBox = new QLineEdit(this);
    searchBox->setPlaceholderText("챔피언 검색...");
    layout->addWidget(searchBox);
    
    // 챔피언 리스트 생성
    championList = new QListWidget(this);
    layout->addWidget(championList);
    
    // 스탯 표시 라벨
    statsLabel = new QLabel(this);
    statsLabel->setWordWrap(true);
    layout->addWidget(statsLabel);
    
    // JSON 데이터 로드
    std::ifstream file("14_23_lol.json");
    if(!file.is_open()){
    throw std::runtime_error ("Could not open JSON file");
  }
  json data = json::parse(file);
  champions = Champions::load_champions(data);
    
    // 챔피언 리스트 초기화
    for (const auto& champion : champions) {
        championList->addItem(QString::fromStdString(champion.name));
    }

    
    // 시그널/슬롯 연결
    connect(searchBox, &QLineEdit::textChanged, 
            this, &MainWindow::onSearchTextChanged);
    connect(championList, &QListWidget::itemClicked, 
            this, &MainWindow::onChampionSelected);
    
    // 윈도우 크기 설정
    resize(400, 600);
}

void MainWindow::onSearchTextChanged(const QString &text) {
    championList->clear();
    for (const auto& champion : champions) {
        QString championName = QString::fromStdString(champion.name);
        if (championName.contains(text, Qt::CaseInsensitive)) {
            championList->addItem(championName);
        }
    }
}

void MainWindow::onChampionSelected(QListWidgetItem *item) {
    QString selectedName = item->text();
    for (const auto& champion : champions) {
        if (champion.name == selectedName.toStdString()) {
            statsLabel->setText(QString::fromStdString(
                "Stats for " + champion.name + ":\n" + 
                champion.stats.dump(2)
            ));
            break;
        }
    }
}
