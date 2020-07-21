package uergs.oo;

public class Conta {

    private String cliente;
    private int numero;
    private double saldo;


    public Conta(String cliente, int numero, double saldo){
        this.cliente = cliente;
        this.numero = numero;
        this.saldo = saldo;
    }

    public String getCliente() {
        return cliente;
    }

    private void setCliente(String cliente) {
        this.cliente = cliente;
    }

    public int getNumero() {
        return numero;
    }

    private void setNumero(int numero) {
        this.numero = numero;
    }

    public double getSaldo() {
        return saldo;
    }

    private void setSaldo(double saldo) {
        this.saldo = saldo;
    }

    public void debitar(double valorADebitar) {
        double saldo = getSaldo();
        if(saldo >= valorADebitar){
            setSaldo(saldo - valorADebitar);
        }
    }

    public void creditar(double valorACreditar) {
        setSaldo(getSaldo() + valorACreditar);
    }

    public void transferir(Conta conta, double valorATransferir) {
        double saldo = getSaldo();
        if(saldo >= valorATransferir){
            debitar(valorATransferir);
            conta.creditar(valorATransferir);
        }
    }

}
