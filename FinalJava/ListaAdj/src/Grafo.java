import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.Iterator;
import java.util.PriorityQueue;


public class Grafo {

	class SAresta {
		int vertice, peso;
	} 

	class SVetor {
		int vertice;
		int grau;
		ArrayList<SAresta> aresta;
	}

	class BFS {
		char cor;
		int dist;
		int predecessor;
	}

	private int vertices;    // N�mero de vertices do grafo
	SVetor[] grafo;         // Lista de adjac�ncia do grafo

	Grafo() {
		File arq = new File("grafos.txt");
		try {
			FileReader fileReader = new FileReader(arq);

			BufferedReader bufferedReader = new BufferedReader(fileReader);

			String linha = "";
			linha = bufferedReader.readLine();

			this.grafo = new SVetor[Integer.valueOf(linha)];
			this.vertices = grafo.length;

			for (int i = 0; i < this.grafo.length; i++) {
				this.grafo[i] = new SVetor();
				this.grafo[i].vertice = i + 1;
				this.grafo[i].aresta = new ArrayList<Grafo.SAresta>();
			}

			carregaArquivo(bufferedReader);

			fileReader.close();
			bufferedReader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void carregaArquivo(BufferedReader bufferedReader) {
		try {
			String linha = "";
			String[] informacao = new String[3];

			while ( ( linha = bufferedReader.readLine() ) != null) {
				informacao = linha.split("\\s");
				//System.out.println(Arrays.toString(informacao));
				insereAresta(informacao);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private boolean pesquisaVertice(String v) {
		if (Integer.valueOf(v) > this.vertices) {
			return false;
		}
		return true;
	}

	private void insereAresta(String[] aresta) {
		if (!pesquisaVertice(aresta[0]) || !pesquisaVertice(aresta[1])) {
			System.out.println("Problemas com o vertice " + aresta[0] + " ou " + aresta[1] + ". Verifique o arquivo carregado.");
		} else {
			this.grafo[Integer.valueOf(aresta[0]) - 1].grau++;
			this.grafo[Integer.valueOf(aresta[1]) - 1].grau++;

			SAresta arestaV1 = new SAresta();
			SAresta arestaV2 = new SAresta();

			arestaV1.vertice = Integer.valueOf(aresta[1]);
			arestaV2.vertice = Integer.valueOf(aresta[0]);
			arestaV1.peso = Integer.valueOf(aresta[2]);
			arestaV2.peso = Integer.valueOf(aresta[2]);

			this.grafo[Integer.valueOf(aresta[0]) - 1].aresta.add(arestaV1);
			this.grafo[Integer.valueOf(aresta[1]) - 1].aresta.add(arestaV2);
		}
	}

	private boolean buscaExtensao(int v1, int v2) {
		PriorityQueue<Integer> fila = new PriorityQueue<Integer>();
		int i, u;
		SAresta aresta = new SAresta(); //apont
		Grafo.BFS[] dadosVertice = new Grafo.BFS[(this.vertices - 1) * 2];

		for (int j = 0; j < dadosVertice.length; j++) {
			dadosVertice[j] = new BFS();
			dadosVertice[j].cor = 'B';
			dadosVertice[j].dist = 999999999;
			dadosVertice[j].predecessor = 0;
		}

		dadosVertice[v1 - 1].cor = 'C';
		dadosVertice[v1 - 1].dist = 0;
		dadosVertice[v1 - 1].predecessor = 0;

		fila.add(v1);

		while ( !fila.isEmpty() ) {

			u = fila.poll();			
			Iterator<SAresta> it = this.grafo[u - 1].aresta.iterator();

			while (it.hasNext()) {

				aresta = it.next();

				if (dadosVertice[aresta.vertice - 1].cor == 'B') {
					dadosVertice[aresta.vertice - 1].dist = dadosVertice[u - 1].dist + aresta.peso;
					dadosVertice[aresta.vertice - 1].predecessor = u;
					fila.add(aresta.vertice);
				}

				if (aresta.vertice == v2) {

					System.out.println("O custo do caminho entre o vertice " + v1 + " ao vertice " + v2 + " e de " +
							dadosVertice[aresta.vertice - 1].dist + " unidade(s).");
					System.out.println("Caminho: ");
					System.out.print(v2);
					i = v2;

					while (!(dadosVertice[i - 1].predecessor == 0)) {
						System.out.print(" - " + dadosVertice[i -1].predecessor);
						i = dadosVertice[i - 1].predecessor;
					}
					return true;
				}
			}
			dadosVertice[u -1].cor = 'P';
		}
		return false;
	}

	public static void main(String[] args) {
		long start = new Date().getTime();
		Grafo g = new Grafo();
		g.buscaExtensao(9, 167);
		long stop = new Date().getTime();
		System.out.println("\nTempo gasto: " + (stop-start) + "ms");
	}
}














