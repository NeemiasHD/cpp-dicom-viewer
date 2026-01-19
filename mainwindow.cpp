#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/dcdeftag.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "dcmtk/dcmjpeg/djdecode.h"

#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Visualizador DICOM");

    // Registra os codecs de descompressão (necessário para JPEG, RLE...)
    DJDecoderRegistration::registerCodecs();

    // Configurações do Label para comportamento responsivo da imagem
    ui->labelImagem->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->labelImagem->setStyleSheet("background-color: white; color: gray; font-size: 16px; font-weight: bold;");

    // Texto inicial do label
    ui->labelImagem->setText("Selecione uma imagem DICOM");

    //conecta o evento de click do botão à função de carregar o arquivo
    connect(ui->btnAbrir, &QPushButton::clicked, this, &MainWindow::carregarImagem);
}


void MainWindow::carregarImagem()
{
    {
        QString filePath = QFileDialog::getOpenFileName(this, "Selecionar DICOM", "", "DICOM (*.dcm);;All (*)");

        if (filePath.isEmpty()) return;

        DcmFileFormat file;
        if (file.loadFile(filePath.toStdString().c_str()).good()) {

            DcmDataset* dataset = file.getDataset();

            OFString patientName, patientID, birthDate, patientSex, studyDate, studyDesc, modality, manufacturer;

            // Extrai as informações usando as tags padrão do DICOM
            dataset->findAndGetOFString(DCM_PatientName, patientName);
            dataset->findAndGetOFString(DCM_PatientID, patientID);
            dataset->findAndGetOFString(DCM_PatientBirthDate, birthDate);
            dataset->findAndGetOFString(DCM_PatientSex, patientSex);
            dataset->findAndGetOFString(DCM_StudyDate, studyDate);
            dataset->findAndGetOFString(DCM_StudyDescription, studyDesc);
            dataset->findAndGetOFString(DCM_Modality, modality);
            dataset->findAndGetOFString(DCM_Manufacturer, manufacturer);

            // Insere informações extraidas do arquivo na label de Metadata
            QString info = "Nome: " + QString(patientName.c_str()) +
                           "  |  Sexo: " + QString(patientSex.c_str()) +
                           "  |  Modalidade: " + QString(modality.c_str()) +
                           "  |  Descrição: " + QString(studyDesc.c_str()) +
                           "  |  Data: " + QString(studyDate.c_str()) +
                           "  |  Equipamento: " + QString(manufacturer.c_str());

            if (ui->lblMetadata) {
                ui->lblMetadata->setText(info);
            }
        }


        // Renderizando a imagem
        DicomImage *image = new DicomImage(filePath.toStdString().c_str());
        if (image != nullptr && image->getStatus() == EIS_Normal) {

            // Aplica Window/Level (Brilho/Contraste)
            // setWindow(0) tenta usar o preset salvo no arquivo médico.
            // Se falhar, setMinMaxWindow calcula o histograma automático
            if (!image->setWindow(0)) {
                image->setMinMaxWindow();
            }

            unsigned long width = image->getWidth();
            unsigned long height = image->getHeight();
            unsigned long dataSize = image->getOutputDataSize();

            if (dataSize > 0) {
                std::unique_ptr<Uint8[]> pixelData(new Uint8[dataSize]);

                if (image->getOutputData(pixelData.get(), dataSize, 8)) {

                    QImage qImg(pixelData.get(), width, height, width, QImage::Format_Grayscale8);
                    m_pixmapOriginal = QPixmap::fromImage(qImg.copy());
                    atualizarVisualizacao();
                }
            }
        } else {
            QMessageBox::critical(this, "Erro", "Esse arquivo não é do formato dcm.");
        }
        delete image;
    }

}

// Evento de redimensionamento da janela
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    atualizarVisualizacao();
}

// Função que escala e centraliza
void MainWindow::atualizarVisualizacao()
{
    if (m_pixmapOriginal.isNull()) return;

    if (ui->labelImagem) {
        QSize tamanhoDisponivel = ui->labelImagem->size();

        ui->labelImagem->setPixmap(m_pixmapOriginal.scaled(
            tamanhoDisponivel,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));
    }
}



MainWindow::~MainWindow()
{
    DJDecoderRegistration::cleanup();
    delete ui;
}

