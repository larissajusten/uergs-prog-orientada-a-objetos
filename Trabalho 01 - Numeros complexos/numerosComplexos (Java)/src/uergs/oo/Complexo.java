package uergs.oo;

import static java.lang.Math.*;

/**
 * @author Larissa E. Justen.
 *
 * @version 1.0.0
 *
 * Classe para Operações Matemáticas com Números Complexos.
 *  * Pode ser iniciada de duas maneiras: 1 e 2.
 *  * Tem como default a forma <a href="#{@link uergs.oo.Forma}"> RETANGULAR </a>..
 *
 * Para compilar online utilize https://www.mycompiler.io/view/FiLF8RE.
 */
public class Complexo implements OperacoesMatematicas {

    private Forma forma = Forma.RETANGULAR;
    private double real;
    private double imaginario;
    private double magnitude;
    private double angulo;

    /**
     *  1: Indicando seus respectivos paramêtros:
     *    @param primeiroParametro indica a parte Real {@code double}
     *    @param segundoParametro indica a parte Imaginaria {@code double}
     *
     *  Gera automaticamente a Magnitude e o Angulo.
     *  @see Complexo#geraESalvaFormaPolar()
     */
    public Complexo(double primeiroParametro, double segundoParametro) {
        this.real = primeiroParametro;
        this.imaginario = segundoParametro;
        geraESalvaFormaPolar();
    }

    /**
     *  2: Indicando a forma e seus respectivos paramêtros:
     *    @param formaSelecionada indica a forma que a classe vai reconhecer os parametros {@code Forma}
     *    @param primeiroParametro indica a parte Real ou a Magnitude {@code double}
     *    @param segundoParametro indica a parte Imaginaria ou o Angulo {@code double}
     *
     *  Gera automaticamente a Magnitude e o Angulo quando selecionada forma <a href="#{@link uergs.oo.Forma}">RETANGULAR</a>.
     *  @see Complexo#geraESalvaFormaPolar()
     *
     *  Gera automaticamente a Magnitude e o Angulo quando selecionada forma <a href="#{@link uergs.oo.Forma}">POLAR</a>.
     *  @see Complexo#geraESalvaFormaRetangular()
     */
    public Complexo(Forma formaSelecionada, double primeiroParametro, double segundoParametro) {
        if(formaSelecionada.equals(Forma.RETANGULAR)) {
            this.real = primeiroParametro;
            this.imaginario = segundoParametro;
            geraESalvaFormaPolar();
        }else {
            this.forma = Forma.POLAR;
            this.magnitude = primeiroParametro;
            this.angulo = segundoParametro;
            geraESalvaFormaRetangular();
        }
    }


    /** Getter e Setter */
    public double getReal() {
        return real;
    }

    private void setReal(double real) {
        this.real = real;
    }

    public double getImaginario() {
        return imaginario;
    }

    private void setImaginario(double imaginario) {
        this.imaginario = imaginario;
    }

    public double getMagnitude() {
        return magnitude;
    }

    private void setMagnitude(double magnitude) {
        this.magnitude = magnitude;
    }

    public double getAngulo() {
        return angulo;
    }

    private void setAngulo(double angulo) {
        this.angulo = angulo;
    }

    public String getFormaPolar() {
        return getMagnitude() + " L " + getAngulo();
    }

    public String getFormaRetangular() {
        return getReal() + " + " + (getImaginario() + "i");
    }


    /** Utilizadas ao inicializar */
    private void geraESalvaFormaPolar() {
        double divisaoImagReal = verificaExcecoes(getImaginario()/getReal());
        double angulo = toDegrees(atan(divisaoImagReal));

        double magnitude = sqrt(pow(getReal(), 2) + pow(getImaginario(), 2));

        setMagnitude(arredondaValor(magnitude));
        setAngulo(arredondaValor(angulo));
    }

    private void geraESalvaFormaRetangular() {
        double parteReal = getMagnitude() * cos(toRadians(getAngulo()));
        double parteImaginaria = getMagnitude() * sin(toRadians(getAngulo()));

        setReal(arredondaValor(parteReal));
        setImaginario(arredondaValor(parteImaginaria));
    }


    /** Util */
    private double verificaExcecoes(Double valor) {
        if(valor.isNaN() || valor.isInfinite()) {
            return 0;
        }
        return valor;
    }

    private double arredondaValor(double valor) {
        return (double)Math.round(valor * 10000d) / 10000d;
    }

