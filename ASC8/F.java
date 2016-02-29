import java.util.*;
import java.io.*;
import java.math.*;

public class F {	
	static Scanner in;
	static PrintStream out;	
	static BigInteger[] fac = new BigInteger[120];	
	
	static {
		String file = "parallel";
		try {
			in = new Scanner(new File(file + ".in"));
			out = new PrintStream(new FileOutputStream(file + ".out"));
		} catch (IOException ex) {
		}
	}

	public static BigInteger C(int a,int b) {
		if (a < b) return BigInteger.ZERO;
		return fac[a].divide(fac[b]).divide(fac[a - b]);		
	}
	
	public static void main(String[] args) {
		int[] f = new int[120];
		int[][] d = new int[30][30];
		BigInteger[] df = new BigInteger[120];
		BigInteger[] ex = new BigInteger[120];
		int n,m,k,p;		
		n = in.nextInt(); m = in.nextInt(); k = in.nextInt(); p = in.nextInt();
		for (int i = 1; i <= p; i++) {
			String s = in.next();
			int a = s.charAt(0) - 'A';
			int b = s.charAt(1) - 'A';
			d[a][b] = d[b][a] = 1;
		}
		String s = in.next();
		int[] A = new int[120];
		for (int i = 1; i <= n; i++)
			A[i] = s.charAt(i - 1) - 'A';
		for (int i = 1; i <= n; i++)
			f[i] = (1 << 30);
		fac[0] = BigInteger.ONE;
		for (int i = 1; i <= n + 1; i++)
			fac[i] = fac[i - 1].multiply(BigInteger.valueOf(i));
		ex[0] = df[0] = BigInteger.ONE;
		for (int t = 0; t < n; t++) {
			boolean flag = true;
			for (int i = t + 1; i <= n; i++) {
				for (int j = i - 1; j > t; j--)
					if (d[A[i]][A[j]] == 0) { flag = false; break; }
				if ((!flag) || i - t > k) break;
				if (f[i] > f[t] + 1) {
					f[i] = f[t] + 1;
					df[i] = df[t];
					ex[i] = ex[t].multiply(C(k,i - t)).multiply(fac[i - t]);
				} else if (f[i] == f[t] + 1) {
					df[i] = df[i].add(df[t]);
					ex[i] = ex[i].add(ex[t].multiply(C(k,i - t)).multiply(fac[i - t]));
				}
			}
		}
		out.println(f[n]);
		out.println(df[n]);
		out.println(ex[n]);
	}
}
