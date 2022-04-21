import java.awt.*;
import java.lang.Double;

import javax.swing.*;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Calculator {

    static JFrame jframe = null;
    static JTextField jtfield = null;

    public static void createAndShowGUI() {
        ActionListener myActionListener = new ActionListener() {
            private char op; //holding the operator sign:  ‘*’,  ‘/’,  ‘+’,  ‘-’  and  ‘=’
            private double value1,value2,result; //holding the first and the second argument and the result for specific operation
            private boolean operation = false; //to control when we put value into value1 or value2
            private String str1 = "";
            private String str2 = "";

            public void actionPerformed(ActionEvent e) {
                char button = e.getActionCommand().charAt(0);

                switch (button) {
                    case '+':
                        System.out.println("Button = " + e.getActionCommand());
                        op = '+';
                        if(operation==true && value2 != 0 ){
                            jtfield.setText(Double.toString(result));
                            System.out.println("Result = " + result);
                            value1 = result;
                            value2 = 0;
                            str1 = "";
                            str2 = "";
                            break;
                        }
                        operation = true;
                        break;
                    case '-':
                        System.out.println("Button = " + e.getActionCommand());
                        op = '-';
                        if(operation==true && value2 != 0 ){
                            jtfield.setText(Double.toString(result));
                            System.out.println("Result = " + result);
                            value1 = result;
                            value2 = 0;
                            str1 = "";
                            str2 = "";
                            break;
                        }
                        operation = true;
                        break;
                    case '*':
                        System.out.println("Button = " + e.getActionCommand());
                        op = '*';
                        if(operation==true && value2 != 0 ){
                            jtfield.setText(Double.toString(result));
                            System.out.println("Result = " + result);
                            value1 = result;
                            value2 = 0;
                            str1 = "";
                            str2 = "";
                            break;
                        }
                        operation = true;
                        break;
                    case '/':
                        System.out.println("Button = " + e.getActionCommand());
                        op = '/';
                        if(operation==true && value2 != 0 ){
                            jtfield.setText(Double.toString(result));
                            System.out.println("Result = " + result);
                            value1 = result;
                            value2 = 0;
                            str1 = "";
                            str2 = "";
                            break;
                        }
                        operation = true;
                        break;
                    case '=':
                        System.out.println("value1 = " + value1);
                        System.out.println("value2 = " + value2);
                        operation = false;
                        if(op == '+'){
                            if(value2 == 0) {
                                value2 = value1;
                                result = value1 + value2;
                                value1 = result;
                            }
                            else {
                                result = value1 + value2;
                                value1 = result;
                            }
                            str1 = "";
                            str2 = "";
                            jtfield.setText(Double.toString(result));
                            System.out.println("Result = " + result);
                            break;
                        }
                        else if (op == '-'){
                            if(value2 == 0) {
                                value2 = value1;
                                result = value1 - value2;
                                value1 = result;
                            }
                            else {
                                result = value1 - value2;
                                value1 = result;
                            }
                            str1 = "";
                            str2 = "";
                            jtfield.setText(Double.toString(result));
                            System.out.println("Result = " + result);
                            break;
                        }
                        else if (op == '*'){
                            if(value2 == 0) {
                                value2 = value1;
                                result = value1 * value2;
                                value1 = result;
                            }
                            else {
                                result = value1 * value2;
                                value1 = result;
                            }
                            str1 = "";
                            str2 = "";
                            jtfield.setText(Double.toString(result));
                            System.out.println("Result = " + result);
                            break;
                        }
                        else if (op == '/'){
                            if(value2 == 0) {
                                value2 = value1;
                                result = value1 / value2;
                                value1 = result;
                            }
                            else {
                                result = value1 / value2;
                                value1 = result;
                            }
                            str1 = "";
                            str2 = "";
                            jtfield.setText(Double.toString(result));
                            System.out.println("Result = " + result);
                            break;
                        }
                        else { //first iteration when OPERATION
                            result = value1;
                            str1 = "";
                            str2 = "";
                            jtfield.setText(Double.toString(result));
                            System.out.println("Result = " + result);
                            break;
                        }
                    case 'C':
                        System.out.println("Button = " + e.getActionCommand());
                        jtfield.setText("0");
                        result = 0;
                        value1 = 0;
                        value2 = 0;
                        str1 = "";
                        str2 = "";
                        operation = false;
                        break;
                    default:
                        if (operation == false) {
                            op = ' ';
                            System.out.println("Button = " + e.getActionCommand());
                            value2 = 0;
                            str1 += e.getActionCommand();
                            value1 = Double.parseDouble(str1);
                            jtfield.setText(Double.toString(value1));
                        } else {
                            System.out.println("Button = " + e.getActionCommand());
                            str2 += e.getActionCommand();
                            value2 = Double.parseDouble(str2);
                            jtfield.setText(Double.toString(value2));
                            if(op == '+'){
                                result = value1 + value2;
                                break;
                            }
                            else if (op == '-'){
                                result = value1 - value2;
                                break;
                            }
                            else if (op == '*'){
                                result = value1 * value2;
                                break;
                            }
                            else{
                                result = value1 / value2;
                                break;
                            }
                        }
                }

            }
        };

        JFrame jf = new JFrame("Calculator");
        jframe = jf;
        jf.setLocationRelativeTo(null);
        jf.setPreferredSize(new Dimension(400,400));
        jf.setResizable(false);

        JTextField jtf = new JTextField("0");
        jtfield = jtf;
        jtf.setHorizontalAlignment(SwingConstants.RIGHT);
        jf.getContentPane().add(jtf,BorderLayout.NORTH);

        JPanel jp = new JPanel();
        jf.getContentPane().add(jp,BorderLayout.CENTER);

        GridLayout gl = new GridLayout(4,4);
        jp.setLayout(gl);

        JButton jb1 = new JButton("1");
        jp.add(jb1);
        jb1.addActionListener(myActionListener); // for events
        JButton jb2 = new JButton("2");
        jp.add(jb2);
        jb2.addActionListener(myActionListener); // for events
        JButton jb3 = new JButton("3");
        jp.add(jb3);
        jb3.addActionListener(myActionListener); // for events
        JButton jb4 = new JButton("+");
        jp.add(jb4);
        jb4.addActionListener(myActionListener); // for events
        JButton jb5 = new JButton("4");
        jp.add(jb5);
        jb5.addActionListener(myActionListener); // for events
        JButton jb6 = new JButton("5");
        jp.add(jb6);
        jb6.addActionListener(myActionListener); // for events
        JButton jb7 = new JButton("6");
        jp.add(jb7);
        jb7.addActionListener(myActionListener); // for events
        JButton jb8 = new JButton("-");
        jp.add(jb8);
        jb8.addActionListener(myActionListener); // for events
        JButton jb9 = new JButton("7");
        jp.add(jb9);
        jb9.addActionListener(myActionListener); // for events
        JButton jb10 = new JButton("8");
        jp.add(jb10);
        jb10.addActionListener(myActionListener); // for events
        JButton jb11 = new JButton("9");
        jp.add(jb11);
        jb11.addActionListener(myActionListener); // for events
        JButton jb12 = new JButton("*");
        jp.add(jb12);
        jb12.addActionListener(myActionListener); // for events
        JButton jb13 = new JButton("0");
        jp.add(jb13);
        jb13.addActionListener(myActionListener); // for events
        JButton jb14 = new JButton("=");
        jp.add(jb14);
        jb14.addActionListener(myActionListener); // for events
        JButton jb15 = new JButton("C");
        jp.add(jb15);
        jb15.addActionListener(myActionListener); // for events
        JButton jb16 = new JButton("/");
        jp.add(jb16);
        jb16.addActionListener(myActionListener); // for events

        jf.pack();
        jf.setVisible(true);
        jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // stop program if you close the window
    }


    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() { createAndShowGUI(); }
        });
    }

}
