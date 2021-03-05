#include <iostream>
#include <string>
#include <cmath>

#define PI 3.14159265

using namespace std;

enum Forma { POLAR, RETANGULAR };

class Complexo
{
  private:
    Forma forma = RETANGULAR;
    double real, imaginario, magnitude, angulo;

  /** Construtores */
  public:
    Complexo()
    {
      real = 0;
      imaginario = 0;
      geraESalvaFormaPolar();
    }

    Complexo(double primeiroParametro, double segundoParametro)
    {
      real = primeiroParametro;
      imaginario = segundoParametro;
      geraESalvaFormaPolar();
    }

    Complexo(Forma formaSelecionada, double primeiroParametro, double segundoParametro)
    {
      if(formaSelecionada == RETANGULAR)
      {
        real = primeiroParametro;
        imaginario = segundoParametro;
        geraESalvaFormaPolar();
      }
      else
      {
        forma = POLAR;
        magnitude = primeiroParametro;
        angulo = segundoParametro;
        geraESalvaFormaRetangular();
      }
    }

  /** Getter e Setter */
  public:
    double getReal() { return real; }

    double getImaginario() { return imaginario; }

    double getMagnitude() { return magnitude; }

    double getAngulo() { return angulo; }

    string getFormaPolar()
    {
      string magnitude = to_string(getMagnitude());
      string angulo = to_string(getAngulo());
      return  magnitude + " L " + angulo ;
    }

    string getFormaRetangular()
    {
      string real = to_string(getReal());
      string imaginario = to_string(getImaginario());
      return real + " + " + (imaginario + "i");
    }

  private:
    void setReal(double real) { this->real = real; }

    void setImaginario(double imaginario) { this->imaginario = imaginario; }

    void setMagnitude(double magnitude) { this->magnitude = magnitude; }

    void setAngulo(double angulo) { this->angulo = angulo; }

  /** Utilizadas no construtor */
  private:
    void geraESalvaFormaPolar()
    {
      double divisaoImagReal = verificaExcecoes(getImaginario()/getReal());
      double angulo = atan(divisaoImagReal)* 180/PI;
      double magnitude = sqrt(pow(getReal(), 2) + pow(getImaginario(), 2));

      setMagnitude(arredondaValor(magnitude));
      setAngulo(arredondaValor(angulo));
    }

    void geraESalvaFormaRetangular()
    {
      double parteReal = getMagnitude() * cos(getAngulo() * 180/PI);
      double parteImaginaria = getMagnitude() * sin(getAngulo() * 180/PI);

      setReal(arredondaValor(parteReal));
      setImaginario(arredondaValor(parteImaginaria));
    }

  /** Util */
  private:
    double verificaExcecoes(double valor)
    {
      if( isnanf(valor) || isinf(valor)) { return 0; }
      return valor;
    }

    double arredondaValor(double valor) { return (double)round(valor * 10000) / 10000; }

    string transformaResultadoParaFormaPolar(double parteReal, double parteImaginaria)
    {
      double divisaoImagReal = verificaExcecoes(getImaginario()/getReal());
      double angulo = atan(divisaoImagReal)* 180 / PI;
      double magnitude = sqrt(pow(parteReal, 2) + pow(parteImaginaria, 2));

      return to_string(arredondaValor(magnitude)) + " L " + to_string(arredondaValor(angulo));
    }

    string transformaResultadoParaFormaRetangular(double magnitude, double angulo)
    {
      double parteReal = magnitude * cos(angulo * PI/180);
      double parteImaginaria = magnitude * sin(angulo * PI/180);

      return to_string(arredondaValor(parteReal)) + " + " + (to_string(arredondaValor(parteImaginaria)) + "i");
    }

  /** Operacoes Matematicas */
  public:
    string soma(Complexo* parcela, Forma formaGerada)
    {
      double somaParteReal = getReal() + parcela->getReal();
      double somaParteImaginaria = getImaginario() + parcela->getImaginario();

      if(formaGerada == POLAR) { return transformaResultadoParaFormaPolar(somaParteReal, somaParteImaginaria); }

      string parteReal = to_string(arredondaValor(somaParteReal));
      string parteImaginaria = to_string(arredondaValor(somaParteImaginaria)) + "i";
      return parteReal + " + " + parteImaginaria;
    }

