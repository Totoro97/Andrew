import java.util.*;
import java.io.*;
import java.math.*;

public class D {

	static Scanner in;
	static PrintStream out;

	static {
		String file = "police";
		try {
			in = new Scanner(new File(file + ".in"));
			out = new PrintStream(new FileOutputStream(file + ".out"));
		} catch (IOException ex) {
		}
	}

	public static void main(String[] args) {
		int n = in.nextInt();
		int m = in.nextInt();
		int p = in.nextInt();
		int d[][] = new int[210][210];
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				d[i][j] = 0;
		for (int i = 1; i <= m; i++) {
			int a = in.nextInt(); int b = in.nextInt();
			d[a][b] = 1;
		}
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					d[i][j] |= d[i][k] & d[k][j];
		int fa[] = new int[210];
		for (int i = 1; i <= n; i++) fa[i] = i;
		int n_ = 0; 
		int size[] = new int[210];
		for (int i = 1; i <= n; i++) {
			size[i] = 0;
			if (fa[i] != i) continue;
			size[i] = 1;
			n_++;
			for (int j = i + 1; j <= n; j++) 
				if (d[i][j] != 0 && d[j][i] != 0) { fa[j] = i; size[i]++; }
		}

		int du[] = new int [210];
		int ud[] = new int [210];

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				if (i == j || fa[i] != i || fa[j] != j) continue;
				if (d[i][j] != 0) { du[j]++; ud[i]++; }
			}

		int a = 0, b = 0, c = 0,t = 0;
		int[] A = new int[210];

		for(int i = 1; i <= n; i++) {
			if (fa[i] != i) continue;
			if (du[i] == 0 && ud[i] == 0) { A[++t] = i; c += size[i]; }
			else if (du[i] == 0) { A[++t] = i; a += size[i]; }
			else if (ud[i] == 0) { A[++t] = i; b += size[i]; }
		}

		BigInteger[][] C = new BigInteger[210][210];

		for (int i = 0; i <= n; i++) {
			C[i][0] = BigInteger.ONE;
			C[i][i] = BigInteger.ONE;
			for (int j = 1; j < i; j++)
				C[i][j] = C[i - 1][j - 1].add(C[i - 1][j]);
		}

		int d_ = n - a - b - c;
		if (t > p) { out.println("0"); return; }
		BigInteger[] f = new BigInteger[210];
		for (int i = 0; i <= n; i++) f[i] = BigInteger.ZERO;
		for (int i = 1; i <= size[A[1]] && i <= p; i++) f[i] = C[size[A[1]]][i];
		for (int i = 2; i <= t; i++) {
			for (int j = p; j >= 0; j--) {
				f[j] = BigInteger.ZERO;
				for (int k = 1; k <= size[A[i]] && k <= j; k++)
					f[j] = f[j].add(f[j - k].multiply(C[size[A[i]]][k]));
			}
		}

		//out.println(a + " " + b + " " + c + " " + d_);
		BigInteger ans = BigInteger.ZERO;
		for (int i = 0; i <= p && i <= d_; i++) 
			ans = ans.add(f[p - i].multiply(C[d_][i]));
		out.println(ans);
	}
}