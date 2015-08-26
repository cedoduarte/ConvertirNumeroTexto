#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->numeroDoubleSpinBox->setMaximum(99999.99);
    ui->numeroDoubleSpinBox->setMinimum(0.0);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString valorCadena = ui->numeroDoubleSpinBox->text();
    QString valorEntero = valorCadena.mid(0, valorCadena.indexOf('.'));
    QString valorDecimal = valorCadena.mid(valorCadena.indexOf('.') + 1);
    QString resultado = QString("Son: ")
            + convierteNumeroTexto(valorEntero.toInt()) + " " + valorDecimal
            + "/MN";
    ui->textoLineEdit->setText(resultado);
}

QString Widget::convierteNumeroTexto(int valor)
{
    QString unidades[] = { "cero", "un", "dos", "tres", "cuatro", "cinco",
                           "seis", "siete", "ocho", "nueve" };
    QString teenagers[] = { "diez", "once", "doce", "trece", "catorce",
                            "quince", "dieciseis", "diecisiete", "dieciocho",
                            "diecinueve" };
    QString decenas[] = { "veinte", "treinta", "cuarenta", "cincuenta",
                          "sesenta", "setenta", "ochenta", "noventa" };
    QString centenas[] = { "cien", "doscientos", "trescientos", "cuatrocientos",
                           "quinientos", "seiscientos", "setecientos",
                           "ochocientos", "novecientos" };
    QString valorCadena;
    QString resultado;
    int cantidadCifras;
    int ultimaCifra;
    int indice1;
    int indice2;
    valorCadena = QString::number(valor);
    cantidadCifras = valorCadena.size();
    resultado = "sin resultado";
    ultimaCifra = cantidadCifras - 1;
    switch (cantidadCifras) {
    case 1:
        resultado = unidades[valorCadena[0].digitValue()];
        break;
    case 2:
        // teenagers
        if (valor >= 10 && valor < 20) {
            indice1 = valorCadena[ultimaCifra].digitValue();
            resultado = teenagers[indice1];
        } else {
            // múltiplos de 10
            if (valor % 10 == 0) {
                indice1 = valorCadena[0].digitValue() - 2;
                resultado = decenas[indice1];
            } else {
                // adultos jóvenes
                if (valor > 20 && valor < 30) {
                    indice1 = valorCadena[ultimaCifra].digitValue();
                    resultado = QString("veinti") + unidades[indice1];
                } else {
                    // adultos ya grandes
                    indice1 = valorCadena[0].digitValue() - 2;
                    indice2 = valorCadena[ultimaCifra].digitValue();
                    resultado = decenas[indice1] + " y " + unidades[indice2];
                }
            }
        }
        break;
    case 3:
        // múltiplos de 100
        if (valor % 100 == 0) {
            indice1 = valorCadena[0].digitValue() - 1;
            resultado = centenas[indice1];
        } else {
            // cualquier número de 3 cifras
            indice1 = valorCadena[0].digitValue() - 1;
            resultado = (centenas[indice1] == "cien"
                         ? "ciento" : centenas[indice1])
                    + " " + convierteNumeroTexto(valorCadena.mid(1).toInt());
        }
        break;
    case 4:
        // múltiplos de mil
        if (valor % 1000 == 0) {
            indice1 = valorCadena[0].digitValue();
            resultado = unidades[indice1] + " mil";
        } else {
            // cualquier número de 4 cifras
            indice1 = valorCadena[0].digitValue();
            resultado = unidades[indice1] + " mil"
                    + " " + convierteNumeroTexto(valorCadena.mid(1).toInt());
        }
        break;
    case 5:
        // teenagers
        if (valor >= 10000 && valor < 20000) {
            indice1 = valorCadena[1].digitValue();
            resultado = teenagers[indice1] + " mil "
                    + convierteNumeroTexto(valorCadena.mid(2).toInt());
            if (resultado.endsWith("cero")) {
                resultado = resultado.mid(0, resultado.size()
                                          - QString("cero").size() - 1);
            }
        } else {
            // múltiplos de 10000
            if (valor % 10000 == 0) {
                indice1 = valorCadena[0].digitValue() - 2;
                resultado = decenas[indice1] + " mil";
            } else {
                resultado = convierteNumeroTexto(valorCadena.mid(0, 2).toInt())
                        + " mil "
                        + convierteNumeroTexto(valorCadena.mid(2).toInt());
            }
            if (resultado.endsWith("cero")) {
                resultado = resultado.mid(0, resultado.size()
                                          - QString("cero").size() - 1);
            }
        }
        break;
    }
    return resultado;
}
