#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QPixmap>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    //Função que o Windows chama quando você puxa a borda da janela
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;

    //Variável para guardar a imagem original em alta resolução
    QPixmap m_pixmapOriginal;

    // Função auxiliar que desenha a imagem no tamanho certo
    void atualizarVisualizacao();
    //função para carregar imagem
    void carregarImagem();
};
#endif // MAINWINDOW_H
