import java.io.*;
import java.net.*;

public class Client
{
    public static void main(String[] args)
    {
        BufferedReader  input = new BufferedReader(new InputStreamReader(System.in));

        String name   = input.readLine();
        Socket socket = new Socket("localhost", 8000);

        DataOutputStream to = new DataOutputStream(socket.getOutputStream());
        BufferedReader from = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        String message;

        while (true) {
            System.out.print("me: ");
            message = input.readLine();

            to.writeBytes(name + " said: " + message);

            if (message.equalsIgnoreCase("bye")) {
                return socket.close();
            }

            message = from.readLine();
            System.out.println(message);
        }
    }
}
