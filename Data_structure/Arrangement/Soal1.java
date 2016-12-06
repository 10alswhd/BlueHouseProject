/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cobacoba;
import javax.swing.JOptionPane;
/**
 *
 * @author AdryanEV
 */
public class Soal1 {
    Integer [] data;
    Integer hasil;
    Integer batas;
    
    public Soal1(Integer batas){
        this.batas = batas;
        hasil = 0;
        data = new Integer[batas];
    }
    void inputData(){
        for(int i = 0; i< data.length; i++){
            data[i] = Integer.parseInt(JOptionPane.showInputDialog("Masukkan Bilangan ke "+(i+1)));
        }
    }
   
    void tampilData(){
        System.out.println("Daftar Bilangan");
        for (int i = 0; i<data.length; i++) {
            
            System.out.print(data[i]+" ");
            hasil += data[i];
        }
        double rata = hasil/batas;
        System.out.println("\nRata- Rata = "+(rata));
    }
    static void test1(){
        Integer batas = new Integer(Integer.parseInt(JOptionPane.showInputDialog("Masukkan Batas Bilangan")));
        
        Soal1 s = new Soal1 (batas);
        
        s.inputData();
        s.tampilData();
    }
    public static void main(String[] args) {
        
        test1();
      
    }
}