    string subtracao(Complexo* subtrativo, Forma formaGerada)
    {
      double subtracaoParteReal = getReal() - subtrativo->getReal();
      double subtracaoParteImaginaria = getImaginario() - subtrativo->getImaginario();

      if(formaGerada == POLAR) { return transformaResultadoParaFormaPolar(subtracaoParteReal, subtracaoParteImaginaria); }

      string parteImaginaria = to_string(arredondaValor(subtracaoParteImaginaria)) + "i";

      if(subtrativo->getImaginario() > getImaginario())
      {
        parteImaginaria = to_string(arredondaValor(subtracaoParteImaginaria) * -1) + "i";
        return to_string(arredondaValor(subtracaoParteReal)) + " - " + parteImaginaria;
      }

      return to_string(arredondaValor(subtracaoParteReal)) + " + " + parteImaginaria;
    }

    string multiplicacao(Complexo* fator, Forma formaGerada)
    {
      double magnitude = getMagnitude() * fator->getMagnitude();
      double angulo = getAngulo() + fator->getAngulo();

      if(formaGerada == RETANGULAR) { return transformaResultadoParaFormaRetangular(magnitude, angulo); }

      return to_string(arredondaValor(magnitude)) + " L " + to_string(arredondaValor(angulo));
    }

    string divisao(Complexo* divisor, Forma formaGerada)
    {
      double magnitude = verificaExcecoes(getMagnitude() / divisor->getMagnitude());
      double angulo = getAngulo() - divisor->getAngulo();

      if(formaGerada == RETANGULAR) { return transformaResultadoParaFormaRetangular(magnitude, angulo); }

      return to_string(arredondaValor(magnitude)) + " L " + to_string(arredondaValor(angulo));
    }

  /** Operacoes para comparar */
  private:
    string compararPorAngulo(Complexo* valor, string valorFormatado)
    {
      double divisaoImagRealA = verificaExcecoes(getImaginario()/getReal());
      double anguloA = atan(divisaoImagRealA)* 180 / PI;

      double divisaoImagRealB = verificaExcecoes(valor->getImaginario()/valor->getReal());
      double anguloB = atan(divisaoImagRealB)* 180 / PI;

      if(isgreater(anguloA, anguloB))
      {
        return "O numero complexo " + getFormaRetangular() +
               " e maior que o numero complexo " + valorFormatado;
      }
      else if(isless(anguloA, anguloB))
      {
        return "O numero complexo " + getFormaRetangular() +
               " e menor que o numero complexo " + valorFormatado;
      }
      else
      {
        return "Os numeros sao iguais";
      }
    }

  public:
    string comparacao(Complexo* valor)
    {
      double magnitudeNumeroA = arredondaValor(sqrt(pow(getReal(), 2) + pow(getImaginario(), 2)));
      double magnitudeNumeroB = arredondaValor(sqrt(pow(valor->getReal(), 2) + pow(valor->getImaginario(), 2)));

      string valorFormatado = to_string(valor->getReal()) + " + " + (to_string(valor->getImaginario()) + "i");

      if(isgreater(magnitudeNumeroA, magnitudeNumeroB))
      {
        return "O numero complexo " + getFormaRetangular() +
               " e maior que o numero complexo " + valorFormatado;
      }
      else if(isless(magnitudeNumeroA, magnitudeNumeroB))
      {
        return "O numero complexo " + getFormaRetangular() +
               " e menor que o numero complexo " + valorFormatado;
      }
      else
      {
        return compararPorAngulo(valor, valorFormatado);
      }
    }
};

class ClasseAbstrata
{
  public:
    ClasseAbstrata() {};
    ~ClasseAbstrata() {};

    virtual void ordenar(int arr[], int n) = 0;
};


class MatrizComplexo : public ClasseAbstrata
{
  private:
    int linhas = 1;
    int colunas = 1;
    Complexo **matrizNumerosComplexos;

  /** Construtores */
  public:
    MatrizComplexo(int x, int y)
    {
      linhas = x;
      colunas = y;
      geraMatriz();
    }

  /** Garbage collector */
    ~MatrizComplexo()
    {
      for (int i = 0; i < colunas; ++i)
      {
        delete [] matrizNumerosComplexos[i];
        delete [] matrizNumerosComplexos;
      }
    }

  /** Getter e Setter */
    int getLinhas() { return linhas; }

    int getColunas() { return colunas; }

