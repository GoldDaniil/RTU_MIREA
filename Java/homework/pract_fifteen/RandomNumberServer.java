import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.Map;
import java.util.Random;
import java.util.stream.Collectors;
import java.util.Arrays;
import java.net.URI;
import java.net.http.HttpRequest;

public class RandomNumberServer {
    public static void main(String[] args) throws Exception {
        int port = 11;//netstat - если что кил ласт

        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        server.createContext("/random", new RandomNumberHandler());

        server.start();
        System.out.println("сервак запущен на порту " + port);
    }

    static class RandomNumberHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String query = exchange.getRequestURI().getQuery();
            Map<String, String> params = parseQueryParams(query);
            String minParam = params.get("min");
            String maxParam = params.get("max");

            if (minParam == null || maxParam == null) {
                sendResponse(exchange, 400, "ошибка- min и max должны быть указаны - пример :{http://localhost:11/random?min=10&max=100}");
                return;
            }

            try {
                int min = Integer.parseInt(minParam);
                int max = Integer.parseInt(maxParam);

                if (min > max) {
                    sendResponse(exchange, 400, "ошибка- min не может быть больше max");
                    return;
                }

                Random random = new Random();
                int randomNumber = random.nextInt(max - min + 1) + min;

                sendResponse(exchange, 200, String.valueOf(randomNumber));//ответка клиенту
            } catch (NumberFormatException e) {
                sendResponse(exchange, 400, "ошибка - неверный формат чисел");
            }
        }

        private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
            exchange.sendResponseHeaders(statusCode, response.getBytes().length);
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        private Map<String, String> parseQueryParams(String query) {
            return Arrays.stream(query.split("&"))
                    .map(param -> param.split("="))
                    .collect(Collectors.toMap(e -> e[0], e -> e[1]));
        }
    }
}
//javac RandomNumberServer.java
//java RandomNumberServer

//gold@MacBook-Pro-Gold java6 % curl "http://localhost:11/random?min=10&max=100" 
46
//gold@MacBook-Pro-Gold java6 % curl "http://localhost:11/random?min=50&max=200"
154
