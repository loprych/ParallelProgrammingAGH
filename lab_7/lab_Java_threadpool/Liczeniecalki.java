import java.util.concurrent.*;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

public class Liczeniecalki {

    private static final int NTHREADS = 10; 
    public static void main(String[] args) {
    	ExecutorService executor = Executors.newFixedThreadPool(NTHREADS); //stworzenie executora o danej puli watkow
    	List<Future<Double>> listaWynikow = new ArrayList<Future<Double>>(); // lista w ktorej zapisujemy obiekty future
    	Scanner scanner = new Scanner(System.in);
	double start = 0;
	double end = Math.PI;
	double task = 50;
	double dx = 0.000001;
	double przedzialPerZadanie = (end - start) / task; //ilosc zadan
	double kX = przedzialPerZadanie;
	for (double pX = start; pX < end; pX += przedzialPerZadanie){
		if(kX > end){kX = end;}  // w przypadku bledu zaokraglen ten if to wychwyci
		Callable<Double> calkacallable = new Calka_callable(pX, kX, dx);  
		Future<Double> future = executor.submit(calkacallable); 
		listaWynikow.add(future); 
		// stworzenie obiektu klasy calka_callable
		// tworzymy future Future, przekazanie do puli watkow 
		// future przechowuje wynik wykonania tego taska, dodawany do listy future'ow
		kX += przedzialPerZadanie;
	}
	double wynik = 0;
	for (Future<Double> future : listaWynikow){
		try {
		wynik += future.get(); // uzyskanie wyniku metody call 
		}
		catch (InterruptedException | ExecutionException e){
			e.printStackTrace();
		}
		
	}
		executor.shutdown();

	// Wait until all threads finish
	while (!executor.isTerminated()) {}
	System.out.println("Finished all threads");
	System.out.println("Wynik calkowania rownolegle: " + wynik);
	
    }
   }