    Complexo **getMatriz() { return matrizNumerosComplexos; }

  /** Util */
    void adicionarNumero(int linha,int coluna,Complexo *elemento)
    {
      if(linha<linhas && coluna<colunas) { matrizNumerosComplexos[linha][coluna]= *elemento; }
    }

    void imprimeMatriz()
    {
      for (int i = 0; i < getLinhas(); ++i)
      {
        for (int j = 0; j <  getColunas(); ++j)
        {
          Complexo ** gM = getMatriz();
          Complexo gM_= gM[i][j];
          cout << "linha=" <<  i << " / " << "coluna=" << j << endl;
          cout << "valor: " << gM_.getFormaRetangular() << endl;
        }
      }
    }

    void ordenar(int arr[], int n)
    {
      int i, j, temp;

      for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                temp = arr[j];
      arr[j] = arr[j+1];
      arr[j+1] = temp;
    }

  private:
    void geraMatriz()
    {
      matrizNumerosComplexos = new Complexo*[getLinhas()];
      for (int i = 0; i < getLinhas(); ++i) {
          matrizNumerosComplexos[i] = new Complexo[getColunas()];
      }
    }
};

int main()
{
  Complexo *numero1, *numero2;
  numero1 = new Complexo(1, 1);
  numero2 = new Complexo(POLAR, 5, 25);

  MatrizComplexo* matriz = new MatrizComplexo(5, 5);

  matriz->adicionarNumero(1, 2, numero1);
  matriz->adicionarNumero(0, 1, numero2);

  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int n = sizeof(arr)/sizeof(arr[0]);

  matriz->ordenar(arr, n);

  cout <<"\n**********************MATRIZ**********************"<< endl;
  cout <<"!Linhas: " << matriz->getLinhas() << endl;
  cout <<"!Colunas: " << matriz->getColunas() << endl;

  cout <<"\n**********************IMPRIME MATRIZ**********************"<< endl;
  matriz->imprimeMatriz();

  //"================NUMEROS COMPLEXOS================"
  string somaRetangular = numero1->soma(numero2, RETANGULAR);
  string somaPolar = numero1->soma(numero2, POLAR);

  string subtracaoRetangular = numero1->subtracao(numero2, RETANGULAR);
  string subtracaoPolar = numero1->subtracao(numero2, POLAR);

  string divisaoRetangular = numero1->divisao(numero2, RETANGULAR);
  string divisaoPolar = numero1->divisao(numero2, POLAR);

  string multiplicacaoRetangular = numero1->multiplicacao(numero2, RETANGULAR);
  string multiplicacaoPolar = numero1->multiplicacao(numero2, POLAR);

  string comparacaoA = numero1->comparacao(numero2);
  string comparacaoB = numero2->comparacao(numero1);

  cout << "\n================NUMEROS COMPLEXOS================" << endl;
  cout << "[Numero1] Forma retangular: " << numero1->getFormaRetangular() << endl;
  cout << "[Numero1] Forma polar: " << numero1->getFormaPolar() << endl;

  cout << "[Numero2] Forma retangular: " << numero2->getFormaRetangular() << endl;
  cout << "[Numero2] Forma polar: " << numero2->getFormaPolar() << endl;

  cout << "\n================SOMA================" << endl;
  cout << "Soma retangular: " << somaRetangular << endl;
  cout << "Soma polar: " << somaPolar << endl;

  cout << "\n================SUBTRACAO================" << endl;
  cout << "Subtracao retangular: " << subtracaoRetangular << endl;
  cout << "Subtracao polar: " << subtracaoPolar << endl;

  cout << "\n================DIVISAO================" << endl;
  cout << "Divisao retangular: " << divisaoRetangular << endl;
  cout << "Divisao polar: " << divisaoPolar << endl;

  cout << "\n================MULTIPLICACAO================" << endl;
  cout << "Multiplicacao retangular: " << multiplicacaoRetangular << endl;
  cout << "Multiplicacao polar: " << multiplicacaoPolar << endl;

  cout << "\n================COMPARACAO================" << endl;
  cout << "[Numero1] Comparacao: " << comparacaoA << endl;
  cout << "[Numero2] Comparacao: " << comparacaoB << endl;

  cout <<"\n**********************delete MATRIZ**********************"<< endl;
  delete matriz;
  matriz->imprimeMatriz();

  return 0;
}
