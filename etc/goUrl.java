import java.awt.Desktop;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

import javax.swing.*;

public class goUrl extends JFrame implements ActionListener{
private JButton urlButton_1 = new JButton("네이버");
private JButton urlButton_2 = new JButton("다음");
private JButton urlButton_3 = new JButton("구글");
private JButton urlButton_4 = new JButton("네이트");
private JButton urlButton_5 = new JButton("유튜브");
private JButton urlButton_6 = new JButton("입력");
private String naver = "http://www.naver.com/";
private String daum = "http://www.daum.net/";
private String google = "https://www.google.co.kr";
private String nate = "http://www.nate.com/";
private String youtube = "https://www.youtube.com/";
    private JPanel pan2 = new JPanel();
    
    public goUrl(){
    this.setTitle("사이트 연결");
    this.setSize(500,250);
    this.setVisible(true);
    this.init();
    this.start();
    }
    
    public void init(){
   
    //버튼 추가
    pan2.add(urlButton_1);
    pan2.add(urlButton_2);
    pan2.add(urlButton_3);
    pan2.add(urlButton_4);
    pan2.add(urlButton_5);
    pan2.add(urlButton_6);
   
    this.getContentPane().add("South",pan2);
    }
    
    public void start(){
    //각각의 버튼에 이벤트 설정
    urlButton_1.addActionListener(this);
    urlButton_2.addActionListener(this);
    urlButton_3.addActionListener(this);
    urlButton_4.addActionListener(this);
    urlButton_5.addActionListener(this);
    urlButton_6.addActionListener(this);
   
    setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    }

@Override
//이벤트 처리
public void actionPerformed(ActionEvent e) {
try {
if(e.getSource() == urlButton_1){
Desktop.getDesktop().browse(new URI(naver));
}else if(e.getSource() == urlButton_2){
Desktop.getDesktop().browse(new URI(daum));
}else if(e.getSource() == urlButton_3){
Desktop.getDesktop().browse(new URI(google));
}else if(e.getSource() == urlButton_4){
Desktop.getDesktop().browse(new URI(nate));
}else if(e.getSource() == urlButton_5){
Desktop.getDesktop().browse(new URI(youtube));
}else if(e.getSource() == urlButton_6){
String inputUrl = JOptionPane.showInputDialog("접속할 url 주소를 입력하세요");
Desktop.getDesktop().browse(new URI(inputUrl));
}
}catch (IOException | URISyntaxException e1) {
e1.printStackTrace();
}
}
public static void main(String [] ar){
goUrl go = new goUrl();
}
