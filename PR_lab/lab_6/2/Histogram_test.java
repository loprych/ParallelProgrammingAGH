import java.util.Scanner;

class Watek implements Runnable{ // klasa jest obiektem wykonywalnym dla wątku
 	
 	public void run (){
 	
 	obraz.calculate_histogram_parallel(start_index, end_index); 
 	obraz.print_histogram_parallel(start_index, end_index, watek_index);
 	}
 	// przy uruchomieniu watku wywolywany jest run
 	
 	public Watek (Obraz obraz, int watek_index, int start_index, int end_index){
 	this.obraz = obraz;
 	this.end_index = end_index;
 	this.start_index = start_index;
 	this.watek_index = watek_index;
 	}
	private Obraz obraz;
	private int start_index;
	private int end_index;
	private int watek_index;
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
	System.out.println("Set number of threads");
	 int num_threads = scanner.nextInt();

	 Thread[] NewThr = new Thread[num_threads];
    	 int numSignsPerThread = 94 / num_threads;
    	 int divisionRest = 94 % num_threads;
    	 int startIndex = 0;
    	 int endIndex = numSignsPerThread;
    	 if (divisionRest > 0) {
    	 	divisionRest--;
    		endIndex++;
    	 }
	 for (int i = 0; i < num_threads; i++) {
	 //stworzenie i uruchomienie watku 
	     (NewThr[i] = new Thread(new Watek(obraz_1, i, startIndex, endIndex))).start(); 
	 //System.out.println(startIndex + " " + endIndex);    
	 	startIndex = endIndex;
	 	endIndex += numSignsPerThread;
	 if(divisionRest > 0) {
	 	divisionRest--;
	 	endIndex++;    
	 }    
	 }
    
	 for (int i = 0; i < num_threads; i++) {
	     try {
	 	NewThr[i].join();
	     } catch (InterruptedException e) {}
	 }
	obraz_1.check_histograms();
    }

}

