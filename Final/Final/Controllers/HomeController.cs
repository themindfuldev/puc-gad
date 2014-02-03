using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Final.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
              int tamanhoDaTabuada = 1000000;
              long start = DateTime.Now.Ticks;

              // Primeiro cálculo e pausa
              Tabuada tabuada1 = new Tabuada();
              tabuada1.calcularTabuadas("tabuada1.txt", tamanhoDaTabuada, new int[] {
                 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });

              // Segundo cálculo e pausa
              Tabuada tabuada2 = new Tabuada();
              tabuada2.calcularTabuadas("tabuada2.txt", tamanhoDaTabuada, new int[] {
                 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 });

              // Terceiro cálculo e pausa
              Tabuada tabuada3 = new Tabuada();
              tabuada3.calcularTabuadas("tabuada3.txt", tamanhoDaTabuada, new int[] {
                 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 });

              // Quarto cálculo e pausa
              Tabuada tabuada4 = new Tabuada();
              tabuada4.calcularTabuadas("tabuada4.txt", tamanhoDaTabuada, new int[] {
                 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 });

              long stop = DateTime.Now.Ticks;
              ViewBag.Message = "Tempo gasto: " + ((stop - start) / TimeSpan.TicksPerMillisecond) + "ms";

            return View();
        }

    }
}
