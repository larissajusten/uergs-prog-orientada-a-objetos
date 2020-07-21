package uergs.oo;

public class TransacoesBancarias {

    private Conta contaDoJoao = new Conta("Joao", 59963, 220.45);
    private Conta contaDaFabiola = new Conta("Fabiola", 54589, 15.9);

    public void transacoesBancariasJoao() {
        contaDoJoao.creditar(500);
        contaDoJoao.debitar(98.20);
        contaDoJoao.debitar(22.25);
        contaDoJoao.transferir(contaDaFabiola, 500);
    }

    public void transacoesBancariasFabiola() {
        contaDaFabiola.debitar(225.9);
    }

    public void imprimeDadosDosClientes() {
        /** Dados do Cliente 1 */
        System.out.println("\n ===============================");
        System.out.println("Conta: " + contaDoJoao.getNumero());
        System.out.println("Cliente: " + contaDoJoao.getCliente());
        System.out.println("Saldo: " + contaDoJoao.getSaldo());

        /** Dados do Cliente 2 */
        System.out.println("\n ===============================");
        System.out.println("Conta: " + contaDaFabiola.getNumero());
        System.out.println("Cliente: " + contaDaFabiola.getCliente());
        System.out.println("Saldo: " + contaDaFabiola.getSaldo());
    }
}
