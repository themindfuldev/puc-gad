using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Final.Controllers
{
    public class Tabuada
    {
        public void calcularTabuadas(String arquivoTabuada, int quantidadeNumeros, params int[] fatores) {
              long[][] matrizTabuadas = new long[quantidadeNumeros][];
              criarTabuadas(matrizTabuadas, quantidadeNumeros, fatores);
              imprimirTabuadas(arquivoTabuada, matrizTabuadas, fatores);
           }

        private void criarTabuadas(long[][] matrizTabuadas, int quantidadeNumeros, params int[] fatores)
        {
            for (int i = 0; i < quantidadeNumeros; i++)
            {
                matrizTabuadas[i] = new long[fatores.Length];
                for (int j = 0; j < fatores.Length; j++)
                {
                    matrizTabuadas[i][j] = i * fatores[j];
                }
            }
        }

        private void imprimirTabuadas(String arquivoTabuada, long[][] matrizTabuadas, params int[] fatores)
        {
            StreamWriter sw = new StreamWriter(System.IO.Path.GetTempPath() + "\\" + arquivoTabuada);

            for (int i = 0; i < matrizTabuadas.Length; i++)
            {
                for (int j = 0; j < fatores.Length; j++)
                {
                    sw.Write(i + "*" + fatores[j] + "=" + matrizTabuadas[i][j] + "\t");
                }
            }
            sw.Close();
        }

    }
}