    private String transformaResultadoParaFormaPolar(double parteReal, double parteImaginaria) {
        double magnitude = sqrt(pow(parteReal, 2) + pow(parteImaginaria, 2));
        double angulo = toDegrees(atan(parteImaginaria/parteReal));

        return arredondaValor(magnitude) + " L " + arredondaValor(angulo);
    }

    private String transformaResultadoParaFormaRetangular(double magnitude, double angulo) {
        double parteReal = magnitude * cos(toRadians(angulo));
        double parteImaginaria = magnitude * sin(toRadians(angulo));

        return arredondaValor(parteReal) + " + " + (arredondaValor(parteImaginaria) + "i");
    }


    /** Operações Matemáticas */
    @Override
    public String soma(Complexo parcela, Forma formaGerada) {
        double somaParteReal = getReal() + parcela.getReal();
        double somaParteImaginaria = getImaginario() + parcela.getImaginario();

        if(formaGerada.equals(Forma.POLAR)){
            return transformaResultadoParaFormaPolar(somaParteReal, somaParteImaginaria);
        }

        String parteReal = String.valueOf(arredondaValor(somaParteReal));
        String parteImaginaria = arredondaValor(somaParteImaginaria) + "i";
        return parteReal + " + " + parteImaginaria;
    }

    @Override
    public String subtracao(Complexo subtrativo, Forma formaGerada) {
        double subtracaoParteReal = getReal() - subtrativo.getReal();
        double subtracaoParteImaginaria = getImaginario() - subtrativo.getImaginario();

        if(formaGerada.equals(Forma.POLAR)){
            return transformaResultadoParaFormaPolar(subtracaoParteReal, subtracaoParteImaginaria);
        }

        String parteImaginaria = (arredondaValor(subtracaoParteImaginaria)) + "i";

        if(subtrativo.getImaginario() > getImaginario()){
            parteImaginaria = (arredondaValor(subtracaoParteImaginaria) * -1) + "i";
            return arredondaValor(subtracaoParteReal) + " - " + parteImaginaria;
        }

        return arredondaValor(subtracaoParteReal) + " + " + parteImaginaria;
    }

    @Override
    public String multiplicacao(Complexo fator, Forma formaGerada) {
        double magnitude = getMagnitude() * fator.getMagnitude();
        double angulo = getAngulo() + fator.getAngulo();

        if(formaGerada.equals(Forma.RETANGULAR)){
            return transformaResultadoParaFormaRetangular(magnitude, angulo);
        }

        return arredondaValor(magnitude) + " L " + arredondaValor(angulo);
    }

    @Override
    public String divisao(Complexo divisor, Forma formaGerada) {
        double magnitude = verificaExcecoes(getMagnitude() / divisor.getMagnitude());
        double angulo = getAngulo() - divisor.getAngulo();

        if(formaGerada.equals(Forma.RETANGULAR)){
            return transformaResultadoParaFormaRetangular(magnitude, angulo);
        }

        return arredondaValor(magnitude) + " L " + arredondaValor(angulo);
    }

    private String compararPorAngulo(Complexo valor, String valorFormatado) {
        double divisaoImagRealA = verificaExcecoes(getImaginario()/getReal());
        Double anguloA = toDegrees(atan(divisaoImagRealA));

        double divisaoImagRealB = verificaExcecoes(valor.getImaginario()/valor.getReal());
        Double anguloB = toDegrees(atan(divisaoImagRealB));

        switch (anguloA.compareTo(anguloB)) {
            case 1:
                return "O número complexo " + getFormaRetangular() +
                        " é maior que o número complexo " + valorFormatado;
            case 0:
                return "Os números são iguais";
            case -1:
                return "O número complexo " + getFormaRetangular() +
                        " é menor que o número complexo " + valorFormatado;
        }
        return null;
    }
    @Override
    public String comparacao(Complexo valor) {
        Double magnitudeNumeroA = arredondaValor(sqrt(pow(getReal(), 2) + pow(getImaginario(), 2)));
        Double magnitudeNumeroB = arredondaValor(sqrt(pow(valor.getReal(), 2) + pow(valor.getImaginario(), 2)));

        String valorFormatado = valor.getReal() + " + " + (valor.getImaginario() + "i");

        switch (magnitudeNumeroA.compareTo(magnitudeNumeroB)) {
            case 1:
                return "O número complexo " + getFormaRetangular() +
                        " é maior que o número complexo " + valorFormatado;
            case 0:
                return compararPorAngulo(valor, valorFormatado);
            case -1:
                return "O número complexo " + getFormaRetangular() +
                        " é menor que o número complexo " + valorFormatado;
        }
        return null;
    }
}
