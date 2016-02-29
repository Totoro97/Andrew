import java.util.*;
import java.io.*;
import java.math.*;

public class B {
	
	static Scanner in;
	static PrintStream out;
	
	static {
		String file = "divide";
		try {
			in = new Scanner(new File(file + ".in"));
			out = new PrintStream(new FileOutputStream(file + ".out"));
		} catch (IOException ex) {
		}
	}
	
	public static void pr(BigInteger[][] A,int n) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) out.print(A[i][j] + " ");
			out.println(A[i][n + 1]);
		}
		out.println();
	}
	
	public static void main(String[] args) {
		int n = in.nextInt();
		BigInteger[][] A;		 	
		A = new BigInteger[21][21];
		BigInteger js = BigInteger.ONE;
		for (int i = 1; i <= n; i++) {
			js = js.multiply(BigInteger.valueOf(2));
			A[i][n + 1] = js.subtract(BigInteger.ONE);
			BigInteger sj = BigInteger.valueOf(i);
			for (int j = 1; j <= n; j++) {
				A[i][j] = sj;
				sj = sj.multiply(BigInteger.valueOf(i));
			}
		}

		//pr(A,n);
		for (int i = 1; i <= n; i++) {
			int k = 0;
			for (int j = i; j <= n; j++) 
				if (!(A[j][i].equals(BigInteger.ZERO))) {
					k = j; break; 
				}
			for (int j = 1; j <= n + 1; j++) {
				BigInteger t = A[i][j];
				A[i][j] = A[k][j];
				A[k][j] = t;				
			}
			for (int j = 1; j <= n; j++) {
				if (i == j) continue;
				if (A[j][i].equals(BigInteger.ZERO)) continue;
				BigInteger g = A[i][i].divide(A[j][i].gcd(A[i][i]));
				for (k = 1; k <= n + 1; k++) {
					A[j][k] = A[j][k].multiply(g);
				}
				g = A[j][i].divide(A[i][i]);
				for (k = 1; k <= n + 1; k++)
					A[j][k] = A[j][k].subtract(A[i][k].multiply(g));
			}
			//pr(A,n);
		}
		out.println(n);
		for (int i = n; i >= 1; i--) {
			BigInteger g = A[i][i].gcd(A[i][n + 1]);
			A[i][i] = A[i][i].divide(g);
			A[i][n + 1] = A[i][n + 1].divide(g);
			if (A[i][i].signum() == -1) {
				A[i][i] = A[i][i].negate();
				A[i][n + 1] = A[i][n + 1].negate();
			}
			out.print(A[i][n + 1] + "/" + A[i][i] + " ");
		}
		out.println("1/1");
	}
}
