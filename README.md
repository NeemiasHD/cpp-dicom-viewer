# 🩻 C++ DICOM Viewer

Um visualizador de imagens médicas de alta performance desenvolvido em **C++17** utilizando o framework **Qt 6** e a biblioteca **DCMTK** (DICOM Toolkit).

![Project Status](https://img.shields.io/badge/status-active-success.svg)
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Qt](https://img.shields.io/badge/Qt-6.0%2B-green.svg)

## 🚀 Funcionalidades

Este projeto resolve desafios comuns no processamento de imagens médicas:

* **Leitura Robusta:** Suporte a arquivos DICOM brutos e comprimidos (JPEG/RLE) via codecs registrados.
* **Metadados:** Extração e formatação automática de tags DICOM (Nome, ID, Modalidade, Data, Equipamento).
* **Renderização Precisa:**
    * Correção de alinhamento de memória (*stride/padding*) para evitar distorções diagonais.
    * Aplicação automática de **Brilho/Contraste** baseada nos presets do exame.
* **Interface Responsiva:** O visualizador mantém o *Aspect Ratio* correto e se adapta ao redimensionamento da janela.

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C++ (Standard 17)
* **GUI:** Qt 6 (Widgets Module)
* **Biblioteca DICOM:** DCMTK 3.7.0
* **Build System:** CMake & Ninja/MinGW


## ⚙️ Como Executar projeto através do Qt 6

### Pré-requisitos
* [Qt 6](https://www.qt.io/development/download-qt-installer-oss) instalado.
* Biblioteca DCMTK compilada e linkada corretamente.
* Compilador MinGW 64-bit ou MSVC.

### Execução pelo Qt 6 (Windows)
1.  Clone o repositório.
2.  Abra o projeto na IDE Qt 6.
3.  Configure o caminho do DCMTK no `CMakeLists.txt`.


![Config caminho do DCMTK](./assets/alterar-caminho-dcmtk.png)


4.  Compile em modo **Release**.


![Config caminho do DCMTK](./assets/compilar-modo-release.png)



## ⚙️ Execução pelo executável presente no repositório

1. Clone o repositório.
2. Abra a pasta "Executável"


![Config caminho do DCMTK](./assets/pasta-executavel.png)


3. Execute o arquivo "DicomViewer.exe"


![Config caminho do DCMTK](./assets/executavel.png)

   
  

