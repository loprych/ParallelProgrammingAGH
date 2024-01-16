import java.util.Scanner;

class Watek extends Thread{ // cała klasa jest wątkiem
 	
 	public void run (){
 	
 	obraz.calculate_histogram_parallel(znak_index); 
 	obraz.print_histogram_parallel(znak_index);
 	
 	}// przy uruchomieniu watku wywolywany jest run
 	
 	public Watek (Obraz obraz, int znak_index){
 	this.obraz = obraz;
 	this.znak_index = znak_index;
 	}
	private Obraz obraz;
	private int znak_index;
}

class Histogram_test{
    
    public static void main(String[] args) {

	Scanner scanner = new Scanner(System.in);
	
	System.out.println("Set image size: n (#rows), m(#kolumns)");
	int n = scanner.nextInt();
	int m = scanner.nextInt();
	Obraz obraz_1 = new Obraz(n, m);

	obraz_1.calculate_histogram();
	obraz_1.print_histogram();
	
	System.out.println("########### Wersja Równoległa #########");
	
         int num_threads = 94;
	 Watek[] NewThr = new Watek[num_threads];
    
	 for (int i = 0; i < num_threads; i++) {
	     (NewThr[i] = new Watek(obraz_1, i)).start(); //stworzenie i uruchomienie watku
	 }
    
	 for (int i = 0; i < num_threads; i++) {
	     try {
	 	NewThr[i].join();
	     } catch (InterruptedException e) {}
	 }
	obraz_1.check_histograms();
    }

}

