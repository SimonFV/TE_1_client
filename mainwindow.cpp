#include "mainwindow.h"
#include "ui_mainwindow.h"

string run_client();
string send_ver(string first, string last);
void close_sock();

/**
 * @brief Constructor de la clase MainWindow
 * @param parent Puntero padre
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    /**
     * @note Conecta el cliente con el servidor, lo que devuelve un string
     * con la informacion del grafo
     */
    string grafo_s = run_client();
    ui->setupUi(this);
    if(grafo_s!="error"){
        generate_Graph(grafo_s);
    }else{
        QLabel *error = new QLabel("Error al conectarse con el servidor");
        ui->grid_graph->addWidget(error, 0,0,1,1);
    }
}

/**
 * @brief Destructor de la clase MainWindow
 */
MainWindow::~MainWindow(){
    delete ui;
}

/**
 * @brief Genera el grafo en el grid principal con la informacion del servidor
 * @param g Puntero del grafo al que se desea aplicar el algoritmo
 * @param start_s Nombre del vertice inicial
 * @param end_s Nombre del vertice final
 */
void MainWindow::generate_Graph(string data){
    /**
     * @note Configuracion del color de los labels del grid del grafo
     */
    QPalette palette_ver;
    QPalette palette_arist;
    palette_ver.setColor(QPalette::Window, Qt::black);
    palette_ver.setColor(QPalette::WindowText, Qt::white);
    palette_arist.setColor(QPalette::Window, Qt::gray);
    palette_arist.setColor(QPalette::WindowText, Qt::black);

    /**
     * @note Se extrae el numero de vertices
     */
    string num_ver = "";
    int ver_totales;
    int i = 0;
    while(data[i]!=','){
        num_ver = num_ver + data[i];
        i++;
    }
    ver_totales = stoi(num_ver);
    i++;

    /**
     * @note Genera los labels de los vertices
     */
    string label_name;
    for(int j=0; j<ver_totales; j++){
        label_name = "";
        while(data[i]!=','){
            label_name = label_name + data[i];
            i++;
        }
        QLabel *ver_label = new QLabel(QString::fromStdString(label_name));
        ui->grid_graph->addWidget(ver_label, j+1,0,1,1);
        ver_label->setAutoFillBackground(true);
        ver_label->setPalette(palette_ver);
        ver_label->setAlignment(Qt::AlignCenter);
        QLabel *ver_label2 = new QLabel(QString::fromStdString(label_name));
        ui->grid_graph->addWidget(ver_label2, 0,j+1,1,1);
        ver_label2->setAutoFillBackground(true);
        ver_label2->setPalette(palette_ver);
        ver_label2->setAlignment(Qt::AlignCenter);
        i++;
    }

    /**
     * @note Genera los labels de las aristas con sus pesos
     */
    string fila_s, colum_s, peso_s;
    int fila, colum;

    while(i<((int)data.size()-4)){
        fila_s = "";
        while(data[i]!=','){
            fila_s = fila_s + data[i];
            i++;
        }
        fila = stoi(fila_s);
        i++;
        colum_s = "";
        while(data[i]!=','){
            colum_s = colum_s + data[i];
            i++;
        }
        colum = stoi(colum_s);
        i++;
        peso_s = "";
        while(data[i]!=','){
            peso_s = peso_s + data[i];
            i++;
        }
        i++;

        QLabel *peso_label = new QLabel(QString::fromStdString(peso_s));
        ui->grid_graph->addWidget(peso_label, fila, colum,1,1);
        peso_label->setAutoFillBackground(true);
        peso_label->setPalette(palette_arist);
        peso_label->setAlignment(Qt::AlignCenter);
    }

}

/**
 * @brief Envia los datos ingresados al servidor al hacer click
 *
 * Despues de enviar los datos, muestra la respuesta en el label inferior,
 * donde se muestra la ruta mas optima de vertice a vertice
 */
void MainWindow::on_send_clicked(){
    QString Qstart = ui->ver1_lineEdit->text();
    QString Qfinal = ui->ver2_lineEdit->text();
    string start, final, path;
    start = Qstart.toStdString();
    final = Qfinal.toStdString();
    path = send_ver(start, final);
    ui->result_label->setText(QString::fromStdString(path));
}

