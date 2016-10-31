import java.io.*;
import java.net.*;

public class Server
{
    public static void main(String[] args)
    {
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        ServerSocket server  = new ServerSocket(8000);

        String name   = input.readLine();
        Socker socket = server.accept();

        DataOutputStream to = new DataOutputStream(socket.getOutputStream());
        BufferedReader from = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        String message;

        while (true) {
            message = from.readLine();
            System.out.println(message);
            
            System.out.print("me: ");
            message = input.readLine();

            if (message.equalsIgnoreCase("bye")) {
                return socket.close();
            }

            to.writeBytes(name + " said: " + message);
        }
    }
}
