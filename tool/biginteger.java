import java.math.BigInteger;
import java.util.Scanner;

public class biginteger {
    public static void main(String[] args) {
        BigInteger a, b, sumAB, subAB, mulAB, DivAB ;
        Scanner cin = new Scanner(System.in);
        a = cin.nextBigInteger();
        b = cin.nextBigInteger();
        sumAB = a.add(b);
        subAB = a.subtract(b);
        mulAB = a.multiply(b);
        DivAB = a.divide(b);
        System.out.println(sumAB);
        System.out.println(subAB);
        System.out.println(mulAB);
        System.out.println(DivAB);
    }
}
// hdu 6222
import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    static final int N = 128;
    static BigInteger[] x = new BigInteger[N];
    static BigInteger[] y = new BigInteger[N];
    static BigInteger[] t = new BigInteger[N];
    static void init() {
        x[0] = BigInteger.valueOf(2);
        y[0] = BigInteger.valueOf(1);
        t[0] = BigInteger.valueOf(4);
        for (int i = 1; i < N; i++) {
            x[i] = x[i-1].multiply(x[0]).add(y[i-1].multiply(BigInteger.valueOf(3)));
            y[i] = y[0].multiply(x[i-1]).add(y[i-1].multiply(x[0]));
            t[i] = x[i].multiply(BigInteger.valueOf(2));
        }
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int T = in.nextInt();
        BigInteger n;
        init();
        while (T != 0) {
            T--;
            n = in.nextBigInteger();
            for (int i = 0 ; i < N; i++) {
                if (n.compareTo(t[i]) != 1) {
                    System.out.println(t[i]);
                    break;
                }
            }
        }
    }
}
